#ifndef _i8desk_concore_inc_
#define _i8desk_concore_inc_



#include "plug.h"
#include "Markup.h"
#include "define.h"

#include <map>
#include <string>
#include <vector>
#include <set>
#include <memory>

#define RTDATASVR_PORT	17918
#define GAMEMGR_PORT	17790

#define UDP_PORT	17900
#define BUF_SIZE	10240

#define WM_CLIENT_NOTIFY		(WM_USER+3128)
#define WM_TASK_NOTIFY			(WM_USER+3129)
#define WM_OFFLINE_NOTIFY		(WM_USER+3130)
#define WM_SERVER_LOG			(WM_USER+3131)

#define RT_COMP_BOOT		"����ˢ��"
#define RT_MENU_RUN			"���в˵�"
#define RT_GAME_RUN			"������Ϸ"

#define VDISK_I8DESK_TEXT	"��Ʒ����������"
#define VDISK_OTHER_TEXT	"������������"

#define EXEC_DIR "Data\\BootExec"

//�ж���
enum {
	NETBAR_COL_NAME			 = 0,
	NETBAR_COL_GID,
	NETBAR_COL_STATUS,
	NETBAR_COL_AUTOUPT,
	NETBAR_COL_PRIORITY,
	NETBAR_COL_RUNTYPE,
	NETBAR_COL_SVRCLICK,
	NETBAR_COL_UPDATETIME,
	NETBAR_COL_SIZE,
	NETBAR_COL_GAMEEXE,
	NETBAR_COL_SVRPATH,
	NETBAR_COL_GAMECLASS,
	NETBAR_COL_DOWNPRIORITY,
	NETBAR_COL_GAMESOURCE,

	NETBAR_COL_COUNT
};

enum {
	MACHINE_NAME = 0,
	MACHINE_STATUS,
	MACHINE_AREA,
	MACHINE_IP,
	MACHINE_PROTINSTALL,
	MACHINE_ALLAREA,
	MACHINE_PROTAREA,
	MACHINE_PROTVER,
	MACHINE_MENUVER,
	MACHINE_CLISVRVER,	
	MACHINE_MAC,
	MACHINE_MARK,
	MACHINE_NETGATE,
	MACHINE_DNS,

	MACHINE_COL_COUNT
};

namespace i8desk
{
	static UINT g_nOptApplyMsg = ::RegisterWindowMessage("i8desk System Option Apply Message");

//����̨Ӧ�õ����ݽṹ��Ӧ�����Ͷ���
#define DECLARE_CONSOLE_TYPE(key_type, value_type) \
	typedef tag##value_type value_type; \
	typedef std::tr1::shared_ptr<value_type> value_type##_Ptr; \
	typedef std::map<key_type, value_type##_Ptr> value_type##Map; \
	typedef value_type##Map::iterator value_type##MapItr; \
	typedef value_type##Map::const_iterator value_type##MapCItr; \
	typedef std::vector<value_type##_Ptr> value_type##Vector; \
	typedef value_type##Vector::iterator value_type##VectorItr; \
	typedef value_type##Vector::const_iterator value_type##VectorCItr; \
	typedef std::vector<value_type> value_type##List; \
	typedef value_type##List::iterator value_type##ListItr; \
	typedef value_type##List::const_iterator value_type##ListCItr;

	typedef struct tagVDiskInfo : public db::tVDisk {
		tagVDiskInfo() { memset(this, 0, sizeof(db::tVDisk)); }
	}tagVDiskInfo;

	DECLARE_CONSOLE_TYPE(std::string, VDiskInfo)

#define RT_UNKNOWN	"δ����"
#define RT_LOCAL	"���ظ���"
#define RT_VDISK	"������"
#define RT_DIRECT	"������,ֱ������"

	typedef struct tagGameRunType : public db::tGameArea {
		std::string AreaName;
	}tagGameRunType;

	DECLARE_CONSOLE_TYPE(std::string, GameRunType)

