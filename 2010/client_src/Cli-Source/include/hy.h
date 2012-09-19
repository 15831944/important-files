#ifndef __i8desk_hy_inc__
#define __i8desk_hy_inc__

#include "..\Include\plug.h"
#include   <algorithm> 
#include <Shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

#define PROT_DLL_NAME	TEXT("wxProt.dll")
#define PROT_PASSWORD	"ST3F95Xfhu9rBqBh"

#pragma pack(1)
typedef struct tag_MOUNT_PACK
{
	LONGLONG qwStartSec;
	LONGLONG qwSecs;
	DWORD    dwDiskNumber;
	char     szDosDevice[MAX_PATH];
}MOUNTPACK, *LPMOUNTPACK;

typedef struct tag_ProtectArea_Info
{
	BYTE	bState;
	BYTE	bCmd;
	BYTE	bCmdAtOnce;
	BYTE	bModifyOutside;
	DWORD	dwStartSec;
	DWORD	dwSecs;
	DWORD	dwDiskNumber;

	DWORD	dwBitmapNotUsedBits;
	DWORD	dwBitmapOldUsedBits;
	DWORD	dwBitmapNewUsedBits;
	DWORD	dwBitmapTmpUsedBits;
}PROTECTAREA_INFO, *LPPROTECTAREA_INFO;

#define MAX_PROTECTAREA_NUMS	100
typedef struct tag_PROTECTAREA_PACK
{
	DWORD	dwInOrOut;
	DWORD	dwNums;
	DWORD	dwReseave[2];
	char	szPassword[256];
	PROTECTAREA_INFO	Area[MAX_PROTECTAREA_NUMS];
}PROTECTAREA_PACK, *LPPROTECTAREA_PACK;

typedef struct tag_PtInfo
{
	DWORD	dwStartSec;	//�˷����ľ��Կ�ʼ����
	DWORD	dwSecs;		//�˷����Ĵ�С��������
	DWORD	dwUsedSecs;	//�˷����Ѿ���ʹ�õ�������
	BYTE	bFsType;		//�˷����ķ�������
	BYTE	bIsMaster;	//�˷��Ƿ�Ϊ��������1��ʾ��������0��ʾ��������
	BYTE	bIsActive;	//�˷����Ƿ�Ϊ�������1��ʾ�������0��ʾΪ�ǻ����
	BYTE	bDosChar;	//�˷������̷���Ϊ�̷���ASCIIֵ���磬C��ASCIIֵΪ67
	char	szVolume[256];	//�˷����ľ��
}PTINFO, *LPPTINFO;	

#define MAX_PTS	 100
typedef struct tag_HDInfo
{
	DWORD	dwHdNumber;		//��Ӳ����ϵͳ�е��豸˳���
	DWORD	dwSecs;			//��Ӳ�̵Ĵ�С��������
	DWORD	dwReseave;		//����
	DWORD	dwPtNums;		//��Ӳ�̵ķ�������
	PTINFO	pt[MAX_PTS];	//������Ϣ����
}HD, *LPHD;

#pragma pack()

namespace i8desk
{
	class CHyOperator
	{
	private:
		//ע�����з����ַ������Ǵ�д�����ݷ��أ���ʾ�ɹ���������������ʾ����������롣

		//��һ��������ʾ��װʱҪ�����ķ����б��ڶ��������õĻ�ԭ���롣������������룬����""���ַ�����
		//���أ���ʾ�ɹ����ǣ��Ǵ�����롣

		//��װ����������ָ���̷�:
		typedef int (WINAPI *PFNINSTALL4DOSCHAR)(LPCSTR szProtectList, LPCSTR szPassword);

		//�õ�����״̬�����أ���ʾ��������װ��������ʾû�а�װ������
		typedef int (WINAPI *PFNGETDRIVESTATE)();

		//ж������
		typedef int (WINAPI *PFNUNINSTALLDRIVER)();

		//�������Ƿ񱻱�������������̣��������"C"��ע�ⲻ��"C:"����"C:\"
		//����ʾ����������ʾû�б���
		typedef int (WINAPI *PFNDRIVERISPROTECTED)(LPCSTR pBuffer);

