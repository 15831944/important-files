#ifndef ICONTABLE_H
#define ICONTABLE_H


#include "../../../include/irtdatasvr.h"
#include "../../../include/frame.h"
#include "../../../include/CustomFileDLL.h"
#include "container.h"

namespace i8desk
{

	struct IDatabase;

	class ZIconTable :public IIconTable
	{
	public:
		ZIconTable(void):version_(0)
		{
		};
		virtual ~ZIconTable(void);

		int RegisterHandler(void);
		void UnregisterHandler(void);


	private:
		stdex::tString strIconPath_;
		HANDLE IconHandle_;
		volatile long version_;

	public:
		bool Ensure(IN long gid, IN size_t size, IN const void *data);
		long GetVersion();
		int Load(IDatabase *pDatabase);

		// �����Զ����ļ���ʽ
		// lpszPath ·��, ���ؾ��
		void * CreateCustomFile(LPCTSTR lpszSavePath);
		// ����
		bool  DestroyCustomFile();
		// ͨ��gid��·�����������
		bool  AddCustomFile(IN long gid, IN LPCTSTR filePath);

		// ͨ��gid���ڴ��������
		bool  AddCustomFile2(IN long gid, IN size_t size, IN const void *data);
		// ɾ��ָ��gid����
		bool  DeleteCustomFile( IN long gid);
		// �޸�����
		bool  ModifyCustomFile(IN long gid, IN LPCTSTR newFilePath);
		bool  ModifyCustomFile2(IN long gid, IN size_t size, IN const void *data);
		// ��ȡָ��gid����
		bool  GetFileData(IN long gid, OUT size_t &size, OUT void *&data);
		// ��ȡ���е�����
		size_t  GetAllFileData(OUT size_t &size, OUT CustomFileInfoPtr &files);



	};


}



#endif 