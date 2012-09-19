#pragma once
#include "WZInterface.h"
#include "../I8UIFrame/NonFrameChildDlg.h"

#include "Skin/SkinLabel.h"

// WZDlgWelcome �Ի���

class WZDlgWelcome 
	: public CDialog
	, public i8desk::wz::WZInterface
{
	DECLARE_DYNAMIC(WZDlgWelcome)

public:
	WZDlgWelcome(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~WZDlgWelcome();

// �Ի�������
	enum { IDD = IDD_DIALOG_WZ_WELCOME };

private:
	i8desk::ui::SkinLabel wndLabelWelCome_;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();


public:
	virtual void OnComplate(){}
	virtual void OnShow(int showtype);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

};
