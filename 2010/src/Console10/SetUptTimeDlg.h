#pragma once
#include "afxdtctl.h"


// CSetUptTimeDlg �Ի���

class CSetUptTimeDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetUptTimeDlg)

public:
	CSetUptTimeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetUptTimeDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SETTIME };

	CTime tmStart;
	CTime tmEnd;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl m_dtStart;
	CDateTimeCtrl m_dtEnd;
	afx_msg void OnBnClickedOk();
};
