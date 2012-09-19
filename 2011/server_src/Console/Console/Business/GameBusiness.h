#ifndef __BUSINESS_GAME_HPP
#define __BUSINESS_GAME_HPP


#include "../Data/DataHelper.h"
#include "../../../../include/TaskInfo.h"
#include <set>

namespace i8desk
{
	namespace business
	{
		// -----------------------------
		// Game

		

		namespace Game
		{
			const extern stdex::tString AutoUpdate;
			const extern stdex::tString ManualUpdate;


			// �������ˡ��ͻ���·��
			void HandlePath(data_helper::GameTraits::ValueType &val);

			// ������Ϸ���з�ʽ����
			void HandleRunTypeDesc(const data_helper::RunTypeTraits::VectorType &runTpes, stdex::tString &desc);

			// ɾ����Ϸ
			void Delete(const data_helper::GameTraits::ValueType &val);

			// ������Ϸ���з�ʽ
			bool SetRunType(const data_helper::GameTraits::ValueType &game, const data_helper::RunTypeTraits::VectorType &runType);

			// ������Ϸ���ָ������
			void AddRunType(const stdex::tString &AID);

			// ɾ��������Ϸָ������
			void EraseRunType(const stdex::tString &AID);
				 

			// �Ƿ���Ҫ����
			bool CouldDownload(const data_helper::GameTraits::ValueType &val);


			// �õ��û��Զ��������ϷGID, ��������
			unsigned long GetCustomGID();

			// ͨ��Name������Ϸ
			bool CheckByName(const stdex::tString &name, i8desk::data_helper::GameTraits::ValueType &findGame);

			// �õ��������ȼ�����
			LPCTSTR GePriorityDesc(DWORD priority);

			// �õ�״̬����
			LPCTSTR GetStatusDesc(const data_helper::GameTraits::ValueType &game);

			// ��ȡ���·�ʽ
			void GetUpdateDesc(const std::tr1::function<int(LPCTSTR)> &callback);

			// ���ø��·�ʽ
			void SetUpdate(const data_helper::GameTraits::ValueType &game, const stdex::tString &updateDesc);

			// ��ȡ�������ȼ�����
			void GetPriorityDesc(const std::tr1::function<int(LPCTSTR)> &callback);

			// ����״̬����
			void SetStatusDesc(const data_helper::GameTraits::ValueType &game, const stdex::tString &desc);

			// �õ����з�ʽ����
			const stdex::tString &GetRunTypeDesc(const data_helper::GameTraits::ValueType &game);

			// �õ���Ϸͼ��
			const utility::ICONPtr &GetIcon(const data_helper::GameTraits::ValueType &game);

			// ������ϷICON
			bool SetIcon(const data_helper::GameTraits::ValueType &game, const utility::ICONPtr &bmp);

			// ��������Ϸ
			void ClassFilter(const data_helper::GameTraits::VectorType &games, data_helper::GameTraits::VectorType &filterGames, const stdex::tString &CID);

			// ������Ϸ
			void CenterFilter(const data_helper::GameTraits::MapType &games, data_helper::GameTraits::VectorType &curGames);


			// ������ֵ��Ϸ
			void CenterI8PlayFilter(const data_helper::GameTraits::MapType &games, data_helper::GameTraits::VectorType &centerGames);

			// δ������Ϸ
			void NoDownloadFilter(const data_helper::GameTraits::MapType &games, data_helper::GameTraits::VectorType &noDownloadGames);

			// ����������Ϸ
			void RecentFilter(const data_helper::GameTraits::MapType &games, data_helper::GameTraits::VectorType &recentGames);
		
			// ����ɾ����Ϸ
			void DeleteFilter( data_helper::GameTraits::VectorType &recentGames);

			// ��Ҫ���µ���Ϸ
			void UpdateFilter(const data_helper::GameTraits::MapType &games, data_helper::GameTraits::VectorType &updateGames);
		
			// ������Ϸ
			void LocalAllFilter(const data_helper::GameTraits::MapType &games, data_helper::GameTraits::VectorType &curGames);
			void LocalFilter(const data_helper::GameTraits::MapType &games, data_helper::GameTraits::VectorType &localGames, const stdex::tString &CID);
		

			// ������Ϸ
			void FindGame(LPCTSTR destText, const data_helper::GameTraits::VectorType &games, data_helper::GameTraits::VectorType &values);
		
			// ��Ϸ����
			bool TaskOperate(long gid, TaskOperation op);

			// ������Ϸ����
			bool LocalTaskOperate(const data_helper::GameTraits::ValueType &game, TaskOperation op, bool isForce);
	
			// ��ȡ������Ϸ�������̷�
			void GetLocalDrv(std::set<TCHAR> &drvs);

			// ��ȡ��ɾ����Ϸ�б�
			void GetCleanGames(data_helper::GameTraits::VectorType &games, TCHAR drv, ulonglong size, int iKeepDay, bool greateHundred);
		
			// �ж�Ӳ�̿ռ��Ƿ��㹻��ѡ��������Ϸ
			bool IsEnoughSpace(const stdex::tString &path, const ulonglong totalSize);

			// �õ�������Ϸ��С
			ulonglong GetSize(data_helper::GameTraits::VectorType &games);

			// ��ȡ��Ϸ�浵·��
			stdex::tString GetSavePath(const data_helper::GameTraits::ValueType &val);
		
			// ���ô浵·��
			void SetSavePath(data_helper::GameTraits::ValueType &val, const stdex::tString &path);
		
			// ͳ��������Դ����
			void CummulateCenterGame(std::map<int, size_t> &centerGames);

			// ͳ�Ʊ�����Ϸ����
			void CummulateLocalGame(std::map<stdex::tString, size_t> &centerGames);

			// ��������������Ϣ�ص�
			typedef std::tr1::function<int (LPCTSTR)> KeepDayDescCallback;
			typedef std::tr1::function<int (int, DWORD_PTR)> KeepDayDataCallback;
			void KeepDayDesc(const KeepDayDescCallback &descCallback, const KeepDayDataCallback &dataCallback);

			// ͨ��GID�õ���Ϸ����
			stdex::tString  GetGameName(const long gid);

			// ͨ��GID�õ���Ϸ�����·��
			stdex::tString  GetSvrPath(const long gid);
			
			// ͨ��GID�õ���Ϸ���
			stdex::tString  GetClass(const long gid);

			// ͨ��GID�õ���Ϸ��С
			ulonglong GetGameSize(const long gid);

            // ͳ����Ϸ��С
            ulonglong GetGameSize(const std::vector<ulong>& gid);

            // ͨ��GID�õ���Ϸ��Ϣ
            db::TCustomGamePtr GetGameInfo(const long gid);

		}
	}
}



#endif