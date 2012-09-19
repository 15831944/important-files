#ifndef __db_mgr_inc__
#define __db_mgr_inc__

#include <comutil.h>
#include <vector>
#include <map>
#include <algorithm>

#include "package.h"

#define CAP_URL_NAV				TEXT("��ַ����")
#define CAP_DOT_CARD			TEXT("�㿨�̳�")
#define URL_DOTCARD				TEXT("http://biz.i8cn.com/CybercafeClient/")
#define URL_URLNAVAGITOER		TEXT("http://www.zhaochina.com")
#define URL_PERSON				TEXT("http://desk.i8.com.cn/CybercafeClient/User/Main.aspx")
#define CAP_PERSON              TEXT("��������")

#define FAV_TYPE_WEB			TEXT("��վ")
#define FAV_TYPE_VIDEO			TEXT("��Ӱ")
#define FAV_TYPE_MUSIC			TEXT("����")

typedef struct tagSTMultiChar
{
	WCHAR                        chChar;
	TCHAR                        szPy[3];
}STMultiChar;

//�ղؼ���Ϣ
typedef struct tagFavInfo
{
	CString strType;			//����
	CString strName;			//����
	CString strUrl;				//��ַ
}FAVINFO;

//������Ϣ
typedef struct tagIdxHeahder
{
	DWORD  lowsize;
	DWORD  highsize;
	DWORD  resv3;
	DWORD  resv4;
	DWORD  resv5;
	DWORD  resv6;
	DWORD  xmlsize;
	WORD   resv8;
	WORD   blknum;
}tagIdxHeahder;

//��Ϸ��Ϣ
typedef struct tagGameInfo
{
	HICON		hIcon;
	DWORD		gid;			//��Ϸid.
	DWORD		pid;			//��Ϸ����id.
	CString		Name;			//��Ϸ����
	CString		Py;				//��Ϸ���Ƶ�ƴ��
	CString     MultiPy;        //������ƴ��
	int         nFindPos;       //ƥ���λ��
	CString		IdcClass;		//��Ϸ���
	CString		Exe;			//��Ϸ���еģţأ�.(���·��)
	CString		Param;			//���еĲ���
	DWORD		Size;			//��Ϸ�Ĵ�С���ԣ�Ϊ��λ��
	bool		DeskLnk;		//�Ƿ���ʾ�������ݷ�ʽ
	bool		Toolbar;		//�Ƿ���ʾ���˵�������
	CString		SvrPath;		//��Ϸ�����·��
	CString		CliPath;		//��Ϸ�ͻ���·��
	DWORD       Priority;		//��Ϸ�ȼ�������ɾ������ʵ͵���Ϸ���������Ҫ
	DWORD		ShowPriority;	//��Ϸ�ڲ˵��ϵ���ʾ���ȼ�
	CString		MatchFile;		//��Ϸ�Զ����������ļ�
	CString		SaveFilter;		//��Ϸ�浵��Ϣ
	DWORD		I8Play;			//��ֵ���Ϸ
	DWORD		IdcClick;		//��Ϸȫ������
	DWORD		SvrClick;		//��Ϸ���ɵ���
	CString		Url;			//��Ϸ����
	DWORD		RunType;		//��Ϸ���з�ʽ
	DWORD       dwNbVer;        //���ɷ������汾
	CString		VID;			//��Ϸ����������ID
	CString     GameArea;       //ר��URL
	CString     RegUrl;         //ע���ַ 
	CString     PayUrl;         //֧����ַ
	CString     VideoUrl;       //��Ƶ����
}GAMEINFO;

//��������Ϣ
typedef struct tagVDiskInfo
{
	CString VID;				//������GUID
	DWORD	IP;					//������ip
	DWORD	Port;				//�����̶˿�
	TCHAR	SvrDrv;				//������̷�
	TCHAR   CliDrv;				//�ͻ���ָ���̷�
	DWORD	Serial;				//�����̵����к�
	DWORD	Type;				//�����̵�����
	DWORD	LoadType;			//�����̵�ˢ�̷�ʽ
	CString SID;				//����������ı�ʶ��
}VDISKINFO;

