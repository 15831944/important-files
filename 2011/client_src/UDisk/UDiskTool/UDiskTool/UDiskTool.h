
// UDiskTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUDiskToolApp:
// �йش����ʵ�֣������ UDiskTool.cpp
//

class CUDiskToolApp : public CWinAppEx
{
public:
	CUDiskToolApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUDiskToolApp theApp;