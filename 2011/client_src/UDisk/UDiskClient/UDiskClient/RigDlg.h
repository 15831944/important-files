#pragma once


// CRigDlg �Ի���

class CRigDlg : public CDialog
{
	DECLARE_DYNAMIC(CRigDlg)

public:
	CRigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRigDlg();

	CString m_strName,m_strPassword;
// �Ի�������
	enum { IDD = IDD_RigDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
