#pragma once

#include <fltuser.h>
#include <strsafe.h>
#include <WinSvc.h>
#include <Tlhelp32.h>
#include <Psapi.h>
#include <Iphlpapi.h.>
#include <string>
#include <vector>
#include "Markup.h"
#include "../include/dbengine.h"
using namespace std;

#pragma comment(lib, "fltLib.lib")
#pragma comment(lib, "fltMgr.lib")
#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "Iphlpapi.lib")

#pragma pack(1)
//��������
enum ATTACH_TYPE
{ 
	ATTACH_NONE = 0,			                      // �޹�����Ϊ
	GATEWAY_ARP_QUERY_ATTACH,                         // α�����ز�ѯ������
	GATEWAY_ARP_REPLY_ATTACH,                         // α�����ػ�Ӧ������
	LAN_SAMEIP_ATTACH,		                          // ������IP��ͻ����
	WAN_SAMEIP_ATTACH,		                          // ������IP��ͻ����
	WRONG_PROTOCOL_ATTACH,	                          // �����Э�鹥��
	UNKNOWN_ATTACH
};

//IP MAC�ṹ
typedef struct  _IP_MAC
{
	DWORD                   Ip;                       //IP��ַ
	BYTE                    Mac[6];                   //MAC��ַ��������"-"
}IP_MAC, *PIP_MAC;

//������Ϣ
typedef struct _ATTACK_INFO
{
    ATTACH_TYPE             AType;                    //��������
	BYTE                    AttackByMac[6];           //����ԴMAC
	BYTE                    AttackByIp[6];            //����ԴIP
}ATTACK_INFO, *PATTACK_INFO;
#pragma pack ()

//���ߺ���

BOOL InstallDriver(LPCTSTR lpFileName, LPCTSTR lpServiceName);
FARPROC WINAPI GetArpModProcAddress(int nIndex);

//��ʼ��ARP�Ļص���������
typedef void (__stdcall *ARP_ATTACK_CALLBACK)(PATTACK_INFO AttackInfo, BOOL IsKnownIP);

//��̬����

//ARP���������ӿ����Ͷ���
//typedef BOOL (__stdcall *PFNINITARPMOD)(ARP_ATTACK_CALLBACK pfnAttackCallback, PIP_MAC LocalIpMac, DWORD Count, PIP_MAC GatewayIpMac);
//typedef BOOL (__stdcall *PFNARPMODISOK)();
//typedef BOOL (__stdcall *PFNSTARTPROTECT)();
//typedef BOOL (__stdcall *PFNDISABLESIGN)();
//typedef BOOL (__stdcall *PFNENABLESIGN)();
//typedef BOOL (__stdcall *PFNINSTALLDRIVER)();
//typedef BOOL (__stdcall *PFNREMOVEDRIVER)();
//typedef BOOL (__stdcall *PFNGETGATEWAYMAC)(DWORD GatewayAddr, char MacAddr[]);
//typedef BOOL (__stdcall *PFNSTOPPROTECT)();
//
////ARP�����ӿڵ���
//BOOL __stdcall InitArpMod(ARP_ATTACK_CALLBACK pfnAttackCallback, PIP_MAC LocalIpMac, DWORD Count, PIP_MAC GatewayIpMac);
//BOOL __stdcall ArpModIsOK();
//BOOL __stdcall StartProtect();
//void __stdcall DisableSign();
//void __stdcall EnableSign();
//BOOL __stdcall InstallDriver();
//BOOL __stdcall RemoveDriver();
//BOOL __stdcall GetGatewayMac(DWORD GatewayAddr, char MacAddr[]);
//BOOL __stdcall StopProtect();
//void __stdcall UnInitArpMod();

//��̬����
__declspec(dllimport) BOOL __stdcall InitArpMod(ARP_ATTACK_CALLBACK pfnAttackCallback, PIP_MAC LocalIpMac, DWORD Count, PIP_MAC GatewayIpMac);
__declspec(dllimport) BOOL __stdcall ArpModIsOK();
__declspec(dllimport) BOOL __stdcall StartProtect();
__declspec(dllimport) void __stdcall DisableSign();
__declspec(dllimport) void __stdcall EnableSign();
__declspec(dllimport) BOOL __stdcall InstallDriver();
__declspec(dllimport) BOOL __stdcall RemoveDriver();
__declspec(dllimport) BOOL __stdcall StopProtect();
__declspec(dllimport) BOOL __stdcall GetGatewayMac(DWORD GatewayAddr, char* pMac);