	//��Ϸ��Ϣ
	typedef struct tagGameInfo : public db::tGame
	{
		DWORD dwUpdateStatus;
		std::string szUpdateStatus;

		GameRunTypeList RunTypes;
		std::string RunTypeDesc;
		bool selected;
		tagGameInfo(DWORD gid = 0) 
		{
			memset(this, 0, sizeof(db::tGame));
			IfUpdate = IfDisplay = TRUE;
			GID = gid;
		}
		std::string GetStatusText()
		{
			if (szUpdateStatus.size())
				return szUpdateStatus;

			if (Status == 0)
				return std::string("δ����");

			if (GID < MIN_IDC_GID)
				return std::string("������");

			if (SvrVer == IdcVer)
				return std::string("������");

			return std::string("�и���");
		}
		std::string GetPriority()
		{
			if (Priority == 4)
				return std::string("��:��ɾ");
			else if (Priority == 3)
				return std::string("�ϸ�:�ݲ�ɾ");
			else if (Priority == 2)
				return std::string("��:��ɾ");
			return std::string("��:��ɾ");
		}
	}tagGameInfo;

	DECLARE_CONSOLE_TYPE(DWORD, GameInfo)

	typedef struct tagAreaInfo : public db::tArea {
		tagAreaInfo() {	memset(this, 0, sizeof(db::tArea)); }
	}tagAreaInfo;

	DECLARE_CONSOLE_TYPE(std::string, AreaInfo)

	typedef struct tagDefClass : public db::tClass {
		tagDefClass() {	memset(this, 0, sizeof(db::tClass)); }
		BOOL IsIdc;
		size_t ResNum;
		ulonglong TotalSize; 
	}tagDefClass;

	DECLARE_CONSOLE_TYPE(std::string, DefClass)

	typedef struct tagMachine : public db::tClient {
		bool		online;
		bool        selected;
		tagMachine() { memset(this, 0, sizeof(db::tClient)); }
	}tagMachine;

	DECLARE_CONSOLE_TYPE(std::string, Machine)

	typedef struct tagUser : public db::tUser {
		tagUser() { memset(this, 0, sizeof(db::tUser)); }
	}tagUser;

	DECLARE_CONSOLE_TYPE(std::string, User)

	typedef enum BootTaskArea
	{
		TASK_AREA_ALL	= 0,		//��ʾ�������ʺ����еļ����
		TASK_AREA_AREA	= 1,		//��ʾ�������ʺ�ĳһ����
		TASK_AREA_CMP	= 2,		//��ʾ�������ʺ�ĳһ�����
	}BootTaskArea;

	typedef struct tagBootTask : public db::tCmpStartTask {
		tagBootTask() { memset(this, 0, sizeof(db::tCmpStartTask)); }
	}tagBootTask;

	DECLARE_CONSOLE_TYPE(std::string, BootTask)

	typedef struct tagFavorite : public db::tFavorite {
		tagFavorite() { memset(this, 0, sizeof(db::tFavorite)); }
	}tagFavorite;

	DECLARE_CONSOLE_TYPE(std::string, Favorite)

	typedef db::tBarSkin tagBarSkin;

	DECLARE_CONSOLE_TYPE(std::string, BarSkin)

	typedef struct tagSyncTask : public db::tSyncTask {
		tagSyncTask() { memset(this, 0, sizeof(db::tSyncTask)); }
	} tagSyncTask;

	DECLARE_CONSOLE_TYPE(std::string, SyncTask)

	typedef struct tagSyncGame : public db::tSyncGame {
		tagSyncGame() { memset(this, 0, sizeof(db::tSyncGame)); }
	} tagSyncGame;

	DECLARE_CONSOLE_TYPE(uint32, SyncGame)	
	
	//���ߺ���
	inline BOOL VariantToBOOL(_variant_t& var)
	{
		if (var.vt == VT_NULL)
			return FALSE;
		return ((bool)var == TRUE);
	}
	inline DWORD VariantToDWORD(_variant_t& var)
	{
		if (var.vt == VT_NULL)
			return 0;
		return (long)var;
	}

	inline std::string VariantToString(_variant_t& var)
	{
		if (var.vt == VT_NULL)
			return std::string("");
		return std::string((LPCSTR)_bstr_t(var));
	}

	void GetPY(std::string& sChinese, std::string& result);
	bool IsValidDirName(std::string strDir);

	DWORD GetBufCrc32(BYTE* buffer, DWORD dwSize);

