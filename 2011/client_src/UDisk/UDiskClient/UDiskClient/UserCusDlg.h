#pragma once


// CUserCusDlg �Ի���

class CUserCusDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserCusDlg)

public:
	CUserCusDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserCusDlg();

// �Ի�������
	enum { IDD = IDD_UserCusDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
