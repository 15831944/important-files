#ifndef __update_inc__
#define __update_inc__

#include <list>

#include "..\Include\plug.h"

namespace i8desk
{
	typedef struct tagFileItem//�ļ���Ϣ
	{
		DWORD dwFileCrc32;//�ļ�CRC32
		char FileName[MAX_PATH];//�ļ�����
	}tagFileItem;

	typedef struct tagIdxFile//�����ļ��б�ṹ
	{
		DWORD dwCrc32;//�ļ��б��CRC
		DWORD dwVersion;//���°汾��
		DWORD dwFileCount;//�����ļ���
		tagFileItem FileList[1];//�ļ��б�
	}tagIdxFile;

	class CAutoUpdate
	{
		//�Ա��ļ��ķ�ʽ
		typedef enum 
		{
			CMP_FILE_CRC32			= 0,		//���ļ���CRC32���Ƚ�
			CMP_FILE_SIZE_MODTIME	= 1,		//���ļ���С�޸�ʱ�����Ա�
			CMP_FILE_VERSION		= 2			//���ļ��汾���Ƚ�		
		}E_CMP_TYPE;

		//�Ա��ļ�������
		typedef enum
		{
			CON_EQUAL				= 0,		//����
			CON_NOT_EQUAL			= 1,		//������
			CON_LESS				= 2,		//С��
			CON_LESS_EQUAL			= 3,		//С�ڵ���
			CON_GREATER				= 4,		//����
			CON_GREATER_EQUAL		= 5			//���ڵ���
		}E_CMP_CONDIV;

		//ÿ���ļ�����Ϣ
		typedef struct tagFileInfo
		{
			bool			NeedUpdate;			//���ļ��Ƿ���Ҫ����
			std::string		szFileName;			//���µ��ļ���
			std::string		szTmpName;			//����ʱ����ʱ�ļ���
			std::string		szRelPath;			//http�ĵ�ַ
			E_CMP_TYPE		dwCmpType;			//�Աȷ�ʽ
 			//E_CMP_CONDIV	dwCmpCondiv;		//�Ա�����
			std::string		szParam1;			//����1.	�ļ�CRC,��С���汾
			std::string		szParam2;			//����2.	�ļ����޸�ʱ��
			tagFileInfo()
			{
				NeedUpdate	= false;
				dwCmpType	= CMP_FILE_CRC32;
				//dwCmpCondiv = CON_EQUAL;
			}
		}tagFileInfo;
	public:
		CAutoUpdate(ILogger* pLogger, IPlugMgr* pPlugMgr,CHyOperator* pHy);
		~CAutoUpdate();
	public:
		//������ֹͣ����Զ�����
		bool StartUpdate();
		void StopUpdate();
	private:
		//�Զ����µļ�������
		//������ͨ�ţ�ȡ�ø��µ������ļ��б�
		bool GetFileList();

		//�ԱȺ󣬵õ���Ҫ���µ��ļ��б�
		void GetNeedUpdateList();

		//��������������Ҫ���µ��ļ���һ����ʱĿ¼
		bool DownAllFile();

		//���������ص��ļ�;
		void WriteDataFile(tstring FileName, char* data, DWORD datalength);

		//����ʱ�ļ����ļ����µ�������Ŀ¼.Ȼ�������Լ�ֹͣ��EXE���߷���.
		bool ExecUpdate();

		//�Ƿ�͸��ԭ����
		bool NeedInProtUpdate(tstring path);

		//���µ��ļ��б�.
		std::list<tagFileInfo> m_lstFileList;

		static UINT __stdcall WorkThread(LPVOID lpVoid);
	private:
		std::string GetFileVersion(const std::string& szFile);
		DWORD		GetFileSizeModifyTime(const std::string& szFile, DWORD& dwModTime);
		DWORD		GetFileCRC32(const std::string&  szFile);
		void		ProccessFilePath(std::string& src,std::string& relPath);
		bool		DownLoadFile(tagFileInfo* pFileInfo);
		tstring		GetOpt(LPCTSTR szSection, LPCTSTR szKeyName, LPCTSTR szDefValue);
		void		EnsureFileDirExist(const std::string& file, int offset = 0);
		void		DelUpdateTmpFile(std::string& FilePath);
		BOOL        DownloadFile( DWORD dwProgramType, DWORD dwPathType, string strRemoteFileName, char** pRecvBuffer, DWORD &dwRecvLen);

	private:
		ILogger*	m_pLogger;
		IPlugMgr*	m_pPlugMgr;
		CHyOperator* m_pHy;
		HANDLE		m_hThread;
		HANDLE		m_hExited;

	};
}

#endif