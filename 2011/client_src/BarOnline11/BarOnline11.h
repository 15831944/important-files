
// BarOnline11.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBarOnlineApp:
// �йش����ʵ�֣������ BarOnline11.cpp
//

namespace except
{
	class MiniDump;
}

class CBarOnlineApp : public CWinAppEx
{
	std::auto_ptr<except::MiniDump> miniDump_;

public:
	CBarOnlineApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBarOnlineApp theApp;