#define KeyCAD                       TEXT("Ctrl + Alt + Del")
#define KeyAT                        TEXT("Alt + Tab")
#define KeyWin                       TEXT("Win")
#define KeyCE                        TEXT("Ctrl + Esc");

//���̣�ע�����
interface  IGuardEngine
{
	//
	// ���ӵ��������棬��ȫ��֤
	//
	virtual bool __stdcall  Connect(DWORD Seed) = 0;

	//
	// ���������߽��̲����򿪣�����ɱ��
	//
	virtual bool __stdcall  ProtectMe() = 0;

	//
	// ��������Ƿ�������
	//
	virtual DWORD __stdcall Subsist() = 0;

	//
	// ����ָ������
	//
	virtual bool __stdcall  TerminateProcess(DWORD Pid) = 0;

	//
	// �����ӿڣ�����ͻ���ר�ýӿڣ�������һ��ʱ����û���յ�����ʱ��������
	//
	virtual bool __stdcall  ClientLiveIt() = 0;

	//
	// �ر��������
	//
	virtual bool __stdcall  DisableLiveCheck() = 0;

	//
	// ֪ͨ�����������������
	//
	virtual bool __stdcall  RebootNotify() = 0;

	//
	// ����ϵͳ
	//
	virtual bool __stdcall  Reboot() = 0;

	//
	// ע�����������ָ��λ�õ�ע����ֵ�Ƿ��д
	//
	virtual bool __stdcall  RegKeyCanWrite(bool CanWrite, HKEY RootKey,	LPCTSTR Key) = 0;

	//
	// ���ΰ��� 
	//
	//virtual bool __stdcall  DisableKey(tstring Keys[]) = 0;

	//
	// ��������, ע�⣺���ݿ��С������2Kb����
	//
	virtual bool __stdcall  SetData(TCHAR Data[], DWORD DataLength) = 0;

	//
	// ��ȡ����, ע��: ���ݿ��С������2Kb����
	//
	virtual bool __stdcall  GetData(TCHAR Data[], DWORD DataLength) = 0;        
};

//
// �õ����������һ��ʵ������
//
IGuardEngine* __stdcall GuardEngineInstance();

//
// ��ȡһ����ȫ��֤���ӣ��������ӵ����������ʱ��
//
DWORD __stdcall GetAuthSeed();

class TGuardEngine : public IGuardEngine
{
public:
	TGuardEngine(){ GEHandle = INVALID_HANDLE_VALUE;}
	virtual ~TGuardEngine()
	{ 
		if (GEHandle != INVALID_HANDLE_VALUE)
	    {
			CloseHandle(GEHandle);
			GEHandle = INVALID_HANDLE_VALUE;
	    }
	}

public:
	//
	// ���ӵ��������棬��ȫ��֤
	//
	bool __stdcall  Connect(DWORD Seed);

	//
	// ���������߽��̲����򿪣�����ɱ��
	//
	bool __stdcall  ProtectMe();

	//
	// ��������Ƿ�������
	//
	DWORD __stdcall Subsist();

	//
	// ����ָ������
	//
	bool __stdcall  TerminateProcess(DWORD Pid);

	//
	// �����ӿڣ�����ͻ���ר�ýӿڣ�������һ��ʱ����û���յ�����ʱ��������
	//
	bool __stdcall  ClientLiveIt();

	//
	// �ر��������
	//
	bool __stdcall  DisableLiveCheck();

	//
	// ֪ͨ�����������������
	//
	bool __stdcall  RebootNotify();

	//
	// ����ϵͳ
	//
	bool __stdcall  Reboot();

	//
	// ע�����������ָ��λ�õ�ע����ֵ�Ƿ��д
	//
	bool __stdcall  RegKeyCanWrite(bool CanWrite, HKEY RootKey,	LPCTSTR Key);

	//
	// ���ΰ��� 
	//
	//bool __stdcall  DisableKey(tstring Keys[]);