//��������б�����
typedef struct tagSvrCfg
{
	CString Sid;
	CString SyncIP;
	CString VDiskIP;
	CString UptIP;
	DWORD	dwSyncType;
	DWORD   dwDestDrv;
	DWORD   dwBalanceType;
}SVRCFG;

CString GetPY(CString& sChinese);
DWORD CalBufCRC32(BYTE* buffer, DWORD dwSize);


//��Ϸ����ʽ�������������򣬶�����ֵ��Ϸһ��������ǰ�档
#define SORT_WINDOWS	0	//��windows��Դ������Ĭ�Ϸ�ʽ����
#define SORT_CLICK		1	//����Ϸ���������
#define SORT_FINDPOS    2   //ƥ��λ��

template<int N = SORT_WINDOWS>
struct Pred
{
	bool operator()(tagGameInfo* p1, tagGameInfo* p2)
	{
		int nLen1 = p1->Name.GetLength();
		int nLen2 = p2->Name.GetLength();
		int nLen = nLen1 > nLen2 ? nLen1 : nLen2;

		//��ֵ����ǰ
		if (p1->I8Play || p2->I8Play)
		{
			if (p1->I8Play && p2->I8Play)
			{
				if (p1->I8Play == p2->I8Play)
					return p1->SvrClick > p2->SvrClick;
				return p1->I8Play > p2->I8Play;
			}
			if (p1->I8Play)
				return true;
			if (p2->I8Play)
				return false;
		}
		//��������Դ�����������з�ʽ���š�(����)
		return StrNCmpI(p1->Name, p2->Name, nLen) < 0;
	}
};

template<>
struct Pred<SORT_CLICK>
{
	bool operator()(tagGameInfo* p1, tagGameInfo* p2)
	{
		//��ֵ����ǰ
		if (p1->I8Play || p2->I8Play)
		{
			if (p1->I8Play && p2->I8Play)
			{
				if (p1->I8Play == p2->I8Play)
					return p1->SvrClick > p2->SvrClick;
				return p1->I8Play > p2->I8Play;
			}

			if (p1->I8Play)
				return true;
			if (p2->I8Play)
				return false;
		}

		//�����������������
		return p1->SvrClick > p2->SvrClick;
	}
};

template<>
struct Pred<SORT_FINDPOS>
{
	bool operator()(tagGameInfo* p1, tagGameInfo* p2)
	{
		//������λ����������
		if (p1->nFindPos != p2->nFindPos)
		{
			return p1->nFindPos < p2->nFindPos;
		}

		int nLen1 = p1->Name.GetLength();
		int nLen2 = p2->Name.GetLength();
		int nLen = nLen1 > nLen2 ? nLen1 : nLen2;
		return StrNCmpI(p1->Name, p2->Name, nLen) < 0;
	}
};

template <int N>
void SortGameList(std::vector<tagGameInfo*>& GameList)
{
	std::sort(GameList.begin(), GameList.end(), Pred<N>());

	//�������ʱ�鿴�����Ƿ���ȷ
// 	for (size_t idx=0; idx<GameList.size(); idx++)
// 	{
// 		TCHAR szLog[MAX_PATH] = {0};
// 		_stprintf_s(szLog, TEXT("%s-%d-%d\r\n"), (LPCTSTR)GameList[idx]->Name, 
// 			GameList[idx]->SvrClick, GameList[idx]->I8Play);
// 		OutputDebugString(szLog);
// 	}
}

class CLock
{
private:
	CRITICAL_SECTION m_lock;
public:
	CLock()			{ InitializeCriticalSection(&m_lock);	}
	~CLock()		{ DeleteCriticalSection(&m_lock);		}
	void Lock()		{ EnterCriticalSection(&m_lock);		}
	void UnLock()	{ LeaveCriticalSection(&m_lock);		}
};

void AfxWriteLog(LPCTSTR lpszLog, bool bAddDate = true);
void AfxWriteLog2(LPCTSTR lpszLog, ...);

