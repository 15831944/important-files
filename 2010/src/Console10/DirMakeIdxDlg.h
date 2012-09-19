#pragma once
#include "afxcmn.h"

#include "makeidxfile.h"
#include "afxwin.h"
class CDirMakeIdxDlg : public CDialog
{
	DECLARE_DYNAMIC(CDirMakeIdxDlg)

public:
	CDirMakeIdxDlg(LPCTSTR dir, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDirMakeIdxDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_MAKEIDX };
	CString m_strDir;
protected:
	bool   m_bFinish;
	i8desk::CMakeIdx MakeIdx;
	int	   m_nIndex;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstCtrl;
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CProgressCtrl m_btnProgress;
	CEdit m_edtLog;
};