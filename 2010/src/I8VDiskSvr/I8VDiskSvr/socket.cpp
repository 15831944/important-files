#include "stdafx.h"
#include "socket.h"

#include "tool.h"
#include "../../../include/Utility/SmartPtr.hpp"
#include "Serialize.h"




namespace i8desk
{


	CSocket::CSocket(i8desk::IPlug* pPlug, i8desk::ILogger* pLogger, HANDLE hExited) 
		: m_pPlug(pPlug)
		, m_pLogger(pLogger)
		, m_Socket(INVALID_SOCKET)
		, m_hExited(hExited)
	{
		WSAData wsaData;
		WSAStartup(0x0202, &wsaData);
		char path[MAX_PATH] = {0};
		GetModuleFileNameA(NULL, path,MAX_PATH);
		PathRemoveFileSpecA(path);
		PathAddBackslashA(path);
		lstrcatA(path, CONFIG_FILE);

		char buf[MAX_PATH] = {0};
		GetPrivateProfileStringA("SYSTEM", "SvrIp", "",  buf, MAX_PATH, path);
		m_SvrIp = buf;
	}

	CSocket::~CSocket()
	{
		WSACleanup();
	}


	bool CSocket::CreateSocket()
	{
		DWORD dwError = 0;
		m_Socket = socket(AF_INET, SOCK_STREAM, 0);
		if (m_Socket == INVALID_SOCKET)
		{
			dwError = WSAGetLastError();
			_com_error error(dwError);
			m_pLogger->WriteLog(LM_INFO, TEXT("Create Socket Fail:%d:%s"), dwError, error.ErrorMessage());
			return false;
		}

		sockaddr_in server = {0};
		server.sin_family = AF_INET;
		server.sin_port = htons(SERVER_PORT);
		server.sin_addr.s_addr = inet_addr(m_SvrIp.c_str());
		if (SOCKET_ERROR == connect(m_Socket, (PSOCKADDR)&server, sizeof(server)))
		{
			dwError = WSAGetLastError();
			_com_error error(dwError);
			m_pLogger->WriteLog(LM_INFO, TEXT("Connect %s Fail:%d:%s"), m_SvrIp.c_str(),dwError, error.ErrorMessage());
			CloseSocket();
			return false;
		}
		//m_pLogger->WriteLog(LM_INFO, TEXT("Create Socket Success"));
		return true;
	}

	void CSocket::CloseSocket()
	{
		if (m_Socket != INVALID_SOCKET)
		{
			::shutdown(m_Socket, SD_BOTH);
			::closesocket(m_Socket);
			m_Socket = INVALID_SOCKET;
		}
		//m_pLogger->WriteLog(LM_INFO, TEXT("Close Socket"));
	}


	void CSocket::FreeVDisk(std::map<DWORD, tagVDInfoEx*>& VDList)
	{
		for (std::map<DWORD, tagVDInfoEx*>::iterator it = VDList.begin(); it != VDList.end(); it++)
		{
			tagVDInfoEx* pVDisk = it->second;
			if (pVDisk->handle != NULL)
			{
				m_pPlug->SendMessage(VDISK_CMD_STOP, (DWORD)pVDisk->handle, 0);				
				m_pLogger->WriteLog(LM_INFO, TEXT("Stop VDisk:%C"), (TCHAR)pVDisk->szSvrDrv);
			}
			delete pVDisk;
		}
		VDList.clear();
	}

