#pragma once

#include "resource.h"
// CWZClassMgrBoard �Ի���

class CWZClassMgrBoard : public CDialog
{
	DECLARE_DYNAMIC(CWZClassMgrBoard)

public:
	CWZClassMgrBoard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWZClassMgrBoard();

// �Ի�������
	enum { IDD = IDD_WZ_CLASSMGR };

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
