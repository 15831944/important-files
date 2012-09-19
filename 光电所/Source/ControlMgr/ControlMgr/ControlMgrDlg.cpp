
// ControlMgrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ControlMgr.h"
#include "ControlMgrDlg.h"

#include <atlbase.h>
#include <atlconv.h>

#include "ControlManager.hpp"


#include "../../Common/Utility.hpp"
#include "../../Common/DBMgr.hpp"

#include "../../../include/UI/ImageHelpers.h"

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


// CControlMgrDlg �Ի���




CControlMgrDlg::CControlMgrDlg(CWnd* pParent /*=NULL*/)
: CDialog(CControlMgrDlg::IDD, pParent)
, isOK_(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CControlMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CControlMgrDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_MONITOR_STATUS, &CControlMgrDlg::OnBnClickedButtonMonitorStatus)
	ON_BN_CLICKED(IDC_BUTTON_TASK_MANAGER, &CControlMgrDlg::OnBnClickedButtonTaskManager)
	ON_BN_CLICKED(IDC_BUTTON_OPERATE_LOG, &CControlMgrDlg::OnBnClickedButtonOperateLog)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CControlMgrDlg ��Ϣ�������

BOOL CControlMgrDlg::OnInitDialog()
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

	GetDlgItem(IDC_STATIC_WINDOW)->ShowWindow(SW_HIDE);
	ctrlMgr_.SetDestWindow(GetDlgItem(IDC_STATIC_WINDOW));

	statusMonitor_.reset(new CDlgStatusMonitor(this));
	statusMonitor_->Create(CDlgStatusMonitor::IDD, this);
	taskMgr_.reset(new CDlgTaskMgr(this));
	taskMgr_->Create(CDlgTaskMgr::IDD, this);
	taskLog_.reset(new CDlgTaskLog(this));
	taskLog_->Create(CDlgTaskLog::IDD, this);

	ctrlMgr_.Register(CDlgStatusMonitor::IDD, statusMonitor_.get());
	ctrlMgr_.Register(CDlgTaskMgr::IDD, taskMgr_.get());
	ctrlMgr_.Register(CDlgTaskLog::IDD, taskLog_.get());

	ctrlMgr_[CDlgStatusMonitor::IDD];


	std::wstring dbIP = common::GetIniConfig<std::wstring>(L"ControlMgr.ini", L"DB", L"DB_IP");
	std::wstring dbName = common::GetIniConfig<std::wstring>(L"ControlMgr.ini", L"DB", L"DB_NAME");
	std::wstring dbuserName = common::GetIniConfig<std::wstring>(L"ControlMgr.ini", L"DB", L"DB_USERNAME");
	std::wstring dbPassword = common::GetIniConfig<std::wstring>(L"ControlMgr.ini", L"DB", L"DB_PASSWORD");

	if( !db::DBMgrInstance().Init(dbIP, dbName, dbuserName, dbPassword) )
		return FALSE;

	std::map<std::wstring, _variant_t> configTable;
	_RecordsetPtr &records = db::DBMgrInstance().GetRecordSet(_T("SELECT * FROM config_t"));

	try
	{
		while(!records->adoEOF)
		{
			configTable[(LPCWSTR)(CString)records->GetCollect(_T("param_name"))] = records->GetCollect(_T("param_value"));
			records->MoveNext();
		}
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.ErrorMessage());
		return FALSE;
	}

	std::wstring proxyIPTmp		= (LPCWSTR)(CString)configTable[_T("UDPPROXY_IP")];
	if( proxyIPTmp.empty() )
		AfxMessageBox(_T("Proxy IP��"));
	std::wstring sendSvrIPTmp	= (LPCWSTR)(CString)configTable[_T("SENDSVR_IP")];
	if( sendSvrIPTmp.empty() )
		AfxMessageBox(_T("sendSvrIP��"));

	std::wstring recvSvrIPTmp	= (LPCWSTR)(CString)configTable[_T("RECVSVR_IP")];
	if( recvSvrIPTmp.empty() )
		AfxMessageBox(_T("recvSvrIP��"));

	u_short proxyPort	= configTable[_T("UDPPROXY_PORT")];
	if( proxyPort == 0 )
		AfxMessageBox(_T("proxyPort��"));

	u_short sendSvrPort	= configTable[_T("SENDSVR_PORT")];
	if( sendSvrPort == 0 )
		AfxMessageBox(_T("sendSvrPort��"));

	u_short recvSvrPort	= configTable[_T("RECVSVR_PORT")];
	if( recvSvrPort == 0 )
		AfxMessageBox(_T("recvSvrPort��"));


	std::string proxyIP		= CW2A(proxyIPTmp.c_str());
	std::string sendSvrIP	= CW2A(sendSvrIPTmp.c_str());
	std::string recvSvrIP	= CW2A(recvSvrIPTmp.c_str());

	ctrl::ControlMgrInstance()->Start(ctrl::RemoteInfo(proxyIP, proxyPort),
		ctrl::RemoteInfo(sendSvrIP, sendSvrPort), ctrl::RemoteInfo(recvSvrIP, recvSvrPort));

	isOK_ = true;
	
	bkImgs_[0].Load((common::GetAppPath() + L"res/StatusMonitor.jpg").c_str());
	bkImgs_[1].Load((common::GetAppPath() + L"res/TaskMgr.jpg").c_str());
	bkImgs_[2].Load((common::GetAppPath() + L"res/OperateLog.jpg").c_str());

	SetTimer(1, 5 * 1000, 0);
	ctrlMgr_.GetCurrentControl()->PostMessage(WM_USER + 0x100);

	CRect rc(0, 0, 800, 620);
	MoveWindow(rc);
	CenterWindow();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CControlMgrDlg::OnDestroy()
{
	KillTimer(1);

	statusMonitor_->DestroyWindow();
	taskMgr_->DestroyWindow();
	taskLog_->DestroyWindow();

	if( isOK_ )
	{
		ctrl::ControlMgrInstance()->Stop();
		ctrl::ControlMgrInstance().reset();

		db::DBMgrInstance().UnInit();
	}


	CDialog::OnDestroy();

}



void CControlMgrDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CControlMgrDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

BOOL CControlMgrDlg::OnEraseBkgnd(CDC* pDC)
{
	if( bkImgs_[0].IsNull() )
		return FALSE;

	CRect rcClient;
	GetClientRect(rcClient);
	CMemDC memDC(*pDC, rcClient);
	
	memDC.GetDC().FillSolidRect(rcClient, RGB(255, 0, 0));


	struct
	{
		UINT id;
		CImage &img;
	}totalBkImgs[] = 
	{
		{
			CDlgStatusMonitor::IDD, bkImgs_[0]
		},
		{
			CDlgTaskMgr::IDD, bkImgs_[1]
		},
		{
			CDlgTaskLog::IDD, bkImgs_[2]
		}
	};

	UINT curID = ctrlMgr_.GetCurrentID();
	for(size_t i = 0; i != _countof(totalBkImgs); ++i)
	{
		if( curID == totalBkImgs[i].id )
		{
			totalBkImgs[i].img.BitBlt(memDC.GetDC(), 0, 0);
			break;
		}
	}
	

	return TRUE;
}


//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CControlMgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CControlMgrDlg::OnTimer(UINT_PTR)
{
	ctrlMgr_.GetCurrentControl()->PostMessage(WM_USER + 0x100);
}


void CControlMgrDlg::OnBnClickedButtonMonitorStatus()
{
	ctrlMgr_[CDlgStatusMonitor::IDD];
	Invalidate();
}

void CControlMgrDlg::OnBnClickedButtonTaskManager()
{
	ctrlMgr_[CDlgTaskMgr::IDD];
	Invalidate();
}

void CControlMgrDlg::OnBnClickedButtonOperateLog()
{
	ctrlMgr_[CDlgTaskLog::IDD];
	Invalidate();
}

