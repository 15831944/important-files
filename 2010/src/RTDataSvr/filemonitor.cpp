#include "StdAfx.h"
#include "filemonitor.h"
#include "../../include/i8logmsg.h"
#include "../../include/Utility/utility.h"
#include "globalfun.h"
#include "filecache.h"

#define UPDATE_IDX_INTERVAL (1000 * 60 * 3)

namespace i8desk {

ZClientSoftMonitor::ZClientSoftMonitor(ZFileCacheMgr *pFileCacheMgr)
	: m_pFileCacheMgr(pFileCacheMgr)
	, m_dwVersion(::_time32(0))
{
}

ZClientSoftMonitor::~ZClientSoftMonitor(void)
{
}

ulong ZClientSoftMonitor::GetVersion(void)
{
	I8_GUARD(ZGuard, ZSync, m_lock);
	return m_dwVersion;
}

void ZClientSoftMonitor::UpdateVersion(DWORD dwVersion)
{
	I8_GUARD(ZGuard, ZSync, m_lock);
	m_pFileCacheMgr->ReloadAll();
	m_dwVersion = dwVersion;
	I8_DEBUG3((LM_DEBUG, I8_TEXT("UpdateVersion:%u\n"), m_dwVersion));
}


int ZClientSoftMonitor::Init(void)
{
	MakeIdx();
	return 0;
}


void ZClientSoftMonitor::Fini(void)
{
}


unsigned int ZClientSoftMonitor::Exec(void)
{
	BOOL bReloadCacheFile;
	while (!IsDone()) {
		WaitEvent(UPDATE_IDX_INTERVAL);
		if (IsDone()) {
			break;
		}

		MakeIdx(&bReloadCacheFile);
		if (!bReloadCacheFile)
			m_pFileCacheMgr->ReloadAll();
	}

	return 0;
}

BOOL ZClientSoftMonitor::MakeIdx(BOOL *pbReloadCacheFile)
{
	I8_GUARD(ZGuard, ZSync, m_MakeLock);

	if (pbReloadCacheFile)
		*pbReloadCacheFile = FALSE;

	std_string strPath = GetAppPath() + _T("BarOnlineUpdate");
	std_string strIdxFile = GetAppPath() + _T("tmp\\Client.idx");
	DWORD dwOldCrc32 = 0, dwOldVersion = 0, dwNewVersion = 0;

	if(!PathFileExists(strPath.c_str()))
	{
		I8_ERROR_RETURN((LM_DEBUG, 
			I8_TEXT("���¿ͻ����������ʱ��Ŀ¼[%s]������,������룬%u\n"), 
			strPath.c_str(), GetLastError()), FALSE);
	}

	std::vector<std_string> vFileList;
	std::vector<ULONGLONG> vSizeList;
	if (!GetFileTreeList(strPath.c_str(),vFileList,vSizeList))
	{
		I8_ERROR_RETURN((LM_DEBUG, 
			I8_TEXT("���¿ͻ����������ʱ����ȡĿ¼[%s]���ļ��б�ʧ��,������룬%u\n"), 
			strPath.c_str(), GetLastError()), FALSE);
	}

	DWORD dwCount=vFileList.size();
	if (dwCount == 0) 
	{
		I8_ERROR_RETURN((LM_DEBUG, 
			I8_TEXT("���¿ͻ����������ʱ����ȡĿ¼[%s]���ļ��б�Ϊ��\n"), 
			strPath.c_str()), FALSE);
	}

	HANDLE hIdx=CreateFile(strIdxFile.c_str(),               
		GENERIC_ALL,          
		FILE_SHARE_READ,                      
		NULL,                   
		CREATE_ALWAYS,          
		FILE_ATTRIBUTE_NORMAL,  
		NULL);
	if(hIdx==INVALID_HANDLE_VALUE)
	{
		I8_ERROR_RETURN((LM_ERROR, 
			I8_TEXT("�����ļ�[%s]ʧ��,������룬%u\n"), 
			strIdxFile.c_str(), GetLastError()), FALSE);
	}

	//�ȶ�Crc��Verд0
	if (!WriteFileContent(hIdx,(BYTE*)&dwOldCrc32,sizeof(DWORD)))
	{
		CloseHandle(hIdx);
		I8_ERROR_RETURN((LM_ERROR, 
			I8_TEXT("д�ļ�[%s]ʧ��,������룬%u\n"), 
			strIdxFile.c_str(), GetLastError()), FALSE);
	}

	if (!WriteFileContent(hIdx,(BYTE*)&dwOldVersion,sizeof(DWORD)))
	{
		CloseHandle(hIdx);
		I8_ERROR_RETURN((LM_ERROR, 
			I8_TEXT("д�ļ�[%s]ʧ��,������룬%u\n"), 
			strIdxFile.c_str(), GetLastError()), FALSE);
	}

	if (!WriteFileContent(hIdx,(BYTE*)&dwCount,sizeof(DWORD)))
	{
		CloseHandle(hIdx);
		I8_ERROR_RETURN((LM_ERROR, 
			I8_TEXT("д�ļ�[%s]ʧ��,������룬%u\n"), 
			strIdxFile.c_str(), GetLastError()), FALSE);
	}

	BOOL bIdxExist=FALSE;
	DWORD dwExceptCount=0;
	for (DWORD i=0;i<dwCount;i++)
	{
		std_string strFullPathFileName=vFileList[i];
		//1.�õ��ļ���
		std::string::size_type b = strFullPathFileName.find_last_of('\\');
		std_string strFileName = strFullPathFileName.substr(b+1);
		if ((GetFileAttributes(strFullPathFileName.c_str()) & FILE_ATTRIBUTE_SYSTEM) == 0
			&& stricmp(strFileName, _T("UPDATE.IDX"))) // && stricmp(strFileName, _T("THUMBS.DB")))
		{
			strFileName=vFileList[i];
			strFileName=strFileName.substr(strPath.size()+1);
			char FileName[MAX_PATH];
			memset(FileName,0,sizeof(FileName));
			strcpy(FileName,"%root%\\");
			strcat(FileName,strFileName.c_str());

			DWORD dwCrc32=0;
			if (!GetFileCrc32(vFileList[i].c_str(), dwCrc32))
			{
				CloseHandle(hIdx);
				I8_ERROR_RETURN((LM_ERROR, 
					I8_TEXT("��ȡ�ļ�[%s]CRCʧ��,������룬%u\n"), 
					vFileList[i].c_str(), GetLastError()), FALSE);
			}

			if (!WriteFileContent(hIdx,(BYTE*)&dwCrc32,sizeof(DWORD)))
			{
				CloseHandle(hIdx);
				I8_ERROR_RETURN((LM_ERROR, 
					I8_TEXT("д�ļ�[%s]ʧ��,������룬%u\n"), 
					strIdxFile.c_str(), GetLastError()), FALSE);
			}

			if (!WriteFileContent(hIdx,(BYTE*)FileName,sizeof(FileName)))
			{
				CloseHandle(hIdx);
				I8_ERROR_RETURN((LM_ERROR, 
					I8_TEXT("д�ļ�[%s]ʧ��,������룬%u\n"), 
					strIdxFile.c_str(), GetLastError()), FALSE);
			}
		}
		else
		{
			bIdxExist=TRUE;
			dwExceptCount++;
		}
	}

	if (bIdxExist)
	{
		if (SetFilePointer(hIdx,8,NULL,FILE_BEGIN)==INVALID_SET_FILE_POINTER)
		{
			CloseHandle(hIdx);
			I8_ERROR_RETURN((LM_ERROR, 
				I8_TEXT("��λ�ļ�[%s]ʧ��,������룬%u\n"), 
				strIdxFile.c_str(), GetLastError()), FALSE);
		}

		dwCount-=dwExceptCount;

		if (!WriteFileContent(hIdx,(BYTE*)&dwCount,sizeof(DWORD)))
		{
			CloseHandle(hIdx);
			I8_ERROR_RETURN((LM_ERROR, 
				I8_TEXT("д�ļ�[%s]ʧ��,������룬%u\n"), 
				strIdxFile.c_str(), GetLastError()), FALSE);
		}
	}

	//������idx�ļ���ǰ2��DWORD

	BOOL bReadOldIdxOk=GetOldIdxInfo(dwOldCrc32,dwOldVersion);
	if (bReadOldIdxOk)
	{
		//�Ȱ�Version��д�ɾ��ļ��İ汾,���ڼ���CRC
		if (SetFilePointer(hIdx,4,NULL,FILE_BEGIN)==INVALID_SET_FILE_POINTER)
		{
			CloseHandle(hIdx);
			I8_ERROR_RETURN((LM_ERROR, 
				I8_TEXT("��λ�ļ�[%s]ʧ��,������룬%u\n"), 
				strIdxFile.c_str(), GetLastError()), FALSE);
		}

		if (!WriteFileContent(hIdx,(BYTE*)&dwOldVersion,sizeof(DWORD)))
		{
			CloseHandle(hIdx);
			I8_ERROR_RETURN((LM_ERROR, 
				I8_TEXT("д�ļ�[%s]ʧ��,������룬%u\n"), 
				strIdxFile.c_str(), GetLastError()), FALSE);
		}

		//�õ���idx����ʱcrc32
		DWORD dwTmpCrc32=0;
		if (!GetFileCrc32(hIdx,dwTmpCrc32))
		{
			CloseHandle(hIdx);
			I8_ERROR_RETURN((LM_ERROR, 
				I8_TEXT("���ɿͻ����������ʱ���õ���idx����ʱcrc32ʧ��\n")),
				FALSE);
		}

		dwNewVersion = _time32(NULL);

		if (SetFilePointer(hIdx,4,NULL,FILE_BEGIN)==INVALID_SET_FILE_POINTER)
		{
			CloseHandle(hIdx);
			I8_ERROR_RETURN((LM_ERROR, 
				I8_TEXT("��λ�ļ�[%s]ʧ��,������룬%u\n"), 
				strIdxFile.c_str(), GetLastError()), FALSE);
		}

		if (!WriteFileContent(hIdx,(BYTE*)&dwNewVersion,sizeof(DWORD)))
		{
			CloseHandle(hIdx);
			I8_ERROR_RETURN((LM_ERROR, 
				I8_TEXT("д�ļ�[%s]ʧ��,������룬%u\n"), 
				strIdxFile.c_str(), GetLastError()), FALSE);
		}

		DWORD dwCrc32=0;
		if (!GetFileCrc32(hIdx,dwCrc32))
		{
			CloseHandle(hIdx);
			I8_ERROR_RETURN((LM_ERROR, 
				I8_TEXT("���ɿͻ����������ʱ���õ���idx����ʱcrc32ʧ��\n")),
				FALSE);
		}

		if (SetFilePointer(hIdx,0,NULL,FILE_BEGIN)==INVALID_SET_FILE_POINTER)
		{
			CloseHandle(hIdx);
			I8_ERROR_RETURN((LM_ERROR, 
				I8_TEXT("��λ�ļ�[%s]ʧ��,������룬%u\n"), 
				strIdxFile.c_str(), GetLastError()), FALSE);
		}

		if (!WriteFileContent(hIdx,(BYTE*)&dwCrc32,sizeof(DWORD)))
		{
			CloseHandle(hIdx);
			I8_ERROR_RETURN((LM_ERROR, 
				I8_TEXT("д�ļ�[%s]ʧ��,������룬%u\n"), 
				strIdxFile.c_str(), GetLastError()), FALSE);
		}

		CloseHandle(hIdx);

		//�ļ����ݱ���
		if (dwOldCrc32!=dwTmpCrc32)
		{
			//���µ������ļ�Copy��ȥ
			std_string strOldIdxFile=GetAppPath()+_T("BarOnlineUpdate\\Update.idx");
			while (TRUE)
			{
				if (PathFileExists(strOldIdxFile.c_str()))
				{
					SetFileAttributes(strOldIdxFile.c_str(),FILE_ATTRIBUTE_NORMAL);
					DeleteFile(strOldIdxFile.c_str());
				}

				if (PathFileExists(strOldIdxFile.c_str()))
				{
					I8_DEBUG((LM_DEBUG, I8_TEXT("ɾ���ļ�%sʧ��,1�������\n"),strOldIdxFile.c_str()));
					Sleep(1000);
					continue;
				}
				else
				{
					I8_DEBUG3((LM_DEBUG, I8_TEXT("ɾ���ļ�%s�ɹ�\n"), strOldIdxFile.c_str()));
					break;
				}
			}

			int iCount=0;
			while (TRUE)
			{
				iCount++;
				BOOL bRet=CopyFile(strIdxFile.c_str(),strOldIdxFile.c_str(),FALSE);
				if (!bRet)
				{
					if (iCount>10)
					{
						I8_ERROR((LM_ERROR, 
							I8_TEXT("�����ļ�%s����ʧ�ܳ���10��,�������%u\n"),
							strOldIdxFile.c_str(),GetLastError()));
						return FALSE;
					}

					I8_DEBUG((LM_DEBUG, 
						I8_TEXT("�����ļ�%sʧ��,�������%u,1�������\n"),
						strOldIdxFile.c_str(),GetLastError()));
					Sleep(1000);
					continue;
				}
				else
				{
					I8_DEBUG3((LM_DEBUG, I8_TEXT("�����ļ�%s�ɹ�\n"),strOldIdxFile.c_str()));
					break;
				}
			}

			//���°汾��
			UpdateVersion(dwNewVersion);
			if (pbReloadCacheFile)
				*pbReloadCacheFile = TRUE;
		}
	}
	else
	{

		dwNewVersion = _time32(NULL);

		if (SetFilePointer(hIdx,4,NULL,FILE_BEGIN)==INVALID_SET_FILE_POINTER)
		{
			CloseHandle(hIdx);
			I8_ERROR_RETURN((LM_ERROR, 
				I8_TEXT("��λ�ļ�[%s]ʧ��,������룬%u\n"), 
				strIdxFile.c_str(), GetLastError()), FALSE);
		}

		if (!WriteFileContent(hIdx,(BYTE*)&dwNewVersion,sizeof(DWORD)))
		{
			CloseHandle(hIdx);
			I8_ERROR_RETURN((LM_ERROR, 
				I8_TEXT("д�ļ�[%s]ʧ��,������룬%u\n"), 
				strIdxFile.c_str(), GetLastError()), FALSE);
		}

		DWORD dwCrc32=0;
		if (!GetFileCrc32(hIdx,dwCrc32))
		{
			CloseHandle(hIdx);
			I8_ERROR_RETURN((LM_ERROR, 
				I8_TEXT("���ɿͻ����������ʱ���õ���idx����ʱcrc32ʧ��\n")),
				FALSE);
		}

		if (SetFilePointer(hIdx,0,NULL,FILE_BEGIN)==INVALID_SET_FILE_POINTER)
		{
			CloseHandle(hIdx);
			I8_ERROR_RETURN((LM_ERROR, 
				I8_TEXT("��λ�ļ�[%s]ʧ��,������룬%u\n"), 
				strIdxFile.c_str(), GetLastError()), FALSE);
		}

		if (!WriteFileContent(hIdx,(BYTE*)&dwCrc32,sizeof(DWORD)))
		{
			CloseHandle(hIdx);
			I8_ERROR_RETURN((LM_ERROR, 
				I8_TEXT("д�ļ�[%s]ʧ��,������룬%u\n"), 
				strIdxFile.c_str(), GetLastError()), FALSE);
		}

		CloseHandle(hIdx);

		//���µ������ļ�Copy��ȥ
		std_string strOldIdxFile=GetAppPath()+_T("BarOnlineUpdate\\Update.idx");
		while (TRUE)
		{
			if (PathFileExists(strOldIdxFile.c_str()))
			{
				SetFileAttributes(strOldIdxFile.c_str(),FILE_ATTRIBUTE_NORMAL);
				DeleteFile(strOldIdxFile.c_str());
			}

			if (PathFileExists(strOldIdxFile.c_str()))
			{
				I8_DEBUG((LM_DEBUG, I8_TEXT("ɾ���ļ�%sʧ��,1�������\n"), strOldIdxFile.c_str()));
				Sleep(1000);
				continue;
			}
			else
			{
				I8_DEBUG3((LM_DEBUG, I8_TEXT("ɾ���ļ�%s�ɹ�\n"), strOldIdxFile.c_str()));
				break;
			}
		}

		int iCount=0;
		while (TRUE)
		{
			iCount++;
			BOOL bRet=CopyFile(strIdxFile.c_str(),strOldIdxFile.c_str(),FALSE);
			if (!bRet)
			{
				if (iCount>10)
				{
					I8_ERROR((LM_ERROR, 
						I8_TEXT("�����ļ�%s����ʧ�ܳ���10��,�������%u,\n"),
						strOldIdxFile.c_str(),GetLastError()));
					return FALSE;
				}

				I8_DEBUG((LM_DEBUG, 
					I8_TEXT("�����ļ�%sʧ��,�������%u,1�������\n"),
					strOldIdxFile.c_str(),GetLastError()));
				Sleep(1000);
				continue;
			}
			else
			{
				I8_DEBUG3((LM_DEBUG, I8_TEXT("�����ļ�%s�ɹ�\n"), strOldIdxFile.c_str()));
				break;
			}
		}

		//���°汾��
		UpdateVersion(dwNewVersion);
		if (pbReloadCacheFile)
			*pbReloadCacheFile = TRUE;
	}

	return TRUE;
}


BOOL ZClientSoftMonitor::GetOldIdxInfo(DWORD& dwCrc, DWORD& dwVersion)
{
	dwCrc=dwVersion=0;
	std_string strOldIdxFile=GetAppPath()+_T("BarOnlineUpdate\\Update.idx");
	if (!PathFileExists(strOldIdxFile.c_str()))
		return FALSE;

	HANDLE hFile = CreateFile(strOldIdxFile.c_str(),           // open MYFILE.TXT 
		GENERIC_READ,              // open for reading 
		FILE_SHARE_READ,           // share for reading 
		NULL,                      // no security 
		OPEN_EXISTING,             // existing file only 
		FILE_ATTRIBUTE_NORMAL,     // normal file 
		NULL);                     // no attr. template 
	if (hFile==INVALID_HANDLE_VALUE) {
		I8_ERROR_RETURN((LM_ERROR, 
			I8_TEXT("���ļ�[%s]ʧ��,������룬%u\n"), 
			strOldIdxFile.c_str(), GetLastError()), FALSE);
	}

	if (!ReadFileContent(hFile,(BYTE*)&dwCrc,sizeof(DWORD))) {
		CloseHandle(hFile);
		return FALSE;
	}

	if (!ReadFileContent(hFile,(BYTE*)&dwVersion,sizeof(DWORD)))
	{
		CloseHandle(hFile);
		return FALSE;
	}

	CloseHandle(hFile);

	return TRUE;
}



} //namespace i8desk
