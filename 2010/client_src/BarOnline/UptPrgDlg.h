#pragma once
#include "UpdateGameCli.h"

class CUptPrgDlg : public CDialog
{
	DECLARE_DYNAMIC(CUptPrgDlg)

public:
	CUptPrgDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUptPrgDlg();

	//ֱ��������Ϸ
	static CString RunGame(tagGameInfo* pGame);
	//������Ϸ
	void           SetStartGame(tagGameInfo* pGame);
	// �Ի�������
	enum { IDD = IDD_DLG_UPTPRG };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnDestroy();
	virtual void PostNcDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedRun();
	afx_msg void OnBnClickedBuycard();
	afx_msg void OnBnClickedVideoSkill();
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedFavorite();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest,	UINT message);
	DECLARE_MESSAGE_MAP()

protected:
	//������Ϸ
	BOOL   UpdateGame(tagGameInfo* pGameInfo);

private:
	DWORD  m_hUpdate;
	bool   m_bAutoRun;	//��ʾ�Ƿ��Զ�������Ϸ	������갴���κμ�ʱ�����Զ����У������û����Ե�������ť��
	bool   m_bIsUpdate;	//��ʾ��ǰ�Ƿ����ڸ��¡�
	bool   m_bNeedWait;	//��ʾ�Ƿ��Լ����ȴ��̶�������û�С�
	FC_COPY_MODE m_fcCopyMode;

	CDockHtmlCtrl m_WebPage;
	CButtonEx m_btnCaption;
	CButtonEx m_btnClose;
	CButtonEx m_btnGamePlug;
	CDockProgress m_btnProgress;
	CButtonEx m_btnStatus;
	CButtonEx m_btnTime;
	CButtonEx m_btnRun;
	CButtonEx m_btnSearch;
	CButtonEx m_btnBuyCard;
	CButtonEx m_btnVidoSkill;
	CButtonEx m_btnModify;
	CButtonEx m_btnFavorite;
	CButtonEx m_btnPlug;

	CImageList m_iGamePlug;
	CListCtrl  m_lstGamePlug;
	tagGameInfo m_arGameInfo[6];
	int        m_nGameCount;
	int        m_nCurrentUptIdx;
	HCURSOR    m_hPlugCursor;
public:
	afx_msg void OnNMClickListGame(NMHDR *pNMHDR, LRESULT *pResult);
};
