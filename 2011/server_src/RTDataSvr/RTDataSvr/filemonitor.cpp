#include "StdAfx.h"
#include "filemonitor.h"
#include "../../../include/frame.h"
#include "../../../include/Utility/utility.h"
#include "globalfun.h"
#include "filecache.h"
#include "LogHelper.h"

#include "i8mp.h"

#define UPDATE_IDX_INTERVAL (1000 * 60 * 3)

namespace i8desk {

	ZClientSoftMonitor::ZClientSoftMonitor(ZFileCacheMgr *pFileCacheMgr)
		: m_pFileCacheMgr(pFileCacheMgr)
		, m_dwVersion(::_time32(0))
	{
	}

	ZClientSoftMonitor::~ZClientSoftMonitor(void)
	{
		Shutdown();
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
		Log(LM_DEBUG, _T("UpdateVersion:%u\n"), m_dwVersion);
	}


	int ZClientSoftMonitor::Init(void)
	{
		MakeIdx();
		return 0;
	}


	void ZClientSoftMonitor::Fini(void)
	{
	}


	uint32 ZClientSoftMonitor::Exec(void)
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

	BOOL ZClientSoftMonitor::IsPriority( const stdex::tString &filename, const std::vector<stdex::tString> &sortfile)
	{
		for (std::vector<stdex::tString>::const_iterator iter = sortfile.begin(); iter != sortfile.end(); ++iter )
		{
			if(filename == (*iter))
				return TRUE;
		}

		return FALSE;
	}

	void ZClientSoftMonitor::SetFileListbySort( LPCTSTR lpPath, std::vector<stdex::tString> &vFileList, std::vector<ULONGLONG> &vSizeList, std::vector<stdex::tString> &sortfile)
	{
		stdex::tString strPath = lpPath;

		strPath += _T("\\Frame.dll");
		sortfile.push_back(strPath);
		strPath = lpPath;
		strPath += _T("\\I8DeskCliSvr.exe");
		sortfile.push_back(strPath);
		strPath = lpPath;
		strPath += _T("\\BootRun.dll");
		sortfile.push_back(strPath);
		strPath = lpPath;
		strPath += _T("\\wxProt.dll");
		sortfile.push_back(strPath);

		for (std::vector<stdex::tString>::iterator iter = sortfile.begin(); iter != sortfile.end(); ++iter )
		{
			WIN32_FIND_DATA FindFileData;
			utility::CAutoFindFile hFind = FindFirstFile((*iter).c_str(), &FindFileData);
			if(!hFind.IsValid())
				continue;
			vFileList.push_back(*iter);
			vSizeList.push_back(MAKEULONGLONG(FindFileData.nFileSizeLow,FindFileData.nFileSizeHigh));
		}
	}

	BOOL ZClientSoftMonitor::GetFileListbySort( LPCTSTR lpPath, std::vector<stdex::tString> &vFileList, std::vector<ULONGLONG> &vSizeList, std::vector<stdex::tString> &sortfile)
	{
		stdex::tString strPath = lpPath;

		WIN32_FIND_DATA FindFileData;

		strPath += _T("\\*.*");
		utility::CAutoFindFile hFind = FindFirstFile(strPath.c_str(), &FindFileData);
		if(!hFind.IsValid())
			return FALSE;

		stdex::tString strFileName;

		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(!((FindFileData.cFileName[0]=='.' && FindFileData.cFileName[1]=='\0')||(FindFileData.cFileName[0]=='.' && FindFileData.cFileName[1]=='.' && FindFileData.cFileName[2]=='\0')))
			{
				strPath = lpPath;
				strPath += _T("\\");
				strPath += FindFileData.cFileName;
				if (!GetFileListbySort(strPath.c_str(),vFileList,vSizeList, sortfile))
					return FALSE;
			}
		}
		else
		{
			strFileName = lpPath;
			strFileName += _T("\\");
			strFileName += FindFileData.cFileName;
			vFileList.push_back(strFileName);
			vSizeList.push_back(MAKEULONGLONG(FindFileData.nFileSizeLow,FindFileData.nFileSizeHigh));
		}

