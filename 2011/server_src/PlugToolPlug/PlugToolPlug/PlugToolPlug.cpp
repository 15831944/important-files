// PlugToolPlug.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "plugTool.h"

__declspec(dllexport) i8desk::ISvrPlug* WINAPI CreateSvrPlug(DWORD /*Reserved*/)
{
	return new i8desk::PlugTool;
}