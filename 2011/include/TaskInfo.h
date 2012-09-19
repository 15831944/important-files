#ifndef __TASK_INFO_HPP
#define __TASK_INFO_HPP

#include <vector>

namespace i8desk
{
	
	//��������
	enum TaskType
	{
		tUserTask,
		tForceTask,
		tSmartForceTask	,	/*���Ի�ǿ��*/
		tTimeTask,			/*ʱ������*/
		tPlugToolTask,		//�������
	};

	enum TaskState 
	{
		tsChecking,			//���ڶԱ�
		tsQueue,			//�ȴ�����
		tsDownloading,		//��������
		tsSuspend,			//��ͣ����
		tsComplete,			//�������
		tsSelfQueue,		//�����Ŷ�
		tsWaitSeed,			//�ȴ�����
		tsHashmap,			//У������
		tsCopyfile,			//�����ļ�
		tsDeleteOldFile,	//�����ļ�
		tsCommit,			//�ϲ��ļ�
	};


	// �������
	enum TaskOperation
	{
		toAdd,		// ��������
		toDel,		// ɾ������
		toGetState,	// ��ȡ����״̬
		toSync,		// ֪ͨͬ������ͬ����Ϸ
		toSuspend,	// ��������
		toRestart,	// �ָ�����
		toAdjust,	// �����ȴ��������ȼ�
		toDelGame,	// ֪ͨͬ������ɾ����ϷĿ¼
	};


	// �������
	enum PlugCenterOperation
	{
		todownload  =1,	// ����
		tostart,	// ����
		tostop,		// ����	
		tooption,	// ѡ��
	};


	// �������ݽӿ�

	struct TaskInfo
	{
		long					gid_;			// gid
		int						state_;			// task state
		int						type_;			// task type
		unsigned short			connections_;	// ������
		unsigned long			downloadState_;	// ������״̬
		unsigned long			transferRate_;	// �����ٶ�
		unsigned long			timeLeft_;		// ʣ��ʱ��
		unsigned long			timeElapsed_;	// ����ʱ��
		unsigned long			progress_;		// ����
		ULONGLONG				bytesTotal_;	// ��������
		ULONGLONG				updateSize_;	// ������
		ULONGLONG				bytesTransferred_;// ������

		TaskInfo()
		{
			::memset(this, 0, sizeof(*this));
		}
	};



	typedef std::vector<TaskInfo> TasksInfo;
}


#endif