
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


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma warning (disable :4996)
#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
#include "..\..\defin.h"
#include "SocketEx.h"
#include "math.h"
#include "string"
#include "vector"
#include "map"
#include "algorithm"
#include "Dbghelp.h"
#include "vssym32.h"
#include "gdiplus.h"
#pragma comment(lib,"Dbghelp.lib")
#pragma comment(lib, "gdiplus.lib")
using namespace std;

using namespace Gdiplus;

enum CustomMessage
{
	WM_MSG_POSTFILE = WM_USER + 0x0100,
	WM_MSG_DOWNODFILE  =  WM_USER +  0x0101,
	WM_MSG_DELETEFILE = WM_USER + 0x0102,
	WM_MSG_PROGRESS = WM_USER + 0x0103,
	WM_MSG_SAVEGAME = WM_USER + 0x0104,
	WM_MSG_READGAME = WM_USER + 0x0105
};
typedef struct tagGameInfo
{
	DWORD	GID;//��ϷGID
	DWORD	PID;//��Ϸ������GID
	char	NAME[MAX_PATH];//��Ϸ��
	char	IDCCLASS[MAX_PATH];//��Ϸ���
	char	GAMEEXE[MAX_PATH];//��Ϸ�ٷ�EXE
	char	PARAM[MAX_PATH];//��Ϸ���в���
	DWORD	SIZE;//��Ϸ��С,��KΪ��λ
	DWORD	DESKLNK;//��Ϸ�Ƿ���ʾ�������ݷ�ʽ
	DWORD	TOOLBAR;//��Ϸ�Ƿ���ʾ���˵��Ĺ�������
	char	SVRPATH[MAX_PATH];//��Ϸ�ڷ������ϵ�·��
	char	VDPATH[MAX_PATH];//��Ϸ�ڿͻ��˵�������·��
    char	CLIPATH[MAX_PATH];//��Ϸ�ڿͻ����ϵ�·��
    DWORD   dwDeleteFlg;    //��Ϸ�ռ䲻��ʱ����ɾ��
	char	MATCHFILE[MAX_PATH];//��Ϸ�Զ����������ļ�
	char	SAVEFILTER[MAX_PATH];//��Ϸ�浵��Ϣ
	DWORD	IDCUPTDATE;//��Ϸ�����ķ������ĸ���ʱ��
	DWORD	SVRUPTDATE;//��Ϸ�����ɷ������ĸ���ʱ��
	DWORD	IDCVER;//��Ϸ�����ķ������ϵİ汾
	DWORD	SVRVER;//��Ϸ�����ɷ������ϵİ汾
	DWORD	AUTOUPT;//��Ϸ�Ƿ��Զ��ӷ������ϸ���
	DWORD	I8PLAY;//��Ϸ��Ҫǿ�Ƹ���
	DWORD	IDCCLICK;//��Ϸȫ������
	DWORD	SVRCLICK;//��Ϸ���ɵ���
	DWORD	ADDDATE;//��Ϸ���ʱ��
	char	GAMELINK[MAX_PATH];//��Ϸ����
	DWORD	RUNTYPE;//��Ϸ���з�ʽ
	DWORD	IFUPDATE;//��Ϸ�Ƿ����
	DWORD	IFDISPLAY;//��Ϸ�Ƿ���ʾ
	char	VID[MAX_PATH];//��Ϸ����������ID
	char    COMMENT[MAX_PATH];//Comment
    DWORD	STATUS;//��Ϸ����״̬
    DWORD   dwRepair; //������Ϸʱ��CRC�Ƚ�
	tagGameInfo()
	{
		ZeroMemory(SAVEFILTER,MAX_PATH);
	}

}tagGameInfo;

//��������Ϣ
typedef struct tagVDiskInfo
{
	CString VID; //������GUID
	DWORD IP; //������ip
	DWORD Port; //�����̶˿�
	TCHAR SvrDrv; //������̷�
	TCHAR   CliDrv; //�ͻ���ָ���̷�
	DWORD Serial; //�����̵����к�
	DWORD Type; //�����̵�����
	DWORD LoadType; //�����̵�ˢ�̷�ʽ
	CString SID; //����������ı�ʶ��
}VDISKINFO;

#define  NET_CMD_FINDSERVER		0x0500

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


