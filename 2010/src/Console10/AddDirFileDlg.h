#pragma once
#include "afxwin.h"


// CAddDirFileDlg �Ի���

class CAddDirFileDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddDirFileDlg)

public:
	CAddDirFileDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddDirFileDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_ADDDIRFILE };

	BOOL m_bIsDir;
	CString m_strDirFile;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CComboBox m_cboDirFile;
};
