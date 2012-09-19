#ifndef __TASK_DISPATCH_IMPL_HPP
#define __TASK_DISPATCH_IMPL_HPP


#include "../../../include/AsyncIO/iocp/IOCP.hpp"
#include "../../../include/MemoryPool/FixedMemoryPool.hpp"
#include "../../../include/Utility/ObjectFactory.hpp"

namespace i8desk
{
	namespace task_helper
	{

		// ---------------------------------
		// class TaskDispatchImpl

		// �������ʵ��
		template<typename ImplT, typename TaskT>
		class TaskDispatchImpl
		{
			typedef TaskT	TaskType;

			typedef async::thread::AutoCriticalSection	Mutex;
			typedef async::thread::AutoLock<Mutex>		AutoLock;

		public:
			struct OperateItem;
			typedef std::tr1::shared_ptr<OperateItem> OperateItemPtr;

		private:
			async::iocp::Iocp iocp_;
			Mutex mutex_;

		protected:
			// ����������
			enum { UNKNOWN = 0, TO_START, TO_ADD, TO_DOWNLOAD, TO_COMPLATE, TO_ERROR, TO_QUIT };
		protected:
			TaskDispatchImpl()
			{
				iocp_.Create(0);
			}
		protected:
			// �������
			struct OperateItem
				: public utility::NewDeleteBase<OperateItem>
			{
				TaskType task_;
				int taskOperate_;

				explicit OperateItem(int taskOperate)
					: taskOperate_(taskOperate)
				{}
				OperateItem(const TaskType &item, int taskOperate)
					: task_(item)
					, taskOperate_(taskOperate)
				{}
			};
			

		protected:
			template<typename T>
			bool Push(const T *val)
			{
				return iocp_.PostStatus(reinterpret_cast<ULONG_PTR>(val), 0, 0);
			}

			template<typename T>
			DWORD Pop(T *&value, DWORD timeOut)
			{
				DWORD dwBytes = 0;
				LPOVERLAPPED overlapped = NULL;

				iocp_.GetStatus(reinterpret_cast<ULONG_PTR *>(&value), &dwBytes, &overlapped, timeOut);

				return ::GetLastError();
			}

		public:
			void PostStart()
			{
				if( !_PostTask(TO_START) )
					Log(LM_ERROR, _T("Ͷ�ݿ�ʼ�����߳�ʧ��!"));
			}

			void PostQuit()
			{
				if( !_PostTask(TO_QUIT) )
					Log(LM_ERROR, _T("Ͷ���˳������߳�ʧ��!"));
			}

			void PostAdd(const TaskType &taskItem)
			{
				if( !_PostTask(taskItem, TO_ADD) )
					Log(LM_ERROR, _T("Ͷ���������ʧ��!"));
			}

			void PostDownload(const TaskType &taskItem)
			{
				if( !_PostTask(taskItem, TO_DOWNLOAD) )
					Log(LM_ERROR, _T("Ͷ����������ʧ��!"));
			}

			void PostComplate(const TaskType &taskItem)
			{
				if( !_PostTask(taskItem, TO_COMPLATE) )
					Log(LM_ERROR, _T("Ͷ����������ʧ��!"));
			}

			void PostError(const TaskType &taskItem)
			{
				if( !_PostTask(taskItem, TO_ERROR) )
					Log(LM_ERROR, _T("Ͷ�ݴ�������ʧ��!"));
			}

		private:
			// �������
			bool _PostTask(const TaskType &item, int taskType)
			{
				OperateItem *operate(new OperateItem(item, taskType));

				return Push(operate);
			}

			bool _PostTask(int taskType)
			{
				OperateItem *operate(new OperateItem(taskType));

				return Push(operate);
			}

		};
	}
}




#endif