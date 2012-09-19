#pragma once
#include "afxwin.h"


// CFindGameDlg �Ի���

class CFindGameDlg : public CDialog
{
	DECLARE_DYNAMIC(CFindGameDlg)

public:
	CFindGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFindGameDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_FINDGAME };

	int m_nCurPos;
	CString m_InputChar;
protected:	
	std::set<int> m_list;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFindNext();
	afx_msg void OnBnClickedSelectAll();
	afx_msg void OnBnClickedOk();
	CButton m_btnDwon;
	int m_btnUp;
	afx_msg void OnBnClickedRadio4();
	CButton m_btnByName;
	int m_btnByGid;
	afx_msg void OnBnClickedRadioDown();
	CEdit m_edtFindStr;
	afx_msg void OnEnSetfocusEditFind();
	afx_msg void OnEnChangedEditFind();
};
