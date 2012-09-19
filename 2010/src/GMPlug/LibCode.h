/*
 * Copyright (c) 2003, �������з�����
 * All rights reserved.
 * 
 * �ļ����ƣ�LibCode.h
 * �ļ���ʶ��WEB���������,�ӽ��ܺ���ͷ�ļ�
 * ժ    Ҫ��BASE64����,�ַ������ܽ���,URI���뺯��
 * ��    �ߣ�����
 * ��    ����030101
 */
 
/// \file LibCode.h
/// ����,�ӽ��ܺ���ͷ�ļ�
/// BASE64����,�ַ������ܽ���,URI���뺯��
   
#ifndef _WEBDEVLIB_CODE_H_
#define _WEBDEVLIB_CODE_H_ 

#include <wtypes.h>
#include <string>

using namespace std;

// WEB Application Develop Library namaspace
namespace webdevlib
{
	/// Base64����
	string base64_encode( const string &source );
	
	/// Base64����
	string base64_decode( const string &source );
	
	/// Sina�ַ�������
	string sina_encrypt( const string &source );
	
	/// Sina�ַ�������
	string sina_decrypt( const string &source );

	/// URI����
	//string uri_encode( const string &source );
	string uri_encode( LPCTSTR lpszSouce);
	
	
	/// URI����
	string uri_decode( const string &source );
}

#endif //_WEBDEVLIB_CODE_H_
