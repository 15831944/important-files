#pragma once

#include "resource.h"
#include "afxwin.h"
#include "ListBoxEx.h"

#include <vector>
#include <sstream>

// CSafeCenterConfigDlg �Ի���

class CSafeCenterConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CSafeCenterConfigDlg)

	typedef struct tagItem
	{
		DWORD	IconID;
		LPCSTR	Caption;
		LPCSTR	Description;
		CDialog*pDlg;
		tagItem(DWORD ID, LPSTR szCaption, LPSTR szDescription, CDialog* pdlg = NULL)
		{
			this->IconID = ID;
			this->Caption = szCaption;
			this->Description = szDescription;
			this->pDlg = pdlg;
		}
	}tagItem;

public:
	CSafeCenterConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSafeCenterConfigDlg();

// �Ի�������
	enum { IDD = IDD_SAFECENTER_CONFIG };

	std::vector<tagItem> m_OptList;
	CDialog* m_pLastDlg;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListBoxEx m_lstBox;
	afx_msg void OnLbnSelchangeList();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedOk();
	afx_msg void OnDestroy();
	CStatic m_btnIcon;
	CStatic m_btnDescription;
};
