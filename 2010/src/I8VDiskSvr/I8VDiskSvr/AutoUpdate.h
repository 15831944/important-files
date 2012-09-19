#ifndef __VDISK_AUTO_UPDATE_HPP
#define __VDISK_AUTO_UPDATE_HPP


#include "../../../include/MultiThread/Thread.hpp"
#include "../../../include/MultiThread/Lock.hpp"

#include "GetFilePolicy.hpp"
#include "UpdateFilePolicy.hpp"


#include <sstream>

namespace i8desk
{

	// -----------------------------------------
	// class AutoUpdate
	
	template<typename GetFileT, typename UpdateFileT>
	class AutoUpdate
	{
		// �ȴ�ʱ��
#ifndef _DEBUG
		enum { WAIT_TIME = 2 * 60 * 60 * 1000 };
		//enum { WAIT_TIME = 20 * 1000 };
#else
		enum { WAIT_TIME = 20 * 1000 };
#endif

		typedef GetFileT		GetFileType;
		typedef UpdateFileT		UpdateFileType;

	private:
		async::thread::ThreadImplEx thread_;	// �����ļ��߳�
		async::thread::AutoEvent	exitEvent_;	// �˳��ź�

		ILogger *log_;
		std::vector<std_string> fileList_;		// ��Ҫ���µ��ļ��б�

		volatile long notUpdate_;				//

		std::auto_ptr<GetFileType>		getFileImpl_;
		std::auto_ptr<UpdateFileType>	updateFileImpl_;

	public:
		AutoUpdate(ILogger *log, CSocket &sock)
			: log_(log)
			, notUpdate_(0)
			, getFileImpl_(new GetFileType(log, sock))
			, updateFileImpl_(new UpdateFileType(log))
		{

		}
		~AutoUpdate();

	private:
		AutoUpdate(const AutoUpdate &);
		AutoUpdate &operator=(const AutoUpdate &);

	public:
		bool Start()
		{
			log_->WriteLog(LM_INFO, _T("��ʼ�Զ�����..."));

			exitEvent_.Create(NULL, TRUE);
			thread_.RegisterFunc(std::tr1::bind(&AutoUpdate::_ThreadCallback, this));
			thread_.Start();

			return true;
		}
		bool Stop()
		{
			exitEvent_.SetEvent();
			thread_.Stop();	

			log_->WriteLog(LM_INFO, _T("�����Զ�����..."));

			return true;
		}
	
		bool NeedUpdate() const
		{
			return notUpdate_ == 1;
		}

	private:
		// ��������
		void _RestartService()
		{
			// ������������
			TCHAR path[MAX_PATH] = {0};
			::GetModuleFileName(NULL, path, MAX_PATH);
			lstrcat(path, TEXT(" -A"));

			STARTUPINFO si	= {sizeof(si)};
			si.dwFlags		= STARTF_USESHOWWINDOW;
			si.wShowWindow	= SW_HIDE;
			PROCESS_INFORMATION pi = {0};
			BOOL ret = ::CreateProcess(NULL, path, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
			::WaitForSingleObject(pi.hProcess, INFINITE);

			if( ret )
			{
				::CloseHandle(pi.hThread);
				::CloseHandle(pi.hProcess);
			}
			else
			{
				std::stringstream os;
				os << ::GetLastError();

				std::string error("���Ҹ��´������ν���ʧ��! code = ");
				error += os.str();

				throw std::runtime_error(error);
			}
		}

		// ����״̬
		void _Reset()
		{
			getFileImpl_->Reset();
			updateFileImpl_->Reset();
			fileList_.clear();
		}

		DWORD _ThreadCallback()
		{
			while( !thread_.IsAborted() )
			{
				//__asm { int 3 }
				// ����״̬
				_Reset();

				DWORD ret = 0;
				try
				{
					getFileImpl_->DoGetFile(fileList_);

					ret = ::WaitForSingleObject(exitEvent_, 0);
					if( ret == WAIT_OBJECT_0 )
						break;

					if( getFileImpl_->IsOK() )
					{
						updateFileImpl_->DoUpdateFile(fileList_);

						ret = ::WaitForSingleObject(exitEvent_, 0);
						if( ret == WAIT_OBJECT_0 )
							break;
					}
					else
					{
						notUpdate_ = 1;
						updateFileImpl_->DeleteAllFileTmp();
					}

					if( updateFileImpl_->IsOK() )
					{
						log_->WriteLog(LM_INFO, "��ʼ��������");
						_RestartService();
					}

					log_->WriteLog(LM_INFO, "=====");
				}
				catch(std::exception &e)
				{
					log_->WriteLog(LM_ERROR, e.what());
				}
				catch(...)
				{
					log_->WriteLog(LM_ERROR, "���³���δ֪�쳣: %d", ::GetLastError());
				}

				ret = ::WaitForSingleObject(exitEvent_, WAIT_TIME);
				if( ret != WAIT_TIMEOUT )
					break;
			}

			return 0;
		}
	};


	typedef AutoUpdate<update::GetUpdateFile, update::UpdateFile>	AutoUpdateFile;
}


#endif