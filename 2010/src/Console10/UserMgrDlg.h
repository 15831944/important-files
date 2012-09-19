#pragma once
#include "afxcmn.h"
#include "ConsoleDlg.h"

// CUserMgrDlg �Ի���

class CUserMgrDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserMgrDlg)

public:
	CUserMgrDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserMgrDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_USERMGR };
	CConsoleDlg* pDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstUser;
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedListUser(NMHDR *pNMHDR, LRESULT *pResult);
};
