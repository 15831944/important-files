#pragma once
#include "afxcmn.h"
#include "ConsoleDlg.h"
#include "afxwin.h"

// CFavMgrDlg �Ի���

class CFavMgrDlg : public CDialog
{
	DECLARE_DYNAMIC(CFavMgrDlg)

public:
	CFavMgrDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFavMgrDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_FAVORITE };
	CConsoleDlg* pDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	void SwapListItem(int first, int second);
	int  FindListItem(int nSubItem, LPCTSTR text);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemChangedListFav(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	CComboBox m_cboType;
	CListCtrl m_lstFav;
	afx_msg void OnBnClickedMoveUp();
	afx_msg void OnBnClickedMoveDown();

private:

	DWORD m_dwFavMaxNo;
};