	bool CSocket::GetVDiskList(std::map<DWORD, tagVDInfoEx*>& VDList)
	{
		using namespace i8desk;
		VDList.clear();

		char buf[4096] = {0};
		_packageheader* pheader = (_packageheader*)buf;
		InitPackage(pheader, CMD_GET_VDISK_CONFIG);

		char* pData = NULL;
		int length = 0;
		if (!_SendCmd(buf, pheader->Length, pData, length))
		{
			m_pLogger->WriteLog(LM_INFO, TEXT("Exec Get VDisk List cmd Error"));
			return false;
		}

		try
		{
			CAutoArrayPtr<char>::AutoPtr data(pData);
			CPackageHelper in(data);
			DWORD dwStatus = in.popDWORD();
			if (dwStatus == CMD_RET_FAIL)
			{
				char Error[8096] = {0};
				in.popString(Error);				
				m_pLogger->WriteLog(LM_INFO, TEXT("Recv VDisk List Error:%s"), (LPCTSTR)_bstr_t(Error));
				return false;
			}
			DWORD dwCount = in.popDWORD();
			//m_pLogger->WriteLog(LM_INFO, TEXT("Get VDisk List Count:%d"), dwCount);
			for (DWORD idx=0; idx<dwCount; idx++)
			{
				tagVDInfoEx* pVDisk = new tagVDInfoEx;
				ZeroMemory(pVDisk, sizeof(tagVDInfoEx));
				in.popString(pVDisk->ID);
				pVDisk->dwIp		= in.popDWORD();
				pVDisk->nPort		= (WORD)in.popDWORD();
				pVDisk->szSvrDrv	= (TCHAR)in.popDWORD();
				pVDisk->szCliDrv	= (TCHAR)in.popDWORD();
				pVDisk->Serial		= in.popDWORD();
				pVDisk->Type		= in.popDWORD();
				pVDisk->LoadType	= in.popDWORD();
				in.popString(pVDisk->SID);
				pVDisk->handle  = NULL;
				if (pVDisk->Type == VDISK_I8DESK)
					pVDisk->IsLocalMachine = _IsLocalMachineVDisk(pVDisk);
				else
					pVDisk->IsLocalMachine = FALSE;

				if (pVDisk->IsLocalMachine)
					VDList.insert(std::make_pair(pVDisk->szSvrDrv, pVDisk));
				else
					delete pVDisk;
			}
			//m_pLogger->WriteLog(LM_INFO, TEXT("End VDisk List."));
		}
		catch (...)
		{
			FreeVDisk(VDList);
			m_pLogger->WriteLog(LM_INFO, TEXT("GetVDiskList Unknown Error."));
			return false;
		}

		return true;
	}


	bool CSocket::ReportVDiskStatus(std::map<DWORD, tagVDInfoEx*>& VDisk)
	{
		CAutoArrayPtr<char>::AutoPtr pSendData(new char[64 * 1024]);
		_packageheader* pheader = (_packageheader*)pSendData.m_Handle;
		InitPackage(pheader, CMD_VDSVR_REPSTATUS);

		try
		{
			CPackageHelper out(pSendData);
			out.pushDWORD(VDisk.size());
			for (std::map<DWORD, tagVDInfoEx*>::iterator it = VDisk.begin();
				it != VDisk.end(); it++)
			{
				tagVDInfoEx* pVDisk = it->second;
				out.pushString(pVDisk->ID, lstrlenA(pVDisk->ID));

				tagVDInfo* pInfo = pVDisk;
				m_pPlug->SendMessage(VDISK_CMD_GETINFO, (DWORD)pVDisk->handle, (DWORD)pInfo);
				out.pushDWORD(pVDisk->dwVersion);
				out.pushDWORD(pVDisk->dwConnect);
			}
			//10����������һ���������
			{
				char szCmpName[MAX_PATH] = {0};
				DWORD dwNameLen = sizeof(szCmpName) - 1;
				GetComputerNameA(szCmpName, &dwNameLen);
				out.pushString(szCmpName, strlen(szCmpName));
			}
			pheader->Length = out.GetOffset();
			out.pushPackageHeader(*pheader);

			char* pData = NULL;
			int nSize = 0;
			if (!_SendCmd(pSendData, pheader->Length, pData, nSize))
			{
				m_pLogger->WriteLog(LM_INFO, TEXT("Exec Report VDisk Status cmd Error"));
				return false;
			}

			i8desk::CAutoArrayPtr<char>::AutoPtr data(pData);
			CPackageHelper in(pData);
			DWORD dwStatus = in.popDWORD();
			if (dwStatus == CMD_RET_FAIL)
			{
				char Error[8096] = {0};
				in.popString(Error);
				m_pLogger->WriteLog(LM_INFO, TEXT("Report VDisk Status Error:%s"), (LPCTSTR)_bstr_t(Error));
				return false;
			}
			//m_pLogger->WriteLog(LM_INFO, TEXT("Report VDisk Status Success."));
		}
		catch (...) 
		{ 
			assert(0);
			m_pLogger->WriteLog(LM_INFO, TEXT("Report VDisk Status Unknown Error."));
		}

		return true;
	}


