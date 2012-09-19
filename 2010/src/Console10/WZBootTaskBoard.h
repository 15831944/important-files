#pragma once

#include "resource.h"
#include "afxcmn.h"
// CWZBootTaskBoard �Ի���

class CWZBootTaskBoard : public CDialog
{
	DECLARE_DYNAMIC(CWZBootTaskBoard)

public:
	CWZBootTaskBoard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWZBootTaskBoard();

// �Ի�������
	enum { IDD = IDD_WZ_BOOTTASK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg LRESULT OnApplyMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_lstFile;
	CComboBox m_cboCell;
	BOOL m_bModify;
	BOOL m_bModify2;
public:
	afx_msg void OnDestroy();
	afx_msg void OnNMClickListExec(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnKillfocusCombo1();
	afx_msg void OnEnChangeCliFile();
	afx_msg void OnEnChangeRunParam();
	afx_msg void OnBnClickedCheckTimeupt();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedOpenDir();
};
