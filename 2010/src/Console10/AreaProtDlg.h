#pragma once
#include "afxwin.h"


// CAreaProtDlg �Ի���

class CAreaProtDlg : public CDialog
{
	DECLARE_DYNAMIC(CAreaProtDlg)

public:
	CAreaProtDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAreaProtDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_AREAPROT };
	CString m_strProtArea;
	CString m_strUnProtArea;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lstUnProt;
	CListBox m_lstProt;	
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedAddAll();
	afx_msg void OnBnClickedRemove();
	afx_msg void OnBnClickedRemoveAll();
	afx_msg void OnBnClickedOk();
};
