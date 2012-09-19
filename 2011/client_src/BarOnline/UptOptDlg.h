#pragma once


// CUptOptDlg �Ի���

class CUptOptDlg : public CDialog
{
	DECLARE_DYNAMIC(CUptOptDlg)

public:
	CUptOptDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUptOptDlg();

// �Ի�������
	enum { IDD = IDD_DLG_UPTOPT };

	BOOL m_bIsQuick;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedClose();
	DECLARE_MESSAGE_MAP()
private:
	CButton   m_btnQuick;
	CButton   m_btnForce;
	I8SkinCtrl_ns::CI8OldButton m_btnClose;
	I8SkinCtrl_ns::CI8OldButton m_btnOK;
	I8SkinCtrl_ns::CI8OldButton m_btnCancel;
};
