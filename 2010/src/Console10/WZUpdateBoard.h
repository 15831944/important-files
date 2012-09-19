#pragma once

#include "resource.h"
// CWZUpdateBoard �Ի���

class CWZUpdateBoard : public CDialog
{
	DECLARE_DYNAMIC(CWZUpdateBoard)

public:
	CWZUpdateBoard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWZUpdateBoard();

// �Ի�������
	enum { IDD = IDD_WZ_UPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg LRESULT OnApplyMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboDrv();
	afx_msg void OnCbnSelchangeInprot();
private:
	CString m_strCliDrv;
	int m_nInProt;
	int m_nP2P;
public:
	afx_msg void OnBnClickedP2p();
};
