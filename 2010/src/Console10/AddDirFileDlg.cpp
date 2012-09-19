// AddDirFileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Console.h"
#include "AddDirFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif // _DEBUG

IMPLEMENT_DYNAMIC(CAddDirFileDlg, CDialog)

CAddDirFileDlg::CAddDirFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDirFileDlg::IDD, pParent)
{
	m_bIsDir = TRUE;
	m_strDirFile = "";
}

CAddDirFileDlg::~CAddDirFileDlg()
{
}

void CAddDirFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DIR, m_cboDirFile);
}


BEGIN_MESSAGE_MAP(CAddDirFileDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAddDirFileDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CAddDirFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cboDirFile.AddString("Ŀ¼");
	m_cboDirFile.AddString("�ļ�");
	m_cboDirFile.SetCurSel(m_bIsDir ? 0 : 1);
	SetDlgItemText(IDC_DIRFILE, m_strDirFile);

	return TRUE;
}
void CAddDirFileDlg::OnBnClickedOk()
{
	m_bIsDir = m_cboDirFile.GetCurSel() == 0 ? TRUE : FALSE;

	GetDlgItemText(IDC_DIRFILE, m_strDirFile);
	m_strDirFile.Trim();
	if (m_strDirFile.IsEmpty())
	{
		AfxMessageBox("�������ļ�����Ŀ¼.");
		((CEdit*)GetDlgItem(IDC_DIRFILE))->SetFocus();
		return ;
	}
	OnOK();
}
