
// ViewClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CViewClientApp:
// �йش����ʵ�֣������ ViewClient.cpp
//

class CViewClientApp : public CWinAppEx
{
public:
	CViewClientApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CViewClientApp theApp;