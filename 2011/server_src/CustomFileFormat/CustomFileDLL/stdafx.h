// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>
#include <Shlwapi.h>


#include<stdlib.h> 
#include<crtdbg.h>

#ifdef _DEBUG   
//#define _CRTDBG_MAP_ALLOC   
//#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)   
#define malloc(n) _malloc_dbg(n, _NORMAL_BLOCK, __FILE__, __LINE__)   
#endif