	//
	// ��������, ע�⣺���ݿ��С������2Kb����
	//
	bool __stdcall  SetData(TCHAR Data[], DWORD DataLength);

	//
	// ��ȡ����, ע��: ���ݿ��С������2Kb����
	//
	bool __stdcall  GetData(TCHAR Data[], DWORD DataLength);        

protected:
	HANDLE                     GEHandle;
};

#pragma pack(1)
typedef struct TParams
{
	DWORD                      CtlCode;
	DWORD                      InputBufferLength;
	void                       *InputBuffer;
	DWORD                      OutputBufferLength;
	void                       *OutputBuffer;
	DWORD                      *BytesReturned;
}*PParams;

typedef struct TProtSetting
{
	DWORD                      ProtMaskCode;
}*PProtSetting;

typedef struct TRegKeyProt 
{
	DWORD                      CanWrite;
	char                       RegKey[MAX_PATH];
}PRegKeyProt;

#pragma pack()
#define SID_REVISION           (1)
#define METHOD_BUFFERED         0 
#define METHOD_IN_DIRECT        1 
#define METHOD_OUT_DIRECT       2 
#define METHOD_NEITHER          3 

#define FILE_ANY_ACCESS         0 

#define IOCTL_INIT              0x00010001
#define IOCTL_PROT_ME           0x00010002
#define IOCTL_DRV_SUBSIST       0x00010003
#define IOCTL_GET_LOG           0x00010004
#define IOCTL_ADD_LOG           0x00010006

#define IOCTL_END_PROCESS       0x00010007
#define IOCTL_CHECK_LIVE_IT     0x00010008
#define IOCTL_REBOOT            0x00010009

#define IOCTL_REGKEY_CAN_WRITE  0x00010010
#define IOCTL_NOTIFY_SHUTDOWN   0x00010011

#define IOCTL_SET_DATA          0x00020001
#define IOCTL_GET_DATA          0x00020002

#define IOCTL_DISABLE_CHECK_LIVE_IT 0x00030001

#define PROT_INITED             0x00000001
#define PROT_MASK_PROCESS       0x00000002

#define ICAFE_GUARD_TYPE        50000


//DWORD __stdcall CTL_CODE( WORD DeviceType, WORD Function, WORD Method, WORD Access );
IGuardEngine* __stdcall GuardEngineInstance();
DWORD __stdcall GetAuthSeed();

void FreeTokenInformation(void* Buffer);
void QueryTokenInformation(HANDLE Token, TOKEN_INFORMATION_CLASS InformationClass, void** Buffer);
char* SIDToString(PSID ASID);
string RegKeyToKernelRegKey( HKEY RootKey, LPCTSTR Key);

//�ļ�����
#define STATUS_NOPROTECT_ACTIVE        0x00000000; // û�б�����Ч
#define STATUS_FILEPROTECT_ACTIVE      0x00000001; // �ļ�������Ч
#define STATUS_FOLDERPROTECT_ACTIVE    0x00000002; // �ļ��б�����Ч
#define STATUS_TIMEPROTECT_ACTIVE      0x00000004; // ʱ�䱣����Ч
#define STATUS_PROCESSPROTECT_ACTIVE   0x00000008; // ���̱�����Ч

#define FILE_ATTR_DENY_ALL             0x00000001; // �ܾ�����
#define FILE_ATTR_READ_ONLY            0x00000002; // ֻ��
#define FILE_ATTR_DENY_DELETE          0x00000004; // ��ֹɾ��
#define FILE_ATTR_HIDE                 0x00000008; // ����

#pragma pack(1)
enum TSniperCommand
{
	cmdAddRuleFile,
	cmdAddRuleFolder,
	cmdAddRuleProcess,

	cmdFileProtStart,
	cmdFileProtStop,

	cmdFolderProtStart,
	cmdFolderProtStop,

	cmdProcessProtStart,
	cmdProcessProtStop,

	cmdClearRuleFile,
	cmdClearRuleFolder,
	cmdClearRuleProcess,

	cmdAddTrustedApp,

	cmdClearTrustedApp,

	cmdEnableTimeProt,
	cmdDisableTimeProt,

	cmdSetTime,

	cmdTerminateProcess,

	cmdGetProcesses, // ��ȡ�����б�
	cmdGetDrivers,   // ��ȡ�����б�

