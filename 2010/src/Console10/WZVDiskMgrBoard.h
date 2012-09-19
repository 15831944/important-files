#pragma once

#include "resource.h"

// CWZVDiskMgrBoard �Ի���

class CWZVDiskMgrBoard : public CDialog
{
	DECLARE_DYNAMIC(CWZVDiskMgrBoard)

public:
	CWZVDiskMgrBoard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWZVDiskMgrBoard();

// �Ի�������
	enum { IDD = IDD_WZ_VDISKMGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg LRESULT OnApplyMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton();
private:
	CFont m_font;
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
};
