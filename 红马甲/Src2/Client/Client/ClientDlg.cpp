
// ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include "afxinet.h"

#include "DataMgr.h"
#include "DlgModify.h"
#include "DlgLoad.h"

#include "AlertExDlg.h"

#define __USE_WININET
#include "../../include/Http/HttpHelper.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "../../include/UI/ImageHelpers.h"

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientDlg �Ի���



CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: ui::frame::CNonFrameDlg(this, CClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	ui::frame::CNonFrameDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_MAIN_MIN, wndBtnMin_);
	DDX_Control(pDX, IDC_BUTTON_MAIN_CLOSE, wndBtnClose_);

	DDX_Control(pDX, IDC_BUTTON_MAIN, wndBtn1_);
	DDX_Control(pDX, IDC_BUTTON_NEI, wndBtn2_);
	DDX_Control(pDX, IDC_BUTTON_VIDEO, wndBtn3_);
	DDX_Control(pDX, IDC_BUTTON_PUSH, wndBtn4_);
}

BEGIN_MESSAGE_MAP(CClientDlg, ui::frame::CNonFrameDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MAIN, &CClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_NEI, &CClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO, &CClientDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_PUSH, &CClientDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_MIN, &CClientDlg::OnBnClickedButtonMainMin)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_CLOSE, &CClientDlg::OnBnClickedButtonMainClose)

	ON_COMMAND(0x01, &CClientDlg::OnModifyPsw)
	ON_MESSAGE(WM_USER + 0x100, &CClientDlg::OnClickAlert)
	ON_MESSAGE(WM_USER + 0x101, &CClientDlg::OnText)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CClientDlg ��Ϣ�������

BOOL CClientDlg::OnInitDialog()
{
	__super::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	bkImg_.Attach(ui::draw::AtlLoadGdiplusImage(IDB_PNG_MAIN_BK, _T("PNG")));

	HBITMAP index0[] = 
	{
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_INDEX0_NORMAL, _T("PNG")),
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_INDEX0_HOVER, _T("PNG")),
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_INDEX0_CLICK, _T("PNG"))
	};
	wndBtn1_.SetImages(index0[0], index0[1], index0[2]);

	HBITMAP index1[] = 
	{
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_INDEX1_NORMAL, _T("PNG")),
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_INDEX1_HOVER, _T("PNG")),
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_INDEX1_CLICK, _T("PNG"))
	};
	wndBtn2_.SetImages(index1[0], index1[1], index1[2]);

	HBITMAP index2[] = 
	{
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_INDEX2_NORMAL, _T("PNG")),
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_INDEX2_HOVER, _T("PNG")),
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_INDEX2_CLICK, _T("PNG"))
	};
	wndBtn3_.SetImages(index2[0], index2[1], index2[2]);

	HBITMAP index3[] = 
	{
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_INDEX3_NORMAL, _T("PNG")),
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_INDEX3_HOVER, _T("PNG")),
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_INDEX3_CLICK, _T("PNG"))
	};
	wndBtn4_.SetImages(index3[0], index3[1], index3[2]);


	HBITMAP min[] = 
	{
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_MIN_NORMAL, _T("PNG")),
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_MIN_HOVER, _T("PNG")),
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_MIN_CLICK, _T("PNG"))
	};
	wndBtnMin_.SetImages(min[0], min[1], min[2]);

	HBITMAP close[] = 
	{
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_CLOSE_NORMAL, _T("PNG")),
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_CLOSE_HOVER, _T("PNG")),
		ui::draw::AtlLoadGdiplusImage(IDB_PNG_CLOSE_CLICK, _T("PNG"))
	};
	wndBtnClose_.SetImages(close[0], close[1], close[2]);

	htmlCtrl_.CreateFromStatic(IDC_STATIC_HTML, this);

	htmlCtrl_.SetHideContextMenu(TRUE);	
	htmlCtrl_.RegisterCmdMap(0x01, _T("�޸�����"));

	htmlCtrl_.Navigate(data::DataMgrInstance().GetUrl(2).c_str());	

	SetChangeSize(false);
	SetWindowText(_T("������û������ն�"));

	SetTimer(0, 5000, 0);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		__super::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		__super::OnPaint();
	}
}

