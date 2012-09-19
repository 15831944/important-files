
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����

#include "process.h"

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxcview.h>

#include "Shlwapi.h"
#include "Dbghelp.h"
#include "Winsvc.h"
#include "Psapi.h"
#include "Tlhelp32.h"
#pragma comment (lib,"Shlwapi.lib")
#pragma comment (lib,"Dbghelp.lib")
#pragma comment (lib,"Psapi.lib")
#include "string"
 using namespace std;



#define STR_VDISKINFOVIEW		_T("��������Ϣ")
#define STR_UPDATEGAMEINFO		_T("����������Ϣ")
#define STR_SYNCGAMEINFO		_T("ͬ����Ϸ��Ϣ")
#define STR_LONGVIEW			_T("��־��Ϣ")
enum TUserData
{
	NODE_VDISK,
	NODE_UPDATEGAME,
	NODE_SYNCGAME
};

#define NET_CMD_INTERACT_GUI		0x0400
#define NET_CMD_SYNCLOG				0x0401
#define NET_CMD_GETSYNCGAMEINFO			0x0402
#define NET_CMD_GETCONNECTINFO			0x0403
#define NET_CMD_IMMUPDATEALLGAME		0x0404
#define NET_CMD_REFRESHGUI				0x0405
#define NET_CMD_ENDSYNCGAME				0x0406

typedef struct tagVDInfo
{
	DWORD dwIp;
	WORD  nPort;
	TCHAR szSvrDrv;
	TCHAR szCliDrv;
	DWORD dwConnect;
	DWORD dwVersion;//(time_t);
	TCHAR szTempDir[MAX_PATH];
}tagVDInfo;
struct FastCopyStatus
{
	DWORD   Progress;					//���µĽ׶Ρ�
	DWORD   StartType;					//���ɹ����º󣬲˵��Ǵ����������������Ǵӱ���������

	DWORD	TotalUpdateFile;			//�ܹ���Ҫ�����ļ�����
	DWORD	UpdateFile;					//�������µ��ļ�����

	DWORD   CurProgress;				//��ǰ�ļ��Ľ���.
	DWORD   TotalProgress;				//������ȡ�

	DWORD   AverageSpeed;				//ƽ���ٶ�
	DWORD   UsedSecond;					//���¼������˶����롣

	DWORD   LeftSecond;					//����Ҫ�����롣

	__int64 TotalFileSize;				//�ܹ���Ҫ���µ��ֽ�����//���ռ䲻��ʱ�����ֵ�Ǹ��߲˵���Ҫɾ�����ֽ�������Ӧ���Ǵ��ڵ�������Ҫ���µ��ֽ�����
	__int64 UpdateFizeSize;				//�������ֽ�����

	char 	szCurFile[260];		//��ǰ���ڲ������ļ�.����д������Ǵ�����Ϣ.
};

struct FastCopyStatusEx: public FastCopyStatus
{

	bool bConnect;
	DWORD gid;
	char GameName[MAX_PATH];
};

typedef struct tagUpdataInfo
{

	DWORD dwip;
	DWORD gid;
	DWORD speed;
	DWORD progress;
	DWORD64 uptsize;
	DWORD64 leftsize;
	char Name[64];

}UpdataInfo;



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


