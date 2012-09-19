
// ClientDlg.h : ͷ�ļ�
//

#pragma once


#include "../../include/UI/Skin/SkinButton.h"
#include "../../include/UI/Frame/NonFrameDlg.h"
#include "../../include/UI/Skin/CustomControl/CustomHtml.h"


// CClientDlg �Ի���
class CClientDlg 
	: public ui::frame::CNonFrameDlg
{
// ����
public:
	CClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();


private:
	ui::skin::Button wndBtnMain_;
	ui::skin::Button wndBtnNei_;
	ui::skin::Button wndBtnVideo_;
	ui::skin::Button wndBtnPush_;
	ui::skin::Button wndBtnGolden_;
	ui::skin::Button wndBtnDiamond_;
	ui::skin::Button wndBtnInstitute_;

	ui::skin::Button wndBtnMin_;
	ui::skin::Button wndBtnClose_;

	ATL::CImage bkImg_;
	CHtmlCtrl htmlCtrl_;

public:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC*);
	afx_msg HCURSOR OnQueryDragIcon();
	
	
	afx_msg void OnBnClickedButtonMain();
	afx_msg void OnBnClickedButtonNei();
	afx_msg void OnBnClickedButtonVideo();
	afx_msg void OnBnClickedButtonPush();
	afx_msg void OnBnClickedButtonGolden();
	afx_msg void OnBnClickedButtonHigh();
	afx_msg void OnBnClickedButtonJigou();
	afx_msg void OnBnClickedButtonMainMin();
	afx_msg void OnBnClickedButtonMainClose();

	afx_msg void OnModifyPsw();
};
