#include "stdafx.h"
#include "makeidxfile.h"

#include <algorithm>
#include <memory>
#include <unordered_map>

#include "Misc.h"
#include "../../../include/Utility/utility.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif // _DEBUG

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



namespace i8desk
{
	unsigned long SystemGranularity()
	{
		SYSTEM_INFO sysInfo = {0};
		::GetSystemInfo(&sysInfo);
		return sysInfo.dwAllocationGranularity;
	}

	const unsigned long BLOCK_SIZE = 10 * SystemGranularity();//0xA0000;
	const LPCWSTR	I8DeskW		= L"i8desk.idx";

	static const TCHAR *I8DESK_SPECIAL_DIR = _T("i8desk");
	static const size_t I8DESK_SPECIAL_DIR_LEN = ::lstrlen(I8DESK_SPECIAL_DIR);



	

	bool CMakeIdx::StartMakeIdx(LPCWSTR dir, bool bOnlyMakeIdx, HWND hWnd)
	{
		m_strError.clear();
		m_strLog.clear();
		if (m_XmlDoc)
			m_XmlDoc.Release();

		m_XmlDoc.CreateInstance(__uuidof(MSXML2::DOMDocument));
		MSXML2::IXMLDOMProcessingInstructionPtr pi = m_XmlDoc->createProcessingInstruction(_T("xml"), _T("version=\"1.0\" encoding=\"utf-8\""));
		m_XmlDoc->appendChild(pi);
		m_XmlDoc->preserveWhiteSpace = VARIANT_TRUE;

		m_XmlLocDoc.CreateInstance(__uuidof(MSXML2::DOMDocument));
		pi = m_XmlLocDoc->createProcessingInstruction(_T("xml"), _T("version=\"1.0\" encoding=\"utf-8\""));
		m_XmlLocDoc->appendChild(pi);
		m_XmlLocDoc->preserveWhiteSpace = VARIANT_TRUE;

		m_strDir = dir;
		m_hWnd = hWnd;
		m_bOnlyMakeIdx = bOnlyMakeIdx;
		if (m_strDir.size() == 0)
		{
			m_strError = _T("Ŀ¼Ϊ��");
			PostMessage(m_hWnd, WM_MAKEIDX, IDX_STATUS_ERROR, 0);
			m_bError = true;
			return false;
		}
		if (*m_strDir.rbegin() != '\\')
			m_strDir += '\\';
		m_strIdxfile = m_strDir + I8DeskW;

		m_bExited = 0;
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, this, 0, NULL);
		if (m_hThread == NULL)
		{
			DWORD dwError = GetLastError();
			_com_error Error(dwError);

			TCHAR szError[MAX_PATH] = {0};
			_stprintf(szError, _T("�����̳߳���:%d:%s"), dwError, Error.ErrorMessage());
			m_strError = szError;
			PostMessage(m_hWnd, WM_MAKEIDX, IDX_STATUS_ERROR, 0);
			m_bError = true;
			return false;
		}
		return true;
	}

	bool CMakeIdx::StopMakeIdx(bool wait)
	{
		if (m_hThread )
		{
			if( !wait )
				m_bExited = 1;

			WaitForSingleObject(m_hThread, INFINITE);
			CloseHandle(m_hThread);

			m_bExited = 1;
			m_hThread = NULL;
		}
		if (m_XmlDoc)
			m_XmlDoc.Release();
		if (m_XmlLocDoc)
			m_XmlLocDoc.Release();

		return m_bError;
	}



	bool CMakeIdx::MakeIdxScanDir(
		MSXML2::IXMLDOMElementPtr& Parent, 
		const std::wstring& Dir, 
		__int64& llTotalSize, 
		std::vector<FileInfo>& FileList)
	{
		bool bResult = true;
		if (Dir.empty()) 
		{
			DWORD dwError = GetLastError();
			_com_error Error(dwError);
			TCHAR szError[MAX_PATH] = {0};
			_stprintf(szError, _T("ɨ��Ŀ¼�����ڡ�"));
			m_strError = szError;
			return false;
		}
		std::wstring DirName = Dir.substr(0, Dir.size()-1);
		DirName = DirName.substr(DirName.rfind('\\')+1);

		MSXML2::IXMLDOMElementPtr DirNode = m_XmlDoc->createElement(_T("d"));
		DirNode->setAttribute(_T("n"), DirName.c_str());
		if (!Parent)
		{
			Parent = DirNode;
			Parent->setAttribute(_T("k"), _T("k"));
		}
		else
			Parent->appendChild(DirNode);
	
		WIN32_FIND_DATAW wfd;
		HANDLE hFinder = FindFirstFileW((Dir + L"*").c_str(), &wfd);
		if (hFinder != INVALID_HANDLE_VALUE)
		{
			int nFileNums = 0;
			//��ֻɨ���ļ�
			while (FindNextFileW(hFinder, &wfd) != 0)
			{
				if (m_bExited)
					break;
				if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0
					&& (wfd.dwFileAttributes & FILE_ATTRIBUTE_OFFLINE) == 0
					&& (wfd.dwFileAttributes & FILE_ATTRIBUTE_VIRTUAL) == 0)
				{
					if( lstrcmpiW(wfd.cFileName, I8DeskW) != 0 )
					{
						FileInfo IdxFile = {0};

						IdxFile.qSize = MAKEQWORD(wfd.nFileSizeHigh, wfd.nFileSizeLow);
						TCHAR buf[MAX_PATH] = {0};

						MSXML2::IXMLDOMElementPtr FileNode = m_XmlDoc->createElement(_T("f"));
						FileNode->setAttribute(_T("n"), wfd.cFileName);

						if (IdxFile.qSize != 0)
						{
							_i64tot(IdxFile.qSize, buf, 16);
							HexStrToUpper(buf);
							FileNode->setAttribute(_T("s"), buf);
						}

						SYSTEMTIME st;
						SYSTEMTIME lt;
						FileTimeToSystemTime(&wfd.ftLastWriteTime, &st);
						SystemTimeToTzSpecificLocalTime(NULL, &st, &lt);
						if (lt.wYear <= 1970 || lt.wYear >= 2029 )
						{
							IdxFile.qModifyTime = MAKEQWORD(wfd.ftLastWriteTime.dwHighDateTime, wfd.ftLastWriteTime.dwLowDateTime);
							_i64tot(IdxFile.qModifyTime, buf, 16);
							i8desk::HexStrToUpper(buf);
							FileNode->setAttribute(_T("w"), buf);
						}
						else
			 			{
							IdxFile.qModifyTime = MakeTimeFromFileTime(wfd.ftLastWriteTime);
							_i64tot(IdxFile.qModifyTime, buf, 16);
							i8desk::HexStrToUpper(buf);
							FileNode->setAttribute(_T("t"), buf);
						}

						IdxFile.dwAttr = wfd.dwFileAttributes & (0x1ff);
						if (IdxFile.dwAttr != 32)
						{
							_i64tot(IdxFile.dwAttr, buf, 16);
							i8desk::HexStrToUpper(buf);
							FileNode->setAttribute(_T("a"), buf);
						}
						DirNode->appendChild(FileNode);

						llTotalSize += IdxFile.qSize;
						
						utility::Strcpy(IdxFile.FileName, Dir);
						::lstrcpyW(IdxFile.FileName + Dir.length(), wfd.cFileName);
						
						FileList.push_back(IdxFile);
						nFileNums++;
					}
				}
			}
			FindClose(hFinder);

			//��ɨ��Ŀ¼
			HANDLE hFinder = FindFirstFileW((Dir + L"*").c_str(), &wfd);
			if (hFinder != INVALID_HANDLE_VALUE)
			{
				while (FindNextFileW(hFinder, &wfd) != 0)
				{
					if (m_bExited)
						break;
					if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						if( ((wfd.cFileName[0] == L'.') && 
							((wfd.cFileName[1] == 0) || (wfd.cFileName[1] == L'.' && wfd.cFileName[2] == 0)))
							)
							continue;

						//�ų�ָ����Ŀ¼
						if( lstrcmpiW(I8DeskW, wfd.cFileName) == 0 )
							continue;

						nFileNums++;
						bResult = MakeIdxScanDir(DirNode, Dir + wfd.cFileName + L"\\", llTotalSize, FileList);
						if (!bResult) 
							break;
					}
				}
				FindClose(hFinder);
			}
			else
			{
				DWORD dwError = GetLastError();
				TCHAR szError[MAX_PATH] = {0};
				_com_error Error(dwError);

				_stprintf(szError, _T("ɨ��Ŀ¼����:%d:%s Ŀ¼: %s"), dwError, Error.ErrorMessage(), Dir.c_str() );
				m_strError = szError;
				return false;
			}

			if (nFileNums == 0)//���Ŀ¼��û���ļ���Ŀ¼��дһ�����ļ���ȥ
			{
				MSXML2::IXMLDOMElementPtr element = m_XmlDoc->createElement(_T("f"));
				element->setAttribute(_T("n"), _T("k"));
				element->setAttribute(_T("a"), _T("10"));
				DirNode->appendChild(element);
			}
		}
		else
		{
			DWORD dwError = GetLastError();
			TCHAR szError[MAX_PATH] = {0};
			_com_error Error(dwError);
			_stprintf(szError, _T("ɨ���ļ�����:%d:%s Ŀ¼: %s"), dwError,Error.ErrorMessage(), Dir.c_str());
			m_strError = szError;
			return false;
		}

		return bResult;
	} 

	bool CMakeIdx::CheckIdxScanDir(const std::wstring& Dir,  __int64& llTotalSize, std::vector<FileInfo>& FileList)
	{
		bool bResult = true;
		WIN32_FIND_DATAW wfd;
		if (Dir.empty()) 
		{
			DWORD dwError = GetLastError();
			TCHAR szError[MAX_PATH] = {0};
			_com_error Error(dwError);
			_stprintf(szError, _T("ɨ��Ŀ¼�����ڡ�"));
			m_strError = szError;
			return false;
		}
		HANDLE hFinder = FindFirstFileW((Dir + L"*").c_str(), &wfd);

		TRACE(_T("��һ��ɨ��Ŀ¼[%s]...\n"), Dir.c_str());
		if (hFinder != INVALID_HANDLE_VALUE)
		{
			int nFileNums = 0;
			while (FindNextFileW(hFinder, &wfd))
			{
				if (m_bExited)
					break;
				if( (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0
					&& (wfd.dwFileAttributes & FILE_ATTRIBUTE_OFFLINE) == 0
					&& (wfd.dwFileAttributes & FILE_ATTRIBUTE_VIRTUAL) == 0 )
				{
					if( lstrcmpiW(I8DeskW, wfd.cFileName) != 0 )
					{
						FileInfo IdxFile = {0};
						IdxFile.qSize = MAKEQWORD(wfd.nFileSizeHigh, wfd.nFileSizeLow);

						IdxFile.qModifyTime = MAKEQWORD(wfd.ftLastWriteTime.dwHighDateTime, wfd.ftLastWriteTime.dwLowDateTime);
						IdxFile.dwAttr = wfd.dwFileAttributes & 0x1ff;

						llTotalSize += IdxFile.qSize;

						utility::Strcpy(IdxFile.FileName, Dir);
						::lstrcpyW(IdxFile.FileName + Dir.size(), wfd.cFileName);

						FileList.push_back(IdxFile);
						nFileNums++;
					}
				}
			}
			FindClose(hFinder);

			TRACE(_T("��ɨ��Ŀ¼[%s]...\n"), Dir.c_str());
			hFinder = FindFirstFileW((Dir + L"*").c_str(), &wfd);
			if (hFinder != INVALID_HANDLE_VALUE)
			{
				while (FindNextFileW(hFinder, &wfd))
				{
					if (m_bExited)
						break;
					if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						if( ((wfd.cFileName[0] == L'.') && ((wfd.cFileName[1] == 0) 
							|| (wfd.cFileName[1] == L'.' && wfd.cFileName[2] == 0)))
							)
							continue;
						
						// �ų�ָ����Ŀ¼
						if( utility::Stricmp(wfd.cFileName, I8DESK_SPECIAL_DIR) == 0 )
							continue;

						nFileNums++;
						std::wstring newDir = Dir + wfd.cFileName + L"\\";
						bResult = CheckIdxScanDir(newDir, llTotalSize, FileList);
					}
				}
				FindClose(hFinder);
			}
			else
			{
				DWORD dwError = GetLastError();
				TCHAR szError[4096] = {0};
				_com_error Error(dwError);
				_stprintf(szError, _T("��ɨ��Ŀ¼����:%d:%s Ŀ¼: %s"), 
					dwError, Error.ErrorMessage(), Dir.c_str() );
				m_strError = szError;
				TRACE(szError);
				return false;
			}
		}
		else
		{
			DWORD dwError = GetLastError();
			TCHAR szError[4096] = {0};
			_com_error Error(dwError);
			_stprintf(szError, _T("��һ��ɨ��Ŀ¼����:%d:%s Ŀ¼: %s"), 
				dwError, Error.ErrorMessage(), Dir.c_str() );
			m_strError = szError;
			TRACE(szError);
			return false;
		}

		return bResult;
	}

	//*
	bool CMakeIdx::CalCrcBlock(std::vector<FileInfo>& FileList, __int64 qGameSize, std::vector<CrcBlock>& crcBlocks)
	{
		m_dwProgress = 0;
		PostMessage(m_hWnd, WM_MAKEIDX, IDX_STATUS_CRC_START, m_dwProgress);

		QWORD qCalSize = 0;
		bool ok = false;
		TCHAR szError[BUFSIZ] = {0};

		for (std::vector<FileInfo>::iterator it = FileList.begin();
			it != FileList.end(); ++it)
		{
			it->dwCrcOffset = crcBlocks.size();

			utility::CAutoFile hFile = CreateFileW((*it).FileName, 
				GENERIC_READ, 
				FILE_SHARE_READ, 
				NULL, 
				OPEN_EXISTING, 
				0, 
				NULL);
			if ( !hFile.IsValid() )
			{
				_stprintf(szError, _T("���ļ�����:%d:%s �ļ���: %s"), GetLastError(),
					_com_error(GetLastError()).ErrorMessage(),(*it).FileName );
				m_strError = szError;
				goto Exit;
			}

			LARGE_INTEGER li = {0};
			if (!GetFileSizeEx(hFile, &li))
			{
				_stprintf(szError, _T("ȡ�ļ���С����:%d:%s �ļ���: %s"), GetLastError(),
					_com_error(GetLastError()).ErrorMessage(),(*it).FileName );
				m_strError = szError;
				goto Exit;
			}

			if( li.QuadPart == 0 )
				continue;

			utility::CAutoHandle hFileMap = ::CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
			if( !hFileMap.IsValid() )
			{
				_stprintf(szError, _T("���ļ�ӳ��:%d:%s �ļ���: %s"), GetLastError(),
					_com_error(GetLastError()).ErrorMessage(),(*it).FileName );
				m_strError = szError;
				goto Exit;
			}

			QWORD qFileSize = li.QuadPart;	
			QWORD qwFileOffset = 0;
			DWORD dwBlockBytes = 0;
			if( qFileSize < BLOCK_SIZE )
				dwBlockBytes = (DWORD)qFileSize;
			else
				dwBlockBytes = BLOCK_SIZE;

			while (qwFileOffset < qFileSize)
			{
				if( qFileSize - qwFileOffset < BLOCK_SIZE )
					dwBlockBytes = static_cast<DWORD>(qFileSize - qwFileOffset);

				utility::CAutoViewOfFile lpbMapAddress = (LPBYTE)::MapViewOfFile(hFileMap, FILE_MAP_READ,
				(DWORD)(qwFileOffset >> 32), (DWORD)(qwFileOffset & 0xFFFFFFFF), dwBlockBytes);
				
				if(lpbMapAddress == NULL)
				{
					_stprintf(szError, _T("ȡ�ļ���С����:%d:%s �ļ���: %s"), GetLastError(),
						_com_error(GetLastError()).ErrorMessage(), (*it).FileName);
					m_strError = szError;
					goto Exit;
				}

				if (m_bExited)
					goto Exit;

				
				{
					CrcBlock block = {0};
					block.dwBlockSize = dwBlockBytes;
					block.dwCrc32 = utility::CalBufCRC32(lpbMapAddress, dwBlockBytes);
					crcBlocks.push_back(block);
					qwFileOffset += dwBlockBytes;
					qCalSize += dwBlockBytes;

					m_dwProgress = (DWORD)((qCalSize*1000)/qGameSize);					
				}
			}
		}
		ok =  true;

Exit:
		PostMessage(m_hWnd, WM_MAKEIDX, IDX_STATUS_CRC_END, m_dwProgress);

		return ok;
	}
	
	bool CMakeIdx::LoadOldIdxFile(std::vector<FileInfo>& FileList, CrcBlock* & pCrcBlock)
	{
		utility::CAutoFile hFile = CreateFileW(m_strIdxfile.c_str(), GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, 0, NULL);
		if( !hFile.IsValid() )
		{
			DWORD dwError = GetLastError();
			TCHAR szError[MAX_PATH] = {0};
			_com_error Error(dwError);
			_stprintf(szError, _T("�������ļ���:%d:%s"), dwError, Error.ErrorMessage());
			m_strError = szError;
			return false;
		}
		DWORD dwFileSize = GetFileSize(hFile, NULL);
		ATL::CAutoVectorPtr<char> pBlock(new char[dwFileSize+1]);
		pBlock[dwFileSize] = 0;
		DWORD dwReadBytes = 0;
		if (dwFileSize < 32)
		{
			m_strError = _T("�����ļ�����ȷ.");
			return NULL;
		}
		if (!ReadFile(hFile, pBlock, dwFileSize, &dwReadBytes, NULL) && dwFileSize != dwReadBytes)
		{
			DWORD dwError = GetLastError();
			TCHAR szError[MAX_PATH] = {0};
			_com_error Error(dwError);
			_stprintf(szError, _T("�������ļ���:%d:%s"), dwError, Error.ErrorMessage());
			m_strError = szError;
			
			return NULL;
		}

		DWORD dwXmlSize  = *(DWORD*)(&pBlock[24]);
		DWORD dwCrcBlock = *(WORD*)(&pBlock[30]);
		DWORD dwStart = (dwCrcBlock + 1) * 32;

		if (dwStart + dwXmlSize + 32 > dwFileSize)
		{
			m_strError = _T("�����ļ��д�.�ļ�̫С,����Ӧ�ֶβ�һ��.");
			
			return NULL;
		}

		std::wstring xmlFile = CA2W(std::string(&pBlock[dwStart], dwXmlSize).c_str(), CP_UTF8);
		
		if (m_XmlLocDoc->loadXML(xmlFile.c_str()) == VARIANT_FALSE)
		{
			m_strError = _T("�����ļ��д�.XML���ݲ��ָ�ʽ����ȷ.");
			
			return NULL;
		}

		DWORD dwSize = dwFileSize - dwStart - dwXmlSize - 32;
		pCrcBlock = (CrcBlock*)(new char[dwSize+1]);
		ZeroMemory(pCrcBlock, dwSize + 1);
		memcpy(pCrcBlock, &pBlock[dwStart + dwXmlSize + 32], dwSize);

		

		int nOffset = 0;
		ParaseXMLFile(m_XmlLocDoc->documentElement, FileList, nOffset);

		return true;
	}

	inline _bstr_t GetNodeAttr(const MSXML2::IXMLDOMNodePtr& node, LPCTSTR name)
	{
		MSXML2::IXMLDOMNamedNodeMapPtr attr = node->Getattributes();
		if (!attr)
			return _T("");
		MSXML2::IXMLDOMNodePtr node2 = attr->getNamedItem(_bstr_t(name));
		if (!node2)
			return _T("");
		return node2->text;
	}

	_bstr_t CMakeIdx::GetNodeFullName(MSXML2::IXMLDOMNodePtr& node)
	{
		MSXML2::IXMLDOMNodePtr next = node;
		_bstr_t name;		
		while (next != NULL)
		{
			if (GetNodeAttr(next, _T("k")).length())
				break;

			_bstr_t x = GetNodeAttr(next, _T("n"));
			if (name.length())
				x += _T("\\");
			name = x + name;
			next = next->parentNode;
		}
		return name;
	}

	MSXML2::IXMLDOMNodePtr CMakeIdx::CmpFile(MSXML2::IXMLDOMNodePtr& node, MSXML2::IXMLDOMNodeListPtr& childs)
	{
		_bstr_t file = GetNodeAttr(node, _T("n"));
		for (int nIdx=0; nIdx<childs->length; nIdx++)
		{
			MSXML2::IXMLDOMNodePtr node2 = childs->Getitem(nIdx);
			if (lstrcmpi(file, GetNodeAttr(node2, _T("n"))) == 0)
			{
				if (lstrcmpi(GetNodeAttr(node, _T("s")), GetNodeAttr(node2, _T("s"))) != 0 ||
					lstrcmpi(GetNodeAttr(node, _T("t")), GetNodeAttr(node2, _T("t"))) != 0 ||
					lstrcmpi(GetNodeAttr(node, _T("a")), GetNodeAttr(node2, _T("a"))) != 0 )
				{
					m_strLog += _T("�ļ���ͬ:") + GetNodeFullName(node) + _T("\r\n");
					return node2;
				}
				return node2;
			}
		}
		m_strLog += _T("�����ļ�:") + GetNodeFullName(node) + _T("\r\n");
		return NULL;
	}


	bool CMakeIdx::CheckIdx(const std::vector<FileInfo>& FileList, const std::vector<FileInfo>& FileList2, 
		CrcBlock* pCrcBlock, CrcBlock* pCrcBlock2)
	{
		//����������ʱ��ϣ�����Ż������ıȽ��ٶ�
		typedef std::tr1::unordered_map<std::wstring, FileInfo> FileListMapType;
		FileListMapType FileListMap, FileListMap2;
		std::string filename;
		TCHAR buf[MAX_PATH*2] = {0};
		TRACE(_T("������ʱ��ϣ��1...\n"));
		for (size_t i = 0; i < FileList.size(); i++)
		{
			std::wstring str(FileList[i].FileName);
			std::transform(str.begin(), str.end(), str.begin(), std::ptr_fun(::tolower));

			FileListMap[str] = FileList[i];
		}

		TRACE(_T("������ʱ��ϣ��2...\n"));
		for (size_t i = 0; i < FileList2.size(); i++)
		{
			std::wstring str(FileList2[i].FileName);
			std::transform(str.begin(), str.end(), str.begin(), std::ptr_fun(::tolower));

			FileListMap2[str] = FileList2[i];
		}

		TRACE(_T("��ʼ�Ƚ�����...\n"));

		stdex::tString log;
		for (FileListMapType::iterator it = FileListMap.begin(); it != FileListMap.end(); ++it)
		{
			FileListMapType::iterator it2 = FileListMap2.find(it->first);
			if (it2 != FileListMap2.end())
			{
				log.clear();
				if (it->second.qSize != it2->second.qSize)
					log += _T("�ļ���С��ͬ,");
				else
				{
					if (it->second.qSize)
					{
						int nCount = (DWORD)(it->second.qSize / BLOCK_SIZE);
						if (it->second.qSize % BLOCK_SIZE)
							nCount++;

						for (int idx=0; idx<nCount; idx++)
						{
							if (pCrcBlock[it->second.dwCrcOffset+idx].dwCrc32 
								!= pCrcBlock2[it2->second.dwCrcOffset+idx].dwCrc32)
							{
								log += _T("�ļ�CRC��ͬ,");
								break;
							}
						}
					}
				}
				if (it->second.qModifyTime != it2->second.qModifyTime) {
					QWORD q;
					if (it->second.qModifyTime > it2->second.qModifyTime) 
						q = it->second.qModifyTime - it2->second.qModifyTime;
					else 
						q = it2->second.qModifyTime - it->second.qModifyTime;
					if (q > 10000000) {
						TCHAR buf[32] = {0};
						log += _T("�޸�ʱ�䲻ͬ,ʱ���:");
						log += _i64tot(q, buf, 10);
						log += _T(",");
					}
				}
				if (it->second.dwAttr != 0 &&
					it->second.dwAttr != it2->second.dwAttr)
					log += _T("�ļ����Բ�ͬ,");
				if (log.size())
				{
					log.resize(log.size()-1);
					log += _T("\r\n");
					m_strLog += it->second.FileName;
					m_strLog += _T(":") + log;
				}
			} 
			else 
			{
				m_strLog += it->second.FileName;
				m_strLog += _T(":��ǰ�ļ��б��������˸��ļ�.\r\n");
			}
		}


		TRACE(_T("��ʼ����Ƚ�����...\n"));
		for (FileListMapType::iterator it2 =FileListMap2.begin(); it2 != FileListMap2.end(); ++it2)
		{
			FileListMapType::iterator it = FileListMap.find(it2->first);
			if (it != FileListMap.end()) {
				;
			} else {
				m_strLog += it2->second.FileName;
				m_strLog += _T(":��ǰ�ļ��б��������˸��ļ�.\r\n");
			} 
		}
		TRACE(_T("�����ȽϽ���.\n"));

		return true;
	}

	void CMakeIdx::ParaseXMLFile(MSXML2::IXMLDOMNodePtr root, std::vector<FileInfo>& fileList, int& nOffset)
	{
		if (!root)	return ;

		MSXML2::IXMLDOMNodeListPtr childs = root->childNodes;
		for (int nIdx=0; nIdx<childs->length; nIdx++)
		{
			MSXML2::IXMLDOMNodePtr Node = childs->Getitem(nIdx);
			if( utility::Strcmp(Node->GetnodeName(), _T("f")) == 0 )
			{
				if(!(utility::Strcmp(GetNodeAttr(Node, _T("n")), _T("k")) == 0 
					&& utility::Strcmp(GetNodeAttr(Node, _T("a")), _T("10")) == 0))
				{
					FileInfo File;

					utility::Strcpy(File.FileName, m_strDir);
					::lstrcpyW(File.FileName + m_strDir.size(), (LPCWSTR)GetNodeFullName(Node));

					std::wstring fileName(File.FileName);
					std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::tolower);

					File.qSize    = HexstrToQword(GetNodeAttr(Node, _T("s")));
					File.qModifyTime = HexstrToQword(GetNodeAttr(Node, _T("w")));
					if (File.qModifyTime == 0) 
					{
						File.qModifyTime = HexstrToQword(GetNodeAttr(Node, _T("t")));
						File.qModifyTime *= 10000000;
						File.qModifyTime += 0x19DB1DED53E8000LL;
					}

					File.dwAttr = (DWORD)HexstrToQword(GetNodeAttr(Node, _T("a"))) & (0x1ff);
					if (File.dwAttr == 0)
						File.dwAttr = 32;

					File.dwCrcOffset = nOffset;
					if (File.qSize)
					{
						nOffset += (DWORD)(File.qSize / BLOCK_SIZE);
						if (File.qSize % BLOCK_SIZE)
							nOffset ++;
					}
					fileList.push_back(File);
				}
			}
		}
		for (int nIdx=0; nIdx<childs->length; nIdx++)
		{
			MSXML2::IXMLDOMNodePtr Node = childs->Getitem(nIdx);
			if( utility::Strcmp(Node->GetnodeName(), _T("d")) == 0 )
			{
				ParaseXMLFile(Node, fileList, nOffset);
			}
		}
	}

	UINT __stdcall CMakeIdx::ThreadProc(LPVOID lpVoid)
	{
		CoInitialize(NULL);
		CMakeIdx* pThis = reinterpret_cast<CMakeIdx*>(lpVoid);
		
		while (1)
		{
			__int64 llTotalSize = 0;
			std::vector<CrcBlock> crcBlocks;
			std::vector<FileInfo> FileList;

			if (!pThis->m_bOnlyMakeIdx && !PathFileExistsW(pThis->m_strIdxfile.c_str()))
			{
				pThis->m_strError = _T("�����ļ�������.");
				Sleep(10);
				PostMessage(pThis->m_hWnd, WM_MAKEIDX, IDX_STATUS_ERROR, 0);
				pThis->m_bError = true;
				break;
			}

			//ɨ�����е�Ŀ¼.
			Sleep(10);
			PostMessage(pThis->m_hWnd, WM_MAKEIDX, IDX_STATUS_SCAN, 0);
			MSXML2::IXMLDOMElementPtr root;
			
			TRACE(_T("��ʼɨ��Ŀ¼...\n"));
			std::transform(pThis->m_strDir.begin(), pThis->m_strDir.end(), pThis->m_strDir.begin(), ::tolower);
			bool ok = pThis->m_bOnlyMakeIdx ? 
				pThis->MakeIdxScanDir(root, pThis->m_strDir, llTotalSize, FileList) :
				pThis->CheckIdxScanDir(pThis->m_strDir, llTotalSize, FileList);

			//root->setAttribute("blksize", "10000");

			if (!ok)
			{
				if (pThis->m_bExited)
					break;
				Sleep(10);
				PostMessage(pThis->m_hWnd, WM_MAKEIDX, IDX_STATUS_ERROR, 0);
				pThis->m_bError = true;
			}
			else
			{
				PostMessage(pThis->m_hWnd, WM_MAKEIDX, IDX_STATUS_GETSIZE, (DWORD)(llTotalSize / 1024));
				Sleep(10);

				if (pThis->m_bExited)
					break;

				TRACE(_T("��ʼ����ãң�Ч��ֵ...\n"));
				if (!pThis->CalCrcBlock(FileList,llTotalSize, crcBlocks))
				{
					if (pThis->m_bExited)
						break;
					Sleep(10);
					PostMessage(pThis->m_hWnd, WM_MAKEIDX, IDX_STATUS_ERROR, 0);
					pThis->m_bError = true;
				}
				else
				{
					if (pThis->m_bExited)
						break;

					if (pThis->m_bOnlyMakeIdx)
					{
						DWORD dwWriteBytes = 0;
						::DeleteFileW(pThis->m_strIdxfile.c_str());
						utility::CAutoFile hFile = CreateFileW(pThis->m_strIdxfile.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
						if( !hFile.IsValid() )
						{
							DWORD dwError = GetLastError();
							TCHAR szError[MAX_PATH] = {0};
							_com_error Error(dwError);
							_stprintf(szError, _T("�������ļ���:%d:%s"), dwError, Error.ErrorMessage());
							pThis->m_strError = szError;
							Sleep(10);
							PostMessage(pThis->m_hWnd, WM_MAKEIDX, IDX_STATUS_ERROR, 0);
							pThis->m_bError = true;
						}
						else
						{
							SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

							//дXML�ļ�
							pThis->m_XmlDoc->appendChild(root);

							std::string doc = CW2A(root->xml, CP_UTF8);

							
							//���ļ�ͷ����.
							FileHeader header = {0};
							header.dwGameSizeLow  = LODWORD(llTotalSize);
							header.dwGameSizeHigh = HIDWORD(llTotalSize);
							header.dwXmlSize      = doc.size();
							header.CrcBlockNum    = 0;
							WriteFile(hFile, &header, sizeof(FileHeader), &dwWriteBytes, NULL);
						
							WriteFile(hFile, doc.c_str(), doc.size(), &dwWriteBytes, NULL);

							//дCRC����Ϣ.
							CrcBlock block = {0};
							block.dwReseverd0 = _time32(NULL);
							crcBlocks.insert(crcBlocks.begin(), block);
							if (!crcBlocks.empty()) {
								WriteFile(hFile, &crcBlocks[0], sizeof(CrcBlock)*crcBlocks.size(), &dwWriteBytes, NULL);
							}
							SetEndOfFile(hFile);

							Sleep(10);
							PostMessage(pThis->m_hWnd, WM_MAKEIDX, IDX_STATUS_FINISH, 0);	
							pThis->m_bError = true;

						}						
					}
					else
					{
						Sleep(10);
						PostMessage(pThis->m_hWnd, WM_MAKEIDX, IDX_STATUS_CHECK, 0);
						std::vector<FileInfo> IdxFileList;
						CrcBlock* pCrcBlock = NULL;
						
						TRACE(_T("����ԭ������...\n"));
						if (!pThis->LoadOldIdxFile(IdxFileList, pCrcBlock) || pCrcBlock == NULL)
						{
							Sleep(10);
							PostMessage(pThis->m_hWnd, WM_MAKEIDX, IDX_STATUS_ERROR, 0);
							pThis->m_bError = true;
						}
						else
						{
							TRACE(_T("׼���Ƚ�����...\n"));
							if (!crcBlocks.empty()) {
								pThis->CheckIdx(FileList, IdxFileList, &crcBlocks[0], pCrcBlock);
							} else  {
								pThis->m_strLog += _T("ֻ�п�Ŀ¼��");
							}
							Sleep(10);
							PostMessage(pThis->m_hWnd, WM_MAKEIDX, IDX_STATUS_FINISH, 0);
							pThis->m_bError = true;
						}
						if (pCrcBlock != NULL)
							delete []pCrcBlock;
					}
				}			
			}
			break;
		}
		CoUninitialize();
		return 0;
	}
}
