// WZDlgClient.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../Console.h"
#include "WZDlgClient.h"
#include "../ManagerInstance.h"
#include "../../../../include/Extend STL/StringAlgorithm.h"
#include "../../../../include/Utility/Utility.h"
#include "../../../../include/ui/ImageHelpers.h"
#include "../MessageBox.h"
#include "../ui/Skin/SkinMgr.h"
#include "../UI/UIHelper.h"

// WZDlgClient �Ի���

IMPLEMENT_DYNAMIC(WZDlgClient, CDialog)

WZDlgClient::WZDlgClient(CWnd* pParent /*=NULL*/)
	: CDialog(WZDlgClient::IDD, pParent)
	, textGonggao_(_T(""))
	, textComboDrv_(_T(""))
	, textNetBar_(_T(""))
	, textTemperatrue_(_T(""))
	, textIE_(_T(""))
	, gonggaoRuntype(0)
{
	workOutLine_.Attach(i8desk::ui::SkinMgrInstance().GetSkin(_T("Common/OutBoxLine.png")));
}

WZDlgClient::~WZDlgClient()
{
	workOutLine_.Detach();
}

void WZDlgClient::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WZ_CLIENTSET_MENUSKIN, wndComboSkin_);
	DDX_Control(pDX, IDC_COMBO_WZ_CLIENTSET_MENUMODE, wndComboDisplayMode_);
	DDX_Control(pDX, IDC_COMBO_WZ_CLIENTSET_MENUSTART, wndComboOperateMode_);
	DDX_Control(pDX, IDC_COMBO_WZ_CLIENTSET_UPDATEPATH, wndComboDrv_);
	DDX_Text(pDX, IDC_COMBO_WZ_CLIENTSET_UPDATEPATH, textComboDrv_);
	DDX_Control(pDX, IDC_RADIO_WZ_CLIENTSET_AGREE, wndRadioAgree_);
	DDX_Control(pDX, IDC_RADIO_WZ_CLIENTSET_CUSTOM, wndRadioCustom_);

	DDX_Control(pDX, IDC_RADIO_WZ_CLIENTSET_GONGGAOPIC, wndRadioNetBarPic_);
	DDX_Control(pDX, IDC_RADIO_WZ_CLIENTSET_NETBARGONGGAO, wndRadioGongGao_);

	DDX_Control(pDX, IDC_CHECK_WZ_CLIENTSET_AUTOSTARTMENU, wndAutoStartMenu_);
	DDX_Control(pDX, IDC_CHECK_WZ_CLIENTSET_BROWSEDIR, wndCheckCliDir_);

	DDX_Control(pDX, IDC_STATIC_WZ_CLIENTSET_MENU, wndLabelCliMenu_);
	DDX_Control(pDX, IDC_STATIC_WZ_CLIENTSET_MENUSKIN, wndLabelCliMenuSkin_);
	DDX_Control(pDX, IDC_STATIC_WZ_CLIENTSET_MENUMODE, wndLabelCliMenuMode_);
	DDX_Control(pDX, IDC_STATIC_WZ_CLIENTSET_MENUSTART, wndLabelRunGame_);
	DDX_Control(pDX, IDC_STATIC_WZ_CLIENTSET_UPDATEPATH, wndLabelLocalDrv_);


	DDX_Control(pDX, IDC_CHECK_WZ_CLIENTSET_ONLYREAD, wndCheckOnlyRead_);

	DDX_Control(pDX, IDC_STATIC_WZ_CLIENTSET_NETBARJPG, wndLabelNetBar_);
	DDX_Control(pDX, IDC_STATIC_WZ_CLIENTSET_CPU_TEMPRATRUE, wndLabelTemperatrue_);
	DDX_Control(pDX, IDC_STATIC_WZ_CLIENTSET_IE, wndLabelIE_);

	DDX_Control(pDX, IDC_EDIT_WZ_CLIENTSET_TEMPERATRUE, wndEditTemperatrue_);
	DDX_Control(pDX, IDC_EDIT_WZ_CLIENTSET_GONGGAOPIC, wndEditGonggaoPic_);
	DDX_Control(pDX, IDC_EDIT_WZ_CLIENTSET_NETBARJPG, wndEditNetBar_);
	DDX_Control(pDX, IDC_EDIT_WZ_CLIENTSET_GONGGAO, wndEditGonggao_);
	DDX_Control(pDX, IDC_EDIT_WZ_CLIENTSET_IE, wndEditIE_);

	DDX_Text(pDX, IDC_EDIT_WZ_CLIENTSET_GONGGAOPIC, textGonggaoPic_);
	DDX_Text(pDX, IDC_EDIT_WZ_CLIENTSET_NETBARJPG, textNetBar_);
	DDX_Text(pDX, IDC_EDIT_WZ_CLIENTSET_GONGGAO, textGonggao_);
	DDX_Text(pDX, IDC_EDIT_WZ_CLIENTSET_TEMPERATRUE, textTemperatrue_);
	DDX_Text(pDX, IDC_EDIT_WZ_CLIENTSET_IE, textIE_);

	DDX_Control(pDX, IDC_BUTTON_WZ_CLIENTSET_GONGGAOPIC, wndBtnGonggaoPic_);
	DDX_Control(pDX, IDC_BUTTON_WZ_CLIENTSET_NETBARJPG, wndBtnNetBar_);
	DDX_Control(pDX, IDC_BUTTON_WZ_CLIENTSET_FONT, wndBtnFont_);

}