	void InitPackage(_packageheader* pheader, WORD cmd, int nExtraLen = 0);
	std::string CreateGUIDString();
	std::string MakeTimeString(DWORD dwTime);
	std::string MakeIpString(DWORD dwIP);

	DWORD MakeTimeFromFileTime(FILETIME& ft);
	void MekeFileTimeFromTime(DWORD dwTime, FILETIME& ft);

	bool IsI8DeskClassGUID(const std::string& ID);
	bool IsI8DeskClassName(LPCTSTR lpszName);
	bool IsValidIP(LPTSTR lpszIP);
	void TrimString(std::string& str);
	void TrimString(char *str);
	bool IntoXmlNode(CMarkup& xml, LPCSTR lpszPath);

//������Ӧ��ʱ����
#define CONSOLE_CMD_TIMEOUT (60 * 10) //S

	class CTcpSocket
	{
	public:
		CTcpSocket() : m_Sck(INVALID_SOCKET), m_bConnected(false) {}
		~CTcpSocket()	{ CloseServer(); }
		void CloseServer();

		bool IsConnected() const { return m_bConnected; }
		bool ConnectServer(LPCTSTR szIpAddr, DWORD wPort = RTDATASVR_PORT, int timeout = -1);
		bool ReconnectServer(int timeout = -1)
		{
			return ConnectServer(m_strIP.c_str(), m_dwPort, timeout);
		}

		int Send(const char *data, int len, int flags = 0)
		{
			ASSERT(m_Sck != INVALID_SOCKET);
			return ::send(m_Sck, data, len, flags);
		}

		int Recv(char *pbuf, int len, int flags = 0)
		{
			ASSERT(m_Sck != INVALID_SOCKET);
			return ::recv(m_Sck, pbuf, len, flags);
		}

	protected:
		CLock  m_lock;
		std::string m_strIP;
		DWORD m_dwPort;
	private:
		bool   m_bConnected;	
		SOCKET m_Sck;
	};

	class CSimpleSocket : public CTcpSocket
	{
	public:
		//���ppInData = NULL,��ʾ������Ӧ������.
		bool ExeCmd(
			LPCSTR pOutData, 
			int nOutLen,
			LPSTR* ppInData, 
			int* pnInSize,
			std::string& ErrInfo);
	};

	#define GET_DRVLIST		0
	#define GET_DIRLIST		1
	#define GET_FILELIST	2

	class CDbMgr
	{
	private:
		CSimpleSocket* m_pSocket;
	public:
		CDbMgr(CSimpleSocket* pSock) : m_pSocket(pSock) {  }
		~CDbMgr() { }
		bool IsConnected(void) const { return m_pSocket->IsConnected(); }
	public:
		//����
		bool HeartBeat(void);
		bool ReloadCacheFile(const char *pathname, std::string& ErrInfo);

		//ͬ���������
		bool GetAllSyncTask(SyncTaskMap& SyncTasks, std::string& ErrInfo);
		bool GetAllMirrorServer(SyncTaskMap& SyncTasks, std::string& ErrInfo);
		bool AddSyncTask(const SyncTask& SyncTask, std::string& ErrInfo);
		bool DelSyncTask(const std::string& ID, std::string& ErrInfo);
		bool ModifySyncTask(const SyncTask& SyncTask, std::string& ErrInfo, uint64 mask = ~0LL);

		//�Զ���ͬ����Ϸ����
		bool AddSyncGame(const std::string& SID, uint32 gid, std::string& ErrInfo);
		bool GetTaskSyncGames(SyncGameMap& SyncGames, const std::string& SID, std::string& ErrInfo);
		bool DelSyncGames(const std::string& SID, std::string& ErrInfo);
		bool DelSyncGames(const std::string& SID, uint32 gid, std::string& ErrInfo);

		//��������
		bool GetAllArea(AreaInfoMap& AreaInfos, std::string& ErrInfo);
		bool AddArea(const AreaInfo& AreaInfo, std::string& ErrInfo);
		bool DelArea(const std::string& ID, std::string& ErrInfo);
		bool ModifyArea(const AreaInfo& areaInfo, std::string& ErrInfo, uint64 mask = ~0LL);

