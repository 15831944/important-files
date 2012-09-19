#pragma once
#include "afxwin.h"


// CChangAreaDlg �Ի���

class CChangAreaDlg : public CDialog
{
	DECLARE_DYNAMIC(CChangAreaDlg)

public:
	CChangAreaDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangAreaDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_CHANGEAREA };
	i8desk::tagMachine m_Machine;
	std::string m_strArea;
	BOOL m_bMulti;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl m_ipFrom;
	CIPAddressCtrl m_ipNetGate;
	CIPAddressCtrl m_ipMark;
	CIPAddressCtrl m_ipDNS;
	CIPAddressCtrl m_ipDNS2;
	CComboBox m_cboArea;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
