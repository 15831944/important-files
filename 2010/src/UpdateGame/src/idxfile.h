#ifndef __idx_file_inc__
#define __idx_file_inc__

#include <string>
#include <map>
#include <vector>

#define INDEX_FILE_NAMEW	L"I8desk.idx"
#define INDEX_FILE_NAMEA	 "I8desk.idx"
#define INDEX_BLOCK_SIZE	0xA0000

#define MAKEQWORD(low, high)	((__int64)((DWORD)(low)) | (((__int64)(DWORD)(high)) << 32))
#define LOWDWORD(num)			((DWORD)(num))
#define HIGHDWORD(num)			((DWORD)((num) >> 32))

#define ALIGN_SIZE(all_size, block_size) (((all_size) + (block_size) -1) / (block_size) * (block_size))

//֧��map��lessģ�⺯�������Դ�Сд�Ƚϡ�
template <> struct std::less<std::wstring> : public binary_function<std::wstring, std::wstring, bool>
{
	bool operator()(const std::wstring& _Left, const std::wstring& _Right) const
	{
		//_Left < _Right;
		return _wcsicmp(_Left.c_str(), _Right.c_str()) < 0;
	}
};

//�����ļ�ͷ
typedef struct tagIdxHeahder
{
	DWORD  lowsize;
	DWORD  highsize;
	DWORD  resv3;
	DWORD  resv4;
	DWORD  resv5;
	DWORD  resv6;
	DWORD  xmlsize;
	WORD   resv8;
	WORD   blknum;
}tagIdxHeahder;

//�������ļ���
typedef struct tagIdxFile
{
	std::wstring name;
	__int64	size;
	__int64	time;
	DWORD   attr;
	DWORD   blknum;
	DWORD   crc;
	DWORD   crcoff;
	DWORD	update;
}tagIdxFile;

////�����е�crc��
typedef struct tagIdxBlock
{
	__int64	offset;
	DWORD	blksize;
	DWORD	update;
	DWORD	crc;
	DWORD	resv6;
	DWORD	fileoff;
	LPSTR	pdata;
}tagIdxBlock;

//�ص�����
typedef bool (__stdcall *IDXCALLBACK)(void* pcookie, LPCWSTR info);

//���������ļ�
DWORD Idxfile_Make(LPCWSTR dir, DWORD blksize = INDEX_BLOCK_SIZE);

//���������ļ�.
DWORD Idxfile_Parse(LPCWSTR filename, std::vector<tagIdxFile*>& vFiles, 
	std::vector<tagIdxBlock*>& vBlocks, std::map<std::wstring, tagIdxFile*>& mFiles);

//�����ڴ������ļ�.
DWORD Idxfile_Parse(char* pfile, DWORD length, std::vector<tagIdxFile*>& vFiles, 
	std::vector<tagIdxBlock*>& vBlocks, std::map<std::wstring, tagIdxFile*>& mFiles);

//������������ϵ��ļ��Աȡ���ͬ�Ŀ����vOutBlocks�
void Idxfile_Compare(LPCWSTR dir, std::vector<tagIdxFile*>& vFiles, std::vector<tagIdxBlock*>& vBlocks, __int64& qSize,
	IDXCALLBACK pfnCallback = NULL, void* pCookie = NULL);

//���£����������Աȡ�
void Idxfile_Compare(std::map<std::wstring, tagIdxFile*>& mNewFiles, std::vector<tagIdxBlock*>& vNewBlocks, 
	std::map<std::wstring, tagIdxFile*>& mOldFiles, std::vector<tagIdxBlock*>& vOldBlocks, __int64& qSize,
	IDXCALLBACK pfnCallback = NULL, void* pCookie = NULL);

//�õ������ļ��汾��.ʧ�ܷ���-1
DWORD Idxfile_GetVersion(LPCWSTR file);

//�õ��ڴ������ļ��汾��.ʧ�ܷ���-1
DWORD Idxfile_GetVersion(char* pfile, DWORD length);

//��������ɾ�������ļ�(����ɾ�������ļ�)
void Idxfile_DeleteMorefile(LPCWSTR dir, std::map<std::wstring, tagIdxFile*>& mFiles, IDXCALLBACK pfnCallback = NULL, void* pCookie = NULL);

//������crcֵ��
DWORD Idxfile_BlockCrc(unsigned char* pdata, int length);

#endif