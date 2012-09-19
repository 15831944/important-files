#pragma once

#include "resource.h"
// CWZServerBoard �Ի���

class CWZServerBoard : public CDialog
{
	DECLARE_DYNAMIC(CWZServerBoard)

public:
	CWZServerBoard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWZServerBoard();

// �Ի�������
	enum { IDD = IDD_WZ_SERVER };

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
