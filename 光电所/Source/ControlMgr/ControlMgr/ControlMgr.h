
// ControlMgr.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CControlMgrApp:
// �йش����ʵ�֣������ ControlMgr.cpp
//

class CControlMgrApp : public CWinAppEx
{
public:
	CControlMgrApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CControlMgrApp theApp;