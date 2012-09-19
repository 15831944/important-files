#ifndef __UPDATE_FILE_GET_FILE_HPP
#define __UPDATE_FILE_GET_FILE_HPP



#include <tuple>


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
			void DoGetFile(std::vector<std_string> &fileList);
			bool IsOK() const
			{
				return needUpdate_;
			}

			void Reset()
			{
				needUpdate_ = false;
			}


		private:
			void _DoGetFileImpl(const i8desk::std_string &file);


			// ��ȡ������µ��ļ��б�
			void _GetAllFileList(std::vector<std_string> &fileList);

			// ��ȡָ���ļ���Ϣ���ļ���С���ļ�CRC
			FileInfo _RequestFileInfo(const i8desk::std_string &file);
			/* �Ƚ��ļ���Ϣ	
					true : ��Ҫ����
					false: ����Ҫ����
			*/			
			bool _CompareFile(DWORD fileSize, DWORD crc, const i8desk::std_string &file);

			// ȷ��Ŀ¼����
			void _EnsureTmpDirExisit();

			// ����ָ���ļ�
			void _DownloadFile(const i8desk::std_string &file);

			// ���ļ�д����ʱĿ¼
			void _WriteFileTmp(const i8desk::std_string &file, char *fileData, DWORD fileSize);

		};
	}
}



#endif