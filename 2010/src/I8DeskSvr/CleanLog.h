#ifndef __CLEAN_LOG_HPP
#define __CLEAN_LOG_HPP

#include "../../include/Utility/FileOperator.hpp"
#include "../../include/MultiThread/ThreadPool.hpp"

#include "../../include/plug.h"

namespace i8desk
{

	// ----------------------------------------
	// class CleanLog

	// �����־�ļ����ڣ��������7�죬��ɾ��

	

	class CleanLog
	{
	private:
		// ���ʱ��
		static const size_t PeriodTime	= 24 * 60 * 60 * 1000;
		// �ӳ�ʱ��
		static const size_t DelayTime	= 10 * 60 * 1000;
		async::thread::QueueTimerPool timer_;

		ILogger*	log_;
	public:
		explicit CleanLog(ILogger *log)
			: timer_(std::tr1::bind(&CleanLog::_ThreadImpl, this, std::tr1::placeholders::_1))
			, log_(log)
		{}
		~CleanLog()
		{
			
		}

	public:
		// Start timer queue
		bool Start()
		{
			if( !timer_.Call(DelayTime, PeriodTime) )
			{
				log_->WriteLog(LM_ERROR, _T("����������־�̳߳���"));
				return false;
			}

			return true;
		}

		// stop timer 
		bool Stop()
		{
			return timer_.Cancel();
		}

	private:
		// timer routine
		void _ThreadImpl(BOOLEAN outTime)
		{
			using namespace utility;

			static FilesOperator<CheckFileTimeT, DeleteFileT> op;

			if( outTime == TRUE )
			{
				static std_string dir(GetAppPath() + _T("Log/"));
				
				log_->WriteLog(LM_DEBUG, _T("�������������־..."));
				op(dir);
			}
			
		}
	};

}



#endif