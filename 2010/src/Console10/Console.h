// Console.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CConsoleApp:
// �йش����ʵ�֣������ Console.cpp
//

class CConsoleApp : public CWinApp
{
public:
	CConsoleApp();

// ��д
	public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();

// ʵ��
	ULONG_PTR m_gdiplusToken;

	DECLARE_MESSAGE_MAP()
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
};

extern CConsoleApp theApp;