BEGIN_MESSAGE_MAP(WZDlgClient, CDialog)
	ON_BN_CLICKED(IDC_RADIO_WZ_CLIENTSET_CUSTOM, &WZDlgClient::OnBnClickedCheckCustom)
	ON_BN_CLICKED(IDC_RADIO_WZ_CLIENTSET_AGREE, &WZDlgClient::OnBnClickedCheckAgree)
	ON_CBN_SELCHANGE(IDC_COMBO_WZ_CLIENTSET_MENUSKIN, &WZDlgClient::OnCbnSelchangeComboMenuSkin)
	ON_BN_CLICKED(IDC_RADIO_WZ_CLIENTSET_GONGGAOPIC, &WZDlgClient::OnBnClickedNetBarPic)
	ON_BN_CLICKED(IDC_RADIO_WZ_CLIENTSET_NETBARGONGGAO, &WZDlgClient::OnBnClickedGongGao)
	ON_BN_CLICKED(IDC_BUTTON_WZ_CLIENTSET_NETBARJPG, &WZDlgClient::OnBnClickedNetbarJpg)
	ON_BN_CLICKED(IDC_BUTTON_WZ_CLIENTSET_GONGGAOPIC, &WZDlgClient::OnBnClickedGonggaoPic)
	ON_BN_CLICKED(IDC_BUTTON_WZ_CLIENTSET_FONT, &WZDlgClient::OnBnClickedButtonClientsetFont)

	ON_WM_ERASEBKGND()

END_MESSAGE_MAP()


// WZDlgClient ��Ϣ�������
BOOL WZDlgClient::OnInitDialog()
{
	CDialog::OnInitDialog();

	//���ò˵���ʾģʽ
	wndComboDisplayMode_.AddString(_T("ȫ��"));
	wndComboDisplayMode_.AddString(_T("����"));

	//�˵���Ϸ�������Զ���
	wndComboOperateMode_.AddString(_T("��С��"));
	wndComboOperateMode_.AddString(_T("�ر�"));

	//�ͻ�����ű�����Ϸ�̷�
	stdex::tString szDrv;
	for (TCHAR chDrv='D'; chDrv<='Z'; chDrv++)
	{
		szDrv = chDrv;
		stdex::ToUpper(szDrv);
		wndComboDrv_.AddString(szDrv.c_str());
	}

	_ReadDatas();

	return TRUE;
}

