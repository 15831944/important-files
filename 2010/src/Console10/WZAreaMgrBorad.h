#pragma once

#include "resource.h"

// CWZAreaMgrBoard �Ի���

class CWZAreaMgrBoard : public CDialog
{
	DECLARE_DYNAMIC(CWZAreaMgrBoard)

public:
	CWZAreaMgrBoard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWZAreaMgrBoard();

// �Ի�������
	enum { IDD = IDD_WZ_AREAMGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg LRESULT OnApplyMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();

private:
	CFont m_font;
};
