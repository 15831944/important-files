// IdcUptToolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CIdcUptToolDlg �Ի���
class CIdcUptToolDlg : public CDialog
{
// ����
public:
	CIdcUptToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MAINFRAME };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	void  ScanDir(CString szDir, int nBaseLen);
	DWORD MakeTimeFromFileTime(FILETIME& ft);
	CString GetFileCrc32(const CString& szFileName);

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListCtrl m_lstCtrl;
	afx_msg void OnBnClickedOpendir();
	afx_msg void OnBnClickedMakeidx();
	afx_msg void OnBnClickedDelfile();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedModifyfile();
};
