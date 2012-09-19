#pragma once;

#include "afxext.h"
#include "UI.h"

class CFormCtrl : public CFormView
{
public:
	enum 
	{
		ID_BTN_MIN		= 0,

		ID_JKZS_CXTJ	= 0,
		ID_JKZS_VIEW,
		
		ID_SERVER_SVR1,
		ID_SERVER_SVR2,
		ID_SERVER_SVR3,
		ID_SERVER_SVR4,

		ID_CLIENT_CLITOTAL,
		ID_CLIENT_ONLINECLI,
		ID_CLIENT_HYNOTUSE,
		ID_CLIENT_SAFENOTUSE,
		ID_CLIENT_IENOTPROT,
		ID_CLIENT_DOTNOTUSE,
		ID_CLIENT_HARDCHANGE,

		ID_GAME_CENTERNUM,
		ID_GAME_NEWADDNUM,
		ID_GAME_LOCALNUM,
		ID_GAME_VIRTUAL,
		ID_GAME_LOCALUPT,
		ID_GAME_DIRECTRUN,

		ID_GAME_MATCHNUM,
		ID_GAME_HAVEUPT,
		ID_GAME_THIRDLIST,
		ID_GAME_THIRDSPEED,
		ID_GAME_INNERLIST,
		ID_GAME_INNERSPEED,
		
		ID_BTN_MAX
	};
	typedef struct tagDisk
	{
		TCHAR Driver;			//�������̷�
		float total;			//�������ܴ�С
		float userd;			//����ʹ�õĴ�С
		float speed;			//��ȡ�ٶ�
	}tagDisk;

	typedef struct tagServer
	{
		TCHAR HostName[MAX_PATH];	//��������
		int MainServer;			//������
		int ThirdLayerUpdate;	//�������
		int VirtualDisk;		//�������
		int InnerUpdate;		//��������
		int ShopCity;			//�̳�������
		int cpuusage;			//cpuռ����
		int memoryusage;		//�ڴ�ռ����
		int networkusage;       //����ʹ����
		int LastBackupDatabaseTime; //�ϴα������ݿ�ʱ�� 
		tagDisk Disk[6];
	}tagServer;

	typedef struct tagClientInfo
	{
		int CliNum;			//�ͻ�������.
		int CliOnlineNum;	//���߿ͻ�����
		int NotProtNum;		//��ԭδ������
		int NotSafeNum;		//��ȫ����δ������
		int NotIeNum;		//IEδ������
		int NotDogNum;		//����δ������
		int HardChgNum;		//Ӳ���Ķ���
	}tagClientInfo;

	typedef struct tagGameInfo
	{
		TCHAR CGameNum[MAX_PATH];			//������Դ��
		TCHAR CAddGameNum[MAX_PATH];		//��������������Դ��
		TCHAR LGameNum[MAX_PATH];			//���ؼ�����Դ��
		TCHAR ConVirRunGameNum[MAX_PATH];	//����Ϊ���������е���Դ��
		TCHAR ConLocRunGameNum[MAX_PATH];	//����Ϊ���ظ������е���Դ��
		TCHAR ConRunNotUptGameNum[MAX_PATH];//����Ϊ�����£�ֱ�����е���Դ��
		TCHAR MatchGameNum[MAX_PATH];		//���ؼ�ƥ�䵽������Դ��
		TCHAR HaveUptGameNum[MAX_PATH];		//�и��µ���Դ��
		TCHAR ThirdDwnListNum[MAX_PATH];	//����������ض�����
		TCHAR ThirdDwnSpeed[MAX_PATH];		//�����������ٶ�
		TCHAR InnerUptListNum[MAX_PATH];	//�������¶�����
		TCHAR InnerUptSpeed[MAX_PATH];		//�����������ٶ�
	}tagGameInfo;

public:
	CFormCtrl(UINT nIDTemplate);
	~CFormCtrl();
	BOOL Create(CWnd* parent);
protected:
	//���¸���״̬
	void UpdateJKZS(int nJK, const CString& strLastBackupTime);
	void UpdateServer(tagServer* pServer, int nCount);
	void UpdateClient(tagClientInfo* pInfo);
	void UpdateGameInfo(tagGameInfo* pInfo);

	//���ְ�ť�¼���
	virtual void HandleEvent(DWORD id, LPVOID p) = 0;
protected:
	int m_nJKZS;
	CString m_strLastBackupTime;
	int m_SvrCount;
	int m_nCurSvr;
	tagServer m_pServer[4];
	tagClientInfo m_cliInfo;
	tagGameInfo	 m_gameInfo;
	CFont m_font, m_fontbold, m_fontunderline;
	CButtonEx m_btnCXTJ, m_btnViewTJ;
	CButtonEx m_btnServer[4];
	CButtonEx m_btnCliStatus[7];
	CButtonEx m_btnGameStatus[12];

	void PaitJKZS(CDC* pDC);
	void PaitServer(CDC* pDC);
	void PaitClient(CDC* pDC);
	void PaitGame(CDC* pDC);

	void UpdateJKZS(CDC* pDC);
	void UpdateServer(CDC* pDC);
	void UpdateDiskUsage(CDC* pDC, const CRect& rx, TCHAR chDrv, float total, float used);
	void UpdateClient(CDC* pDC);
	void UpdateGame(CDC* pDC);

	virtual void OnDraw(CDC* pDC);
	virtual void PostNcDestroy();
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickButton(UINT id);
};
			
