#pragma once

#include "resource.h"
#include "afxcmn.h"

// CClientListDlg �Ի���

class CClientListDlg : public CDialog
{
	DECLARE_DYNAMIC(CClientListDlg)

public:
	enum {
		ONLINE, NORESTOREPROT, NOSAFECENTER, NOIEPROT, NODOGPROT 
	};
	CClientListDlg(
		i8desk::AreaInfoMap& AreaInfos,
		i8desk::MachineMap& Machines,
		int selector, 
		CWnd* pParent = NULL
		);   
	virtual ~CClientListDlg();

// �Ի�������
	enum { IDD = IDD_CLIENT_LIST };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnGetdispinfoList(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()
	
	CString GetMachineArea(const i8desk::Machine& Machine);
	size_t GetSelectedClients(std::vector<DWORD>& clients);

private:

	int m_selector;
	i8desk::AreaInfoMap m_AreaInfos;
	i8desk::MachineVector m_Machines;
	CListCtrl m_list;
public:
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAll();
	afx_msg void OnBnClickedClear();
};
