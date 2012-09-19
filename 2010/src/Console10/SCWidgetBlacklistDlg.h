#pragma once

#include "resource.h"
#include "afxcmn.h"

// CSCWidgetBlacklistDlg �Ի���

class CSCWidgetBlacklistDlg : public CDialog
{
	DECLARE_DYNAMIC(CSCWidgetBlacklistDlg)

public:
	CSCWidgetBlacklistDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSCWidgetBlacklistDlg();

// �Ի�������
	enum { IDD = IDD_SC_WIDGET_BLACKLIST };
	void InsertItem(LPCTSTR lpAddTime, LPCTSTR lpName, LPCTSTR lpDesc);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnApplyMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedRemove();
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnDeleteitemList(NMHDR *pNMHDR, LRESULT *pResult);
};
