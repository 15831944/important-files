// SendSvr.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include <atlbase.h>
#include <atlconv.h>

#include "../../Common/Utility.hpp"
#include "../../../include/Win32/System/except.h"

#include "SendSvr.hpp"

except::MiniDump dump;


int _tmain(int argc, _TCHAR* argv[])
{
	
	sendsvr::SendSvrMgr mgr;

	mgr.ProcessCmdLine(argc, argv);

	return 0;
}

