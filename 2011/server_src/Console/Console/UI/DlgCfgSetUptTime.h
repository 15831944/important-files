#pragma once

#include "../I8UIFrame/NonFrameChildDlg.h"

#include "Skin/SkinLabel.h"
#include "Skin/SkinButton.h"
#include "Skin/SkinImage.h"

// CSetUptTimeDlg �Ի���

class CDlgCfgSetUptTime : public CNonFrameChildDlg
{
	DECLARE_DYNAMIC(CDlgCfgSetUptTime)

public:
	CDlgCfgSetUptTime(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCfgSetUptTime();

// �Ի�������
	enum { IDD = IDD_DIALOG_CONFIG_SETTIME };


private:
	CDateTimeCtrl wnddateStart_;
	CDateTimeCtrl wnddateEnd_;

	i8desk::ui::SkinLabel wndStartTime_;
	i8desk::ui::SkinLabel wndStopTime_;

	i8desk::ui::SkinButton wndbtnOk_;
	i8desk::ui::SkinButton wndbtnCancel_;

public:
	CTime tmStart;
	CTime tmEnd;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	ATL::CImage outboxLine_;


public:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

};