BOOL CClientDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rcClient;
	GetClientRect(rcClient);

	WTL::CMemoryDC memDC(*pDC, rcClient);

	bkImg_.Draw(memDC, rcClient);

	return TRUE;
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientDlg::OnBnClickedButton1()
{
	/*if( !data::DataMgrInstance().HasPermission(2) )
	{
		AfxMessageBox(_T("��Ǹ������Ȩ���޷��鿴�����ݡ������µ�����VIP �ͷ����ߣ�400-699-0897��"));
		return;
	}*/
	htmlCtrl_.Navigate(data::DataMgrInstance().GetUrl(2).c_str());	
}

void CClientDlg::OnBnClickedButton2()
{
	/*if( !data::DataMgrInstance().HasPermission(3) )
	{
		AfxMessageBox(_T("��Ǹ������Ȩ���޷��鿴�����ݡ������µ�����VIP �ͷ����ߣ�400-699-0897��"));
		return;
	}*/
	htmlCtrl_.Navigate(data::DataMgrInstance().GetUrl(3).c_str());			
}


void CClientDlg::OnBnClickedButton3()
{
	/*if( !data::DataMgrInstance().HasPermission(4) )
	{
		AfxMessageBox(_T("��Ǹ������Ȩ���޷��鿴�����ݡ������µ�����VIP �ͷ����ߣ�400-699-0897��"));
		return;
	}*/
	htmlCtrl_.Navigate(data::DataMgrInstance().GetUrl(4).c_str());
}


void CClientDlg::OnBnClickedButton4()
{
	//if( !data::DataMgrInstance().HasPermission(5) )
		htmlCtrl_.Navigate(data::DataMgrInstance().GetUrl(9).c_str());	
	//else
	//	htmlCtrl_.Navigate(data::DataMgrInstance().GetUrl(5).c_str());	
}



void CClientDlg::OnBnClickedButtonMainMin()
{
	ShowWindow(SW_MINIMIZE);
}


void CClientDlg::OnBnClickedButtonMainClose()
{
	if( MessageBox(_T("ȷ����Ҫ�˳���?"), _T("��ʾ"), MB_YESNO) == IDYES )
		PostQuitMessage(0);
}


void CClientDlg::OnModifyPsw()
{
	CDlgModify dlg;
	if( IDOK == dlg.DoModal() )
	{
		ShowWindow(SW_HIDE);

		CDlgLoad load;
		if( load.DoModal() != IDOK )
			PostQuitMessage(0);
		else
			ShowWindow(SW_SHOW);

	}
}

LRESULT CClientDlg::OnClickAlert(WPARAM, LPARAM)
{
	ShowWindow(SW_SHOWDEFAULT);

	return TRUE;
}

LRESULT CClientDlg::OnText(WPARAM wParam, LPARAM)
{
	wParam = (WPARAM)(LPCTSTR)text_;
	return TRUE;
}

void CClientDlg::OnTimer(UINT_PTR)
{
	static CString text;

	CInternetSession sion(NULL,0);  
	CString str;
	CString url= L"http://www.hjw9999.com/index.php?m=content&c=index&a=lists&catid=29";
	std::auto_ptr<CHttpFile> http((CHttpFile *)sion.OpenURL(url));  

	text_.Empty();
	char buf[8192] = {0};
	while (http->ReadString((LPTSTR)buf, 8192))  
	{  
		text_ += CA2W(buf);
	}
	http->Close();

	TRACE(text_);

	if( text != text_ )
	{

		CAlertExDlg *dlg = new CAlertExDlg(this);
		dlg->Create(CAlertExDlg::IDD, GetDesktopWindow());
		dlg->ShowWindow(SW_SHOW);

		text = text_;
	}
}