		//������
		bool GetAllClass(DefClassMap& ClassInfos, std::string& ErrInfo);
		bool AddClass(const DefClass& defClass, std::string& ErrInfo);
		bool DelClass(const std::string& ID, std::string& ErrInfo);
		bool ModifyClass(const DefClass& defClass, std::string& ErrInfo, uint64 mask = ~0LL);

		//�����̹���
		bool GetAllVDisk(VDiskInfoMap& VDiskInfos, std::string& ErrInfo);
		bool AddVDisk(const VDiskInfo& vdisk, std::string& ErrInfo);
		bool DelVDisk(const std::string& ID, std::string& ErrInfo);
		bool ModifyVDisk(const VDiskInfo& vdisk, std::string& ErrInfo);

		//��Ϸ��Ϣ
		bool CheckGameNameCheck(const std::string& Name, DWORD gid, std::string& ErrInfo, DWORD& rgid, bool& IsLocal);
		bool GetAllGame(GameInfoMap& GameInfos, std::set<DWORD>& IDArray, std::string& ErrInfo);
		bool GetGame(const std::string& name, GameInfo& game, std::string& ErrInfo);
		bool GetGame(GameInfo& pGame, std::string& ErrInfo);
		bool GetAllLocalGame(GameInfoMap& GameInfos, std::string& ErrInfo);
		bool AddGame(const GameInfo& pGameInfo, std::string& ErrInfo);
		bool DelGameArea(DWORD gid, std::string& ErrInfo);
		bool DelGameArea(i8desk::std_string &strArea, std::string& ErrInfo);
		bool DelGame(DWORD gid, std::string& ErrInfo);
		//bool DelGame(std::vector<DWORD> gids, std::string& ErrInfo);
		//bool CleanLocalGame(std::vector<DWORD> gids, std::string& ErrInfo);
		bool ModifyGame(const GameInfo& pGameInfo, std::string& ErrInfo, uint64 mask = ~0LL);

		bool ModifyAutoSync(const std::string& ID,std::string& ErrInfo);

		bool UpdateGameSizeAndVer(DWORD gid, DWORD dwSize,  DWORD dwVer, std::string& ErrInfo);

		//�õ���������Ϸ���ڷ��������з�ʽ
		bool GetGameRunType(DWORD gid, GameRunTypeList& list, std::string& ErrInfo, const AreaInfoMap& AreaInfos);
		bool SetGameRunType(DWORD gid, const GameRunTypeList& list, std::string& ErrInfo);

		//�ͻ�������
		bool GetAllMachine(MachineMap& MachineInfos, std::string& ErrInfo);
		bool GetMachine(Machine& machine, std::string& ErrInfo);
		bool AddMachine(const Machine& machine, std::string& ErrInfo);
		bool DelMachine(const std::string& Name, std::string& ErrInfo);
		bool ModifyMachine(const Machine& machine, std::string& ErrInfo);
		bool ModifyMachineArea(const Machine& machine, std::string& ErrInfo);

		//�û�����
		bool GetAllUser(std::map<std::string, tagUser*>& UserInfos, std::string& ErrInfo);
		bool AddUser(tagUser* pUser, std::string& ErrInfo);
		bool DelUser(const std::string& Name, std::string& ErrInfo);
		bool ModifyUser(tagUser* pUser, std::string& ErrInfo);

		//�ղؼй���
		bool GetAllFavorite(FavoriteVector& FavInfos, std::string& ErrInfo);
		bool AddFavorite(tagFavorite* pFavorite, std::string& ErrInfo);
		bool DelFavorite(const std::string& ID, std::string& ErrInfo);
		bool ModifyFavorite(tagFavorite* pFavorite, std::string& ErrInfo);

		//ϵͳѡ��
		bool GetAllSysOpt(std::map<std::string, std::string>& AllOpt, std::string& ErrInfo);
		std::string GetOptString(LPCSTR lpszOptName, LPCSTR lpszDef = NULL);
		int GetOptInt(LPCSTR lpszOptName, int nDefValue = 0);
		bool SetOption(const std::string& OptName, const std::string& OptValue);
		bool SetOption(const std::string& OptName, int nValue);

		//�����������
		bool GetBootTask(BootRunTask TaskType, std::map<std::string, tagBootTask*>& BootTasks, std::string& ErrInfo);
		bool AddBootTask(tagBootTask* pTask, std::string& ErrInfo);
		bool DelBootTask(BootRunTask TaskType, std::string& ErrInfo);
		bool DelBootTask(const std::string& TID, std::string& ErrInfo);
	
