#pragma once


// CLogDialog �Ի���

class CLogDialog : public CDialog
{
	DECLARE_DYNAMIC(CLogDialog)

public:
	CLogDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogDialog();

	CString m_strUsername,m_strPassword;
// �Ի�������
	enum { IDD = IDD_LOGDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRegister();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
