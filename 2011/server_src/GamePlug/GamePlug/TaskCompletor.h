#ifndef __I8DESK_TASK_COMPLETOR_HPP
#define __I8DESK_TASK_COMPLETOR_HPP


#include "../../../include/MultiThread/Lock.hpp"


namespace i8desk
{
	// forward declare
	class TaskItem;
	typedef std::tr1::shared_ptr<TaskItem>	TaskItemPtr;


	// ---------------------------------------
	// class TaskCompletor

	class TaskCompletor
	{
	private:
		TaskItemPtr					taskItem_;				// ��������
		ISvrPlugMgr					*plugMgr_;				
		IRTDataSvr					*rtDataSvr_;			// ���ݽӿ�
		ISysOpt						*sysOpt_;				// ѡ���

		async::thread::AutoEvent	&exit_;					// �˳��¼�
		std::wstring				plRoot_;				// PL root

	public:
		TaskCompletor(const TaskItemPtr &taskItem,
			ISvrPlugMgr *plugMgr, IRTDataSvr *rtDatasvr, ISysOpt *sysOpt, async::thread::AutoEvent &exit);
		~TaskCompletor();

	private:
		TaskCompletor(const TaskCompletor &);
		TaskCompletor &operator=(const TaskCompletor &);

	public:
		void Run();		// ʧ���׳��쳣
		void Clear();	// �����ʱ�ļ�
		void Stop();

	private:
		void _ReplaceIndex(const stdex::tString &);
		void _DeleteOldFiles(const stdex::tString &);

	private:
		void _RunImpl();
		void _ClearImpl();
	};

	typedef std::tr1::shared_ptr<TaskCompletor> TaskCompletorPtr;
}

#endif