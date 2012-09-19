#pragma once

#include "afxwin.h"
#include "afxcmn.h"
#include "GongGaoDlg.h"
#include "UptPrgDlg.h"
#include "HotGamePanel.h"
#include "DockDlg.h"
#include "FavPanel.h"
#include "RBPopAdvDlg.h"
#include "UI/I8SkinCtrl/Header.h"
#include "UI.h"
#include "DockBrowseBar.h"
#include "DockFinderBar.h"
#include "DockStatusBar.h"

static int WM_EXEC_START_PARAM		= RegisterWindowMessage(TEXT("_i8desk_exec_start_param"));

typedef struct tagMenuItemEx
{
	DWORD	dwId;
	int		dwGid;
	TCHAR	szText[MAX_PATH];
}tagMenuItemEx;

class CMainFrame : public CFrameWnd
{
	friend class CHotGamePanel;

	enum	FrameWndMode
	{
		FWM_UNKNOWN = 0,
		FWM_GAME	= 1,
		FWM_IE		= 2,
		FWM_PERSON	= 3
		//FWM_DOCK	= 4
	};

public:
	CMainFrame(LPCTSTR lpszWindowName = NULL);
	virtual ~CMainFrame();
public:
	//���������������еĿؼ�
	void CreateControl();
	void SetToolbarGame();

	//��ʾ�����ڵ�����ģʽ
	void SetFrameMode(FrameWndMode FrameMode);
	CRect GetWndDefRect();	//�õ�����Ĭ��λ��
	void  ShowUrlFavorite(BOOL bIsLeft);
	void  ClickUrlFavorite(CString szUrl);
	void  HideUrlFavorite();
	void  RefreshUrlFavorite();
	BOOL m_bLeftUrlFav;
	BOOL m_bRightUrlFav;
	BOOL m_bShowDock;
	BOOL m_bDockMode;
	
	//���̲˵�����
	void ShowTray(DWORD dwMessage);

	//��ʾ����,���£����½ǹ�浯�����ڡ�
	CGongGaoDlg*	m_pDlgGongGao;
	CUptPrgDlg*		m_pDlgUptPrg;
	CRBPopAdvDlg*	m_pDlgRbPopAdv;
	CDockDlg*		m_pDlgDock;
	tagMenuItemEx*	m_pPopMenu;
	tagMenuItemEx*  m_pTrayMenu;
	void ShowGongGao();
	void ShowUptPrg(tagGameInfo* pGameInfo);
	void ShowRBPopAdv();
	void ShowDockWnd();

	//���ڿ���
	BOOL         IsMaxWindow();
	void         ShowMaxWindow();
	void         ShowNormalWindow();

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* pMMI);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg LRESULT OnThemeChanged();
	afx_msg LRESULT OnDisplayChange(WPARAM wParam, LPARAM lParam);

	//�����������Ͽؼ����¼�
	afx_msg LRESULT HandleNavClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT HandleBrowseClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT HandleFinderClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT HandleTabClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT HandleStatusClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT HandleTrayMessage(WPARAM wParam, LPARAM lParam);

	//���������в���
	//wParam:1��ʾ�ǵڶ���ʵ������������Ϣ��0��ʾ���Լ��ڲ���������Ϣ��
	//�����е����ݣ�����д�������ڴ��У��ڷ�����Ϣǰ��
	afx_msg LRESULT HandleCmdLine(WPARAM wParam, LPARAM lParam);

	//����̬ˢ����������
	afx_msg LRESULT HandleRefreshData(WPARAM wParam, LPARAM lParam);

	//������ҳ��ʧ�����
	afx_msg LRESULT HandleHttpError(WPARAM wParam, LPARAM lParam);

	//List��Ϣ����
	afx_msg void OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkDockList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickDockList(NMHDR* pNMHDR, LRESULT* pResult);

	//List�Ҽ��˵���Ϣ����
	afx_msg void OnListPopRunGame();
	afx_msg void OnListPopOpenDir();
	afx_msg void OnListPopSearchGame();
	afx_msg void OnListPopAddGameFav();
	afx_msg void OnListPopSaveProgress();
	afx_msg void OnListPopLoadProgress();

	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMis);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDis);

	//���̲˵���Ϣ����
	afx_msg void OnTrayExit();
	afx_msg void OnTrayBrowse();
	afx_msg void OnTrayGameRoom();
	afx_msg void OnTrayChat();
	afx_msg void OnTraySoftware();
	afx_msg void OnTrayDotCard();
	afx_msg void OnTrayVDMusic();

	virtual void ActivateFrame(int nCmdShow = -1);
	
	DECLARE_MESSAGE_MAP()
private:
	void AddUrlToHistory(CString url);
	CString GetLastUrl();
	CString GetNextUrl();
	CString GetPrevUrl();

private:
    BOOL ReleaseResToFile(CString strFileName, CString strDir, DWORD dwResId, LPCWSTR lpType);

private:
	HICON	m_hIcon;
	HICON	m_hOnlineProt, m_hOnlineNProt, m_hNOnlineProt, m_hNOnlineNProt;
	FrameWndMode	m_FrameMode;

	std::vector<tagGameInfo*>	m_CurGameInfo;
	std::vector<CString>		m_UrlHistory;
	std::map<DWORD, DWORD>		m_GameClicks;

	CString			m_oldInputString;
	CString			m_strLastUrl;
	bool			m_bAddBlankPage;
	bool            m_bFirstShow;
	bool            m_bMaxWindow;
	int				m_nLastNav;
	int				m_nLastTab;
	
	I8SkinCtrl_ns::CI8HtmlView m_WebPage;
	CHotGamePanel   m_HotPanel;
	CFavPanel		m_FavPanel;
	CDockNavBar		m_DockNav;
	CDockFinderBar	m_DockFinder;
	CDockBrowseBar	m_DockBrowse;
	CI8TabBar       m_DockTab;
	CListCtrl		m_DockList;
	CImageList		m_ilLstCtrl;
	CDockStatusBar	m_DockStaBar;
    I8SkinCtrl_ns::CI8WndShadow m_Shadow;
	CBitmap*		m_pbmpLstBk;
	CBitmap*        m_pbmpLstTop;
	CBitmap         m_LstBmp;
};
