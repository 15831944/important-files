#pragma once
#include "afxcmn.h"


// CAddGameDlg �Ի���

class CAddGameDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddGameDlg)

public:
	CAddGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddGameDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_ADDGAME };

	i8desk::GameInfoMap m_GameInfos;
	//i8desk::GameInfoMap m_GameInfos;
	std::set<DWORD> m_IDs;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstGame;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSelect();
	afx_msg void OnBnClickedUnselect();
};
