#pragma once

#include "resource.h"
#include "afxcmn.h"

// COptionPenetateFile �Ի���

class COptionPenetateFile : public CDialog
{
	DECLARE_DYNAMIC(COptionPenetateFile)

public:
	COptionPenetateFile(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COptionPenetateFile();

// �Ի�������
	enum { IDD = IDD_OPTION_PENETRATEFILE };
	BOOL m_bModify;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickListdir(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnDeleteitemListdir(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnApplyMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDel();
private:
	CListCtrl m_list;
public:
	afx_msg void OnBnClickedMkidx();
};