	bool CSocket::ReportServerStatus(std::map<DWORD, tagVDInfoEx*>& VDisks, DWORD bInnerUpdate, IPlug* pPlug)
	{
		/*
		֡��		����		��������	˵��
		HostName	����������	String	����<64
		I8DeskSvr	������״̬	DWORD	0�����ֶ���Ч��
		1��������
		2��δ��װ
		3��δ����
		-1���쳣��
		��ͬ
		I8VDiskSvr	�����̷���״̬	DWORD	
		DNAService	�������ط���״̬	DWORD	
		I8MallCashier	�̳�������״̬	DWORD	
		LastBackupDBTime	�ϴα������ݿ�ʱ��	DWORD	Time32_t
		CPUUtilization	������	DWORD	%
		MemoryUsage	�ڴ�ʹ����	DWORD	KB
		�ڴ�ʣ��ֵ  DWORD   KB
		���緢���ٶ�DWORD   KB	�޸ĳ�����������
		��������ٶ�DWORD   KB	δ��

		DiskCount	������Ŀ	DWORD	
		��һ����������	Partition	DWORD	�̷�
		Type	DWORD	1��FAT32��2��NTFS
		0������
		Capacity	ULONGLONG	Byte
		UsedSize	ULONGLONG	Byte
		FreeSize	ULONGLONG	Byte
		speed		DWORD		kb/s.
		��			
		*/
		using namespace i8desk;
		CAutoArrayPtr<char>::AutoPtr pSendData(new char[64*1024]);
		_packageheader* pheader = (_packageheader*)pSendData.m_Handle;
		InitPackage(pheader, CMD_SVRRPT_SERVERINFO_EX);

		try
		{
			CPackageHelper out(pSendData);
			char szBuf[MAX_PATH] = {0};
			DWORD nBufSize = sizeof(szBuf) - 1;
			GetComputerNameA(szBuf, &nBufSize);

			out.pushString(szBuf, nBufSize);		//�������
			out.pushDWORD(0);						//������ (0��Ч)
			out.pushDWORD(1);						//�����̷���״̬ (1����)
			out.pushDWORD(bInnerUpdate);			//��������״̬
			out.pushDWORD(0);						//DNAService (0��Ч)
			out.pushDWORD(0);						//�̳������� (0��Ч)
			out.pushDWORD(0);						//���ݿ��ϱ��ݵ�ʱ��
			out.pushDWORD(i8desk_GetCpuUsage());	//cpu������
			DWORD dwLeft = 0;
			out.pushDWORD(i8desk_GetMemoryUsage(dwLeft));	//memory������
			out.pushDWORD(dwLeft);							//�ڴ�ʣ��ֵ

			out.pushDWORD(0/*i8desk_GetNetCardUsage()*/);//���緢���ٶ� -->�ı������������.2010����汾
			out.pushDWORD(0);						//��������ٶ� -->δ��(0)

			std::string str = GetServerDeviceInfo();
			out.pushString(str.c_str(), str.size());//�豸��Ϣ

			std::set<char> setDrivers;
			{
				//��������̵��̷�
				for (std::map<DWORD, tagVDInfoEx*>::iterator it = VDisks.begin();
					it != VDisks.end(); it++)
				{
					setDrivers.insert((char)::toupper(it->first));
				}

				//���ͬ�������ԴĿ¼�̷�
				try
				{
					if (pPlug != NULL)
					{
						char buf[30] = {0};
						DWORD dwSize = 0;
						//cmd = 1.��ʾȡͬ��������̷����wparam:��ʾ�洢�̷��Ļ�������lparam:��ʾ�洢����д��������̷������ĵ�ַ��
						pPlug->SendMessage(1, (DWORD)(&buf), (DWORD)(&dwSize));
						for (DWORD idx=0; idx< dwSize; idx++)
						{
							setDrivers.insert(::toupper(buf[idx]));
						}
					}
				}
				catch (...) 
				{
					assert(0);
				}
			}

			out.pushDWORD(setDrivers.size());
			for (std::set<char>::const_iterator it = setDrivers.begin();
				it != setDrivers.end(); it++)
			{
				DWORD dwType = 0, dwSize = 0, dwUsed = 0, dwFree = 0;
				char chDrv = (char)(*it);
				i8desk_GetDriverInfo(chDrv, dwType, dwSize, dwUsed, dwFree);
				out.pushDWORD(chDrv);
				out.pushDWORD(dwType);
				out.pushDWORD(dwSize);
				out.pushDWORD(dwUsed);
				out.pushDWORD(dwFree);
				out.pushDWORD(0);
			}
			pheader->Length = out.GetOffset();
			out.pushPackageHeader(*pheader);

			char* pData = NULL;
			int nSize = 0;
			if (!_SendCmd(pSendData, pheader->Length, pData, nSize))
			{
				m_pLogger->WriteLog(LM_INFO, TEXT("Exec Report Server Status cmd Error"));
				return false;
			}

			i8desk::CAutoArrayPtr<char>::AutoPtr data(pData);
			CPackageHelper in(data);
			DWORD dwStatus = in.popDWORD();
			if (dwStatus == CMD_RET_FAIL)
			{
				char Error[8096] = {0};
				in.popString(Error);
				m_pLogger->WriteLog(LM_INFO, TEXT("Report Server Status Error:%s"), (LPCTSTR)_bstr_t(Error));
				return false;
			}
		}
		catch (...) 
		{ 
			m_pLogger->WriteLog(LM_INFO, TEXT("Report Server Status Unknown Error."));
		}

		return true;
	}