class CDbMgr
{
public:
	~CDbMgr();
	static CDbMgr* getInstance();
	static void CheckCliService();
	static void CheckVDiskService();
	static void WriteI8deskProtocol();

public:
	std::map<CString, CString>			m_mapSysOpt;	//ϵͳѡ���б�
	std::map<CString, tagVDiskInfo*>	m_mapVDisk;		//��������б�
	std::map<DWORD, tagGameInfo*>		m_mapGameInfo;	//��Ϸ��Ϣ�б�
	std::vector<tagGameInfo*>			m_toolGameInfo;	//�������ϵ���Ϸ�б�
	std::vector<tagFavInfo*>			m_FavList;		//�ղؼ��б�

	std::vector<CString>				m_GameRoomTab;	//��Ϸ������TAB�б�
	std::vector<CString>				m_ChatRoomTab;	//���칤�ߵ�TAB�б�
	std::vector<CString>				m_SoftwareTab;	//���������TAB�б�

	std::vector<CString>				m_BrowseTab;	//�������TAB�б�
	std::vector<CString>				m_DotCardTab;	//�㿨�̳ǵ�TAB�б�
	std::vector<CString>				m_VideoTab;		//Ӱ��/���ֵ�TAB�б�

public:
	void            WaitExit();
	void            RefreshOfflineData();
	void            LoadMultiChar();
	DWORD           Idxfile_GetVersion(LPCWSTR file);

	//��ѯϵͳѡ��
	bool	        GetBoolOpt(LPCTSTR lpOptName, bool nOptDef = false);
	long	        GetIntOpt(LPCTSTR lpOptName, long nOptDef = 0);
	__int64         GetInt64Opt(LPCTSTR lpOptName, __int64 nOptDef = 0);
	CString         GetStrOpt(LPCTSTR lpOptName, LPCTSTR lpOptDef = TEXT(""), bool bEmptyIsDef = false);

	bool	        IsRefVDiskFinish();
	CString         TransChToGBK(LPCTSTR lpszSouce);

	//ϵͳ�����ļ�
	CString         GetIniFile();
	CString         LoadIpAddr();
	void            SaveIpAddr(CString str);

	CString	        GetUptSvrList();
	void            GetMacAddr(LPSTR buf, int nSize);
	void            GetMacAddr(LPTSTR buf, int nSize);
	void            GetGameNamePy(tagGameInfo* pGameInfo);

	//ˢָ��������
	bool            RefreshVDisk(TCHAR chCltDrv);

	//������Һ���
	tagGameInfo*	FindGameInfo(DWORD gid);
	tagFavInfo*		FindFavInfo(CString name);
	tagVDiskInfo*	FindVDiskInfo(CString vid);
	//Dno't DestroyIcon return hIcon.(if hIcon != NULL)
	HICON			FindIconOfGame(DWORD gid);

	//��ֵ����Ŀ��Ƹ�������
	CString			GetDotCardCap()		{ return m_strDotCardCap;	}
	CString			GetDotCardUrl()		{ return m_strDotCardUrl;	}
	CString			GetNavigateCap()	{ return m_strNavUrlCap;	}
	CString			GetNavigateUrl()	{ return m_strNavUrl;		}
	CString			GetPersonUrl()		{ return m_strPersonUrl;	}
	CString         GetPersonTabText()  { return m_strPersonTabText;}
	long			GetDefaultPage()	{ return m_nDefaultPage;	}
	bool			GetIsShowGongGao()	{ return m_bShowGongGao;	}
	long			GetRBPopAdv()		{ return m_nRBPopAdv;		}
	bool			GetPreGameUrl(CString Name, CString& url)	
	{
		url = TEXT("");
		std::vector<std::pair<CString, CString>>::iterator it = m_GamePreUrlList.begin();
		for (; it != m_GamePreUrlList.end(); it++)
		{
			if (Name.CompareNoCase(it->first) == 0)
			{
				url = it->second;
				return true;
			}
		}
		return false;
	}

private:
	HANDLE m_hThread;
	HANDLE m_hExit;
	bool CheckConnect(DWORD ip, WORD port);
	static UINT __stdcall ThreadProc(LPVOID lpVoid);

private:
	CDbMgr();
	char* m_pIconInfo;
	std::map<TCHAR, WCHAR*> m_mapMultiChar;
	std::map<DWORD, char*> m_mapIconInfo;
	std::vector<tagSvrCfg*> m_SvrCfg;
	std::vector<std::pair<CString, CString>> m_GamePreUrlList;
	CString  m_strDotCardCap;
	CString  m_strDotCardUrl;
	CString  m_strNavUrlCap;
	CString  m_strNavUrl;
	CString	 m_strPersonUrl;
	CString  m_strPersonTabText;
	long	 m_nDefaultPage;
	bool	 m_bShowGongGao;
	long	 m_nRBPopAdv;

