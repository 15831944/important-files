#ifndef __BUSINESS_SYNC_TASK_HPP
#define __BUSINESS_SYNC_TASK_HPP

#include "../Data/DataHelper.h"
#include <set>
namespace i8desk
{
	namespace business
	{
		// -----------------------------
		// SyncTask

		namespace SyncTask
		{
			// ���ͬ������
			bool AddSyncTask(const data_helper::SyncTaskTraits::ValueType &syncTask, const data_helper::GameTraits::VectorType &games);
			
			// �޸�ͬ������
			bool ModifySyncTask(const data_helper::SyncTaskTraits::ValueType &syncTask);

			// ɾ��ͬ������
			bool DelSyncTask(const stdex::tString &SID);
			
			// ���ͬ����Ϸ
			bool AddSyncGame(const stdex::tString &SID, long gid);

			// ɾ��ͬ����Ϸ
			bool DelSyncGame(const data_helper::SyncTaskStatusTraits::VectorType &syncGamestatus);

			// �޸�ͬ����Ϸ
			bool ModifySyncGame(const data_helper::SyncTaskTraits::ValueType &syncTask,	data_helper::SyncTaskStatusTraits::VectorType &syncGamestatus);

			// ����ͬ����Ϸ�����ݿ�
			bool SaveSyncGame(data_helper::SyncTaskStatusTraits::VectorType &syncGamestatus);

			// ��ȡ��������
			void GetAllTypes(const std::tr1::function<void(int, const stdex::tString &)> &callback);
			
			// �õ�����·��
			void GetAllGamesPath( std::set<stdex::tString> &pathes);

			// ���ͬ��IP���������������Ⱥ����ͬIP
			bool HasSameIP(const data_helper::SyncTaskTraits::ValueType &syncTask);

			// ���ͬ���������ƣ�������ͬ
			bool HasSameTaskName( const data_helper::SyncTaskTraits::ValueType &syncTask);

			// ����Ƿ���ͬ����������ͬλ�õ�����
			bool HasSameNodeDir( const data_helper::SyncTaskTraits::ValueType &syncTask);

			// ����Ƿ���ͬ��Դ·����Ŀ��·����ͬ
			bool HasSamePath( const data_helper::SyncTaskTraits::ValueType &syncTask, const data_helper::GameTraits::VectorType &games);

			// ��ȡͬ������ǰ�ٶ�
			uint64 GetSyncTaskSpeed();


			// ƥ��ͬ����Ϸ
			void MatchSyncTask(const data_helper::SyncTaskTraits::VectorType &syncTasks, data_helper::GameTraits::VectorType &syncGames);
			
			// ����ͬ����Ϸ��С
			void CumulateSize(const data_helper::GameTraits::VectorType &curGames, uint64 &gamesSize);
		
			// ��ȡ��������
			void GetTaskName( std::set<std::pair<stdex::tString, stdex::tString>> &tasknames);
			
			// ��������������ͬ������
            void SetSyncTaskStatus( const stdex::tString &SID, i8desk::SyncTaskState state);
		
			// Ѱ�Ҳ�ͬSID��ͬ������
			void FilterByNameID(const data_helper::SyncTaskTraits::MapType &syncTasks, data_helper::SyncTaskTraits::MapType &diffSyncTasks);
		
			// ��ȡ��ͬNameID��ͬ������Դ·��
			void GetSameNameIDSrcPaths(const stdex::tString &nameID, std::vector<stdex::tString> &srcPaths);

			// ��ȡ��ͬNameID��ͬ������Ŀ��·��
			void GetSameNameIDDstPaths(const stdex::tString &nameID, std::vector<stdex::tString> &dstPaths);

			// ɾ��ͬ������
			bool DeleteSyncGame(data_helper::SyncTaskTraits::ValueType &taskgame);

			// ֪ͨͬ��
			bool CanNotifyGame(data_helper::GameTraits::VectorType &games, const std::tr1::function<void(const stdex::tString &)> &callback);
		
		
			// ��ȡ����ͬ������
			void GetSyncTasks(data_helper::SyncTaskTraits::VectorType &syncTasks);

			// ��ȡ����ͬ������״̬
			void GetSyncTaskStatus(data_helper::SyncTaskStatusTraits::VectorType &synctaskStatus);
		
			// ��ȡͬ��״̬����
			stdex::tString GetStateDesc(const data_helper::SyncTaskStatusTraits::ValueType &val);

			// ��ȡͬ����������
			stdex::tString GetTaskNameBySID(const stdex::tString &SID);

			// ��ȡͬ����������
			stdex::tString GetTaskDesc(const data_helper::SyncTaskStatusTraits::ValueType &val);

			// ��ȡ��ͬ�����ͬ��״̬
			void TaskFilter(data_helper::SyncTaskStatusTraits::VectorType &taskstatus, const stdex::tString &SID);

			// ����ͬ����Ϸ
			void FindSync(LPCTSTR destText, const data_helper::SyncTaskStatusTraits::VectorType &tasks, data_helper::SyncTaskStatusTraits::VectorType &values);

			// ����ͬ����Ϸ
			void FindSync(LPCTSTR destText, const data_helper::SyncGameTraits::VectorType &tasks, data_helper::SyncGameTraits::VectorType &values);

			// ����ͬ��״̬
			void SetSyncStatus(data_helper::SyncTaskStatusTraits::VectorType &taskstatus, const stdex::tString &SID);
			
			// ��ȡ��ͬSID��ͬ����Ϸ
			void GetSyncGamesBySID(const stdex::tString &SID,  data_helper::GameTraits::VectorType &games);

			// �Ƿ�����ͣ
			bool IsPaused(const stdex::tString &SID);

			// �Ƿ�����ͣ
			bool IsRunning(const stdex::tString &SID);
		}
	}
}

#endif