		//�˵�Ƥ������
		bool GetAllBarSkin(BarSkinList& BarSkins, std::string& ErrInfo);
		bool SetBarSkin(const BarSkin& BarSkin, std::string& ErrInfo);
		bool DelBarSkin(const std::string& style, std::string& ErrInfo);

		//��������
		//nType=0,��ʾȡ�̷��б�,=1��ʾĿ¼�б�=2��ʾ�ļ��б�
		bool GetFileOrDir(const std::string& szDir, DWORD nType, bool isAbsPath, 
			std::vector<std::string>& lstFiles, std::string& ErrInfo);

		//��Ϸͼ�괦��
		bool AddIcon(DWORD gid, char* pData, DWORD dwSize, std::string& ErrInfo);
		bool DelIcon(DWORD gid, std::string& ErrInfo);
		
		bool GetIconData(DWORD gid, const std::string& szFromFile, 
			char *_Desc, DWORD& dwSize, std::string& ErrInfo);

		bool NotifySvrCheck(std::string& ErrInfo);
		bool NotifySvrUptVer(DWORD dwVer, std::string& ErrInfo);
		bool NotifySvrSaveData(std_string &strError);


		// �ͻ���ʹ�ã���ȡ���пͻ�����Ϣ
		bool GetAllClients(MachineMap &machins, std::string &strError);


		//ViewCmpAllGame��= true��ʾ�鿴һ�������������Щ��Ϸ.��= false��ʾ�鿴һ����Ϸ��������������.
		bool ViewGameInfo(DWORD param, bool ViewCmpAllGame, std::string& ErrInfo);

		bool UpdateClientIndex(DWORD& oldversion, DWORD& newversion, std::string& ErrInfo);
		bool UpdateIconlistVersion(DWORD& oldversion, DWORD& newversion, std::string& ErrInfo);

	private:
		bool ExeSql(
			char **ppInData, 
			int* pSize, 
			DWORD table, 
			std::string& ErrInfo, 
			uint32 CondMode = 0, 
			uint64 CondMask = 0, 
			DWORD dwParam1 = 0, 
			const std::string& strParam1 = "",
			uint64 mask = 0, 
			uint32 desc = 0,
			DWORD dwParam2 = 0, 
			const std::string& strParam2 = ""
			);

		template<typename T>
		bool ExeSql(
			DWORD optype, 
			DWORD table, 
			std::string& ErrInfo,
			DWORD dwParam1 = 0, 
			const std::string& strParam1 = "",  
			uint32 CondMode = SQL_COND_MODE_KEY, 
			uint64 CondMask = 0, 
			const T *const d = 0, 
			uint64 mask = 0,
			DWORD dwParam2 = 0, 
			const std::string& strParam2 = ""
			);
	};

	class CDownloadMgr
	{
	private:
		CSimpleSocket* m_pSocket;
	public:
		CDownloadMgr(CSimpleSocket* pSock) : m_pSocket(pSock) {  }
		~CDownloadMgr() { }
	public:
		bool GetSvrStatus(
			bool online, 
			bool b3up, 
			bool vdisk, 
			bool uptsvr, 
			bool uptcli, 
			CMarkup& xml, 
			std::string& ErrInfo,
			bool svrstatus,
			bool diskstatus,
			bool plugtools);
		bool TaskOperator(
			TaskOperation op,
			DWORD gid, 
			std::string& ErrInfo, 
			DWORD DownPriority = 0, 
			DWORD IdcVer = 0, 
			bool bIsFore = false,
			DWORD IdcClick = 0);

		bool NotifyRefreshPL(std::string& ErrInfo);
		bool NotifyServerMedical(std::string& ErrInfo);

		bool _PlugOperator(long gid, int operate, std::string &errInfo);
		bool DownloadPlug(long gid, std::string &errInfo);
		bool StartPlug(long gid, std::string &errInfo);
		bool StopPlug(long gid, std::string &errInfo);
		bool OptionPlug(long gid, std::string &errInfo);
	};

	class CCliMgr
	{
	private:
		CSimpleSocket* m_pSock;
		SOCKET	m_sckUdp;
		HANDLE  m_hThread;
		HANDLE  m_hExited;
		DWORD	m_dwCmd;