	cmdGetStatus
};

enum TSniperRuleType
{
	RuleTypeFile,
	RuleTypeFolder,
	RuleTypeTrustedApp,
	RuleTypeProcess,
	RULE_COUNT
};

enum TSniperFilenameType
{
	FileNameTypeFull,     // ����·��������·��
	FileNameTypeRelative, // ���·��
	FileNameTypeOnly      // ֻ���ļ���
};

enum TSniperFolderType
{
	FolderNameTypeFull,
	FolderNameTypeOnly
};

typedef struct TRuleFile
{
    char                   FileName[MAX_PATH * 2];
    TSniperFilenameType    FileNameType;
    DWORD                  Attributes;
}*PRuleFile;

typedef struct TRuleFolder
{
	char                   FolderName[MAX_PATH * 2];
	TSniperFolderType      FolderNameType;
	DWORD                  Attributes;
}*PRuleFolder;

typedef struct TRuleTrustedApp
{
	char                   ImageName[MAX_PATH];
}*PRuleTrustedApp;

typedef struct TRuleProcess
{
	char                   ImageName[MAX_PATH];
	TSniperFilenameType    FileNameType;
}*PRuleProcess;

typedef struct TCommandMessage 
{
    TSniperCommand         Command;
    DWORD                  Reserved;
    char                   Data[1];
}*PCommandMessage;

typedef struct TRuleDetail
{
	union 
	{
	    TRuleFile          RuleFile ;
	    TRuleFolder        RuleFolder;
	    TRuleTrustedApp    RuleTrustedApp;
	    TRuleProcess       RuleProcessProt;
	};
}*PRuleDetail;

typedef struct TDriverInfoEntry
{
    DWORD                  NextEntry;
    TCHAR                  BaseName[MAX_PATH];
    TCHAR                  FullName[MAX_PATH];
    DWORD                  DllBase;
    DWORD                  SizeOfImage;
}*PDriverInfoEntry;

typedef struct TProcessInfoEntry
{
    DWORD                  NextEntry;
    DWORD                  Pid;
    char                   ImageName[16];
    char                   CommandLine[260];
}*PProcessInfoEntry;

#pragma pack()

interface IISecEngine
{
	//
	// ���ӵ��������棬��ȫ��֤
	//
	virtual bool __stdcall Connect(DWORD Seed) = 0;

	//
	// �Ƿ����ӵ���������
	//
	virtual bool __stdcall IsConnected() = 0;

	//
	// �ļ�����ֹͣ
	//
	virtual bool __stdcall FileProtStop() = 0;

	//
	// �ļ���������
	//
	virtual bool __stdcall FileProtResume() = 0;

	//
	// �ļ��б���ֹͣ
	//
	virtual bool __stdcall FolderProtStop() = 0;

	//
	// �ļ��б�������
	//
	virtual bool __stdcall FolderProtResume() = 0;

	//
	// ���̱���ֹͣ
	//
	virtual bool __stdcall ProcessProtStop() = 0;

	//
	// ���̱�������
	//
	virtual bool __stdcall ProcessProtResume() = 0;

	//
	// ����һ���ļ���������
	//
	virtual bool __stdcall AddRuleFile(const string FileName, DWORD ProtectAttributes) = 0;

	//
	// ����һ���ļ��б�������
	//
	virtual bool __stdcall AddRuleFolder(const string FolderName, DWORD ProtectAttributes) = 0;

	//
	// ������̱�������
	//
	virtual bool __stdcall AddRuleProcess(const string ProcessName) = 0;

	//
	// ����һ�������ε�Ӧ�ó���
	//
	virtual bool __stdcall AddTrustedApp(const string FileName) = 0;

	//
	// ����ļ���������
	//
	virtual bool __stdcall ClearRuleFile() = 0;

	//
	// ����ļ��б�������
	//
	virtual bool __stdcall ClearRuleFolder() = 0;

	//
	// ������̱�������
	//
	virtual bool __stdcall ClearRuleProcess() = 0;

	//
	// ������γ���
	//
	virtual bool __stdcall ClearTrustedApp() = 0;

	//
	// ����ʱ�䱣��
	//
	virtual bool __stdcall EnabledTimeProtect() = 0;

