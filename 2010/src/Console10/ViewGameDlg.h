#pragma once
#include "afxcmn.h"


// CViewGameDlg �Ի���

class CViewGameDlg : public CDialog
{
	DECLARE_DYNAMIC(CViewGameDlg)

public:
	CViewGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CViewGameDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_VIEWGAME };
	DWORD gid;
	bool m_bViewCmpAllGame;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstCtrl;
};
