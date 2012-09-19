#include "StdAfx.h"
#include "LogHelper.h"
#include "Icontable.h"


namespace i8desk
{

	ZIconTable::~ZIconTable(void)
	{
		if(IconHandle_ != 0)
			DestroyCustomFile();
	}

	long ZIconTable::GetVersion()
	{
		return ::InterlockedExchangeAdd(&version_, 0);
	}
	// �����Զ����ļ���ʽ
	// lpszPath ·��, ���ؾ��
	void * ZIconTable::CreateCustomFile(LPCTSTR lpszSavePath)
	{
		return ::CreateCustomFile(lpszSavePath);
	}

	// ����
	bool  ZIconTable::DestroyCustomFile()
	{
		return ::DestroyCustomFile( IconHandle_);
	}


	// ͨ��gid��·�����������
	bool  ZIconTable::AddCustomFile(IN long gid, IN LPCTSTR filePath)
	{
		::InterlockedExchange(&version_,::_time32(0));
		::AddCustomFile( IconHandle_,  gid,  filePath);
		return ::FlushCustomFile( IconHandle_ );

	}

	// ͨ��gid���ڴ��������
	bool  ZIconTable::AddCustomFile2(IN long gid, IN size_t size, IN const void *data)
	{
		::InterlockedExchange(&version_,::_time32(0));
		void *tmpdata;
		size_t outsize = 0;
		if(!::GetFileData( IconHandle_,  gid,  outsize,  tmpdata))
			 ::AddCustomFile2( IconHandle_, gid, size,  data);
		else
			 ::ModifyCustomFile2( IconHandle_, gid, size,  data);

		return ::FlushCustomFile( IconHandle_ );

	}


	// ɾ��ָ��gid����
	bool  ZIconTable::DeleteCustomFile( IN long gid)
	{
		::InterlockedExchange(&version_,::_time32(0));
		return ::DeleteCustomFile( IconHandle_,  gid);
	}


	// �޸�����
	bool  ZIconTable::ModifyCustomFile(IN long gid, IN LPCTSTR newFilePath)
	{
		::InterlockedExchange(&version_,::_time32(0));
		::ModifyCustomFile( IconHandle_,  gid,  newFilePath);
		return ::FlushCustomFile( IconHandle_ );

	}

	bool  ZIconTable::ModifyCustomFile2(IN long gid, IN size_t size, IN const void *data)
	{
		::InterlockedExchange(&version_,::_time32(0));
		::ModifyCustomFile2( IconHandle_,  gid,  size,  data);
		return ::FlushCustomFile( IconHandle_ );

	}


	// ��ȡָ��gid����
	bool  ZIconTable::GetFileData(IN long gid, OUT size_t &size, OUT void *&data)
	{
		return ::GetFileData( IconHandle_,  gid,  size,  data);
	}


	// ��ȡ���е�����
	size_t  ZIconTable::GetAllFileData(OUT size_t &size, OUT CustomFileInfoPtr &files)
	{
		return ::GetAllFileData(IconHandle_,  size,  files);
	}

	int ZIconTable::Load(IDatabase *pDatabase)
	{
		Log(LM_INFO, _T("���ر�����Ϸͼ������...\n"));

		stdex::tString m_strIconPath = utility::GetAppPath() + _T("Data\\Icon\\");
		stdex::tString strCustomPath = m_strIconPath + _T("icon.dat");

		if(!PathFileExists(m_strIconPath.c_str()))
		{
			if( !::CreateDirectory(m_strIconPath.c_str(), NULL) )
			{
				Log(LM_DEBUG,_T("���ر�����Ϸͼ������ʱ��Ŀ¼[%s]������,������룬%u\n"), 
					m_strIconPath.c_str(), GetLastError());
				return FALSE;
			}
		}

		if (!PathFileExists(strCustomPath.c_str()))
		{
			IconHandle_ = CreateCustomFile(strCustomPath.c_str());

			if (IconHandle_ == false)
			{
				Log(LM_INFO,_T("ͼ�������ļ�Icon.dat����ʧ��!"));
				return FALSE;
			}

			_RecordsetPtr prcd;
			{
				TCHAR sql[BUFSIZ] = _T("SELECT GID FROM tblGame WHERE Status  = 1");
				

				CGuard<IDatabase> lock(*pDatabase);
				if(!pDatabase->ExecSql(sql, prcd)) 
				{
					Log(LM_ERROR, _T("��ȡ������Ϸ�б�ʧ��!\n"));
					return -1;
				}
			}

			size_t m_nRecords = prcd->GetRecordCount() + 1;

			for (uint32 i = 1; i < m_nRecords; ++i) 
			{
				_variant_t gid = prcd->GetCollect(_T("GID"));

				TCHAR szIconFile[MAX_PATH];
				_stprintf(szIconFile, _T("%s%u.ICO"), m_strIconPath.c_str(), (long)gid);

				if( !AddCustomFile((long)gid,szIconFile) )
				{
					assert(0);
					Log(LM_ERROR,_T("����ͼ��%d.ICOʧ��"),(long)gid);
				}

				prcd->MoveNext();
			}

		}
		else
		{

			IconHandle_ = CreateCustomFile(strCustomPath.c_str());

			if (IconHandle_ == 0)
			{
				Log(LM_INFO,_T("ͼ�������ļ�Icon.dat��ʧ��!"));
				return FALSE;
			}
		}

		::InterlockedExchange(&version_,::_time32(0));		

		return 0;
	}

	int ZIconTable::RegisterHandler(void)
	{

		return 0;
	}

	void ZIconTable::UnregisterHandler(void)
	{
		//delete m_pIconEventHandler;
	}

	

}//namespace i8desk
	
