#ifndef __I8DESK_TASK_DISPATCHER_HPP
#define __I8DESK_TASK_DISPATCHER_HPP

#include "../../../include/MultiThread/Thread.hpp"


#include "SchedulerQueue.h"
#include "TaskImpl.h"
#include "TaskPolicy.h"

#include "TaskSerialize.h"
#include "TaskDispatchImpl.h"

#include "DownloadEngine.h"

namespace i8desk
{

	
	// -------------------------------------------------
	// class TaskDispatcher

	// �������

	class TaskDispatcher
		: private task_policy::UpdateAddTask< TaskDispatcher >
		, private task_policy::CheckAddTask< TaskDispatcher >
		, private task_policy::CheckDownloadTask< TaskDispatcher >
		, private task_helper::TaskSerialize< TaskDispatcher, task_helper::ProductTaskItem >
		, public task_helper::TaskDispatchImpl< TaskDispatcher, TaskImplPtr >
	{
		// ��������������ȴ���
		static const size_t MaxWaitting = 4096; 
		static const size_t MaxDownload = 3;

	public:
		typedef task_helper::ProductTaskItem							ProductTaskType;		// �ڲ�����ʹ������
		typedef TaskImplPtr												TaskType;				// ��������

		typedef TaskDispatchImpl<TaskDispatcher, TaskType>				TaskDispatchImplType;	// �������ʵ������

		typedef task_policy::UpdateAddTask<TaskDispatcher>				UpdateAddTaskPolicy;
		typedef task_policy::CheckAddTask<TaskDispatcher>				CheckAddTaskPolicy;		// ������Ӳ���
		typedef task_policy::CheckDownloadTask<TaskDispatcher>			CheckDownloadTaskPolicy;// �������ز���
		typedef task_helper::TaskSerialize<TaskDispatcher, ProductTaskType>	TaskSerializeType;	// ���л�����

		typedef SchedulerQueue<TaskType, MaxDownload>					TaskQueue;				// ���ض���

		typedef DownloadEngine::EventCallback							EventCallback;		// �¼��ص�

	private:
		ISvrPlugMgr	*plugMgr_;
		IRTDataSvr	*rtData_;
		ISysOpt		*sysOpt_;
		EventCallback evenCallback_;

	private:
		async::thread::ThreadImplEx thread_;
		TaskQueue taskQueue_;

	public:
		TaskDispatcher(ISvrPlugMgr *plugMgr, IRTDataSvr *rtData, ISysOpt *sysOpt);
	
	public:
		void Start();
		void Stop();

		void Register(const EventCallback &callback);
		
	public:
		/*
			1. ����Ƿ�Ϊ������
			2. ��������ض����У���ֹͣ���ز�ȥ��������ڵȴ������У���ȥ��
			3. ���������񵽵ȴ�����
		*/
		void AddTask(const task_helper::ProductTaskItem &item);

		// ɾ������
		void DeleteTask(long gid);

		// ��������������
		void SuspendTask(long gid);

		// �ָ�����������
		void ResumeTask(long gid);
	
		// �������ȼ�
		void AdjustTask(long gid, int priority);

		// �ö� 
		void PutTop(long gid);

		// �õ�
		void PutBottom(long gid);

		// ����
		void Save();

		//
		template<typename ContainerT>
		void GetTasksInfo(ContainerT &container)
		{
			// ��������������
			using namespace std::tr1::placeholders;
			typedef typename TaskQueue::value_type value_type;
			taskQueue_.ForEach(std::tr1::bind(&task_helper::PushTaskInfo<value_type, ContainerT>,
				_1, &container));
		}


	private:
		// ��������;
		void _TaskProductorImpl(const task_helper::ProductTaskItem &item);

		// �������ʵ�� 
		void _AddTaskImpl(const TaskType &task);

		// ��������ʵ��
		void _DownloadTaskImpl(const TaskType &task);

		// �������ʵ��
		void _ComplateTaskImpl(const TaskType &task);
		
		// ��������ʵ��
		void _ErrorTaskImpl(const TaskType &task);

		// ��ʼ����ʵ��
		void _StartImpl();

		// ��������ʵ��
		void _QuitImpl();

	private:
		DWORD _Thread();
	};
}



namespace utility
{
	typedef i8desk::TaskDispatcher::TaskDispatchImplType::OperateItem			TaskOperateItem;

	template<>
	struct ObjectFactory<TaskOperateItem>
	{
		typedef async::memory::FixedMemoryPool<true, sizeof(TaskOperateItem)>	PoolType;
		typedef ObjectPool<PoolType>											ObjectPoolType;
	};
}



#endif