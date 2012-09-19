#pragma once

#include "I8UIFrame/NonFrameChildDlg.h"
#include "CustomControl/CustomLabel.h"
#include "CustomControl/CustomButton.h"

// CMessageBox �Ի���

class CMessageBox 
	: public CNonFrameChildDlg
{
	DECLARE_DYNAMIC(CMessageBox)

public:
	CMessageBox(const stdex::tString &title, const stdex::tString &content, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMessageBox();

// �Ի�������
	enum { IDD = IDD_DIALOG_MESSAGE_BOX };

private:
	CCustomLabel wndText_;
	CCustomButton wndBtnOK_;
	CCustomButton wndBtnCancel_;

	stdex::tString title_;
	stdex::tString content_;

public:
	void SetContent(const stdex::tString &title, const stdex::tString &content);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnStnClickedStaticMessageboxText();
};
