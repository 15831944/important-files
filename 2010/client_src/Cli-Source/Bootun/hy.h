#ifndef _HY_H_
#define _HY_H_

#pragma pack(1)
typedef struct tag_MOUNT_PACK
{
	LONGLONG qwStartSec;
	LONGLONG qwSecs;
	DWORD  dwDiskNumber;
	char  szDosDevice[MAX_PATH];
}MOUNTPACK, *LPMOUNTPACK;
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

//������дһ����Ҫ��������ݣ� ��С0x100 BYTE��������ݱ����ǣ������ֽڵĻ���ռ䣬��Ӧ�ó������д˽�����ݵ��������棬Ҳ���Զ�������
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
typedef int (WINAPI *PFNGETMOUNTINFO)( MOUNTPACK *lpMountPack, char *szPassword );

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

#define PROT_DLL_NAME		"wxProt.dll"
#define PROT_PASSWORD		"ST3F95Xfhu9rBqBh"

HMODULE						_hModule = NULL;
PFNINSTALL4DOSCHAR 			pfnInstall4DosChar = NULL;
PFNGETDRIVESTATE			pfnGetDriveState = NULL;
PFNUNINSTALLDRIVER			pfnUnInstallDriver = NULL;
PFNDRIVERISPROTECTED		pfnDriverIsProtected = NULL;	   
PFNCHECKPASSWORD			pfnCheckPassword = NULL;
PFNCHANGEPASSWORD			pfnChangePassword = NULL;
PFNRWAPDATA					pfnRWAPData = NULL;
PFNSETPROTECTAREAFORDOSCHAR pfnProtArea = NULL;
PFNGETPROTECTEDDRIVES		pfnGetProtectDrivers = NULL;
PFNMOUNTPTDOSCHAR			pfnMountDosChar = NULL;				
PFNUMOUNTPTDOSCHAR			pfnUMountDosChar = NULL;

inline bool CheckBeforeOperator()
{
	if (pfnGetDriveState() == 0)
	{
		if (pfnCheckPassword("") == 0)
			pfnChangePassword("", PROT_PASSWORD);
		return true;
	}
	return false;
}
	
inline bool Initialize()
{
	char szModule[MAX_PATH] = {0};
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
			pfnUMountDosChar		!= NULL )
		return true;
	}
	else
	{
//		SDG_WriteLog("load %s fail:%d", PROT_DLL_NAME, GetLastError());
	}
	return false;
}

inline void UnInitialize()
{
	if (_hModule != NULL)
		FreeLibrary(_hModule);
}

#endif
