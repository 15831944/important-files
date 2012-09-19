#pragma once

#include "resource.h"
// CWZAccountBoard �Ի���

class CWZAccountBoard : public CDialog
{
	DECLARE_DYNAMIC(CWZAccountBoard)

public:
	CWZAccountBoard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWZAccountBoard();

// �Ի�������
	enum { IDD = IDD_WZ_ACCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg LRESULT OnApplyMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeUsername();
	afx_msg void OnEnChangePassword();
	afx_msg void OnEnChangePassword2();
private:
	CString m_strAccount;
	CString m_strPassword;
	// ����̨��¼����
	CString m_strPassword2;
	//�˵���¼����
	CString m_strCliPassword;
public:
	afx_msg void OnEnChangeClipassword();
};
