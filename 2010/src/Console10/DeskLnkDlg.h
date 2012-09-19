#pragma once
#include "afxcmn.h"

#include "ShortcutsListCtrl.h"


// CDeskLnkDlg �Ի���

class CDeskLnkDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeskLnkDlg)

public:
	CDeskLnkDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeskLnkDlg();

// �Ի�������
	enum { IDD = IDD_OPTION_DESKLNK };

private:
	BOOL m_bModify;
	CListCtrl m_lstDeskLnk;
	CShortcutsListCtrl m_lstDeskClassLnk;		// ����ݷ�ʽList Ctrl
	CImageList	m_images;						// ����ݷ�ʽImage

	std::vector<i8desk::std_string> m_vecClassShortcuts;	// ����ݷ�ʽ����

public:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

private:
	void _InitClassShortcuts();
	void _InitListCtrl();
	void _InsertBootTask();

public:
	DECLARE_MESSAGE_MAP()

	LRESULT OnApplyMessage(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedDel();
	afx_msg void OnDestroy();
	afx_msg void OnLvnItemchangedListDesklnk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListDesklnkClass(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListDesklnkClass(NMHDR *pNMHDR, LRESULT *pResult);
};
