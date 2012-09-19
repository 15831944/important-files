#ifndef __UPDATE_FILE_GET_FILE_HPP
#define __UPDATE_FILE_GET_FILE_HPP



#include <tuple>
#include <vector>

namespace i8desk
{

	struct ILogger;
	class CSocket;


	namespace update
	{

		// ------------------------------
		// class GetUpdateFile

		class GetUpdateFile
		{
			ILogger *log_;
			CSocket &sock_;
			bool needUpdate_;

			// �ļ���С���ļ�CRC
			typedef std::tr1::tuple<DWORD, DWORD> FileInfo;

		public:
			GetUpdateFile(ILogger *log, CSocket &sock);

		private:
			GetUpdateFile(const GetUpdateFile &);
			GetUpdateFile &operator=(const GetUpdateFile &);

		public:
			void DoGetFile(std::vector<stdex::tString> &fileList);

			bool GetUpdateFile::IsRunOnMainServer() const;

			bool IsOK() const
			{
				return needUpdate_;
			}

			void Reset()
			{
				needUpdate_ = false;
			}


		private:
			void _DoGetFileImpl(const stdex::tString &file);


			// ��ȡ������µ��ļ��б�
			void _GetAllFileList(std::vector<stdex::tString> &fileList);

			// ��ȡָ���ļ���Ϣ���ļ���С���ļ�CRC
			FileInfo _RequestFileInfo(const stdex::tString &file);
			/* �Ƚ��ļ���Ϣ	
					true : ��Ҫ����
					false: ����Ҫ����
			*/			
			bool _CompareFile(DWORD fileSize, DWORD crc, const stdex::tString &file);

			// ȷ��Ŀ¼����
			void _EnsureTmpDirExisit();

			// ����ָ���ļ�
			void _DownloadFile(const stdex::tString &file);

			// ���ļ�д����ʱĿ¼
			void _WriteFileTmp(const stdex::tString &file, const char *fileData, DWORD fileSize);

		};
	}
}



#endif