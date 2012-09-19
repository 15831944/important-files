
// Console.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <memory>


namespace i8desk
{
	struct ManagerInstance;
}


namespace except
{
	class MiniDump;
}
// CConsoleApp:
// �йش����ʵ�֣������ Console.cpp
//

class CConsoleApp : public CWinAppEx
{
public:
	CConsoleApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();


protected:
	void ParseCommandLine(CCommandLineInfo& rCmdInfo);

private:
	std::auto_ptr<except::MiniDump> miniDump_;
	bool isRunWizard_;
// ʵ��

	DECLARE_MESSAGE_MAP()

};


i8desk::ManagerInstance *AfxManagerInstance();

extern CConsoleApp theApp;