void WZDlgClient::_ReadDatas()
{
	_SetComboBarSkin();

	stdex::tString str;
	//���ò˵�Ƥ���ļ�
	str = _T("Ĭ��");
	str = i8desk::GetDataMgr().GetOptVal(OPT_M_CLISKIN,str);
	str = str.substr(0, str.find('|'));
	int nitem = wndComboSkin_.SelectString(-1,str.c_str());
	wndComboSkin_.SetCurSel(nitem);

	//���ò˵���ʾģʽ
	wndComboDisplayMode_.SetCurSel(i8desk::GetDataMgr().GetOptVal(OPT_M_WINMODE, 0));

	//�˵���Ϸ������
	switch (i8desk::GetDataMgr().GetOptVal(OPT_M_MENUACT, 0))
	{
	case 0://Ĭ���޶���
		OnBnClickedCheckAgree();
		wndComboOperateMode_.SetCurSel(0);
		break;
	case 1://��ʾ���»�
		OnBnClickedCheckCustom();
		wndComboOperateMode_.SetCurSel(0);
		break;
	case 2://��ʾ�ر�
		OnBnClickedCheckCustom();
		wndComboOperateMode_.SetCurSel(1);
		break;
	}

	//�Ҽ����Ŀ¼
	wndCheckCliDir_.SetCheck(i8desk::GetDataMgr().GetOptVal(OPT_M_BROWSEDIR, 1));

	//����ʱ������Ϸ�˵�
	wndAutoStartMenu_.SetCheck(i8desk::GetDataMgr().GetOptVal(OPT_M_RUNMENU, 0));

	

	// ��ʾ����ķ�ʽ��0��ͼƬ���棻1���������� 2:��������֣�
	gonggaoRuntype = i8desk::GetDataMgr().GetOptVal(OPT_M_SHOWGONGGAOTYPE, 0);
	if (gonggaoRuntype == i8desk::Pic)
		OnBnClickedNetBarPic();
	else
		OnBnClickedGongGao();

	//����ͼƬ·��();
	str = _T("");
	textGonggaoPic_ = i8desk::GetDataMgr().GetOptVal(OPT_M_GGPICDIR, str).c_str();


	//����ͼƬ·��
	str = _T("");
	textNetBar_ = i8desk::GetDataMgr().GetOptVal(OPT_M_NETBARJPG, str).c_str();

	//��������
	str = _T("");
	textGonggao_ = _GetGonggao(i8desk::GetDataMgr().GetOptVal(OPT_M_GGMSG, str)).c_str();
	if(textGonggao_.IsEmpty())
	{
		str = _T("\r\n\r\n\r\n ��ӭ���ٱ����ɣ������Ʊ��ܺ����Ĳ�����ⶪʧ��\r\n ����������Ҫ��������ϵ���ܣ�лл��");
		_SetGonggao(str);
		textGonggao_ = _GetGonggao(i8desk::GetDataMgr().GetOptVal(OPT_M_GGMSG, str)).c_str();
	}

	//��������
	str = _T("Microsoft Sans Serif|30|0|0");
	strFontString_ = i8desk::GetDataMgr().GetOptVal(OPT_M_GGFONT,str ).c_str();


	//�ͻ�����ű�����Ϸ�̷�
	str = _T("E");
	str = i8desk::GetDataMgr().GetOptVal(OPT_M_GAMEDRV, str);
	int item = wndComboDrv_.SelectString(-1,str.c_str());
	wndComboDrv_.SetCurSel(item);

	// CPU����¶�
	textTemperatrue_ = i8desk::GetDataMgr().GetOptVal(OPT_M_CPU_TEMPRATURE, _T("60")).c_str();

	// IE��ҳ
	str = _T("");
	textIE_ = i8desk::GetDataMgr().GetOptVal(OPT_M_IEURL , str).c_str();

	UpdateData(FALSE);
}

stdex::tString WZDlgClient::_GetGonggao(const stdex::tString &text)
{
	if(utility::IsEmpty(text.c_str()))
		return text;

	std::string src = CT2A(text.c_str());
	int len = ATL::Base64DecodeGetRequiredLength(src.length());
	std::vector<byte> vec(len + 1);

	ATL::Base64Decode(src.data(), len, &vec[0], &len);

	stdex::tString savePath(CA2T((char *)&(vec[0])));
	return savePath;
}

