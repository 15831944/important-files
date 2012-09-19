#include "stdafx.h"
#include "hy.h"
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi")

#define PROT_DLL_NAMEW	L"wxProt.dll"
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
	DWORD	dwStartSec;			//�˷����ľ��Կ�ʼ����
	DWORD	dwSecs;				//�˷����Ĵ�С��������
	DWORD	dwUsedSecs;			//�˷����Ѿ���ʹ�õ�������
	BYTE	bFsType;			//�˷����ķ�������
	BYTE	bIsMaster;			//�˷��Ƿ�Ϊ��������1��ʾ��������0��ʾ��������
	BYTE	bIsActive;			//�˷����Ƿ�Ϊ�������1��ʾ�������0��ʾΪ�ǻ����
	BYTE	bDosChar;			//�˷������̷���Ϊ�̷���ASCIIֵ���磬C��ASCIIֵΪ67
	char	szVolume[256];		//�˷����ľ��
}PTINFO, *LPPTINFO;	

#define MAX_PTS	 100
typedef struct tag_HDInfo
{
	DWORD	dwHdNumber;			//��Ӳ����ϵͳ�е��豸˳���
	DWORD	dwSecs;				//��Ӳ�̵Ĵ�С��������
	DWORD	dwReseave;			//����
	DWORD	dwPtNums;			//��Ӳ�̵ķ�������
	PTINFO	pt[MAX_PTS];		//������Ϣ����
}HD, *LPHD;

#pragma pack()

//ע�����з����ַ������Ǵ�д�����ݷ��أ���ʾ�ɹ���������������ʾ����������롣

//��һ��������ʾ��װʱҪ�����ķ����б��ڶ��������õĻ�ԭ���롣������������룬����""���ַ�����
//���أ���ʾ�ɹ����ǣ��Ǵ�����롣


//��װ����������ָ���̷�:
typedef int (WINAPI *PFNINSTALL4DOSCHAR)(LPCSTR szProtectList, LPCSTR szPassword );

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

//������дһ����Ҫ��������ݣ� ��С0x100 BYTE��������ݱ����ǣ������ֽڵĻ���ռ䣬
//��Ӧ�ó������д˽�����ݵ��������棬Ҳ���Զ�������
typedef int (WINAPI *PFNRWAPDATA)(BYTE *lpBuf, BYTE isWrite );//1��ʾд������ʾ��

//���ñ�����������Ҫ���̷��б�:���أ���ʾ�ɹ���������ʾ������롣
#define PROT_DRIVER		1
#define UNPROT_DRIVER	3
#define FLAG_REBOOT		0
#define FLAG_IMME		1
typedef int (WINAPI *PFNSETPROTECTAREAFORDOSCHAR)(
	LPCSTR szDosCharList, 
	int iState /*1:��ʾ����������3��ʾȡ����������*/,
	int iCmd, //д0
	LPCSTR szPassword, //��������
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

typedef int (WINAPI * PFNUPDATEDIR)( char *lpPath );

static HMODULE _hModule = NULL;
static PFNINSTALL4DOSCHAR 			pfnInstall4DosChar		= NULL;
static PFNGETDRIVESTATE				pfnGetDriveState		= NULL;
static PFNUNINSTALLDRIVER			pfnUnInstallDriver		= NULL;
static PFNDRIVERISPROTECTED			pfnDriverIsProtected	= NULL;
static PFNCHECKPASSWORD				pfnCheckPassword		= NULL;
static PFNCHANGEPASSWORD			pfnChangePassword		= NULL;
static PFNRWAPDATA					pfnRWAPData				= NULL;
static PFNSETPROTECTAREAFORDOSCHAR	pfnProtArea				= NULL;
static PFNGETPROTECTEDDRIVES		pfnGetProtectDrivers	= NULL;
static PFNMOUNTPTDOSCHAR			pfnMountDosChar			= NULL;
static PFNUMOUNTPTDOSCHAR			pfnUMountDosChar		= NULL;
static PFNGETMOUNTINFO				pfnGetMountInfo			= NULL;
static PFNGETPROTECTAREA			pfnGetProtectArea		= NULL;
static PFNGETHDINFO					pfnGetHDInfo			= NULL;
static PFNUPDATEDIR					pfnUpdateDir			= NULL;

static bool hy_Initlialize()
{
	if (_hModule != NULL)
		return true;

	wchar_t szModule[MAX_PATH] = {0};
	GetModuleFileNameW(NULL, szModule, MAX_PATH);
	PathRemoveFileSpecW(szModule);
	PathAddBackslashW(szModule);
	wcscat_s(szModule, PROT_DLL_NAMEW);
	_hModule = LoadLibraryW(szModule);
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
		pfnUpdateDir			= (PFNUPDATEDIR)GetProcAddress(_hModule,"UpDateDir");
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
			return true;
		}
	}
	return false;
}

