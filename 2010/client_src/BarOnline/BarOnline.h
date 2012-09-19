#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"

typedef struct tagFileMap
{
	HWND hWnd;
	TCHAR szCmdLine[1024];
}tagFileMap;

class CBarOnlineApp : public CWinAppEx
{
public:
	CBarOnlineApp();
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	CString GetCmdLine();

	DECLARE_MESSAGE_MAP()
private:
	Gdiplus::GdiplusStartupInput	gdiplusStartupInput;
	ULONG_PTR						gdiplusToken;
	HANDLE							m_hFileMap;
};

extern CBarOnlineApp theApp;