		//�������룺���������Ϊ�գ���""�սڷ��������أ���ʾ������ȷ�����������벻��ȷ
		typedef int (WINAPI *PFNCHECKPASSWORD)(LPCSTR szPassWord );

		//�������룺�������������룬�����롣
		typedef int (WINAPI *PFNCHANGEPASSWORD)(LPCSTR szOldPassWord, LPCSTR szNewPassword );

		//������дһ����Ҫ��������ݣ� ��С0x100 BYTE��������ݱ����ǣ������ֽڵĻ���ռ䣬��Ӧ�ó������д˽�����ݵ��������棬Ҳ���Զ�������
		typedef int (WINAPI *PFNRWAPDATA)(BYTE *lpBuf, BYTE isWrite );//1��ʾд������ʾ��

		//���ñ�����������Ҫ���̷��б�:���أ���ʾ�ɹ���������ʾ������롣
		#define PROT_DRIVER		1
		#define UNPROT_DRIVER	3
		#define FLAG_REBOOT		0
		#define FLAG_IMME		1
		typedef int (WINAPI *PFNSETPROTECTAREAFORDOSCHAR)(
			LPCTSTR szDosCharList, 
			int iState /*1:��ʾ����������3��ʾȡ����������*/,
			int iCmd, //д0
			LPCTSTR szPassword, //��������
			int iIsOnTime /*����ʾ������Ч������ʾ��������Ч����ϵͳ���Լ�ҳ���ļ����ڸ÷����Ļ�������Ҫ���������Ч����Щ����0)*/
			);


		//�õ������ķ����б������Ǵ�����ݵĻ��������Լ��������Ĵ�С��һ��ʹ�ã������ֽڼ��ɡ���Ϊ�����ǣ����ڡ�
		//���������Уã��ģ��ţ��ƣ��ǣ����ҵ�ǰ�����ˣģ��ơ��򷵻��ڻ�������д"DF".
		typedef int (WINAPI *PFNGETPROTECTEDDRIVES)(LPSTR pBuffer, int cxBuffer);

		//���������������ڴ�͸��ԭ����͸��ԭ��ԭ���ǣ������͸���̣���͸ǰ�ѣ�����һ�������豸��Ȼ����������д���ݣ��ʹ�͸�ˡ�������󣬰�������ɾ����
		//�õ������̵���Ϣ��
		typedef int (WINAPI *PFNGETMOUNTINFO)( MOUNTPACK *lpMountPack, LPCSTR szPassword );

		//ɾ�������豸��
		typedef int (WINAPI *PFNUMOUNTPTDOSCHAR)(LPCSTR szdevicePath,   LPCSTR szPassword);

		//��������̡���һ�������Ƿ�����ĸ������"D".�ڶ��������������������Լ�ȡ�ģ�
		//�������ǵ�������Ҫʹ�÷�����ĸ�����������ȡ���������֡���I8DESKD,����ȡ
		//D:�������������ʾ����Դ�������У����������������롣
		typedef int (WINAPI *PFNMOUNTPTDOSCHAR)(LPCSTR szDosChar, LPCSTR szdevicePath, LPCSTR szPassword);

		//���ӣ���͸���̡�
		//��͸ǰ���ȵ���MoutPtDosChar��"D", "I8DESKD","password");����һ���豸������

		//�������豸д�ļ��ͻ�ֱ�Ӵ�͸��\\\\.\\������豸����\�ļ�·����
		//CopyFile(����:\\boot.ini��, ��\\\\.\\I8DESKD\\boot.ini, 0 ).���ѣ��̵�����ļ�д�������																				 
		//�������ɾ�������豸��
		//UMoutPtDosChar("I8DESKD", "password");

		typedef int (WINAPI * PFNGETPROTECTAREA)(PROTECTAREA_PACK *lpProtect);

		typedef int (WINAPI * PFNGETHDINFO)( LPHD lphd );
		
