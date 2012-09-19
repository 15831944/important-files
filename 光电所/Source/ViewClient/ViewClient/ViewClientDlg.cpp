
// ViewClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ViewClient.h"
#include "ViewClientDlg.h"

#include <memory>
#include <fstream>
#include <sstream>
#include <atlbase.h>
#include <atlconv.h>

#include "DataMgr.hpp"
#include "../../../include/UI/ImageHelpers.h"

#include "../../Common/Utility.hpp"

#include "BitmapHelper.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CViewClientDlg �Ի���



CViewClientDlg::CViewClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CViewClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CViewClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CViewClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_REFRESH_UI_I, &CViewClientDlg::OnRefreshUI_I)
	ON_MESSAGE(WM_REFRESH_UI_J, &CViewClientDlg::OnRefreshUI_J)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CViewClientDlg ��Ϣ�������


BOOL CViewClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	u_short portI = common::GetIniConfig<u_short>(L"ViewClient.ini", L"CONFIG", L"SVR_PORT_I");
	u_short portJ = common::GetIniConfig<u_short>(L"ViewClient.ini", L"CONFIG", L"SVR_PORT_J");
	std::wstring ip = common::GetIniConfig<std::wstring>(L"ViewClient.ini", L"CONFIG", L"SVR_IP");

	dataMgrI_.reset(new view::DataMgr(portI, (LPCSTR)CW2A(ip.c_str()),
		std::tr1::bind(&CViewClientDlg::PostMessage, this, WM_REFRESH_UI_I, 0, 0)));
	dataMgrI_->Start();
	dataMgrJ_.reset(new view::DataMgr(portJ, (LPCSTR)CW2A(ip.c_str()),
		std::tr1::bind(&CViewClientDlg::PostMessage, this, WM_REFRESH_UI_J, 0, 0)));
	dataMgrJ_->Start();

	bk_.Load((common::GetAppPath() + L"res/Bk.jpg").c_str());
	bkAll_.Load((common::GetAppPath() + L"res/ViewClientBK.jpg").c_str());


	SetTimer(1, 500, 0);
	MoveWindow(CRect(0, 0, 1280, 820));
	CenterWindow();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CViewClientDlg::OnDestroy()
{
	KillTimer(1);

	dataMgrI_->Stop();
	dataMgrI_.reset();

	dataMgrJ_->Stop();
	dataMgrJ_.reset();

	CDialog::OnDestroy();
}


void CViewClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

template < typename MemDCT >
void DrawImage(CImage &img, MemDCT &memDC, size_t x_offset, size_t y_offset)
{
	if( !img.IsNull() )
	{
		CRect rcImg(0, 0, img.GetWidth(), img.GetHeight());
		CRect rcDest(CPoint(x_offset, y_offset),
			CSize(img.GetWidth(), img.GetHeight()));
		img.BitBlt(memDC.GetDC(), rcDest, CPoint(0, 0));
	}
}

template < typename BitmapContainerT >
std::pair<size_t, size_t> Caculate(BitmapContainerT &bitmaps, ATL::CImage &img, size_t offsetLeft)
{
	auto info = bitmaps.front();
	bitmaps.pop_front();

	img.Attach(info.bmp_);

	size_t x_offset = offsetLeft+ (512 - img.GetWidth()) / 2;
	size_t y_offset = 231 + (512 - img.GetHeight()) / 2;

	return std::make_pair(x_offset, y_offset);
}

void CViewClientDlg::OnPaint()
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
		CPaintDC dc(this);
		CRect rcClient;
		GetClientRect(rcClient);
		CMemDC memDC(dc, rcClient);
		//memDC.GetDC().FillSolidRect(rcClient, RGB(0, 0, 0));
		for(size_t i = 0; i <= rcClient.Width(); i += bk_.GetWidth())
			bk_.BitBlt(memDC.GetDC().GetSafeHdc(), CPoint(i, 0));

		size_t offsetLeft = (rcClient.Width() - bkAll_.GetWidth()) / 2;
		bkAll_.BitBlt(memDC.GetDC().GetSafeHdc(), CPoint(offsetLeft, 0));

		CRect rcText(offsetLeft + bkAll_.GetWidth() - 380, 80, offsetLeft + bkAll_.GetWidth() - 100, 200);
		memDC.GetDC().SetTextColor(RGB(0, 0, 0));
		memDC.GetDC().SetBkMode(TRANSPARENT);

		CFont font;   
		font.CreatePointFont(150, L"����");
		HGDIOBJ oldFont = memDC.GetDC().SelectObject(font);
		memDC.GetDC().DrawText(dataMgrI_->GetTaskID().c_str(), rcText, DT_TOP | DT_LEFT);
		memDC.GetDC().DrawText(dataMgrI_->GetTaskTime().c_str(), rcText, DT_TOP | DT_RIGHT);
		memDC.GetDC().SelectObject(oldFont);
	
		{
			if( !bitmapHandlesI_.empty() )
			{
				ATL::CImage img;
				std::pair<size_t, size_t> i_bitmap_pos = Caculate(bitmapHandlesI_, img, offsetLeft + 62);
				DrawImage(img, memDC, i_bitmap_pos.first, i_bitmap_pos.second);
			}
			

			if( !bitmapHandlesJ_.empty() )
			{
				ATL::CImage img;
				std::pair<size_t, size_t> j_bitmap_pos = Caculate(bitmapHandlesJ_, img, offsetLeft + 683);
				DrawImage(img, memDC, j_bitmap_pos.first, j_bitmap_pos.second);
			}
		}


		return CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CViewClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


