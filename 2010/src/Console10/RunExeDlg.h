#pragma once


// CRunExeDlg �Ի���

class CRunExeDlg : public CDialog
{
	DECLARE_DYNAMIC(CRunExeDlg)

public:
	CRunExeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRunExeDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_RUNEXE };
	CString m_strExeFile;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
