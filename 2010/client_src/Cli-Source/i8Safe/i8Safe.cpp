
// i8Safe.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "i8Safe.h"
#include "SafeCenter.h"
#include "i8SafeDlg.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _DEBUG
#include "vld.h"
#endif

// Ci8SafeApp

BEGIN_MESSAGE_MAP(Ci8SafeApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Ci8SafeApp ����

Ci8SafeApp::Ci8SafeApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� Ci8SafeApp ����

Ci8SafeApp theApp;
BOOL Ci8SafeApp::InitInstance()
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

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	//ִ�а�ȫ��������
	CLogFile::WriteLog("������ȫ����");
	ExcuteSafeCenter();

	//Ci8SafeDlg dlg;
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: �ڴ˷��ô����ʱ��
	//	//  ��ȷ�������رնԻ���Ĵ���
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: �ڴ˷��ô����ʱ��
	//	//  ��ȡ�������رնԻ���Ĵ���
	//}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

BOOL Ci8SafeApp::ExcuteSafeCenter()
{
	CSafeCenter safeCenter;
	char xmlPath[MAX_PATH]={0};
	GetModuleFileName(NULL, xmlPath, MAX_PATH);
	PathRemoveFileSpecA(xmlPath);
	int iIdx = strlen(xmlPath) - 1;
	while (xmlPath[iIdx] && xmlPath[iIdx] != '\\')
	{
		iIdx--;
	}
	xmlPath[iIdx] = '\0';
	lstrcat(xmlPath, TEXT("\\Data\\Config\\i8Safe.xml"));

	char szLog[2*MAX_PATH] = {0};
	sprintf(szLog, "��ȡ�����ļ�:%s", xmlPath);
	CLogFile::WriteLog(szLog);

	BOOL bOK = safeCenter.ReadConfig(xmlPath);
	if(bOK == FALSE)
	{
		CLogFile::WriteLog("�����ļ���ȡʧ��.");
		return FALSE;
	}
	bOK = safeCenter.Start();
	if (!bOK)
	{
		CLogFile::WriteLog("��ȫ��������ʧ��.");
		return FALSE;
	}
	else
	{
		CLogFile::WriteLog("��ȫ���������ɹ�.");
	}
	while (safeCenter.IsRun())
	{
		Sleep(100);
	}
	return TRUE;
}