#pragma once

#include "Extend STL/UnicodeStl.h"

#define PROT_DLL_NAME    TEXT("wxProt.dll")
#define PROT_PASSWORD    "ST3F95Xfhu9rBqBh"

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
    BYTE    bState;
    BYTE    bCmd;
    BYTE    bCmdAtOnce;
    BYTE    bModifyOutside;
    DWORD    dwStartSec;
    DWORD    dwSecs;
    DWORD    dwDiskNumber;

    DWORD    dwBitmapNotUsedBits;
    DWORD    dwBitmapOldUsedBits;
    DWORD    dwBitmapNewUsedBits;
    DWORD    dwBitmapTmpUsedBits;
}PROTECTAREA_INFO, *LPPROTECTAREA_INFO;

#define MAX_PROTECTAREA_NUMS    100
typedef struct tag_PROTECTAREA_PACK
{
    DWORD    dwInOrOut;
    DWORD    dwNums;
    DWORD    dwReseave[2];
    char    szPassword[256];
    PROTECTAREA_INFO    Area[MAX_PROTECTAREA_NUMS];
}PROTECTAREA_PACK, *LPPROTECTAREA_PACK;

typedef struct tag_PtInfo
{
    DWORD    dwStartSec;    //�˷����ľ��Կ�ʼ����
    DWORD    dwSecs;        //�˷����Ĵ�С��������
    DWORD    dwUsedSecs;    //�˷����Ѿ���ʹ�õ�������
    BYTE    bFsType;        //�˷����ķ�������
    BYTE    bIsMaster;    //�˷��Ƿ�Ϊ��������1��ʾ��������0��ʾ��������
    BYTE    bIsActive;    //�˷����Ƿ�Ϊ�������1��ʾ�������0��ʾΪ�ǻ����
    BYTE    bDosChar;    //�˷������̷���Ϊ�̷���ASCIIֵ���磬C��ASCIIֵΪ67
    char    szVolume[256];    //�˷����ľ��
}PTINFO, *LPPTINFO;    

#define MAX_PTS     100
typedef struct tag_HDInfo
{
    DWORD    dwHdNumber;        //��Ӳ����ϵͳ�е��豸˳���
    DWORD    dwSecs;            //��Ӳ�̵Ĵ�С��������
    DWORD    dwReseave;        //����
    DWORD    dwPtNums;        //��Ӳ�̵ķ�������
    PTINFO    pt[MAX_PTS];    //������Ϣ����
}HD, *LPHD;

#pragma pack()

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
#define PROT_DRIVER        1
#define UNPROT_DRIVER    3
#define FLAG_REBOOT        0
#define FLAG_IMME        1
typedef int (WINAPI *PFNSETPROTECTAREAFORDOSCHAR)(
    LPCSTR szDosCharList, //Ҫ�������̷��б��硰CDEF��
    int iState /*0:����(�ֶ���ԭ)��1:����(���������ݱ��Զ���ԭ)��3:������*/,
    int iCmd, //0:�޲�����1:��ԭ��2:�������ݣ�ˢ�����ݵ����̣�
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

class CHyOperator
{
public:
    CHyOperator(BOOL bDisableUnloadVDisk = TRUE);
    ~CHyOperator();

    //��ԭ��ز���
public:
    BOOL IsInitialize();
    BOOL IsInstallHy();                                              //��ԭ�Ƿ�װ    
    BOOL InstallHy(LPCTSTR szProtectList);                            //��װ��ԭ    
    BOOL UnInstallHy();                                              //ж�ػ�ԭ
    int  GetHDInfo(LPHD lphd );                                      //��ȡӲ����Ϣ��
    BOOL IsDriverProtected(LPCTSTR lpszArea);                        //�����Ƿ񱣻���
    BOOL IsDriverProtected(TCHAR chDriver);
    BOOL ProtectDriver(LPCTSTR lpszArea, BOOL* pbNeedRestart = NULL); //��������
    BOOL UnProtectDriver(LPCTSTR lpszArea, BOOL* pbNeedRestart = NULL); //ȡ����������
    void CreateProtDiskService(LPCTSTR lpszSvrName);
    BOOL IsAnyDriverProt();                                          //�д��̴��ڻ�ԭ������
    BOOL ShutdownComputer(BOOL bReboot);
    BOOL LoadVirtualDevice(TCHAR drv);
    BOOL UnloadVirtualDevice(TCHAR drv);
    BOOL LoadVirtualDeviceEx(TCHAR drv, LPCTSTR pVirtualDeviceName);
    BOOL UnloadVirtualDeviceEx(TCHAR drv, LPCTSTR pVirtualDeviceName);
    BOOL LoadVDevice(TCHAR drv);
    BOOL UnloadVDevice(TCHAR drv);
    stdex::tString ConvertPath(LPCTSTR lpszPath);
    BOOL GetDiskRoomSize(TCHAR drv, PLARGE_INTEGER pliSize);
    BOOL RefreshDirectory(LPCTSTR dir);
    BOOL RefreshDriver(TCHAR drv);
    BOOL IsVirtualDeviceExist(TCHAR drv);
    BOOL ProtectFile(LPCTSTR lpszFile);
    BOOL DeleteFile(LPCTSTR lpszFile);
    BOOL DeleteDirectory(LPCTSTR pPath);
    BOOL MakeSureDirectoryPathExists(const std::wstring& dir);
protected:
    std::string GetVirtualDeviceName(TCHAR drv);
    std::string GetDriverName(TCHAR drv);
private:        
    
    PFNINSTALL4DOSCHAR                    pfnInstall4DosChar;
    PFNGETDRIVESTATE                   pfnGetDriveState;
    PFNUNINSTALLDRIVER                   pfnUnInstallDriver;
    PFNDRIVERISPROTECTED               pfnDriverIsProtected;       
    PFNCHECKPASSWORD                   pfnCheckPassword;
    PFNCHANGEPASSWORD                   pfnChangePassword;
    PFNRWAPDATA                           pfnRWAPData;
    PFNSETPROTECTAREAFORDOSCHAR        pfnProtArea;
    PFNGETPROTECTEDDRIVES               pfnGetProtectDrivers;
    PFNMOUNTPTDOSCHAR                   pfnMountDosChar;                
    PFNUMOUNTPTDOSCHAR                   pfnUMountDosChar;
    PFNGETMOUNTINFO                       pfnGetMountInfo;
    PFNGETPROTECTAREA                   pfnGetProtectArea;
    PFNGETHDINFO                       pfnGetHDInfo;
    PFNUPDATEDIR                       pfnUpdateDir;
    HMODULE                               m_hModule;
    BOOL                               m_bDisableUnloadVDisk;
};

