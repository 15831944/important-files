#pragma once
#include "WZInterface.h"
#include "../I8UIFrame/NonFrameChildDlg.h"

#include "../ManagerInstance.h"
#include "Skin/SkinButton.h"
#include "Skin/SkinListCtrl.h"


// WZDlgPushGame �Ի���

class WZDlgPushGame 
	: public CDialog
	, public i8desk::wz::WZInterface

{
	DECLARE_DYNAMIC(WZDlgPushGame)

public:
	WZDlgPushGame(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~WZDlgPushGame();

// �Ի�������
	enum { IDD = IDD_DIALOG_WZ_PUSHGAME };

private:
	i8desk::ui::SkinButton wndbtnAdd_;
	i8desk::ui::SkinButton wndbtnDel_;
	i8desk::ui::SkinButton wndbtnModify_;

	i8desk::ui::SkinListCtrl wndListPushGames_;

	i8desk::data_helper::PushGameTraits::VectorType curPushGames_;
	ATL::CImage workOutLine_;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

private:
	//bool _CheckDatas(i8desk::data_helper::PushGameTraits::ValueType &val);
	void _ShowView();

public:
	virtual void OnComplate(){}
	virtual void OnShow(int showtype);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButtonPushGameAdd();
	afx_msg void OnBnClickedButtonPushGameDel();
	afx_msg void OnBnClickedButtonPushGameModify();
	afx_msg void OnLvnGetdispinfoListPushGameInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRDblclkListPushGameInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

};
