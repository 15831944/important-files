
// i8Safe.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ci8SafeApp:
// �йش����ʵ�֣������ i8Safe.cpp
//

class Ci8SafeApp : public CWinAppEx
{
public:
	Ci8SafeApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

public:
	BOOL		ExcuteSafeCenter();
};

extern Ci8SafeApp theApp;