void WZDlgClient::_SetGonggao( const stdex::tString &text)
{
	std::string src = CT2A(text.c_str());
	int len = ATL::Base64EncodeGetRequiredLength(src.length());
	std::vector<char> vec;
	vec.resize(len + 1);

	ATL::Base64Encode((const byte *)src.c_str(), src.length(), &vec[0], &len);

	stdex::tString val = CA2T(&vec[0]);

	i8desk::GetDataMgr().SetOptVal(OPT_M_GGMSG,  val);
}

void WZDlgClient::OnCbnSelchangeComboMenuSkin()
{
	int nSel = 0;
	if ((nSel = wndComboSkin_.GetCurSel()) == -1) 
		nSel = 0;
	TCHAR buf[MAX_PATH] = {0};
	wndComboSkin_.GetLBText(nSel, buf);

}

void WZDlgClient::OnBnClickedNetBarPic()
{
	wndRadioGongGao_.SetCheck(FALSE);
	wndRadioNetBarPic_.SetCheck(TRUE); 
	gonggaoRuntype = i8desk::Pic;
}

void WZDlgClient::OnBnClickedGongGao()
{
	wndRadioGongGao_.SetCheck(TRUE);
	wndRadioNetBarPic_.SetCheck(FALSE);
	gonggaoRuntype = i8desk::Text;
}

void WZDlgClient::OnBnClickedCheckCustom()
{
	wndRadioAgree_.SetCheck(FALSE);
	wndRadioCustom_.SetCheck(TRUE); 
	wndComboOperateMode_.EnableWindow(TRUE);
}

void WZDlgClient::OnBnClickedCheckAgree()
{
	wndRadioAgree_.SetCheck(TRUE);
	wndRadioCustom_.SetCheck(FALSE); 
	wndComboOperateMode_.EnableWindow(FALSE);
}

void WZDlgClient::_SetComboBarSkin()
{
	i8desk::data_helper::BarSkinTraits::VectorType barSkins;
	i8desk::GetDataMgr().GetBarSkin(barSkins); 
	wndComboSkin_.ResetContent();
	for(i8desk::data_helper::BarSkinTraits::VecIterator it= barSkins.begin();	
		it != barSkins.end(); ++it) 
	{ 
		wndComboSkin_.AddString((*it)->Style);
	}
}

void WZDlgClient::OnBnClickedNetbarJpg()
{

	UpdateData(TRUE);

	if( textNetBar_.Right(1) == _T("\\") )
		textNetBar_.Delete(textNetBar_.GetLength() - 1);

	CFileDialog fileDlg(TRUE, _T(""), _T(""), 4|2, _T("�����ļ�(*.*)|*.*||"));
	CString fileName;
	fileDlg.m_ofn.lpstrInitialDir = textNetBar_;
	if( fileDlg.DoModal() == IDOK )
		fileName = fileDlg.GetPathName();
	else
		return;

	textNetBar_ = fileName;

	UpdateData(FALSE);
}

void WZDlgClient::OnBnClickedGonggaoPic()
{
	UpdateData(TRUE);

	if( textGonggaoPic_.Right(1) == _T("\\") )
		textGonggaoPic_.Delete(textGonggaoPic_.GetLength() - 1);

	CFileDialog fileDlg(TRUE, _T(""), _T(""), 4|2, _T("�����ļ�(*.*)|*.*||"));
	CString fileName;
	fileDlg.m_ofn.lpstrInitialDir = textGonggaoPic_;
	if( fileDlg.DoModal() == IDOK )
		fileName = fileDlg.GetPathName();
	else
		return;

	textGonggaoPic_ = fileName;

	UpdateData(FALSE);
}

void WZDlgClient::OnBnClickedButtonClientsetFont()
{
	CFontDialog dlg(&logfont_);
	dlg.m_cf.rgbColors = fontColor_;
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetCurrentFont(&logfont_);
		DWORD flag = 0;

		if (dlg.IsBold())		flag |= (1<<0);
		if (dlg.IsItalic())		flag |= (1<<1);
		if (dlg.IsUnderline())	flag |= (1<<2);
		if (dlg.IsStrikeOut())	flag |= (1<<3);

		strFontString_.Format(_T("%s|%d|%d|%d"), 
			logfont_.lfFaceName, abs(logfont_.lfHeight), dlg.GetColor(), flag);
		font_.DeleteObject();
		font_.CreateFontIndirect(&logfont_);
		fontColor_ = dlg.GetColor();
	}	
}