		while (FindNextFile(hFind,&FindFileData))
		{
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				//.or ..
				if (FindFileData.cFileName[0] == '.')
				{
					if (FindFileData.cFileName[1] == '\0' ||
						(FindFileData.cFileName[1] == '.' &&
						FindFileData.cFileName[2] == '\0'))
					{
						continue;
					}
				}

				strPath = lpPath;
				strPath += _T("\\");
				strPath += FindFileData.cFileName;
				if (!GetFileListbySort(strPath.c_str(),vFileList,vSizeList, sortfile))
					return FALSE;
			}
			else
			{
				strFileName = lpPath;
				strFileName += _T("\\");
				strFileName += FindFileData.cFileName;
				if(	!IsPriority(strFileName, sortfile) )
				{
					vFileList.push_back(strFileName);
					vSizeList.push_back(MAKEULONGLONG(FindFileData.nFileSizeLow,FindFileData.nFileSizeHigh));
				}
			}
		}

		DWORD dwErrorCode = GetLastError();
		if (dwErrorCode != ERROR_NO_MORE_FILES)
		{
			SetLastError(dwErrorCode);
			return FALSE;
		}

		return TRUE;

	}


	BOOL ZClientSoftMonitor::MakeIdx(BOOL *pbReloadCacheFile)
	{
		I8_GUARD(ZGuard, ZSync, m_MakeLock);

		if (pbReloadCacheFile)
			*pbReloadCacheFile = FALSE;

		stdex::tString strPath = utility::GetAppPath() + _T("BarOnlineUpdate");
		stdex::tString strIdxFile = utility::GetAppPath() + _T("tmp\\Client.idx");
		DWORD dwOldCrc32 = 0, dwOldVersion = 0, dwNewVersion = 0;


		if(!PathFileExists(strPath.c_str()))
		{
			if( !::CreateDirectory(strPath.c_str(), NULL) )
			{
				Log(LM_DEBUG,_T("���¿ͻ����������ʱ��Ŀ¼[%s]������,������룬%u\n"), 
					strPath.c_str(), GetLastError());
				return FALSE;
			}
		}

		std::vector<stdex::tString> vFileList;
		std::vector<stdex::tString> sortfile;
		std::vector<ULONGLONG> vSizeList;
		// ���̶���������
		SetFileListbySort(strPath.c_str(), vFileList, vSizeList, sortfile);
		if (!GetFileListbySort(strPath.c_str(), vFileList, vSizeList, sortfile))
			Log(LM_DEBUG,_T("���¿ͻ����������ʱ��δ��ȡ������Ŀ¼���ļ��б�\n"));			


		DWORD dwCount=vFileList.size();
		if (dwCount == 0) 
		{
			Log(LM_DEBUG,_T("���¿ͻ����������ʱ����ȡĿ¼[%s]���ļ��б�Ϊ��\n"), 
				strPath.c_str());
			return FALSE;
		}

		if( !::PathFileExists(strIdxFile.c_str()) )
		{
			std::ofstream out(strIdxFile.c_str());
		}

		std::fstream out(strIdxFile.c_str(), std::ios::binary | std::ios::out);
		if( !out )
		{
			Log(LM_ERROR, _T("�����ļ�[%s]ʧ��,������룬%u\n"), 
				strIdxFile.c_str(), GetLastError());
			return FALSE;
		}

		//�ȶ�Crc��Verд0
		out.write((const char *)&dwOldCrc32, sizeof(DWORD));
		if( !out )
		{
			Log(LM_ERROR, _T("д�ļ�[%s]ʧ��,������룬%u\n"), 
				strIdxFile.c_str(), GetLastError());
			return FALSE;
		}

		out.write((const char *)&dwOldVersion, sizeof(DWORD));
		if( !out )
		{
			Log(LM_ERROR, _T("д�ļ�[%s]ʧ��,������룬%u\n"), 
				strIdxFile.c_str(), GetLastError());
			return FALSE;
		}

		out.write((const char *)&dwCount, sizeof(DWORD));
		if( !out )
		{
			Log(LM_ERROR, _T("д�ļ�[%s]ʧ��,������룬%u\n"), 
				strIdxFile.c_str(), GetLastError());
			return FALSE;
		}


		BOOL bIdxExist=FALSE;
		DWORD dwExceptCount=0;
		for (DWORD i=0;i<dwCount;i++)
		{
			stdex::tString strFullPathFileName=vFileList[i];
			//1.�õ��ļ���
			stdex::tString::size_type b = strFullPathFileName.find_last_of('\\');
			stdex::tString strFileName = strFullPathFileName.substr(b+1);
			if ((GetFileAttributes(strFullPathFileName.c_str()) & FILE_ATTRIBUTE_SYSTEM) == 0
				&& _tcsicmp(strFileName.c_str(), _T("UPDATE.IDX"))!=0) // && stricmp(strFileName, _T("THUMBS.DB")))
			{
				strFileName=vFileList[i];
				strFileName=strFileName.substr(strPath.size()+1);
				TCHAR FileName[MAX_PATH] = {0};
				_tcscpy(FileName,_T("%root%\\"));
				_tcscat(FileName,strFileName.c_str());

				DWORD dwCrc32=0;
				if (!utility::GetFileCrc32(vFileList[i].c_str(), dwCrc32))
				{
					Log(LM_ERROR, 
						_T("��ȡ�ļ�[%s]CRCʧ��,������룬%u\n"), 
						vFileList[i].c_str(), GetLastError());
					return FALSE;
				}

				out.write((const char *)&dwCrc32, sizeof(DWORD));
				if( !out )
				{
					Log(LM_ERROR, _T("д�ļ�[%s]ʧ��,������룬%u\n"), 
						strIdxFile.c_str(), GetLastError());
					return FALSE;
				}

				char fileNameTmp[MAX_PATH] ={0};
				strcpy_s(fileNameTmp, MAX_PATH, CT2A(FileName));
				out.write(fileNameTmp, MAX_PATH);
				if( !out )
				{
					Log(LM_ERROR, _T("д�ļ�[%s]ʧ��,������룬%u\n"), 
						strIdxFile.c_str(), GetLastError());
					return FALSE;
				}
			}
			else
			{
				bIdxExist=TRUE;
				dwExceptCount++;
			}
		}

		DWORD size = out.tellp();

		if (bIdxExist)
		{
			out.seekp(8, std::ios_base::beg);
			if ( !out )
			{
				Log(LM_ERROR, 
					_T("��λ�ļ�[%s]ʧ��,������룬%u\n"), 
					strIdxFile.c_str(), GetLastError());
				return FALSE;
			}

			dwCount-=dwExceptCount;

			out.write((const char *)&dwCount, sizeof(DWORD));
			if( !out )
			{
				Log(LM_ERROR, _T("д�ļ�[%s]ʧ��,������룬%u\n"), 
					strIdxFile.c_str(), GetLastError());
				return FALSE;
			}
		}

		//������idx�ļ���ǰ2��DWORD

		BOOL bReadOldIdxOk=GetOldIdxInfo(dwOldCrc32,dwOldVersion);
		if (bReadOldIdxOk)
		{
			//�Ȱ�Version��д�ɾ��ļ��İ汾,���ڼ���CRC
			out.seekp(4, std::ios_base::beg);
			if ( !out )
			{
				Log(LM_ERROR,_T("��λ�ļ�[%s]ʧ��,������룬%u\n"), 
					strIdxFile.c_str(), GetLastError());
				return FALSE;
			}

			out.write((const char *)&dwOldVersion, sizeof(DWORD));
			if( !out )
			{
				Log(LM_ERROR, _T("д�ļ�[%s]ʧ��,������룬%u\n"), 
					strIdxFile.c_str(), GetLastError());
				return FALSE;
			}

			//�õ���idx����ʱcrc32
			DWORD dwTmpCrc32=0;
			out.flush();

			if (!utility::GetFileCrc32(strIdxFile.c_str(),dwTmpCrc32))
			{
				Log(LM_ERROR,_T("���ɿͻ����������ʱ���õ���idx����ʱcrc32ʧ��\n"));
				return FALSE;
			}

			dwNewVersion = _time32(NULL);

			out.seekp(4, std::ios_base::beg);
			if ( !out )
			{
				Log(LM_ERROR,_T("��λ�ļ�[%s]ʧ��,������룬%u\n"), 
					strIdxFile.c_str(), GetLastError());
				return FALSE;
			}

			out.write((const char *)&dwNewVersion, sizeof(DWORD));
			if( !out )
			{
				Log(LM_ERROR, _T("д�ļ�[%s]ʧ��,������룬%u\n"), 
					strIdxFile.c_str(), GetLastError());
				return FALSE;
			}

			DWORD dwCrc32=0;
			out.flush();
			if (!utility::GetFileCrc32(strIdxFile.c_str(),dwCrc32))
			{
				Log(LM_ERROR,_T("���ɿͻ����������ʱ���õ���idx����ʱcrc32ʧ��\n"));
				return FALSE;
			}

			out.seekp(0, std::ios_base::beg);
			if ( !out )
			{
				Log(LM_ERROR,_T("��λ�ļ�[%s]ʧ��,������룬%u\n"), 
					strIdxFile.c_str(), GetLastError());
				return FALSE;
			}

			out.write((const char *)&dwCrc32, sizeof(DWORD));
			if( !out )
			{
				Log(LM_ERROR, _T("д�ļ�[%s]ʧ��,������룬%u\n"), 
					strIdxFile.c_str(), GetLastError());
				return FALSE;
			}

			out.close();
			//////////////////////////////////////////////////////////////////////////
			//�ļ����ݱ���
			if (dwOldCrc32!=dwTmpCrc32)
			{
				//���µ������ļ�Copy��ȥ
				stdex::tString strOldIdxFile= utility::GetAppPath()+_T("BarOnlineUpdate\\Update.idx");
				while (TRUE)
				{
					if (PathFileExists(strOldIdxFile.c_str()))
					{
						SetFileAttributes(strOldIdxFile.c_str(),FILE_ATTRIBUTE_NORMAL);
						DeleteFile(strOldIdxFile.c_str());
					}

					if (PathFileExists(strOldIdxFile.c_str()))
					{
						Log(LM_DEBUG, _T("ɾ���ļ�%sʧ��,1�������\n"),strOldIdxFile.c_str());
						Sleep(1000);
						continue;
					}
					else
					{
						Log(LM_DEBUG, _T("ɾ���ļ�%s�ɹ�\n"), strOldIdxFile.c_str());
						break;
					}
				}

				int iCount=0;
				while (TRUE)
				{
					iCount++;
					//				out.flush();
					BOOL bRet=CopyFile(strIdxFile.c_str(),strOldIdxFile.c_str(),FALSE);
					if (!bRet)
					{
						if (iCount>10)
						{
							Log(LM_ERROR, 
								_T("�����ļ�%s����ʧ�ܳ���10��,�������%u\n"),
								strOldIdxFile.c_str(),GetLastError());
							return FALSE;
						}

						Log(LM_DEBUG, 
							_T("�����ļ�%sʧ��,�������%u,1�������\n"),
							strOldIdxFile.c_str(),GetLastError());
						Sleep(1000);
						continue;
					}
					else
					{
						Log(LM_DEBUG, _T("�����ļ�%s�ɹ�\n"),strOldIdxFile.c_str());
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

			out.seekp(4, std::ios_base::beg);
			if ( !out )
			{
				Log(LM_ERROR,_T("��λ�ļ�[%s]ʧ��,������룬%u\n"), 
					strIdxFile.c_str(), GetLastError());
				return FALSE;
			}

			out.write((const char *)&dwNewVersion, sizeof(DWORD));
			if( !out )
			{
				Log(LM_ERROR, _T("д�ļ�[%s]ʧ��,������룬%u\n"), 
					strIdxFile.c_str(), GetLastError());
				return FALSE;
			}

			DWORD dwCrc32=0;
			out.flush();

			if (!utility::GetFileCrc32(strIdxFile.c_str(),dwCrc32))
			{
				Log(LM_ERROR,_T("���ɿͻ����������ʱ���õ���idx����ʱcrc32ʧ��\n"));
				return FALSE;
			}

			out.seekp(0, std::ios_base::beg);
			if ( !out )
			{
				Log(LM_ERROR,_T("��λ�ļ�[%s]ʧ��,������룬%u\n"), 
					strIdxFile.c_str(), GetLastError());
				return FALSE;
			}

			out.write((const char *)&dwCrc32, sizeof(DWORD));
			if( !out )
			{
				Log(LM_ERROR, _T("д�ļ�[%s]ʧ��,������룬%u\n"), 
					strIdxFile.c_str(), GetLastError());
				return FALSE;
			}

			out.close();
			//////////////////////////////////////////////////////////////////////////
			//���µ������ļ�Copy��ȥ
			stdex::tString strOldIdxFile = utility::GetAppPath()+_T("BarOnlineUpdate\\Update.idx");
			while (TRUE)
			{
				if (PathFileExists(strOldIdxFile.c_str()))
				{
					SetFileAttributes(strOldIdxFile.c_str(),FILE_ATTRIBUTE_NORMAL);
					DeleteFile(strOldIdxFile.c_str());
				}

				if (PathFileExists(strOldIdxFile.c_str()))
				{
					Log(LM_DEBUG, _T("ɾ���ļ�%sʧ��,1�������\n"), strOldIdxFile.c_str());
					Sleep(1000);
					continue;
				}
				else
				{
					Log(LM_DEBUG, _T("ɾ���ļ�%s�ɹ�\n"), strOldIdxFile.c_str());
					break;
				}
			}

			int iCount=0;
			while (TRUE)
			{
				iCount++;
				//out.flush();
				BOOL bRet=CopyFile(strIdxFile.c_str(),strOldIdxFile.c_str(),FALSE);
				if (!bRet)
				{
					if (iCount>10)
					{
						Log(LM_ERROR, 
							_T("�����ļ�%s����ʧ�ܳ���10��,�������%u,\n"),
							strOldIdxFile.c_str(),GetLastError());
						return FALSE;
					}

					Log(LM_DEBUG, 
						_T("�����ļ�%sʧ��,�������%u,1�������\n"),
						strOldIdxFile.c_str(),GetLastError());
					Sleep(1000);
					continue;
				}
				else
				{
					Log(LM_DEBUG, _T("�����ļ�%s�ɹ�\n"), strOldIdxFile.c_str());
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
		stdex::tString strOldIdxFile=utility::GetAppPath()+_T("BarOnlineUpdate\\Update.idx");
		if (!PathFileExists(strOldIdxFile.c_str()))
			return FALSE;

		utility::CAutoFile hFile = CreateFile(strOldIdxFile.c_str(),           // open MYFILE.TXT 
			GENERIC_READ,              // open for reading 
			FILE_SHARE_READ,           // share for reading 
			NULL,                      // no security 
			OPEN_EXISTING,             // existing file only 
			FILE_ATTRIBUTE_NORMAL,     // normal file 
			NULL);                     // no attr. template 
		if (!hFile.IsValid()) 
		{
			Log(LM_ERROR, 
				_T("���ļ�[%s]ʧ��,������룬%u\n"), 
				strOldIdxFile.c_str(), GetLastError());
			return FALSE;
		}

		if (!utility::ReadFileContent(hFile,(BYTE*)&dwCrc,sizeof(DWORD))) {
			return FALSE;
		}

		if (!utility::ReadFileContent(hFile,(BYTE*)&dwVersion,sizeof(DWORD)))
		{
			return FALSE;
		}


		return TRUE;
	}



} //namespace i8desk
