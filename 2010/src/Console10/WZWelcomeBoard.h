#pragma once

#include "resource.h"

// CWZWelcomeBoard �Ի���

class CWZWelcomeBoard : public CDialog
{
	DECLARE_DYNAMIC(CWZWelcomeBoard)

public:
	CWZWelcomeBoard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWZWelcomeBoard();

// �Ի�������
	enum { IDD = IDD_WZ_WELCOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg LRESULT OnApplyMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
