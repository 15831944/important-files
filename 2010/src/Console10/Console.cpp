// Console.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"

#pragma comment(lib, "gdiplus.lib")

#define CRASH_DUMP_FILE "Console.dmp"

#include "Console.h"
#include "ConsoleDlg.h"
#include "except.h"

#include "oem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CConsoleApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CConsoleApp::CConsoleApp()
{
	SetUnhandledExceptionFilter(::Local_UnhandledExceptionFilter);
}

CConsoleApp theApp;

BOOL CConsoleApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	AfxInitRichEdit2();
	AfxOleInit();

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, 0);

	WSAData wsaData;
	WSAStartup(0x0202, &wsaData);

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	AfxEnableControlContainer();

	//���ÿ���̨�����ڱ���
	free((void*)m_pszAppName);

	CString strAppName;
	if (I8DESK_OEM->LoadString(strAppName))
		m_pszAppName=_tcsdup((LPCTSTR)strAppName);
	else 
		m_pszAppName=_tcsdup(_T("i8desk����̨"));

	//��֤����ֻ������һ��ʵ��.
	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, "__i8desk_console_instance__");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AfxMessageBox("��������һ������̨�����Ϸ����,���ȷ�Ϻ��˳�������̨.");
		CloseHandle(hEvent);

		HWND hWnd = ::FindWindow("#32770", m_pszAppName);
		if (hWnd != NULL)
		{
			::ShowWindow(hWnd, SW_RESTORE);
			::SetForegroundWindow(hWnd);
		}
		return TRUE;
	}
	
	CConsoleDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}	
	CloseHandle(hEvent);

	return FALSE;
}

BOOL CConsoleApp::ExitInstance()
{
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
	return CWinApp::ExitInstance();
}


void CConsoleApp::WinHelp(DWORD dwData, UINT nCmd)
{
	// TODO: �ڴ����ר�ô����/����û���

	//CWinApp::WinHelp(dwData, nCmd);
}
