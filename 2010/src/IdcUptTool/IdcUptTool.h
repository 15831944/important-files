// IdcUptTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIdcUptToolApp:
// �йش����ʵ�֣������ IdcUptTool.cpp
//

class CIdcUptToolApp : public CWinApp
{
public:
	CIdcUptToolApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIdcUptToolApp theApp;