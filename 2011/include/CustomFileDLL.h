#pragma once


#include <memory>

#ifdef CUSTOMFILEDLL_EXPORTS
#define CUSTOMFILEDLL_API __declspec(dllexport)
#else
#define CUSTOMFILEDLL_API __declspec(dllimport)
#endif


#ifdef  __cplusplus
extern "C" {
#endif


struct CustomFileInfo
{
	long gid;						// gid
	DWORD crc;						// crc
	size_t size;					// ���ݴ�С
	const void * data;				// ����
};
typedef std::tr1::shared_ptr<CustomFileInfo> CustomFileInfoPtr;


// �����Զ����ļ���ʽ
// lpszPath ·��, ���ؾ��
CUSTOMFILEDLL_API void *WINAPI CreateCustomFile(LPCTSTR lpszSavePath);

// ����
CUSTOMFILEDLL_API bool WINAPI DestroyCustomFile(void *handle);

// ˢ��
CUSTOMFILEDLL_API bool WINAPI FlushCustomFile(void *handle);

// ͨ��gid��·�����������
CUSTOMFILEDLL_API bool WINAPI AddCustomFile(void *handle, IN long gid, IN LPCTSTR filePath);
// ͨ��gid���ڴ��������
CUSTOMFILEDLL_API bool WINAPI AddCustomFile2(void *handle, IN long gid, IN size_t size, IN const void *data);

// ɾ��ָ��gid����
CUSTOMFILEDLL_API bool WINAPI DeleteCustomFile(void *handle, IN long gid);

// �޸�����
CUSTOMFILEDLL_API bool WINAPI ModifyCustomFile(void *handle, IN long gid, IN LPCTSTR newFilePath);
CUSTOMFILEDLL_API bool WINAPI ModifyCustomFile2(void *handle, IN long gid, IN size_t size, IN const void *data);

// ��ȡָ��gid����
CUSTOMFILEDLL_API bool WINAPI GetFileData(void *handle, IN long gid, OUT size_t &size, OUT void *&data);

// ��ȡ���е�����
CUSTOMFILEDLL_API size_t WINAPI GetAllFileData(void *handle, OUT size_t &size, OUT CustomFileInfoPtr &files);


#ifdef  __cplusplus
}
#endif