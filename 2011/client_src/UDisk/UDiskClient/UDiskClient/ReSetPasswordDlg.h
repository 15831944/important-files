#pragma once


// CReSetPasswordDlg �Ի���

class CReSetPasswordDlg : public CDialog
{
	DECLARE_DYNAMIC(CReSetPasswordDlg)

public:
	CReSetPasswordDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReSetPasswordDlg();
	CString m_strNewPassword,m_strOldPassword;
// �Ի�������
	enum { IDD = IDD_ReSetDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
