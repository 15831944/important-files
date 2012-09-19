#pragma once
#include "afxwin.h"


// CDlgInfoTip �Ի���

class CDlgInfoTip 
	: public CDialog
{
	DECLARE_DYNAMIC(CDlgInfoTip)


private:
	i8desk::std_string m_strContent;		// ��ʾ������
	i8desk::std_string m_strUrl;			// ���ȷ����λ��URL

	BOOL m_bShowCancel;						// �Ƿ���ʾCancel��ť��־


public:
	CDlgInfoTip(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInfoTip();

// �Ի�������
	enum { IDD = IDD_DIALOG_INFO_TIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
	void _InitCtrl();			// ��ʼ��Ctrl
	void _InitContent();		// ��ʼ������			
	void _InitUrl();			// ��ʼ��Url
	
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButtonInfoTipOk();
	afx_msg void OnBnClickedCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

};
