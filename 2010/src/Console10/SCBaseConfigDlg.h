#pragma once

#include "resource.h"

// CSCBaseConfigDlg �Ի���

class CSCBaseConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CSCBaseConfigDlg)

public:
	CSCBaseConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSCBaseConfigDlg();

// �Ի�������
	enum { IDD = IDD_SC_BASE_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg LRESULT OnApplyMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
