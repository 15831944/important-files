#pragma once
#include "afxwin.h"


// CDelTipDlg �Ի���

class CDelTipDlg : public CDialog
{
	DECLARE_DYNAMIC(CDelTipDlg)

public:
	CDelTipDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDelTipDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_DELTIP };
	BOOL m_bDelLocal;
	BOOL m_bDelClient;
	BOOL m_bDelSync;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnDelLocal;
	CButton m_btnDelClient;
	CButton m_btnDelSync;
	afx_msg void OnBnClickedOk();
};
