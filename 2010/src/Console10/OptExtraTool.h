#pragma once


// COptExtraTool �Ի���

class COptExtraTool : public CDialog
{
	DECLARE_DYNAMIC(COptExtraTool)

public:
	COptExtraTool(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COptExtraTool();

// �Ի�������
	enum { IDD = IDD_OPTION_EXTRATOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg LRESULT OnApplyMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL m_bAutoStartIeHistory;
	BOOL m_bUseUdisk;
	BOOL m_bModify;
	afx_msg void OnBnClickedCheckAutoStartIeHistory();
	afx_msg void OnBnClickedUdisk();

};
