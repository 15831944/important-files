#pragma once

class COptLgnDlg : public CDialog
{
	DECLARE_DYNAMIC(COptLgnDlg)

public:
	COptLgnDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COptLgnDlg();

// �Ի�������
	enum { IDD = IDD_DLG_OPTLLOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	DECLARE_MESSAGE_MAP()
private:
	CEdit	  m_edtPassword;
	CButtonEx m_btnCaption;
	CButtonEx m_btnClose;
	CButtonEx m_btnTip;
	CButtonEx m_btnOK;
	CButtonEx m_btnCancel;
};
