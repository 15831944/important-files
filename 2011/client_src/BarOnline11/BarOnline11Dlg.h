
// BarOnline11Dlg.h : ͷ�ļ�
//

#pragma once

#include "../../include/ui/Frame/NonFrameDlg.h"


// CBarOnlineDlg �Ի���
class CBarOnlineDlg 
	: public CNonFrameDlg
{
	typedef CNonFrameDlg ParentWnd;
// ����
public:
	CBarOnlineDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BARONLINE11_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual BOOL OnInitDialog();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	
public:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
};
