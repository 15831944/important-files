#pragma once

#include "resource.h"
// CWZSyncTaskBoard �Ի���

class CWZSyncTaskBoard : public CDialog
{
	DECLARE_DYNAMIC(CWZSyncTaskBoard)

public:
	CWZSyncTaskBoard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWZSyncTaskBoard();

// �Ի�������
	enum { IDD = IDD_WZ_SYNCTASK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg LRESULT OnApplyMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
private:
	CFont m_font;
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
};
