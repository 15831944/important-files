// DlgInfoTip.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgInfoTip.h"
#include "ConsoleDlg.h"

// CDlgInfoTip �Ի���

IMPLEMENT_DYNAMIC(CDlgInfoTip, CDialog)

CDlgInfoTip::CDlgInfoTip(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoTip::IDD, pParent)
	, m_bShowCancel(FALSE)
{

}

CDlgInfoTip::~CDlgInfoTip()
{
}

void CDlgInfoTip::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgInfoTip, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_INFO_TIP_OK, &CDlgInfoTip::OnBnClickedButtonInfoTipOk)
	ON_BN_CLICKED(IDC_INFO_TIP_CANCEL, &CDlgInfoTip::OnBnClickedCancel)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()




void CDlgInfoTip::_InitCtrl()
{
	// �Ƿ���ȡ����ť
	m_bShowCancel = GetConsoleDlg()->m_pDbMgr->GetOptInt(OPT_U_CONSHOWCANCEL);
	if( m_bShowCancel == FALSE )
	{
		CRect rcCancelRect;
		GetDlgItem(IDC_INFO_TIP_CANCEL)->GetWindowRect(rcCancelRect);
		GetDlgItem(IDC_INFO_TIP_CANCEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_INFO_TIP_CANCEL)->DestroyWindow();
		
		ScreenToClient(rcCancelRect);
		GetDlgItem(IDC_BUTTON_INFO_TIP_OK)->MoveWindow(rcCancelRect);
	}
}

void CDlgInfoTip::_InitUrl()
{
	// ��ȡURL
	m_strUrl = GetConsoleDlg()->m_pDbMgr->GetOptString(OPT_U_CONOKURL);
}


void CDlgInfoTip::_InitContent()
{
	// ��ȡ��ʾ����
	m_strContent = GetConsoleDlg()->m_pDbMgr->GetOptString(OPT_U_CONMESSAGE);
	SetDlgItemText(IDC_STATIC_INFO_TIP_MESSAGE, m_strContent.c_str());
}


// CDlgInfoTip ��Ϣ�������

BOOL CDlgInfoTip::OnInitDialog()
{
	CDialog::OnInitDialog();

	_InitCtrl();

	_InitContent();

	_InitUrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgInfoTip::OnBnClickedButtonInfoTipOk()
{
	if( m_strUrl.empty() == false )
	{
		ShellExecute(GetSafeHwnd(), _T("open"), m_strUrl.c_str(), _T(""), _T(""), SW_SHOWNORMAL);
	}

	OnCancel();
}

void CDlgInfoTip::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

void CDlgInfoTip::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

int CDlgInfoTip::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	/*CMenu *pSysMenu = GetSystemMenu(FALSE);
	ASSERT(pSysMenu != NULL);
	VERIFY(pSysMenu->RemoveMenu(SC_CLOSE, MF_BYCOMMAND));*/

	return CDialog::OnCreate(lpCreateStruct);
}

BOOL CDlgInfoTip::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg->message == WM_KEYDOWN )      
	{      
		if( pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE )      
		{      
			return   TRUE;      
		}      
	}        

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgInfoTip::OnSysCommand(UINT nID, LPARAM lParam)
{
	////add the following code
	//if ( ( nID & 0xFFF0 ) == SC_CLOSE ) 
	//{
	//	//if user clicked the "X"
	//	//OnExit();
	//	//---end of code you have added
	//}
	//else 
	//{
	//	CDialog::OnSysCommand( nID, lParam );
	//}

	CDialog::OnSysCommand( nID, lParam );
}