		tstring						m_sDevicePath;
		ILogger*					m_pLogger;
		HMODULE						_hModule;
		PFNINSTALL4DOSCHAR 			pfnInstall4DosChar;
		PFNGETDRIVESTATE			pfnGetDriveState;
		PFNUNINSTALLDRIVER			pfnUnInstallDriver;
		PFNDRIVERISPROTECTED		pfnDriverIsProtected;	   
		PFNCHECKPASSWORD			pfnCheckPassword;
		PFNCHANGEPASSWORD			pfnChangePassword;
		PFNRWAPDATA					pfnRWAPData;
		PFNSETPROTECTAREAFORDOSCHAR pfnProtArea;
		PFNGETPROTECTEDDRIVES		pfnGetProtectDrivers;
		PFNMOUNTPTDOSCHAR			pfnMountDosChar;				
		PFNUMOUNTPTDOSCHAR			pfnUMountDosChar;
		PFNGETMOUNTINFO				pfnGetMountInfo;
		PFNGETPROTECTAREA			pfnGetProtectArea;
		PFNGETHDINFO				pfnGetHDInfo;
	public:
		CHyOperator()
		{
			TCHAR szModule[MAX_PATH] = {0};
			GetModuleFileName(NULL, szModule, MAX_PATH);
			PathRemoveFileSpec(szModule);
			PathAddBackslash(szModule);
			lstrcat(szModule, PROT_DLL_NAME);
			_hModule = LoadLibrary(szModule);		
			if (_hModule != NULL)
			{
				pfnInstall4DosChar		= (PFNINSTALL4DOSCHAR)GetProcAddress(_hModule, "Install4DosChar");
				pfnGetDriveState		= (PFNGETDRIVESTATE)GetProcAddress(_hModule, "GetDriveState");
				pfnUnInstallDriver		= (PFNUNINSTALLDRIVER)GetProcAddress(_hModule, "UnInstallDriver");
				pfnDriverIsProtected	= (PFNDRIVERISPROTECTED)GetProcAddress(_hModule, "DriverIsProtected");	   
				pfnCheckPassword		= (PFNCHECKPASSWORD)GetProcAddress(_hModule, "CheckPassWord");
				pfnChangePassword		= (PFNCHANGEPASSWORD)GetProcAddress(_hModule, "ChangePassWord");
				pfnRWAPData				= (PFNRWAPDATA)GetProcAddress(_hModule, "RWAPData");
				pfnProtArea				= (PFNSETPROTECTAREAFORDOSCHAR)GetProcAddress(_hModule, "SetProtectAreaForDosChar");
				pfnGetProtectDrivers	= (PFNGETPROTECTEDDRIVES)GetProcAddress(_hModule, "GetProtectedDrives");
				pfnMountDosChar			= (PFNMOUNTPTDOSCHAR)GetProcAddress(_hModule, "MountPtDosChar");
				pfnUMountDosChar		= (PFNUMOUNTPTDOSCHAR)GetProcAddress(_hModule, "UMountPtDosChar");
				pfnGetMountInfo			= (PFNGETMOUNTINFO)GetProcAddress(_hModule, "GetMountInfo");
				pfnGetProtectArea		= (PFNGETPROTECTAREA)GetProcAddress(_hModule, "GetProtectArea");
				pfnGetHDInfo			= (PFNGETHDINFO)GetProcAddress(_hModule, "GetHDInfo");
				if (pfnInstall4DosChar		!= NULL &&
					pfnGetDriveState		!= NULL &&
					pfnUnInstallDriver		!= NULL &&
					pfnDriverIsProtected	!= NULL &&
					pfnCheckPassword		!= NULL && 
					pfnChangePassword		!= NULL &&
					pfnRWAPData				!= NULL &&
					pfnProtArea				!= NULL &&
					pfnGetProtectDrivers	!= NULL &&
					pfnMountDosChar			!= NULL &&
					pfnUMountDosChar		!= NULL &&
					pfnGetMountInfo			!= NULL && 
					pfnGetProtectArea		!= NULL &&
					pfnGetHDInfo			!= NULL)
				{
				
					CheckBeforeOperator();
					return ;
				}

				CheckBeforeOperator();				
			}
		}
		~CHyOperator()
		{
			UnInitialize();
		}
		void SetLogger(ILogger* pLogger)
		{
			m_pLogger = pLogger;
			return;

		}
		void CheckBeforeOperator()
		{
			int ret =pfnGetDriveState();
			if (ret == 0)
			{
				ret = pfnCheckPassword("");
				if ( ret == 0)
					pfnChangePassword("", PROT_PASSWORD);
//				else
//					m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("pfnChangePassword RetCode:%d"),ret);
			}
//			else
//				m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("pnfCheckPassword RetCode:%d"),ret);
		}

