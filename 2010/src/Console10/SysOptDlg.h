#pragma once
#include "afxwin.h"
#include "ListBoxEx.h"
#include <vector>
#include <sstream>

// CSysOptDlg �Ի���

class CSysOptDlg : public CDialog
{
	DECLARE_DYNAMIC(CSysOptDlg)

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
	CSysOptDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysOptDlg();

// �Ի�������
	enum { IDD = IDD_OPTION_SYSOPT };

	size_t m_nInitBoard;
	std::vector<tagItem> m_OptList;
	CDialog* m_pLastDlg;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedOk();
	afx_msg void OnDestroy();
	CListBoxEx m_lstBox;
	CStatic m_btnIcon;
	CStatic m_btnDescription;
};