void WZDlgClient::OnComplate()
{
	UpdateData(TRUE);

	int nSel = 0;
	if ((nSel = wndComboSkin_.GetCurSel()) == -1) 
	{
		CMessageBox box(_T("��ʾ"), _T("û�����ÿͻ���Ƥ��ͼƬ"));
		box.DoModal();
	}
	else
	{
		CString skin;
		wndComboSkin_.GetLBText(nSel, skin);
		skin += _T("|") + skin + _T(".png");
		i8desk::GetDataMgr().SetOptVal(OPT_M_CLISKIN,(LPCTSTR)skin);

	}
	
	//����ģʽ
	i8desk::GetDataMgr().SetOptVal(OPT_M_WINMODE, wndComboDisplayMode_.GetCurSel());
	
	//�˵���Ϸ������
	int act = 0;
	if(wndRadioCustom_.GetCheck())
	{ 
		if (0 == wndComboOperateMode_.GetCurSel())
			act = 1 ;
		else
			act = 2;
	}
	i8desk::GetDataMgr().SetOptVal(OPT_M_MENUACT, act);

	//�Ҽ����Ŀ¼
	i8desk::GetDataMgr().SetOptVal(OPT_M_BROWSEDIR, wndCheckCliDir_.GetCheck());

	//�����Զ������˵�
	i8desk::GetDataMgr().SetOptVal(OPT_M_RUNMENU, wndAutoStartMenu_.GetCheck());

	//����������
	i8desk::GetDataMgr().SetOptVal(OPT_M_ONLYONE, wndCheckOnlyRead_.GetCheck());
	
	//�ͻ�����ű�����Ϸ�̷�
	nSel = 0;
	TCHAR buf[10] = {0};
	nSel = wndComboDrv_.GetCurSel();
	if (nSel == -1) nSel = 1;
	wndComboDrv_.GetLBText(nSel, buf);
	i8desk::GetDataMgr().SetOptVal(OPT_M_GAMEDRV, buf);

	// ��ʾ����ķ�ʽ��0��ͼƬ���棻1���������� 2:��������֣�
	i8desk::GetDataMgr().SetOptVal(OPT_M_SHOWGONGGAOTYPE, gonggaoRuntype);
	if( gonggaoRuntype == i8desk::Pic )
	{
		//����ͼƬ·��
		i8desk::GetDataMgr().SetOptVal(OPT_M_GGPICDIR, (LPCTSTR)textGonggaoPic_);
	}
	else
	{
		//��������
		stdex::tString text = textGonggao_;
		_SetGonggao(text);
		//��������
		i8desk::GetDataMgr().SetOptVal(OPT_M_GGFONT, (LPCTSTR)strFontString_);
	}

	//����ͼƬ·��
	i8desk::GetDataMgr().SetOptVal(OPT_M_NETBARJPG, (LPCTSTR)textNetBar_);

	// CPU����¶�
	i8desk::GetDataMgr().SetOptVal(OPT_M_CPU_TEMPRATURE, (LPCTSTR)textTemperatrue_);

	// IE��ҳ
	i8desk::GetDataMgr().SetOptVal(OPT_M_IEURL, (LPCTSTR)textIE_);


}

void WZDlgClient::OnShow(int showtype)
{
	ShowWindow(showtype);
}


BOOL WZDlgClient::OnEraseBkgnd(CDC* pDC)
{
	CRect rcClient;
	GetClientRect(rcClient);

	WTL::CMemoryDC memDC(pDC->GetSafeHdc(), rcClient);
	HBRUSH brush = AtlGetBackgroundBrush(GetSafeHwnd(), GetParent()->GetSafeHwnd());
	memDC.FillRect(rcClient, brush);

	wndEditGonggao_.GetWindowRect(rcClient);
	i8desk::ui::DrawFrame(this, memDC, rcClient, &workOutLine_);

	//CRect rc
	return TRUE;

}