	void CSocket::ProcessVDisk(std::map<DWORD, tagVDInfoEx*>& VDList, std::map<DWORD, tagVDInfoEx*>& newVDList)
	{
		std::map<DWORD, tagVDInfoEx*>::iterator it = VDList.begin();

		std::string str;
		for (; it != VDList.end(); it++)
		{
			//��������µ��������б�ʱ��ֹͣ
			if (newVDList.find(it->first) == newVDList.end() && it->second->handle != NULL)
			{
				m_pPlug->SendMessage(VDISK_CMD_STOP, (DWORD)it->second->handle, 0);
				//StopServer(it->second->handle);
				m_pLogger->WriteLog(LM_INFO, TEXT("Stop VDisk: [%C] %s"), (TCHAR)it->first, 
					it->second->handle != NULL ? TEXT("Success") : TEXT("Fail"));
				it->second->handle = NULL;
				str += (char)it->first;
			}
		}
		for (size_t idx=0; idx<str.size(); idx++)
		{
			it = VDList.find((DWORD)str[idx]);
			if (it != VDList.end())
			{
				delete it->second;
				VDList.erase(it);
			}
		}

		it = newVDList.begin();
		for (; it != newVDList.end(); it ++)
		{
			//������ڼ����������������б������������̲�����
			if (VDList.find(it->first) == VDList.end() && 
				it->second->Type == 0 &&	//���һ���Ҫ��i8desk���͵�������
				it->second->IsLocalMachine  //���һ���Ҫ�Ǳ�����������
				)
			{
				tagVDInfoEx* pVDisk = new tagVDInfoEx;
				*pVDisk = *it->second;
				tagVDInfo* pInfo = pVDisk;
				pVDisk->handle = (HANDLE)m_pPlug->SendMessage(VDISK_CMD_START, (DWORD)pInfo, 0);
				m_pLogger->WriteLog(LM_INFO, TEXT("Start VDisk: [%C] %s"), (TCHAR)pVDisk->szSvrDrv, 
					(pVDisk->handle != NULL) ? TEXT("Success") : TEXT("Fail"));

				if (pVDisk->handle != NULL)
					VDList.insert(std::make_pair(pVDisk->szSvrDrv, pVDisk));
				else
					delete pVDisk;
			}
		}
	}


