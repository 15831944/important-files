#pragma once


// CDialogRealTSGame �Ի���

class CConsoleDlg;

class CDialogRealTSGame : public CDialog
{
	DECLARE_DYNAMIC(CDialogRealTSGame)

private:
	CListCtrl	m_wndListClients;
	CListCtrl	m_wndListGames;
	UINT		m_uLimitSpeed;

	CConsoleDlg *m_pParent;

	i8desk::GameInfoMap m_GameInfos;		// ���б�����Ϸ
	i8desk::MachineMap  m_OnlineMachines;	// �������߿ͻ���

	const std::vector<unsigned int>	&m_vecGids;			// ����ѡ����ϷGID



public:
	CDialogRealTSGame(const std::vector<unsigned int> &vecGids, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogRealTSGame();

// �Ի�������
	enum { IDD = IDD_DIALOG_REAL_TSGAME };
	enum { IDT_UPDATE_CLIENT = 1 };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

private:
	void _InitListCtrl();
	void _InitClientsList();
	void _InitGamesList();
	void _InitArguments();
	void _SetPanelInfo();	
	void _SetStaticInfo(int nClients, int nGames, double fSize);
	void _UpdateClients();				// ���¿ͻ���״̬

public:
	DECLARE_MESSAGE_MAP()

	
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLvnItemchangedListRealTsgameGame(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListRealTsgameClient(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckClientSelectAll();
	afx_msg void OnBnClickedCheckGameSelectAll();
};