bool hy_DriverProtected(wchar_t drv)
{
	if (!hy_Initlialize())
		return false;
	char driver[5] = {0};
	sprintf_s(driver, "%c", (char)towupper(drv));

	if (pfnGetDriveState() == 0 && pfnDriverIsProtected(driver) == 0)
		return true;

	return false;
}

bool hy_LoadVirtualDevice(wchar_t drv)
{
	if (hy_DriverProtected(drv) && pfnMountDosChar != NULL)
	{
		char driver[20] = {0};
		char device[20] = {0};
		sprintf_s(driver, "%C", towupper(drv));
		sprintf_s(device, "I8Desk%C", towupper(drv));
		pfnMountDosChar(driver, device, PROT_PASSWORD);
		return true;
	}
	return true;
}

std::wstring hy_ConvertPath(const std::wstring& path)
{
	std::wstring file(path);
	if (file.size() > 3 && file[1] == L':' && file[2] == L'\\' && hy_DriverProtected(file[0]))
	{
		std::wstring pre = L"\\\\.\\I8Desk";
		pre += towupper(file[0]);
		file.replace(0, 2, pre);
	}
	return file;
}

bool hy_CreateDirectory(const std::wstring& dir)
{
	std::wstring::size_type pos = 3;	//X:\.(���ܴ�����Ŀ¼.����C:\)
	std::wstring::size_type len = wcslen(L"\\\\.\\I8Desk");
	if (dir.size() >= len && _wcsnicmp(dir.c_str(), L"\\\\.\\I8Desk", len) == 0)
		pos = len + 2;

	pos = dir.find(L'\\', pos);
	while (pos != dir.npos)
	{
		std::wstring sub = dir.substr(0, pos+1);
		if (!CreateDirectoryW(sub.c_str(), NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
			return false;
		pos = dir.find(L'\\', pos+1);
	}
	return true;
}

bool hy_GetDiskRoomSize(wchar_t drv, PLARGE_INTEGER pliSize)
{
	if (pliSize == NULL)
		return false;

	char driver = (char)towupper(drv);
	pliSize->QuadPart = 0;
	if (hy_DriverProtected(drv))
	{
		for (DWORD idx=0; idx<5; idx++)
		{
			tag_HDInfo hdInfo = {0};
			hdInfo.dwHdNumber = idx;
			if (0 != pfnGetHDInfo(&hdInfo))
				continue;
			
			for (DWORD loop=0; loop<hdInfo.dwPtNums; loop++)
			{
				if (hdInfo.pt[loop].bDosChar == driver)
				{
					DWORD dwStartSec = hdInfo.pt[loop].dwStartSec;
					tag_PROTECTAREA_PACK Areainfo = {0};
					if (0 != pfnGetProtectArea(&Areainfo))
						continue;
					for (DWORD iArea=0; iArea<Areainfo.dwNums; iArea++)
					{
						if (Areainfo.Area[iArea].dwStartSec == dwStartSec)
						{
							pliSize->QuadPart = (__int64)Areainfo.Area[iArea].dwBitmapNotUsedBits * 512;
							return true;
						}
					}
				}
			}
		}
	}

	wchar_t sdriver[] = L"X:\\";
	sdriver[0] = driver;
	return (TRUE == GetDiskFreeSpaceExW(sdriver, (PULARGE_INTEGER)pliSize, NULL, NULL));
}

bool hy_ExueteUpdateDir(LPCWSTR dir)
{
	if (dir != NULL && wcslen(dir) > 3 && dir[1] == L':' && 
		hy_DriverProtected(dir[0]) && pfnUpdateDir != NULL && pfnUMountDosChar!= NULL)
	{
		char path[MAX_PATH] = {0};
		WideCharToMultiByte(CP_ACP, 0, dir, -1, path, sizeof(path), NULL, NULL);

		char device[10] = {0};
		sprintf_s(device, "I8Desk%c", toupper(path[0]));
		pfnUMountDosChar(device, PROT_PASSWORD);

		bool ret = true;
		for (size_t idx=0; idx<3; idx++)
			ret = (0 == pfnUpdateDir(path));
		return ret;
	}
	return false;
}

void hy_DyncaRefreDriver(wchar_t drv)
{
	if (hy_DriverProtected(drv) && pfnUMountDosChar != NULL && pfnProtArea != NULL && pfnMountDosChar != NULL)
	{
		char driver[20] = {0};
		char device[20] = {0};
		sprintf_s(driver, "%C", towupper(drv));
		sprintf_s(device, "I8Desk%C", towupper(drv));
		
		pfnUMountDosChar(device, PROT_PASSWORD);
		pfnProtArea(driver, 1, 1, PROT_PASSWORD, FLAG_IMME);
		pfnMountDosChar(driver, device, PROT_PASSWORD);
	}
}