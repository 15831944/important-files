#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"

class CDeskLockerApp : public CWinAppEx
{
public:
	CDeskLockerApp();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
private:
	GdiplusStartupInput	gdiplusStartupInput;
	ULONG_PTR			gdiplusToken;
};

extern CDeskLockerApp theApp;