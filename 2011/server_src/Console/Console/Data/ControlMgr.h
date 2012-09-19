#ifndef __CONSOLE_CONTROL_MANAGER_HPP
#define __CONSOLE_CONTROL_MANAGER_HPP

#include "DataHelper.h"
#include <vector>


namespace i8desk
{
	// forward declare
	class NetworkDataMgr;

	namespace manager
	{
		// --------------------------
		// class ControlMgr
		
		class ControlMgr
		{
			typedef std::tr1::function<void(const stdex::tString &)>	ErrorCallback;
			typedef NetworkDataMgr::AutoLock							AutoLock;

		private:
			NetworkDataMgr	*network_;
			ErrorCallback	errorCallback_;

		public:
			explicit ControlMgr(NetworkDataMgr *network);
			~ControlMgr();

		private:
			ControlMgr(const ControlMgr &);
			ControlMgr &operator=(const ControlMgr &);

		public:
			void RegisterError(const ErrorCallback &errorCallback);

		public:
			// ��װ��ԭ�����������з���.
			bool InstallProt(const std::vector<DWORD>& list, bool bProtAllArea);
			// ���ð�ȫ����
			bool EnableSafeCenter(const std::vector<DWORD>& list);
			// ����IE����
			bool EnableIEProt(const std::vector<DWORD>& list);
			// ���÷�������
			bool EnableDogProt(const std::vector<DWORD>& list);
			// ɾ����ԭ
			bool RemoveProt(const std::vector<DWORD>& list);
			// ��������
			bool ProtArea(const std::vector<DWORD>& list, const stdex::tString &ProtArea, const stdex::tString &UnProtArea);
			// �ػ���������
			bool ShutDown(const std::vector<DWORD>& list, bool bReBoot);
			// ʵʱ������Ϸ
			bool RealPush(const std::vector<DWORD>& list, const stdex::tString &strGids, DWORD dwLimitSpeed, DWORD dwConstructWay);
			// ִ��һ��EXE�ļ�
			bool ExecExeFile(const std::vector<DWORD>& list, const stdex::tString &szFile);
			// ������
			bool Chkdsk(const std::vector<DWORD>& list, const stdex::tString &strArea);
			// �ͻ�����Ϣ�鿴
			bool ViewClientInfo(const std::vector<DWORD>& list, DWORD flag, stdex::tString &text);
			// ֹͣ������߽�������
			bool KillProcSvr(const stdex::tString &file,  DWORD ip, bool bIsProcess);
			// Զ�̿���
			bool RemoteControl(DWORD ip, int bstart);
			// �õ��̷���Ŀ¼�����ļ��б�
			bool GetFileOrDir(const stdex::tString& szDir, DWORD nType, bool IsAbsPath, 
							 std::vector<stdex::tString>& ListFiles);
			// ��ȡ�ļ�
			bool GetFileData(const stdex::tString &dir, data_helper::Buffer &data);
			// �����ļ�
			bool SaveFileData(const stdex::tString &dir, data_helper::Buffer &data);

			// ��ȡ������Ϸͼ��
			bool GetGameIcons(data_helper::Buffer &data);
			// ��ȡ�������ͼ��
			bool GetClassIcons(data_helper::Buffer &data);

			// ���ICON
			bool AddIcon(DWORD gid, unsigned char* pData, size_t size);

			// ɾ��ICON
			bool DelIcon(DWORD gid);

			// ��ȡICON
			bool GetIcon(DWORD gid, unsigned char *data, size_t &size);

			// ֪ͨ�������д���ݿ�
			bool NotifySaveData();

			// ����PlugTool
			bool PlugToolOperate(long gid, DWORD op);

			// ��ȡPlugToolͼ��
			bool GetPlugIcon(long gid, unsigned char *data, size_t &size);

			// ɾ������������ʱ�ļ�
			bool DeleteTmpFiles();

			// ��ȡ��Ϸ���ڿͻ���
			bool GetViewGame(DWORD param, data_helper::ViewGameTraits::VectorType &viewGames);

			// ��ȡ�ͻ�����������Ϸ
			bool GetViewClient(DWORD param, data_helper::ViewClientTraits::VectorType &viewClients);

			// ��֤�û���������
			bool CheckUser(const stdex::tString &userName, const stdex::tString &psw);
		
			// ֪ͨ�޸�������Ϣ
			bool ModifyNetbarInfo();

			// ����ͻ���Ӳ����Ϣ
			bool SaveHardware();

			// ֪ͨ�����ļ���Ϣ
			bool NotifyReloadFile(const stdex::tString &path);

			// ֪ͨ������ɾ�����������ļ�
			bool NotifySmartClean(const std::vector<long> &gids);

			// �ж�Ӳ�̿ռ��Ƿ��㹻����
			bool NeedSmartClean(const stdex::tString &path, const ulonglong totalSize, bool &isEnough);
			// ͬ���������
			bool SyncTaskOperate(int cmd, long gid, const stdex::tString &SID, const stdex::tString &TaskName, const bool &isDelFile = false);
		};
	}
}



#endif