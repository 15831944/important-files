#ifndef __update_inc__
#define __update_inc__

#pragma once

#include <list>
#include "plugmgr.h"

namespace i8desk
{
	//////////////////////////////////////////////////////////////////////////
	//����XML�ļ��б������.��http����ʱ,���ص���xml�ļ�����base64�������ַ���
	/*	url:http://update.i8desk.com/update2/u2.do
		<?xml version="1.0" encoding="gb2312" ?>
		<filelist>
			<!-- file.name��ʾ��Ҫ���µ��ļ���֧��%root%,%system$,%program%������ʽ -->
			<!-- file.url��ʾ����ļ���http���ص�ַ -->
			<!-- file.crc��ʾ����ļ���crc32(16���Ƶ�ֵ��ǰ��û��0x) -->
			<!-- file.modifytime��ʾ����ļ����޸�ʱ��(utc) -->
			<file name="%root%\a.exe" url="http://www.i8desk.com/a.exe" crc="123456" modifytime = "112233" />
			<file name="%root%\BarOnlineUpdate\wxnda.sys" url="http://www.i8desk.com/wxnda.sys" crc="" modifytime = "112233" />
		</filelist>
	*/
	//////////////////////////////////////////////////////////////////////////
	class CAutoUpate
	{
		//ÿ���ļ�����Ϣ
		typedef struct tagFileInfo
		{
			stdex::tString		szFileName;			//(file.name)
			stdex::tString		szParseFile;		//(dst file name)
			stdex::tString		szTmpName;			//(download tmpe file name)
			stdex::tString		szUrl;				//(file.url)
			DWORD		dwCrc;				//(file.crc)
			DWORD		dwModifyTime;		//(file.modifytime:time_t)
			tagFileInfo()
			{
			}
		}tagFileInfo;
	public:
		CAutoUpate(CPlugMgr* pPlugMgr, ILogger* pLogger);
		~CAutoUpate();
	public:
		bool StartUpdate();
		void StopUpdate();
	private:
		void GetFileList();
		bool DownAllFile();
		void ExecUpdate();
		std::list<tagFileInfo> m_lstFileList;
		static UINT __stdcall WorkThread(LPVOID lpVoid);
	private:
		DWORD		GetFileCRC32(const stdex::tString&  szFile);
		void		ProccessFilePath(tagFileInfo* pFileInfo);
		bool		DownLoadFile(tagFileInfo* pFileInfo);
		void		EnsureFileDirExist(const stdex::tString& file, int offset = 0);
		DWORD		StringToInt(LPCTSTR pString, int K = 16);
		stdex::tString CAutoUpate::uri_encode(LPCTSTR lpszSouce);
	private:
		CPlugMgr*	m_pPlugMgr;
		ILogger*	m_pLogger;
		HANDLE		m_hThread;
		HANDLE		m_hExited;
		bool		m_bNeedReStartService;
	};
}

#endif