		bool IsInitialize()
		{
			return _hModule != NULL;
		}

		void UnInitialize()
		{
			if (_hModule != NULL)
				FreeLibrary(_hModule);

			pfnInstall4DosChar = NULL;
			pfnGetDriveState = NULL;
			pfnUnInstallDriver = NULL;
			pfnDriverIsProtected = NULL;	   
			pfnCheckPassword = NULL;
			pfnChangePassword = NULL;
			pfnRWAPData = NULL;
			pfnProtArea = NULL;
			pfnGetProtectDrivers = NULL;
			pfnMountDosChar = NULL;				
			pfnUMountDosChar = NULL;
			pfnGetMountInfo  = NULL;
			pfnGetProtectArea = NULL;
			pfnGetHDInfo = NULL;
		}


		//��ԭ�Ƿ�װ
		bool IsInstallHy()
		{
			int ret = pfnGetDriveState();
			if (ret == 0)
				return true;
			else
			{
				return false;
			}
		}

		//��װ��ԭ
		void InstallHy(LPCSTR szProtectList)
		{			
			if (IsInstallHy())
				return ;
			int ret = pfnInstall4DosChar(szProtectList, PROT_PASSWORD);
			if (ret == 0)
			{
				CreateProtDiskService("ProtDisk");
				ShutDown(true);
			}
			else
				m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("pfnInstall4DosChar RetCode:%d"),ret);
			
		}

