// ReSetPasswordDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDiskClient.h"
#include "ReSetPasswordDlg.h"


// CReSetPasswordDlg �Ի���

IMPLEMENT_DYNAMIC(CReSetPasswordDlg, CDialog)

CReSetPasswordDlg::CReSetPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReSetPasswordDlg::IDD, pParent)
{

}

CReSetPasswordDlg::~CReSetPasswordDlg()
{
}

void CReSetPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReSetPasswordDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CReSetPasswordDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CReSetPasswordDlg ��Ϣ�������

void CReSetPasswordDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT1,m_strOldPassword);
	GetDlgItemText(IDC_EDIT2,m_strNewPassword);
	CString str;
	GetDlgItemText(IDC_EDIT3,str);
	if(str.Compare(m_strNewPassword) != 0)
	{
		AfxMessageBox("������������벻һ��");
		return;
	}
	OnOK();
}