	std::tr1::tuple<DWORD, DWORD> CSocket::GetFileInfo(const i8desk::std_string &file)
	{
		CAutoArrayPtr<char>::AutoPtr pSendData(new char[64 * 1024]);
		_packageheader* pheader = (_packageheader*)pSendData.m_Handle;
		InitPackage(pheader, CMD_VDSVR_GETUPDATE_FILEINFO);


		CPackageHelper out(pSendData);
		out.pushDWORD(file.length());
		out << file.c_str();

		pheader->Length = out.GetOffset();
		out.pushPackageHeader(*pheader);

		char *outData = NULL;
		int outLen = 0;
		if( !_SendCmd(pSendData, pheader->Length, outData, outLen) )
		{
			std_string error = "��ȡ�ļ�: " + file + " ��Ϣ����!";
			throw std::logic_error(error);
		}

		i8desk::CAutoArrayPtr<char>::AutoPtr data(outData);
		CPackageHelper in(data);
		DWORD dwStatus = in.popDWORD();
		if( dwStatus == 0 )
		{
			std_string error = "��ȡ�ļ�: " + file + " ��Ϣ����!";
			throw std::runtime_error(error);
		}

		DWORD dwSize = in.popDWORD();	// File Size
		DWORD dwCRC = in.popDWORD();	// File Data CRC

		return std::tr1::make_tuple(dwSize, dwCRC);
	}

	void CSocket::GetFileData(const i8desk::std_string &file, char *&fileDataBuf, DWORD &recvSize)
	{
		// ���Ȼ�ȡ�ļ�����
		DWORD dwFileSize = 0;

		{
			CAutoArrayPtr<char>::AutoPtr pSendData(new char[4 * 1024]);
			_packageheader* pheader = (_packageheader*)pSendData.m_Handle;
			InitPackage(pheader, CMD_CLIUPT_DOWNFILE_START);

			CPackageHelper out(pSendData);
			out << 1 << fprelPath << file.c_str();

			pheader->Length = out.GetOffset();
			out.pushPackageHeader(*pheader);

			char *outData = NULL;
			int outLen = 0;
			if( !_SendCmd(pSendData, pheader->Length, outData, outLen) )
			{
				i8desk::std_string error = "��ȡ�ļ�" + file + "���ȳ���!";
				throw std::logic_error(error.c_str());
			}

			i8desk::CAutoArrayPtr<char>::AutoPtr data(outData);
			CPackageHelper in(data);
			DWORD dwStatus = in.popDWORD();
			if( dwStatus == 0 )
			{
				std_string error = "��ȡ�ļ�: " + file + " ���ݳ���!";
				throw std::runtime_error(error);
			}

			dwFileSize = in.popDWORD();	// File Size
		}

		// ѭ����ȡ�ļ�����
		CAutoArrayPtr<char>::AutoPtr pSendData(new char[4 * 1024]);
		CAutoArrayPtr<char>::AutoPtr pRecvDataBuf(new char[dwFileSize]);

		DWORD recvFileSize = 0;
		while(recvFileSize < dwFileSize)
		{
			_packageheader* pheader = (_packageheader*)pSendData.m_Handle;
			InitPackage(pheader, CMD_DOWNFILE_NEXT);

			CPackageHelper out(pSendData);

			pheader->Length = out.GetOffset();
			out.pushPackageHeader(*pheader);
			
			char *outData = NULL;
			int outLen = 0;
			if( !_SendCmd(pSendData, out.GetLength(), outData, outLen) )
				throw std::logic_error("��ȡ�ļ����ݳ���!");
			
			i8desk::CAutoArrayPtr<char>::AutoPtr data(outData);
			CPackageHelper in(data);
			DWORD dwStatus = in.popDWORD();
			DWORD dwLastFlag = in.popDWORD();
			DWORD curSize = in.popData(reinterpret_cast<BYTE *>(pRecvDataBuf.m_Handle) + recvFileSize, in.GetLength());

			recvFileSize += curSize;

			// ���һ����
			if( dwLastFlag == 1 )
				break;

			// ���������ʱ
			::Sleep(10);
		}

		if( recvFileSize != dwFileSize )
			throw std::logic_error(file + "���յ��ļ����ݴ�С����");

		fileDataBuf = pRecvDataBuf.Detach();
		recvSize = dwFileSize;
	}

