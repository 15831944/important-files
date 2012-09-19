#pragma once
#include "afxwin.h"


#include "../ManagerInstance.h"
#include "../I8UIFrame/NonFrameChildDlg.h"
#include "Skin/SkinButton.h"
#include "Skin/SkinRadioBox.h"
#include "Skin/SkinComboBox.h"
#include "../../../../include/Extend STL/UnicodeStl.h"

// CDlgSyncTaskAddorCopy �Ի���

class CDlgSyncTaskAddorCopy : public CNonFrameChildDlg
{
	DECLARE_DYNAMIC(CDlgSyncTaskAddorCopy)

public:
	CDlgSyncTaskAddorCopy( CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSyncTaskAddorCopy();

	// �Ի�������
	enum { IDD = IDD_DIALOG_SYNCTASK_ADDORCOPY };
	enum BtnStatus { isadd = 0, ismodify, iscopy };

private:
	i8desk::ui::SkinRadioBox wndRadioSyncNew_;
	i8desk::ui::SkinRadioBox wndRadioSyncCopy_;

	i8desk::ui::SkinComboBox wndComboSyncCopyTask_;

	i8desk::ui::SkinButton wndBtnOk_;
	i8desk::ui::SkinButton wndBtnCancel_;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();


public:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRadioCopy();
	afx_msg void OnBnClickedRadioNew();


};

