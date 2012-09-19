// DlgGameVersion.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../Console.h"
#include "DlgGameVersion.h"

#include "../ManagerInstance.h"

// CDlgGameVersion �Ի���

IMPLEMENT_DYNAMIC(CDlgGameVersion, CNonFrameChildDlg)

CDlgGameVersion::CDlgGameVersion(CWnd* pParent /*=NULL*/)
	: CNonFrameChildDlg(CDlgGameVersion::IDD, pParent)
{

}

CDlgGameVersion::~CDlgGameVersion()
{
}

void CDlgGameVersion::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_GAME_VERSION_TIP, wndLabel_);
	DDX_Control(pDX, IDC_CHECK_GAME_VERSION, wndCheckOK_);
}


BEGIN_MESSAGE_MAP(CDlgGameVersion, CNonFrameChildDlg)
END_MESSAGE_MAP()


// CDlgGameVersion ��Ϣ�������

BOOL CDlgGameVersion::OnInitDialog()
{
	__super::OnInitDialog();

	SetTitle(_T("��Ȩ��ʾ"));

	wndLabel_.SetBkColor(RGB(255, 255, 255));
	wndLabel_.SetWindowText(_T("1��I8һ��ͨ�����ڡ������ϴ��������Դ�������������ѹ���������ϴ��������ҹ�˾����Դ���ҹ�˾δ���ṩ��������Դ�����ء����ϴ����������ṩ��Դʱ�����ʹ��������Ϸ������������Ը���\n\n")
		_T("2���Ѿ���װ��ʹ�á������ϴ�������Դ���û����޷�ȷʵ�Ƿ�Ϊ������Դ�ģ�����24Сʱ��ֹͣʹ�û��������Դ��������ɾ�����Ա������벻��Ҫ�ľ���֮�С�\n\n")
		_T("3��������˾�������еİ���������i8ƽ̨�����û�����������ز�����ʹ�����������֧������."));

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgGameVersion::OnCancel()
{
	UpdateData(TRUE);

	if( IsDlgButtonChecked(IDC_CHECK_GAME_VERSION) != 0 )
		i8desk::GetDataMgr().SetOptVal(OPT_M_GAMEVERSION, 0);

	return __super::OnCancel();
}