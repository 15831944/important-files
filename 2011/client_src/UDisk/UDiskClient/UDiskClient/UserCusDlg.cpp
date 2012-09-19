// UserCusDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDiskClient.h"
#include "UserCusDlg.h"
#include "UDiskClientDlg.h"

// CUserCusDlg �Ի���

IMPLEMENT_DYNAMIC(CUserCusDlg, CDialog)

CUserCusDlg::CUserCusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserCusDlg::IDD, pParent)
{

}

CUserCusDlg::~CUserCusDlg()
{
}

void CUserCusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserCusDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CUserCusDlg ��Ϣ�������

BOOL CUserCusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	string strInfo = ((CUDiskClientDlg*)AfxGetMainWnd())->m_pSrvConfigInfo->szCustomInfo;

	CFont* pfont;
	pfont =  new CFont;
	VERIFY(pfont->CreateFont(
		30,                        // nHeight
		20,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"������"));                 // lpszFacename

	// Do something with the font just created...

	GetDlgItem(IDC_STATIC1)->SetFont(pfont);
	GetDlgItem(IDC_STATIC1)->SetWindowText(strInfo.c_str());
	pfont->DeleteObject(); 

	delete pfont;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

HBRUSH CUserCusDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	 switch(nCtlColor)     
	{   
	case   CTLCOLOR_STATIC: 
		{
			 
			pDC->SetBkMode(TRANSPARENT); 
		//	pDC->SetTextColor(RGB(255,128,128));
		}

	}  
	return   hbr;   

}
