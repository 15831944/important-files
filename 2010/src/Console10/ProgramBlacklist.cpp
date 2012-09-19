// ProgramBlacklist.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProgramBlacklist.h"


// CProgramBlacklist �Ի���

IMPLEMENT_DYNAMIC(CProgramBlacklist, CDialog)

CProgramBlacklist::CProgramBlacklist(CWnd* pParent /*=NULL*/)
	: CDialog(CProgramBlacklist::IDD, pParent)
	, m_strProgram(_T(""))
	, m_strDescription(_T(""))
{

}

CProgramBlacklist::~CProgramBlacklist()
{
}

void CProgramBlacklist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PROGRAM, m_strProgram);
	DDX_Text(pDX, IDC_DESCRIPTION, m_strDescription);
}


BEGIN_MESSAGE_MAP(CProgramBlacklist, CDialog)
	ON_BN_CLICKED(IDC_SELECT, &CProgramBlacklist::OnBnClickedSelect)
	ON_BN_CLICKED(IDOK, &CProgramBlacklist::OnBnClickedOk)
END_MESSAGE_MAP()


// CProgramBlacklist ��Ϣ�������

void CProgramBlacklist::OnBnClickedSelect()
{
	static CString strDir = i8desk::GetAppPath().c_str();

	CFileDialog Open(TRUE, "", "", 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		"�����ļ�(*.exe)|*.exe||");	
	Open.m_ofn.lpstrInitialDir = strDir;
	if (Open.DoModal() == IDOK)
	{
		strDir = Open.GetPathName();
		m_strProgram = Open.GetFileName();
		UpdateData(FALSE);
	}
}

void CProgramBlacklist::OnBnClickedOk()
{
	UpdateData();

	OnOK();
}
