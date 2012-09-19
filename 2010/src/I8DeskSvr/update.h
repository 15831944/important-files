#ifndef __update_inc__
#define __update_inc__

#include <list>

#include "../../include/plug.h"
#include "plugmgr.h"

namespace i8desk
{
	//////////////////////////////////////////////////////////////////////////
	//����XML�ļ��б������.��http����ʱ,���ص���xml�ļ�����base64�������ַ���
	/*
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
			std::string		szFileName;			//���µ��ļ���					(file.name)
			std::string		szParseFile;		//��������ļ���
			std::string		szTmpName;			//����ʱ����ʱ�ļ���		 
			std::string		szUrl;				//http�ĵ�ַ					(file.url)
			DWORD			dwCrc;				//�ļ��ãң�.					(file.crc)
			DWORD			dwModifyTime;		//�ļ��޸�ʱ��					(file.modifytime)
			tagFileInfo()
			{
			}
		}tagFileInfo;
	public:
		CAutoUpate(ILogger* pLogger, CPlugMgr* pPlugMgr);
		~CAutoUpate();
	public:
		//������ֹͣ����Զ�����
		bool StartUpdate();
		void StopUpdate();
	private:
		//�Զ����µļ�������
		//������ͨ�ţ�ȡ�ø��µ������ļ��б�
		void GetFileList();

		//��������������Ҫ���µ��ļ���һ����ʱĿ¼
		bool DownAllFile();

		//����ʱ�ļ����ļ����µ�������Ŀ¼.Ȼ�������Լ�ֹͣ��EXE���߷���.
		void ExecUpdate();

		//���µ��ļ��б�.
		std::list<tagFileInfo> m_lstFileList;

		static UINT __stdcall WorkThread(LPVOID lpVoid);
	private:
		DWORD		GetFileCRC32(const std::string&  szFile);
		void		ProccessFilePath(tagFileInfo* pFileInfo);
		bool		DownLoadFile(tagFileInfo* pFileInfo);
		tstring		GetOpt(LPCTSTR szSection, LPCTSTR szKeyName, LPCTSTR szDefValue);
		void		EnsureFileDirExist(const std::string& file, int offset = 0);
		DWORD		StringToInt(LPCSTR pString, int K = 16);
		tstring		GetFileVersion();
		std::string	uri_encode(LPCTSTR lpszSouce);
	private:
		ILogger*	m_pLogger;
		CPlugMgr*	m_pPlugMgr;
		HANDLE		m_hThread;
		HANDLE		m_hExited;
		bool		m_bNeedReStartService;
	};
}

#endif