	bool CSocket::_SendCmd(char* pOutData, int outlength, char*& pInData, int& inlength)
	{
		if (pOutData == NULL || outlength == 0)
		{
			m_pLogger->WriteLog(LM_INFO, TEXT("parameter error or func call erorr."));
			return false;
		}
		pInData = NULL;	inlength = 0;

		//send data.
		int left = outlength;
		DWORD dwError = 0;
		while (left)
		{
			int len = send(m_Socket, &pOutData[outlength-left], left, 0);
			if (len <= 0)
			{
				dwError = WSAGetLastError();
				_com_error error(dwError);
				m_pLogger->WriteLog(LM_INFO, TEXT("Send Data Fail:%d:%s"), dwError, error.ErrorMessage());
				CloseSocket();
				return false;
			}
			left -= len;
		}

		//recv data.
		DWORD dwSize = 1024 * 16;
		char* pData = new char[dwSize];
		DWORD dwRecvLen = 0;
		int nTimes = 0;	//��ʱ�ؽ��մ���.һ��ֻʹ��1��.����м��ξ��Ǽ����ʱ�ų�ʱ
		while (1)
		{
			FD_SET fdset;
			timeval tv = {1, 0};
			FD_ZERO(&fdset);
			FD_SET(m_Socket, &fdset);
			int ret = select(0, &fdset, NULL, NULL, &tv);
			if (ret == 0)
			{
				//timeout.
				if (nTimes < 10)
				{
					nTimes ++;
					if (WaitForSingleObject(m_hExited, 0) == WAIT_OBJECT_0)
					{
						m_pLogger->WriteLog(LM_INFO, TEXT("Service Should Exit."));
						delete []pData;
						return false;
					}
					continue;
				}
				m_pLogger->WriteLog(LM_INFO, TEXT("Recv Ack Data Timeouts."));
				CloseSocket();
				delete []pData;
				return false;
			}
			else if (ret < 0)
			{
				dwError = WSAGetLastError();
				_com_error error(dwError);
				m_pLogger->WriteLog(LM_INFO, TEXT("Select Fail:%d:%s"), dwError, error.ErrorMessage());
				delete []pData;
				CloseSocket();
				return false;
			}

			if (FD_ISSET(m_Socket, &fdset))
			{
				int len = recv(m_Socket, &pData[dwRecvLen], dwSize - dwRecvLen, 0);
				if (len <= 0)
				{
					dwError = WSAGetLastError();
					_com_error error(dwError);
					m_pLogger->WriteLog(LM_INFO, TEXT("Recv Data Fail:%d:%s"), dwError, error.ErrorMessage());
					delete []pData;
					CloseSocket();
					return false;
				}

				dwRecvLen += len;
				if (dwRecvLen >= sizeof(i8desk::_packageheader))
				{
					//���˴������ݰ���
					{
						WORD dwStartFlag = *(WORD*)pData;
						if (dwStartFlag != START_FLAG)
						{
							m_pLogger->WriteLog(LM_INFO, "Recv Data Flag Error.");
							delete[]pData;
							CloseSocket();
							return false;
						}
					}
					DWORD dwTotal = ((i8desk::_packageheader*)pData)->Length;
					if (dwSize < dwTotal)
					{
						dwSize = dwTotal+16;
						char* pTemp = new char[dwSize];
						memcpy(pTemp, pData, dwRecvLen);
						delete []pData;
						pData = pTemp;
					}
					if (dwRecvLen >= dwTotal)
						break;
				}
			}
		}
		pInData = pData;
		inlength = dwRecvLen;
		return true;
	}

	//bool CSocket::_SendData(char* pOutData, int outlength)
	//{
	//	//send data.
	//	int left = outlength;
	//	DWORD dwError = 0;
	//	while (left)
	//	{
	//		int len = send(m_Socket, &pOutData[outlength-left], left, 0);
	//		if (len <= 0)
	//		{
	//			dwError = WSAGetLastError();
	//			_com_error error(dwError);
	//			m_pLogger->WriteLog(LM_INFO, TEXT("Send Data Fail:%d:%s"), dwError, error.ErrorMessage());
	//			CloseSocket();
	//			return false;
	//		}
	//		left -= len;
	//	}

	//	return true;
	//}

