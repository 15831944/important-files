#pragma once

#include "I8UIFrame/NonFrameChildDlg.h"
#include "CustomControl/CustomButton.h"
#include "CustomControl/CustomLabel.h"

// CDlgInfoMsg �Ի���

class CDlgInfoMsg 
	: public CNonFrameChildDlg
{
	DECLARE_DYNAMIC(CDlgInfoMsg)

public:
	CDlgInfoMsg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInfoMsg();

// �Ի�������
	enum { IDD = IDD_DIALOG_INFO_MESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	
private:
	bool isShowCancel_;						// �Ƿ���ʾCancel��ť��־

	CString infoMsg_;
	stdex::tString url_;					// ���ȷ����λ��URL

	CCustomButton wndBtnOK_;
	CCustomButton wndBtnCancel_;
	CCustomLabel wndText_;

public:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	
};
