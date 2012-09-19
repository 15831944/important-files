#pragma once

#include "../I8UIFrame/NonFrameChildDlg.h"
#include "Skin/SkinLabel.h"
#include "Skin/SkinCheckBox.h"


// CDlgGameVersion �Ի���

class CDlgGameVersion 
	: public CNonFrameChildDlg
{
	DECLARE_DYNAMIC(CDlgGameVersion)

public:
	CDlgGameVersion(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgGameVersion();

// �Ի�������
	enum { IDD = IDD_DIALOG_GAME_VERSION_TIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual void OnCancel();

private:
	i8desk::ui::SkinLabel wndLabel_;
	i8desk::ui::SkinCheckBox wndCheckOK_;

public:
	DECLARE_MESSAGE_MAP()
	
};