	//bool CSocket::_RecvData(char *&inData, int &inLen)
	//{
	//	// recv data.
	//	const static DWORD dwSize = 1024 * 64 + 10 * 1024;
	//	i8desk::CAutoArrayPtr<char>::AutoPtr pData(new char[dwSize]);
	//	DWORD dwError = 0;
	//	DWORD dwRecvLen = 0;
	//	int nTimes = 0;	//��ʱ�ؽ��մ���.һ��ֻʹ��1��.����м��ξ��Ǽ����ʱ�ų�ʱ

	//	while (1)
	//	{
	//		FD_SET fdset;
	//		timeval tv = {5, 0};
	//		FD_ZERO(&fdset);
	//		FD_SET(m_Socket, &fdset);
	//		int ret = select(0, &fdset, NULL, NULL, &tv);
	//		if (ret == 0)
	//		{
	//			//timeout.
	//			if (nTimes < 10)
	//			{
	//				nTimes ++;
	//				if (WaitForSingleObject(m_hExited, 0) == WAIT_OBJECT_0)
	//				{
	//					m_pLogger->WriteLog(LM_INFO, TEXT("Service Should Exit."));
	//					return false;
	//				}
	//				continue;
	//			}
	//			m_pLogger->WriteLog(LM_INFO, TEXT("Recv Ack Data Timeouts."));
	//			CloseSocket();
	//			return false;
	//		}
	//		else if (ret < 0)
	//		{
	//			dwError = WSAGetLastError();
	//			_com_error error(dwError);
	//			m_pLogger->WriteLog(LM_INFO, TEXT("Select Fail:%d:%s"), dwError, error.ErrorMessage());
	//			CloseSocket();
	//			return false;
	//		}

	//		if (FD_ISSET(m_Socket, &fdset))
	//		{
	//			int len = recv(m_Socket, &pData[dwRecvLen], dwSize - dwRecvLen, 0);
	//			if (len <= 0)
	//			{
	//				dwError = WSAGetLastError();
	//				_com_error error(dwError);
	//				m_pLogger->WriteLog(LM_INFO, TEXT("Recv Data Fail:%d:%s"), dwError, error.ErrorMessage());
	//				CloseSocket();
	//				return false;
	//			}

	//			dwRecvLen += len;
	//			if (dwRecvLen >= sizeof(i8desk::_packageheader))
	//			{
	//				//���˴������ݰ���
	//				{
	//					WORD dwStartFlag = *(WORD*)pData;
	//					if (dwStartFlag != START_FLAG)
	//					{
	//						m_pLogger->WriteLog(LM_INFO, "Recv Data Flag Error.");
	//						CloseSocket();
	//						return false;
	//					}
	//				}
	//				DWORD dwTotal = ((i8desk::_packageheader*)pData)->Length;
	//				if (dwSize < dwTotal)
	//				{
	//					dwSize = dwTotal + 16;
	//					char* pTemp = new char[dwSize];
	//					memcpy(pTemp, pData, dwRecvLen);

	//					pData->CleanUp();
	//					pData = pTemp;
	//				}
	//				if (dwRecvLen >= dwTotal)
	//					break;
	//			}
	//		}
	//	}

	//	inData = pData->Detach();
	//	inLen = dwRecvLen;
	//}

	BOOL CSocket::_IsLocalMachineVDisk(tagVDInfoEx* pVDisk)
	{
		if (_strcmpi(pVDisk->SID, MAIN_SERVER_SID) == 0)
			return TRUE;

		IP_ADAPTER_INFO info[16] = {0};
		DWORD dwSize = sizeof(info);
		if (ERROR_SUCCESS != GetAdaptersInfo(info, &dwSize))
		{
			DWORD dwError = GetLastError();
			_com_error Error(dwError);
			m_pLogger->WriteLog(LM_INFO, TEXT("GetAdaptersInfo Error:%d:%s"), dwError, Error.ErrorMessage());
			return FALSE;
		}

		PIP_ADAPTER_INFO pAdapter = info;
		while (pAdapter != NULL)
		{
			PIP_ADDR_STRING pAddr = &pAdapter->IpAddressList;
			while (pAddr != NULL)
			{
				DWORD dwIp = inet_addr(pAddr->IpAddress.String);
				if (dwIp == pVDisk->dwIp)
					return TRUE;
				pAddr = pAddr->Next;
			}
			pAdapter = pAdapter->Next;
		}
		return FALSE;
	}

}