#pragma once


// CBrowseDirDlg �Ի���

class CDlgCfgBrowseDir : public CDialog
{
	DECLARE_DYNAMIC(CDlgCfgBrowseDir)

public:
	CDlgCfgBrowseDir(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCfgBrowseDir();

// �Ի�������
	enum { IDD = IDD_DIALOG_CONFIG_BROWSEDIR };

private:
	CTreeCtrl listDir_;

public:
	CString strDirOrFile_;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
	stdex::tString GetSelDir(HTREEITEM hSel = NULL);
	bool SelectTreeNode(LPCTSTR lpszText, HTREEITEM hItem);
	
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();	
	afx_msg void OnTvnItemexpandedTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);

};
