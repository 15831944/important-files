
// UDiskClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUDiskClientApp:
// �йش����ʵ�֣������ UDiskClient.cpp
//

class CUDiskClientApp : public CWinAppEx
{
public:
	CUDiskClientApp();
	CSocketEx* m_pSocket ;

	ULONG_PTR m_gdiplusToken;
	HANDLE m_hMapFile;
// ��д
	public:
	virtual BOOL InitInstance();
	void SetMainHWnd(HWND hWnd);
	BOOL OneInstance();
	bool Init(CString& szUserName);
// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
protected:
	int FindServer(vector<string>& veclst);
};

extern CUDiskClientApp theApp;