		//ж�ػ�ԭ
		void RemoveHy()
		{
			if (IsInstallHy())
			{
				int ret = pfnUnInstallDriver();
				if (ret == 0)
				{
					ShutDown(true);
				}
				else
					m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("pfnUnInstallDriver RetCode:%d"),ret);
				
			}
		}
		//��ȡӲ����Ϣ��
		int GetHDInfo(LPHD lphd )
		{
			int ret = pfnGetHDInfo(lphd);
			if (ret != 0 )
			{
				m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("pfnGetHDInfo RetCode:%d"),ret);
			}
			return ret;
		}

		//�����Ƿ񱣻���
		bool IsDriverProtected(char* pszArea)
		{
			int ret = pfnDriverIsProtected(pszArea);
			if (ret == 0)			
				return true;			
			else
			{
				m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("pfnDriverIsProtected RetCode:%d"),ret);
				return false;
			}
		}
		//��ȡ��ԭ�����豸·����	
		tstring GetDevicePath()
		{
			return m_sDevicePath;
		}
		//��������豸��
		bool MountDosChar(char* pszArea)
		{
			if (IsInitialize())
			{
				if (IsInstallHy())
				{
					char device[MAX_PATH] = {0};
					
					tstring path(pszArea);					
					transform(path.begin(),path.end(),path.begin(),toupper);  
					sprintf(device, "I8Desk%c", path[0]);
					path[1]= 0;					
					if (IsDriverProtected((char*)path.c_str()))
					{	
						int ret = pfnMountDosChar(path.c_str(),device,PROT_PASSWORD);
						if ( ret== 0 || ret == 0x1001)
						{
							m_sDevicePath = tstring(device);
							return true;							
						}
						else
						{
							m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("pfnMountDosChar RetCode:%d"),ret);
							return false;
						}
// 						if (MountDosChar((char*)path.c_str(), device) == 0)
// 						{
// 							m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("load virtual device success:%s-%s."), path.c_str(), device);
// 							return true;
// 						}
// 						else
// 						{
// 							m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("load virtual device fail."));
// 						}
					}
					else
					{
						m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("driver is not protected."));
					}
				}
			}
			return false;


				
		}

		//ɾ�������豸��
		bool UMountDosChar(char* pszArea)
		{
			return true;
// 			char device[MAX_PATH] = {0};
// 			tstring path(pszArea);
// 			sprintf(device, "I8Desk%c", path[0]);
// 			path[1]= 0;			
			int ret = pfnUMountDosChar(m_sDevicePath.c_str(),PROT_PASSWORD);
			if (ret == 0)
			{
				m_sDevicePath = "";
				return true;
			}
			else
			{
				m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("pfnUMountDosChar RetCode:%d"),ret);
				return false;
			}
		}

		//��������
		void ProtArea(char* pszArea)
		{
			if (pszArea == NULL || lstrlenA(pszArea) == 0)
			{
				return ;
			}

			if (!IsInstallHy())
			{
				return ;
			}
			int ret = pfnCheckPassword("");
			if (ret == 0)
			{
				ret = pfnChangePassword("", PROT_PASSWORD);
				if (ret != 0)
				{
					m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("pfnChangePassword RetCode:%d"),ret);					
				}
			}
			else
				m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("pfnCheckPassword RetCode:%d"),ret);

			ret = pfnProtArea(pszArea, PROT_DRIVER, 0, PROT_PASSWORD, FLAG_IMME);
			if (0 != ret)
			{
				m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("pfnProtArea:PROT_DRIVER,FLAG_IMME RetCode:%d"),ret);

				ret = pfnProtArea(pszArea, PROT_DRIVER, 0, PROT_PASSWORD, FLAG_REBOOT);
				if (ret == 0)				
					ShutDown(true);				
				else
					m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("pfnProtArea:PROT_DRIVER,FLAG_REBOOT RetCode:%d"),ret);
			}
		}

		//ȡ����������
		void UnProtArea(char* pszArea)
		{
			if (pszArea == NULL || lstrlenA(pszArea) == 0)
			{
				return ;
			}
			if (!IsInstallHy())
			{
				return ;
			}

			int ret = pfnCheckPassword("");
			if (ret == 0)
			{
				ret = pfnChangePassword("", PROT_PASSWORD);
				if (ret != 0)
				{
					m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("pfnChangePassword RetCode:%d"),ret);					
				}
			}
			else
				m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("pfnCheckPassword RetCode:%d"),ret);

			ret = pfnProtArea(pszArea, UNPROT_DRIVER, 0, PROT_PASSWORD, FLAG_IMME);
			if (0 != ret)
			{
				m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("pfnProtArea:UNPROT_DRIVER,FLAG_IMME RetCode:%d"),ret);
				
				ret = pfnProtArea(pszArea, UNPROT_DRIVER, 0, PROT_PASSWORD, FLAG_REBOOT);
				if (ret == 0)				
					ShutDown(true);				
				else
					m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("pfnProtArea:UNPROT_DRIVER,FLAG_REBOOT RetCode:%d"),ret);
			}
		}

		//�ػ��������ػ�
		bool ShutDown(bool bReBoot = true)
		{
			HANDLE hToken; 
			TOKEN_PRIVILEGES tkp; 

			if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
				return false; 

			LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); 

			tkp.PrivilegeCount = 1; 
			tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 	
			AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0); 	

			ExitWindowsEx(bReBoot ? EWX_REBOOT|EWX_FORCE : EWX_SHUTDOWN|EWX_FORCE, 0);
			return true;
		}
		
		void CreateProtDiskService(LPCTSTR lpszSvrName)
		{
			#define PROTDISKFILE	TEXT("ProtDisk.sys")
			SC_HANDLE   schSCManager;
			schSCManager = OpenSCManager(
				NULL,                   // machine (NULL == local)
				NULL,                   // database (NULL == default)
				SC_MANAGER_CONNECT | SC_MANAGER_CREATE_SERVICE  // access required
				);
			if (schSCManager == NULL)
				return ;

			TCHAR szModule[MAX_PATH] = {0};
 			//GetModuleFileName(NULL, szModule, MAX_PATH);
 			//PathRemoveFileSpec(szModule);
 			//PathAddBackslash(szModule);
			GetSystemDirectory(szModule, MAX_PATH);
			PathAddBackslash(szModule);
			lstrcat(szModule, "drivers\\ProtDisk.sys");
 		//	lstrcat(szModule, PROTDISKFILE);			

			SC_HANDLE schService = CreateService(schSCManager,lpszSvrName,lpszSvrName,SERVICE_ALL_ACCESS,SERVICE_KERNEL_DRIVER,SERVICE_SYSTEM_START,SERVICE_ERROR_IGNORE,szModule,NULL,NULL,NULL,NULL,NULL);
			if (schService == NULL)
				m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("CreateService ProtDisk fail! ErrCode:%d"),GetLastError());
			else
				::CloseServiceHandle(schService);

			::CloseServiceHandle(schSCManager); 

			return ;
		}
	};
}
#endif