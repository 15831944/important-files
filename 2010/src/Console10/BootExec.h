#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CBootExec �Ի���

class CBootExec : public CDialog
{
	DECLARE_DYNAMIC(CBootExec)

public:
	CBootExec(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBootExec();

// �Ի�������
	enum { IDD = IDD_OPTION_BOOTEXEC };

protected:
	BOOL m_bModify;
	BOOL m_bModify2;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstFile;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg LRESULT OnApplyMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnNMClickListBootExec(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnKillfocusCombo1();
	CComboBox m_cboCell;
	afx_msg void OnEnChangeCliFile();
	afx_msg void OnBnClickedOpenDir();
	CButton m_btnSyncTime;
	afx_msg void OnLvnItemchangedListExec(NMHDR *pNMHDR, LRESULT *pResult);
};
