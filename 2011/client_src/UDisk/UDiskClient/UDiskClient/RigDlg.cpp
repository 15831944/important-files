// RigDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDiskClient.h"
#include "RigDlg.h"


// CRigDlg �Ի���

IMPLEMENT_DYNAMIC(CRigDlg, CDialog)

CRigDlg::CRigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRigDlg::IDD, pParent)
{

}

CRigDlg::~CRigDlg()
{
}

void CRigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRigDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CRigDlg::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CRigDlg ��Ϣ�������

void CRigDlg::OnBnClickedOk()
{
	GetDlgItemText(IDC_EDIT1,m_strName);
	GetDlgItemText(IDC_EDIT2,m_strPassword);
	CString strtmp;
	GetDlgItemText(IDC_EDIT3,strtmp);
	if(strtmp.Compare(m_strPassword) != 0)
	{
		AfxMessageBox("�����������벻һ��");
		return ;
	}
	if(m_strName.IsEmpty())
	{
		AfxMessageBox("�û�������Ϊ��");
		return ;
	}
	if(m_strPassword.IsEmpty())
	{
		AfxMessageBox("���벻��Ϊ��");
		return ;
	}
	OnOK();
}

HBRUSH CRigDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{

	static CBrush brush;
	if (brush.m_hObject == NULL)
	{
		brush.CreateSolidBrush(RGB(255, 255, 255));
	}
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_STATIC )
	{
		pDC->SetBkMode(1);
		return brush;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

BOOL CRigDlg::OnEraseBkgnd(CDC* pDC)
{
	CDialog::OnEraseBkgnd(pDC);
	static CBrush brush(RGB(255,255,255));
	RECT rt;
	GetClientRect(&rt);
	rt.bottom-=40;
	pDC->FillRect(&rt,&brush);
	return TRUE;
}