	//
	// �ر�ʱ�䱣��
	//
	virtual bool __stdcall DisableTimeProtect() = 0;

	//
	// �޸�����ʱ��
	//
	virtual bool __stdcall SetDateTime(SYSTEMTIME sysDateTime ) = 0;

	//
	// ����ָ������
	//
	virtual bool __stdcall TerminateProcess(DWORD Pid) = 0;

	//
	// ��ȡ�����б�
	//
	virtual bool __stdcall EnumDrivers(PDriverInfoEntry DriversInfo,
                           DWORD DriversInfoLength, DWORD &ReturnLength) = 0;

	//
	// ��ȡ�����б�
	virtual bool __stdcall EnumProcesses(PProcessInfoEntry ProcessInfo,
                           DWORD ProcessInfoLength, DWORD &ReturnLength) = 0;

	//
	//
	// ȡ�õ�ǰ��״̬, ����ֵ����Ϊ���״ֵ̬�����
	//
	virtual DWORD __stdcall GetStatus() = 0;
};

class TISecEngine : public IISecEngine
{
public:
	TISecEngine(){ Port = INVALID_HANDLE_VALUE;}
	virtual ~TISecEngine()
	{
		if (Port != INVALID_HANDLE_VALUE)
		{
			CloseHandle(Port);
			Port = INVALID_HANDLE_VALUE;
		}
	}

protected:
	HANDLE                  Port;

private:
	string __stdcall   FileNameToNtName(const string FileName);
	bool __stdcall     IsFullPath(const string FileName);
	bool __stdcall     IsRelativePath(const string FileName);
public:
	//
	// ���ӵ��������棬��ȫ��֤
	//
	bool __stdcall Connect(DWORD Seed);

	//
	// �Ƿ����ӵ���������
	//
	bool __stdcall IsConnected();

	//
	// �ļ�����ֹͣ
	//
	bool __stdcall FileProtStop();

	//
	// �ļ���������
	//
	bool __stdcall FileProtResume();

	//
	// �ļ��б���ֹͣ
	//
	bool __stdcall FolderProtStop();

	//
	// �ļ��б�������
	//
	bool __stdcall FolderProtResume();

	//
	// ���̱���ֹͣ
	//
	bool __stdcall ProcessProtStop();

	//
	// ���̱�������
	//
	bool __stdcall ProcessProtResume();

	//
	// ����һ���ļ���������
	//
	bool __stdcall AddRuleFile(const string FileName, DWORD ProtectAttributes);

	//
	// ����һ���ļ��б�������
	//
	bool __stdcall AddRuleFolder(const string FolderName, DWORD ProtectAttributes);

	//
	// ������̱�������
	//
	bool __stdcall AddRuleProcess(const string ProcessName);

	//
	// ����һ�������ε�Ӧ�ó���
	//
	bool __stdcall AddTrustedApp(const string FileName);

	//
	// ����ļ���������
	//
	bool __stdcall ClearRuleFile();

	//
	// ����ļ��б�������
	//
	bool __stdcall ClearRuleFolder();

	//
	// ������̱�������
	//
	bool __stdcall ClearRuleProcess();

	//
	// ������γ���
	//
	bool __stdcall ClearTrustedApp();

	//
	// ����ʱ�䱣��
	//
	bool __stdcall EnabledTimeProtect();

	//
	// �ر�ʱ�䱣��
	//
	bool __stdcall DisableTimeProtect();

	//
	// �޸�����ʱ��
	//
	bool __stdcall SetDateTime(SYSTEMTIME sysDateTime );

	//
	// ����ָ������
	//
	bool __stdcall TerminateProcess(DWORD Pid);

	//
	// ��ȡ�����б�
	//
	bool __stdcall EnumDrivers(PDriverInfoEntry DriversInfo,
		DWORD DriversInfoLength, DWORD &ReturnLength);

	//
	// ��ȡ�����б�
	bool __stdcall EnumProcesses(PProcessInfoEntry ProcessInfo,
		DWORD ProcessInfoLength, DWORD &ReturnLength);

	//
	//
	// ȡ�õ�ǰ��״̬, ����ֵ����Ϊ���״ֵ̬�����
	//
	DWORD __stdcall GetStatus();
};
IISecEngine* ISecEngineInstance();

