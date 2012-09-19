
// UDiskServer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "UDiskServer.h"
#include "UDiskServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUDiskServerApp

BEGIN_MESSAGE_MAP(CUDiskServerApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CUDiskServerApp ����

CUDiskServerApp::CUDiskServerApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CUDiskServerApp ����

CUDiskServerApp theApp;


// CUDiskServerApp ��ʼ��
void CUDiskServerApp::SetMainHWnd(HWND hWnd)
{
	char buf[1024] = {0};
	HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, 
		PAGE_READWRITE, 0, 1024, _T("I8Desk_Udisk_Server"));	
	if (hMapFile == NULL || hMapFile == INVALID_HANDLE_VALUE) 
		return ;

	LPSTR pBuf = (LPSTR) MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 
		0, 0, 1024);
	if (pBuf == NULL)
		return ;
	*(HWND*)pBuf = hWnd;
	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);	
}
BOOL CUDiskServerApp::OneInstance()
{
	char buf[1024] = {0};
	m_hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, 
		PAGE_READWRITE, 0, 1024, _T("I8Desk_Udisk_Server"));	
	if (m_hMapFile == NULL || m_hMapFile == INVALID_HANDLE_VALUE) 
	{
		printf(buf, "Could not create file mapping object (%d).\n", GetLastError());
		AfxMessageBox(buf);
		return FALSE;
	}
	DWORD dwErr = GetLastError();
	if (ERROR_ALREADY_EXISTS == dwErr)
	{
		LPSTR pBuf = (LPSTR) MapViewOfFile(m_hMapFile, FILE_MAP_ALL_ACCESS, 
			0, 0, 1024);
		if (pBuf == NULL)
			return FALSE;
		HWND hWnd = *(HWND*)(pBuf);
		if (hWnd != NULL)		
		{
			try		{
				::ShowWindow(hWnd, SW_RESTORE);
				::SetForegroundWindow(hWnd);
			}	
			catch (...) {	}

		}
		UnmapViewOfFile(pBuf);
		CloseHandle(m_hMapFile);
		m_hMapFile = INVALID_HANDLE_VALUE;
		return FALSE;
	}
	return TRUE;
}
BOOL CUDiskServerApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();
	m_pConfigInfo = new SrvConfigInfo;
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	if(!OneInstance())
		return FALSE;

	WSADATA data;
	WSAStartup(0x0202,&data);

	CUDiskServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CUDiskServerApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
		if(m_pConfigInfo)
			delete m_pConfigInfo;
		WSACleanup();
	return CWinAppEx::ExitInstance();
}

