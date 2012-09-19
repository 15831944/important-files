#pragma once

#include "./GridListCtrlEx/CGridListCtrlEx.h"
#include "afxdtctl.h"
#include "afxwin.h"

// CDlgTaskLog �Ի���

class CDlgTaskLog : public CDialog
{
	DECLARE_DYNAMIC(CDlgTaskLog)

public:
	CDlgTaskLog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTaskLog();

// �Ի�������
	enum { IDD = IDD_DIALOG_TASK_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

private:
	CDateTimeCtrl wndTimeStart_;
	CDateTimeCtrl wndTimeStop_;
	CGridListCtrlEx wndListLog_;
	
public:
	DECLARE_MESSAGE_MAP()
	
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonTaskLogSearch();
	afx_msg void OnBnClickedButtonTaskLogRefresh();
	afx_msg void OnBnClickedButtonTaskLogExport();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnPaint();
	
};
