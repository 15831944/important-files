
// ServerUI.h : ServerUI Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CServerUIApp:
// �йش����ʵ�֣������ ServerUI.cpp
//

class CServerUIApp : public CWinApp
{
public:
	CServerUIApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
	BOOL OneInstance();
	void SetMainHWnd(HWND hWnd);
};

extern CServerUIApp theApp;
