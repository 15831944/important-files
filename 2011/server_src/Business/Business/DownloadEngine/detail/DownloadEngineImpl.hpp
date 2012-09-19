#ifndef __DOWNLOAD_ENGINE_IMPL_HPP
#define __DOWNLOAD_ENGINE_IMPL_HPP

#include "Queue.hpp"
#include "../../../../../include/AsyncIO/iocp/Dispatcher.hpp"
#include "../../../../../include/MultiThread/Thread.hpp"
#include "../../I8ExInfoMgrS.h"


namespace engine
{
	namespace detail
	{

		// ------------------------------------------
		// class DownloadEngineImpl

		// Scheduler


		struct Task;
		typedef std::tr1::shared_ptr<Task> TaskPtr;
		
		
		class DownloadEngineImpl
		{
			typedef BlockQueue<TaskPtr> TaskQueue;
			typedef async::thread::AutoEvent Event;

			enum { MAX_RUNNING = 3 };		// ���ͬʱ������

			TaskQueue tasks_;				// �������
			Event exit_;					// �˳��¼�
		
			async::iocp::IODispatcher dispath_;
			volatile long running_;			// ��ǰ���ظ���

			async::thread::ThreadImplEx thread_;

		public:
			explicit DownloadEngineImpl();

		private:
			DownloadEngineImpl(const DownloadEngineImpl &);
			DownloadEngineImpl &operator=(const DownloadEngineImpl &);
			

		public:
			void Start();
			void Stop();

            void Add(long type, long gid, long priority, i8desk::ISvrPlugMgr *plugMgr, CI8ExInfoMgrS* gameExInfoMgr);

		private:
			void _OnError(const TaskPtr &task);
			void _OnComplate(const TaskPtr &task);

			DWORD _Thread();
		};
	}
}




#endif