	//��������
	CString GetDataDir();
	void LoadSysOpt();
	void LoadVDisk();
	void LoadFavorite();
	void LoadGameInfo();
	void LoadIconInfo();
	void ParseInValue();	//������ֵ��������
	void ParseSvrList();

	HICON FindIconOfGame_(DWORD gid);   

	//�ͷ�������ռ���ڴ�
	void FreeSysOpt();
	void FreeVDisk();
	void FreeFavorite();
	void FreeGameInfo();
	void FreeIconInfo();
	void FreeSvrList();
};

class CRptData
{
public:
	CRptData();
	~CRptData();
public:
	void ReprotDataToServer(CDockNavBar* pNav, std::map<DWORD, DWORD>& GameClick, bool bAck = true);
private:
	bool ConnectToServer();
	bool SendDataToServer(char* pData, int len, bool bAck = false);
	void CloseServer();
	
private:
	SOCKET m_sck;
};

inline void i8desk_GetShareData(bool& bOnline, bool& bProt)
{
	bOnline = bProt = false;
	HANDLE hFileMap = OpenFileMapping(FILE_MAP_READ, FALSE, TEXT("I8MENU_SHARE"));
	if (hFileMap != NULL)
	{
		DWORD* pShareData = (DWORD*)MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, MAX_PATH);
		if (pShareData != NULL)
		{
			bOnline = (pShareData[0] == 1);
			bProt   = (pShareData[1] == 1);
			UnmapViewOfFile(pShareData);
		}
		CloseHandle(hFileMap);
	}
};


inline CDbMgr* AfxGetDbMgr()
{
	return CDbMgr::getInstance();
}

class CPersonMgr
{
public:
	~CPersonMgr() 
	{
		if (m_hThread != NULL && m_hExited != NULL)
		{
			SetEvent(m_hExited);
			WaitForSingleObject(m_hThread, INFINITE);
			CloseHandle(m_hExited);
			CloseHandle(m_hThread);
		}
		DeleteFavOfAdded();
//		ChangeDisplaySetting(m_nDefWidth, m_nDefHeight);
		CoUninitialize();
	}
public:
	static CPersonMgr* getInstance()
	{
		static CPersonMgr self;
		return &self;
	}
	enum RES_AddGame
	{
		RES_AddGame_OK,
		RES_AddGame_NotLogin,
		RES_AddGame_Failed
	};
	void NoOperator();
	void GetPersonState();
	RES_AddGame AddGameToFavList(DWORD gid);
	void GetPersonFavorite(DWORD dwNum = -1, DWORD dwDefault = 1);
	void GetPersonalizationSet();
private:
	CPersonMgr() : m_dwUserId(-1), m_hThread(NULL), m_hExited(NULL)
	{
		CoInitialize(NULL);
		m_nDefWidth = GetSystemMetrics(SM_CXSCREEN);
		m_nDefHeight = GetSystemMetrics(SM_CYSCREEN);
		m_hExited = CreateEvent(NULL, TRUE, FALSE, NULL);
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, this, 0, NULL);
	}
	LPCTSTR GetCookie();
	void ChangeDisplaySetting(int nWidth, int nHeight);
	void DeleteFavOfAdded();
	HRESULT CreateShortcutToURL(LPCTSTR pszURL, LPCTSTR pszLinkFile);
	void ChangeMouseSpeed(int nSpeed);
	void InstallInput(CString str);

	static UINT __stdcall ThreadProc(LPVOID lpVoid);
private:
	DWORD m_nDefWidth, m_nDefHeight;
	DWORD m_dwUserId;
	HANDLE m_hThread;
	HANDLE m_hExited;
	CString m_strUserName;
	CString m_strLgnIp;
	CString m_strLgnDate;
	std::vector<CString> m_favlst;
};

inline CPersonMgr* AfxGetPersonMgr()
{
	return CPersonMgr::getInstance();
}

#endif