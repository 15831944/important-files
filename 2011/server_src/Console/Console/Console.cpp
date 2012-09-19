
// Console.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Console.h"
#include "ConsoleDlg.h"

#include <atlwin.h>

#include "DlgLogin.h"
#include "LoginMgr.h"
#include "LogHelper.h"
#include "DlgWaitMsg.h"
#include "UI/WZDialog.h"


#include "../../../include/Win32/System/except.h"
#include "../../../include/MultiThread/Lock.hpp"
#include "../../../include/Utility/ScopeGuard.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



i8desk::ManagerInstance *AfxManagerInstance()
{
	return i8desk::loginHelper.mgrInstance_.get();
}



// CConsoleApp

BEGIN_MESSAGE_MAP(CConsoleApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CConsoleApp ����

CConsoleApp::CConsoleApp()
: miniDump_(new except::MiniDump)
, isRunWizard_(false)
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}



// Ψһ��һ�� CConsoleApp ����

CConsoleApp theApp;


// CConsoleApp ��ʼ��

BOOL CConsoleApp::InitInstance()
{
	CWinAppEx::InitInstance();


	struct ScopeExit
	{
		void Run()
		{
			::TerminateProcess(::GetCurrentProcess(), 0);
		}
	}scopeExit;
	async::ScopeGuard<void> scope(std::tr1::bind(&ScopeExit::Run, scopeExit));

	SetRegistryKey(_T("i8desk"));
	SECURITY_ATTRIBUTES arributes = {0};
	async::thread::AutoMutex Mutex(&arributes, TRUE, _T("i8DeskConsoleEvent"));

	if( ::GetLastError() == ERROR_ALREADY_EXISTS )
		return FALSE;

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// ��������
	if( isRunWizard_ )
	{
		if( !i8desk::loginHelper.Connect(_T("127.0.0.1")) )
			AfxMessageBox(_T("�������ӵ�������"));
		CWZDialog dlg;
		if( IDOK != dlg.DoModal() )
			return FALSE;
	}
	else
	{
		CDlgLogin login(std::tr1::bind(&i8desk::LoginMgr::Connect, &i8desk::loginHelper, std::tr1::placeholders::_1),
			std::tr1::bind(&i8desk::LoginMgr::Password, &i8desk::loginHelper, std::tr1::placeholders::_1));
		if( login.DoModal() != IDOK )
			return FALSE;

	}

	//CDlgWaitMsg waitDlg;
	//waitDlg.Exec(std::tr1::bind(&AsyncDataImpl::Run));

	//i8desk::Log() << logsystem::Endl;
	//i8desk::Log() << _T("===================================================");

	CConsoleDlg dlg;
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

	// �˳�
	i8desk::loginHelper.LogOff();
	i8desk::DestroyLog();


	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}


int CConsoleApp::ExitInstance()
{


	return CWinAppEx::ExitInstance();
}


void CConsoleApp::ParseCommandLine(CCommandLineInfo& rCmdInfo)
{
	for (int i = 1; i < __argc; i++)
	{
		LPCTSTR pszParam = __targv[i];
		if( (pszParam[0] == '-' || pszParam[0] == '/') 
			&& pszParam[1] == 'w' )
		{
			isRunWizard_ = true;
		}
	}

}
