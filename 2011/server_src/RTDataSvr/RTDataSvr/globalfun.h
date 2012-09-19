#ifndef __GLOBALFUN__H__
#define __GLOBALFUN__H__



#include <vector>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <stdarg.h>


#include "../../../include/Zip/XUnzip.h"
#include "../../../include/Utility/Smartptr.hpp"
#include "../../../include/Extend STL/StringAlgorithm.h"


#ifdef min		// for std::min
#undef min
#endif


#pragma comment(lib,"Version.lib")
#if !defined(MAKEULONGLONG)
#define MAKEULONGLONG(low,high) \
	((ULONGLONG)(((DWORD)(low)) | ((ULONGLONG)((DWORD)(high))) << 32))
#endif



namespace utility
{



	typedef struct tagFileHeader
	{
		DWORD dwGameSizeLow;
		DWORD dwGameSizeHigh;
		DWORD resv1;  //������ʾ���ǲ�ʹ��,��ֱ���ǻ�ʹ��.
		DWORD resv2;
		DWORD resv3;
		DWORD resv4;
		DWORD dwXmlSize; //XML�ļ��Ĵ�С.
		WORD  resv5;
		WORD  CrcBlockNum; //CRC����.
	}tagFileHeader;



	typedef std::tr1::unordered_set<stdex::tString> StringHashSet;
	typedef StringHashSet::iterator StringHashSetItr;
	typedef StringHashSet::const_iterator StringHashSetCItr;



	//Ŀ¼����󲻴�'\'
	BOOL GetFileTreeList(LPCTSTR lpPath,std::vector<stdex::tString> &vFileList,std::vector<ULONGLONG> &vSizeList);


	BOOL GetFileTreeList2(LPCTSTR lpPath,  
		std::vector<stdex::tString> &vFileList,
		std::vector<stdex::tString> &vDirList,
		std::vector<ULONGLONG> &vSizeList);


	BOOL GetFileTreeList3(LPCTSTR lpPath,
		std::vector<stdex::tString> &vFileList,
		std::vector<stdex::tString> &vDirList,
		std::vector<ULONGLONG> &vSizeList,
		std::vector<stdex::tString> &vCreateTimeList);


	// ��ULONGLONG��ʱ��ת����string���͵�ʱ��
	stdex::tString DateTimeToString(ULONGLONG ulDT);

	BOOL GetFileLastWriteTime(LPCTSTR lpszFileName,ULONGLONG &ftLastWriteTime);

	BOOL ExtractZipContent(LPCTSTR lpZipFileName, 
		LPCTSTR lpTargetPath, 
		LPCTSTR lpContent, 
		stdex::tString& strErrorInfo);

	// ����Ŀ¼
	bool CreateDirectory(const stdex::tString &path);
	// ɾ��Ŀ¼
	BOOL DeleteDirectory(const stdex::tString& path);

	BOOL GetFileCrc32(HANDLE hFile,DWORD& dwCrc32);

	BOOL GetFileCrc32(LPCTSTR lpFileName,DWORD& dwCrc32);

	BOOL GetFileSize(LPCTSTR lpszFileName,ULONGLONG &ulFileSize);


	// ��ѹ
	template<typename InBufferT, typename OutBufferT>
	bool UnZip(const InBufferT &inBuf, size_t inBufLen, OutBufferT &outBuf, size_t &outBufLen)
	{
		// ��ѹ
		HZIP hz = OpenZip(inBuf, inBufLen, ZIP_MEMORY);
		if( hz == 0 )
			return false;

		ZIPENTRY ze = {0}; 
		const int index = 0;
		HRESULT res = GetZipItem(hz, index, &ze);
		if( res != S_OK )
			return false;

		typedef typename OutBufferT::RealType CharType;
		outBuf = new CharType[ze.unc_size];
		outBufLen = ze.unc_size;
		::memset(outBuf.Get(), 0, sizeof(CharType) * outBufLen);

		HRESULT zr = ZR_MORE; 
		ulong readSize = 0;
		const size_t unzipLen = 4096;
		while( zr == ZR_MORE )
		{
			const size_t leftLen = outBufLen - readSize;
			size_t readLen = std::min(leftLen, unzipLen);

			res = UnzipItem(hz,index, outBuf + readSize, readLen, ZIP_MEMORY);

			if( res == S_OK )
				break;

			readSize += readLen;
		}

		assert(readSize == ze.unc_size);
		CloseZip(hz);

		return true;
	}

}

#endif