HBITMAP Convert(size_t width, size_t height, const char *data, size_t len)
{
	BITMAPINFOHEADER *lpBitmapHeader = 0;
	BYTE lpBitmapInfo[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)] = {0};

	lpBitmapHeader = (BITMAPINFOHEADER *)lpBitmapInfo;
	lpBitmapHeader->biSize = sizeof (BITMAPINFOHEADER) ;
	lpBitmapHeader->biWidth = width;
	lpBitmapHeader->biHeight = height;
	lpBitmapHeader->biPlanes = 1 ;
	lpBitmapHeader->biBitCount = 8 ;
	lpBitmapHeader->biCompression = BI_RGB ;
	lpBitmapHeader->biSizeImage = width * height;
	lpBitmapHeader->biXPelsPerMeter = 0 ;
	lpBitmapHeader->biYPelsPerMeter = 0 ;
	lpBitmapHeader->biClrUsed = 0 ;
	lpBitmapHeader->biClrImportant = 0 ;


	RGBQUAD *lpRgb = (RGBQUAD *)(lpBitmapInfo + sizeof(BITMAPINFOHEADER));
	for(size_t i = 0; i < 256; i++) 
	{
		lpRgb->rgbBlue = i;
		lpRgb->rgbGreen = i;
		lpRgb->rgbRed = i;
		lpRgb->rgbReserved = 0;
		lpRgb++;
	}

	void* pArray = NULL;
	HBITMAP hbmp = ::CreateDIBSection(0/*pDC->GetSafeHdc()*/, (BITMAPINFO *)lpBitmapInfo, DIB_RGB_COLORS, &pArray, NULL, 0);//����DIB
	ASSERT(hbmp != NULL);
	::SetBitmapBits(hbmp, len, data);

	return hbmp; 
}

LRESULT CViewClientDlg::OnRefreshUI_I(WPARAM, LPARAM)
{
	view::BmpInfo info = dataMgrI_->GetBuffer();

#ifdef COVERT_8
	utility::BITMAPPtr bmp = ui::draw::AtlLoadGdiplusImage(info.buf_.first.get(), info.buf_.second);
#else
	utility::BITMAPPtr bmp = Convert(info.width_, info.height_, info.buf_.first.get(), info.buf_.second);
#endif


	if( bmp == 0 )
		return 0;

	if( bitmapHandlesI_.size() > 500 )
		return 0;
	
	BitmapInfo bmpInfo = { bmp, info.width_, info.height_ };
	bitmapHandlesI_.push_back(bmpInfo);

	CRect rcClient;
	GetClientRect(rcClient);
	rcClient.right = rcClient.CenterPoint().x;
	InvalidateRect(rcClient);
	return 1;
}

LRESULT CViewClientDlg::OnRefreshUI_J(WPARAM, LPARAM)
{
	view::BmpInfo info = dataMgrJ_->GetBuffer();
#ifdef COVERT_8
	utility::BITMAPPtr bmp = ui::draw::AtlLoadGdiplusImage(info.buf_.first.get(), info.buf_.second);
#else
	utility::BITMAPPtr bmp = Convert(info.width_, info.height_, info.buf_.first.get(), info.buf_.second);
#endif
	if( bmp == 0 )
		return 0;

	if( bitmapHandlesJ_.size() > 500 )
		return 0;

	BitmapInfo bmpInfo = { bmp, info.width_, info.height_ };
	bitmapHandlesJ_.push_back(bmpInfo);

	CRect rcClient;
	GetClientRect(rcClient);
	rcClient.left = rcClient.CenterPoint().x;
	InvalidateRect(rcClient);
	return 1;
}

BOOL CViewClientDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CViewClientDlg::OnTimer(UINT_PTR)
{
	if( !bitmapHandlesI_.empty() )
		Invalidate();
}

void CViewClientDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	Invalidate();
}
