
// UDiskServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUDiskServerApp:
// �йش����ʵ�֣������ UDiskServer.cpp
//

class CUDiskServerApp : public CWinAppEx
{
public:
	CUDiskServerApp();

// ��д
	public:
	virtual BOOL InitInstance();
	BOOL OneInstance();
	void SetMainHWnd(HWND hWnd);
	SrvConfigInfo* m_pConfigInfo;
	HANDLE m_hMapFile;
// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CUDiskServerApp theApp;