// Business.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"


#include "BusinessPlug.hpp"

__declspec(dllexport) i8desk::ISvrPlug* WINAPI CreateSvrPlug(DWORD /*Reserved*/)
{
	return new i8desk::BusinessPlug;
}