//DWORD        GetAuthSeed()
//{
//    DWORD Result = GetCurrentProcessId();
//    Result = (Result << 3);
//    Result = (Result ^ 0x65438088);
//	return Result;
//}


// ���ڲ�ɱ�����̲�ɱ
#define    POOLINGTIME  1 * 1000 
#pragma pack(1)
enum TOperType
{
	uAdd,
	uDel,
	uClear
};
enum TDataType
{
	uProc,
	uWindows
};

typedef struct TMsgBuffer
{
    TOperType    OperType;
    TDataType    DataType;
    char*        Buffer;
    int          BufferLen;
    TMsgBuffer*  Next;
}*PMsgBuffer;

typedef struct TProhiProc 
{
	char    ProcessName[50];
	char    ProcessPath[1000];
}*PProhiProc;

typedef struct TProhiWindows 
{
	char    WindowsName[50];
}*PProhiWindows;

typedef struct TProcessInfo
{
    HANDLE  ProcessHandle;
    string  ProcessName;
    string  ProcessFillName;
}*PProcessInfo;

typedef struct TWindowsInfo
{
    char  WindowsName[MAX_PATH];
}*PWindowsInfo;
#pragma pack()

//���ٴ���
void DisposeWindow(char* Buf);
//���ٽ���
void DisposeProc(char* Buf);

//���ٽ�������
void DisposeProcList(char* Buf);
BOOL CALLBACK EnumWindowsFunc(HWND Handle, LPARAM Param);
void DisposeWinInfo(char* Buf);


class TProhiThread
{
public:
	TProhiThread();
	virtual~ TProhiThread();

private:
	void AddInfo(TDataType DataType, char* Buffer, int Bufferlen);
	void DelInfo(TDataType DataType, char* Buffer, int Bufferlen);
	void Clear(TDataType DataType);
	void PollingTask();
	void AddQueue(TOperType OperType, TDataType DataType, char* Data, int Datalen);
	void GetExeNameList(vector<PProcessInfo>& ProcessName);
	void CloseWindows();
	void CloseProc();

public:
	vector<PWindowsInfo> m_WndList;
	static UINT __stdcall ExecuteWorkThread(LPVOID lpVoid);
	void Execute();
	void Start();
	void Stop();

public:
	HANDLE	   m_hThread;
    HANDLE     FEvent;
    CRITICAL_SECTION FCS;
	PMsgBuffer FFirst;
    PMsgBuffer FLast;
    DWORD      FTick;
	vector<PProhiProc> FProhiProcList;
    vector<PProhiWindows> FProhiWindowsList; //��ֹ���̺ʹ����б�

public:
	void ClearData(TDataType DataType);
	void AddData(TDataType DataType, string Name, string Path);
	void DelData(TDataType DataType, string Name, string Path);
};


void __stdcall Arp_Attck_Callback(PATTACK_INFO AttackInfo, BOOL IsKnownIP);
//��ȫ������
class CSafeCenter
{
	//����/����
public:
	CSafeCenter();
	virtual ~CSafeCenter();

public:
	//��ȡ�����ļ�
	BOOL		ReadConfig(LPCTSTR lpFilePath);
	//������ȫ����
	BOOL        Start();
	//ֹͣ��ȫ����
	BOOL        Stop();
	//�Ƿ�����
	BOOL        IsRun(){return m_bIsStart;}

protected:
	//����ARP����
	BOOL        StartArpProtect();
	//�ر�ARP����
	BOOL        StopArpProtect();
	//�������ڽ��̲�ɱ
	BOOL        StartWndProcDetect();
	//�رմ��ڽ��̲�ɱ
	BOOL        StopWndProcDetect();

private:
	BOOL        GetLocalIpMac(IP_MAC LocalAddr[], int &iCount);
	BOOL        GetGatewayAddr();
	BOOL        ParserMacToByte(string strMac, BYTE cbMac[]);
private:
	//���ڽ��̲�ɱ��
    TProhiThread                 m_KillWndProc;
    //�Ƿ�����ARP����
    BOOL                         m_bIsStartARP;
	BOOL                         m_bIsStart;
	BOOL                         m_bIsAutoGetGateAddr;
	//����IP
	IP_MAC                       m_GateAddr;
};

