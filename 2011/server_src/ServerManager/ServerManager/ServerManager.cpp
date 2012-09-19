
// ServerManager.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ServerManager.h"
#include "ServerManagerDlg.h"

#include "../../../include/MultiThread/Lock.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerManagerApp

BEGIN_MESSAGE_MAP(CServerManagerApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CServerManagerApp ����

CServerManagerApp::CServerManagerApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CServerManagerApp ����

CServerManagerApp theApp;


// CServerManagerApp ��ʼ��

BOOL CServerManagerApp::InitInstance()
{
	CWinAppEx::InitInstance();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("I8Desk Server Manager"));


	SECURITY_ATTRIBUTES arributes = {0};
	async::thread::AutoMutex Mutex(&arributes, TRUE, _T("i8DeskSvrMgr"));

	if( ::GetLastError() == ERROR_ALREADY_EXISTS )
		return FALSE;

	CServerManagerDlg dlg;
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
