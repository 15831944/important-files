#ifndef __INIT_DOWNLOADER_HPP
#define __INIT_DOWNLOADER_HPP


#include "../../../include/Lava/massctl.h"
#include "LogHelper.h"


namespace i8desk
{

	namespace msc
	{


		// -----------------------------------------
		// MscInit
		// ��ʼ���������

		class MscInit
		{
		public:
			explicit MscInit(IRTDataSvr *rtDatasvr);
			~MscInit();

		private:
			MscInit(const MscInit &);
			MscInit &operator=(const MscInit &);
		};



		// ---------------------------------------
		// MscSpeed
		// MSC ���ٶ�

		struct MscSpeed
		{
			volatile long	upRate_;							// �ϴ����ٶ�
			volatile long	downRate_;							// �������ٶ�

			MscSpeed()
				: upRate_(0)
				, downRate_(0)
			{}

			// ��������
			void Update();

			// ����
			static MscSpeed &GetInstance()
			{
				static MscSpeed mscSpeed;
				return mscSpeed;
			}
		};


		// -----------------------------------------------
		// helper function

		// MscStop
		template<typename TaskItemPtrT>
		inline void MscPause(const TaskItemPtrT &taskItem)
		{
			::msc_stop(taskItem->GetTaskName().c_str());
			Log(LM_INFO, _T("��ͣ����, GID=%u"), taskItem->GetGid());
		}

		// MscRestart
		template<typename TaskItemPtrT>
		inline void MscResume(const TaskItemPtrT &taskItem)
		{
			::msc_restart(taskItem->GetTaskName().c_str());
			Log(LM_INFO, _T("�ָ�����, GID=%u"), taskItem->GetGid());
		}

		// MscDelete
		template<typename TaskItemPtrT>
		inline void MscDelete(const TaskItemPtrT &taskItem)
		{
			if( ::msc_delete(taskItem->GetTaskName().c_str()) == 0 )
				Log(LM_INFO, _T("ɾ������ɹ�,GID = %d"), taskItem->GetGid());
			else
				Log(LM_ERROR, _T("ɾ������ʧ��,GID = %d"), taskItem->GetGid());
		}

		// MscDeleteEx
		template<typename TaskItemPtrT>
		inline void MscDeleteEx(const TaskItemPtrT &taskItem , int flag)
		{
			if( ::msc_deleteex(taskItem->GetTaskName().c_str(), flag) == 0 )
				Log(LM_INFO, _T("ɾ������ɹ�,GID = %d, flag = %d"), taskItem->GetGid(), flag);
			else
				Log(LM_ERROR, _T("ɾ������ʧ��,GID = %d, flag = %d"), taskItem->GetGid(), flag);
		}

		// MscRebuild
		template<typename ProgressFuncT, typename TaskItemPtrT>
		inline bool MscRebuild(BSTR seed, const wchar_t *mdes, UINT mode, wchar_t *taskName, 
			ProgressFuncT progressfn, const TaskItemPtrT &taskItem)
		{
			int ret = ::msc_rebuild(seed, mdes, mode, taskName, progressfn, taskItem.get());
			if( ret != 0 )
				Log(LM_ERROR, _T("msc_rebuildʧ��! code=%d"), ret);

			return ret == 0;
		}

		// MscTaskList
		inline bool MscTaskList(BSTR &taskList, size_t &cnt)
		{
			int ret = ::msc_gettasklist(&taskList, &cnt);
			if( ret != 0 )
				Log(LM_WARNING, _T("msc_gettasklistʧ��! code=%d"), ret);

			return ret != 0;
		}

		template<typename TaskItemPtrT, typename MscProgressT>
		inline bool MscProgress(const TaskItemPtrT &taskItem, MscProgressT pdp)
		{
			int ret = ::msc_getprogress(taskItem->GetTaskName().c_str(), pdp);
			if( ret < 0 )
				Log(LM_WARNING, _T("msc_getprogressʧ�ܣ�GID = %u, code = %d"), taskItem->GetGid(), ret);

			return ret >= 0;
		}

		template<typename TaskItemPtrT, typename MscProgressT>
		bool MscCommitEx(const TaskItemPtrT &taskItem, MscProgressT progress)
		{
			int ret = ::msc_commitex(taskItem->GetTaskName().c_str(), NULL, NULL, progress, taskItem.get());
			if( ret != 0 )
				Log(LM_ERROR, _T("�ύ����ʧ��.GID = %u, code = %d"), taskItem->GetGid(), ret);

			return ret == 0;
		}
	}
}

#endif