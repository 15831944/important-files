#include "stdafx.h"
#include "GetFilePolicy.hpp"


#include <algorithm>
#include <functional>
#include <memory>
#include <fstream>


#include "Socket.h"
#include "tool.h"
#include "../../../include/Utility/SmartPtr.hpp"
#include "../../../include/Utility/utility.h"


#ifdef _DEBUG 
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
#endif

namespace i8desk
{


	namespace update
	{

		GetUpdateFile::GetUpdateFile(ILogger *log, CSocket &sock)
			: log_(log)
			, sock_(sock)
			, needUpdate_(false)
		{}
		
		bool GetUpdateFile::IsRunOnMainServer() const
		{
			const stdex::tString &svrIP = sock_.GetSvrIP();

			return i8desk::IsLocalMachine((LPCSTR)CT2A(svrIP.c_str()));
		}

		void GetUpdateFile::DoGetFile(std::vector<stdex::tString> &fileList)
		{
			// ��ȡ��Ҫ���µ��ļ��б�
			log_->WriteLog(LM_INFO, _T("��ȡ��Ҫ���µ��ļ��б�"));
			_GetAllFileList(fileList);

			// ����������Ҫ���µ��ļ�
			log_->WriteLog(LM_INFO, _T("��ȡ��Ҫ���µ��ļ���Ϣ���Ա�"));
			std::for_each(fileList.begin(), fileList.end(), 
				std::tr1::bind(&GetUpdateFile::_DoGetFileImpl, this, std::tr1::placeholders::_1));
		
			if( needUpdate_ )
			{
				log_->WriteLog(LM_INFO, _T("ȷ����ʱĿ¼����"));
				_EnsureTmpDirExisit();

				// ������Ҫ���³���
				log_->WriteLog(LM_INFO, _T("������Ҫ���³�������ʱĿ¼"));
				std::for_each(fileList.begin(), fileList.end(), 
					std::tr1::bind(&GetUpdateFile::_DownloadFile, this, std::tr1::placeholders::_1));
			}
		}

		void GetUpdateFile::_EnsureTmpDirExisit()
		{
			// ����������ʱĿ¼.
			const stdex::tString dir = utility::GetAppPath() + internal::tmpFile;
			::CreateDirectory(dir.c_str(), NULL);
		}


		void GetUpdateFile::_DoGetFileImpl(const stdex::tString &file)
		{
			FileInfo info = _RequestFileInfo(file);

			if( _CompareFile(std::tr1::get<0>(info), std::tr1::get<1>(info), file) )
			{
				needUpdate_ = true;
			}

			//needUpdate_ = true;
		}


		void GetUpdateFile::_GetAllFileList(std::vector<stdex::tString> &fileList)
		{
			//log_->WriteLog(LM_INFO, "Start _GetAllFileList");
			sock_.GetFileList(fileList);
		}

		GetUpdateFile::FileInfo GetUpdateFile::_RequestFileInfo(const stdex::tString &file)
		{
			return sock_.GetFileInfo(file);
		}


		bool GetUpdateFile::_CompareFile(DWORD fileSize, DWORD crc, const stdex::tString &file)
		{
			// �ȱȽ��ļ���С������ͬ���ٱȽ��ļ�CRC

			const stdex::tString filePath = utility::GetAppPath() + file.c_str();

			ULONGLONG srcfileSize = 0;
			GetFileSize(filePath.c_str(), srcfileSize);
			if( fileSize != srcfileSize )
				return true;

			ULONG srcCRC = 0;
			GetFileCrc32(filePath.c_str(), srcCRC);

			if( srcCRC != crc )
				return true;

			return false;
		}


		void GetUpdateFile::_DownloadFile(const stdex::tString &file)
		{
			char *inBuf = NULL;
			DWORD fileSize = 0;

			// ��ȡ�ļ�����
			sock_.GetFileData(file, inBuf, fileSize);
			utility::CArrayCharPtr buf(inBuf);

			// д����ʱĿ¼
			_WriteFileTmp(file, buf, fileSize);
		}

		void GetUpdateFile::_WriteFileTmp(const stdex::tString &file, const char *fileData, DWORD fileSize)
		{
			// ��ɾ��ԭ���ļ�
			const stdex::tString tmpFile = utility::GetAppPath() + internal::tmpFile + _T("/") + file;
			if( ::PathFileExists(tmpFile.c_str()) )
			{
				::SetFileAttributes(tmpFile.c_str(), FILE_ATTRIBUTE_NORMAL);
				::DeleteFile(tmpFile.c_str());
			}

			// ��д��
			std::ofstream out(tmpFile.c_str(), std::ios::binary | std::ios::out);

			if( out.good() )
			{
				out.write(fileData, fileSize);
				out.close();
			}
			else
			{
				std::string error = "��ʱ�ļ�";
				error += CT2A(file.c_str());
				error += "��ʧ��!";
				throw std::runtime_error(error);
			}
		}

	}
}