		std::string m_strInfo;	//�ͻ���ϵͳ֪ͨ
		
		CLock	m_Lock;
		HWND m_hMainWnd;
	public:

		CCliMgr(CSimpleSocket* pSock, HWND hwnd = NULL)
			: m_pSock(pSock)
			, m_sckUdp(INVALID_SOCKET)
			, m_hThread(NULL)
			, m_hExited(NULL)
			, m_hMainWnd(hwnd)
		{
			m_dwCmd = 0;
			m_hExited = CreateEvent(NULL, TRUE, FALSE, NULL);
		}
		~CCliMgr()	{ CloseHandle(m_hExited); }

		void SetMainWnd(HWND hwnd) { m_hMainWnd = hwnd; }
		HWND GetMainWnd() const { return m_hMainWnd; }

	public:
		void PauseWork();
		void ResumeWork();

		//����ֹͣUDP�̡߳�
		std::string StartUdpThead(); //�������һ���մ�����ʾ�����ɹ��������Ǵ�ġ�
		bool GetUdpInfo(DWORD& cmd, std::string& Info);
		void StopUdpThread();

		//��װ��ԭ�����������з���.
		bool InstallProt(const std::vector<DWORD>& list, bool bProtAllArea, std::string& ErrInfo);
		
		//���ð�ȫ����
		bool EnableSafeCenter(const std::vector<DWORD>& list, std::string& ErrInfo);

		//����IE����
		bool EnableIEProt(const std::vector<DWORD>& list, std::string& ErrInfo);
		
		//���÷�������
		bool EnableDogProt(const std::vector<DWORD>& list, std::string& ErrInfo);
		
		//ɾ����ԭ
		bool RemoveProt(const std::vector<DWORD>& list, std::string& ErrInfo);
		
		//��������
		bool ProtArea(const std::vector<DWORD>& list, std::string& ProtArea,
			std::string& UnProtArea, std::string& ErrInfo);

		//�ػ���������
		bool ShutDown(const std::vector<DWORD>& list, bool bReBoot, std::string& ErrInfo);

		//ʵʱ������Ϸ
		bool RealPush(const std::vector<DWORD>& list, const i8desk::std_string &strGids, DWORD dwLimitSpeed, DWORD dwConstructWay, std::string& ErrInfo);

		//ִ��һ��EXE�ļ�
		bool ExecExeFile(const std::vector<DWORD>& list, std::string& szFile, std::string& ErrInfo);

		//������
		bool Chkdsk(const std::vector<DWORD>& list, const std::string &strArea, std::string& ErrInfo);
	
		//Զ�̿���
		bool RemoteControl(DWORD ip, std::string& ErrInfo);

		//�������Ϣ�鿴
		bool ViewSysInfo(const std::vector<DWORD>& list, std::string& ErrInfo);

		//�鿴���������
		bool ViewProcInfo(const std::vector<DWORD>& list, std::string& ErrInfo);

		//�鿴���������
		bool ViewSviInfo(const std::vector<DWORD>& list, std::string& ErrInfo);

		//ֹͣ������߽�������
		bool KillProcSvr(const std::string& file,  DWORD ip, std::string& ErrInfo, bool bIsProcess = true);

		bool RemoteControl(DWORD ip, bool bstart, std::string& ErrInfo);
	private:
		bool SendCtrlCmd(LPSTR lpSendData, int nSize, std::string& ErrInfo);
		static UINT __stdcall WorkThread(LPVOID lpVoid);
	};

}

#if 1 //test console type define
namespace test_console_type_namespace {
inline void test_console_gameinfo_type(i8desk::GameInfoMap& gameinfos)
{
	gameinfos[1] = i8desk::GameInfo_Ptr(new i8desk::GameInfo);
	i8desk::GameInfoMapItr it = gameinfos.find(1);
	if (it != gameinfos.end()) {
		gameinfos[1]->AutoUpt = TRUE;
	}
}

class TestConsoleType {
public:
	TestConsoleType()
	{
		i8desk::GameInfoMap gim;
		test_console_gameinfo_type(gim);
		gim.clear();
	}
};
static const TestConsoleType tct;
}
#endif 

#endif