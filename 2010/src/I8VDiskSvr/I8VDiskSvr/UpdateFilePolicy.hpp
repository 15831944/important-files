#ifndef __UPDATE_FILE_UPDATE_FILE_HPP
#define __UPDATE_FILE_UPDATE_FILE_HPP




namespace i8desk
{

	struct ILogger;


	namespace update
	{

		// --------------------------------------
		// class UpdateFile

		class UpdateFile
		{
		private:
			i8desk::ILogger *log_;
			bool restartService_;					// �Ƿ���Ҫ��������

		public:
			explicit UpdateFile(ILogger *log);

		private:
			UpdateFile(const UpdateFile &);
			UpdateFile &operator=(const UpdateFile &);

		public:
			void DoUpdateFile(const std::vector<i8desk::std_string> &fileList);
			bool IsOK() const
			{
				return restartService_;
			}
			void Reset()
			{
				restartService_ = false;
			}
	
			// ɾ�����е���ʱ�ļ���Ŀ¼
			void DeleteAllFileTmp();

		private:
			// ���������ļ�
			void _UpdateAllFileImpl(const i8desk::std_string &file);

			
		};
	}
}





#endif