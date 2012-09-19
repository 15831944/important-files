// UptPrgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BarOnline.h"
#include "UptPrgDlg.h"
#include "MainFrame.h"
#include "UpdateGameCli.h"
#include "UptOptDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "UpdateGameCli.lib")

IMPLEMENT_DYNAMIC(CUptPrgDlg, CDialog)

CUptPrgDlg::CUptPrgDlg(CWnd* pParent /*=NULL*/)
: CDialog(CUptPrgDlg::IDD, pParent)
{
	m_hUpdate = NULL;
	m_fcCopyMode = FC_COPY_VERSION;
	m_hPlugCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND));
}

CUptPrgDlg::~CUptPrgDlg()
{
}

void CUptPrgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CAPTION, m_btnCaption);
	DDX_Control(pDX, IDC_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_GAMEPLUG, m_btnGamePlug);
	DDX_Control(pDX, IDC_PROGRESS, m_btnProgress);
	DDX_Control(pDX, IDC_STATUS, m_btnStatus);
	DDX_Control(pDX, IDC_TIME, m_btnTime);
	DDX_Control(pDX, IDC_RUN, m_btnRun);
	DDX_Control(pDX, IDC_SEARCH, m_btnSearch);
	DDX_Control(pDX, IDC_BUYCARD, m_btnBuyCard);
	DDX_Control(pDX, IDC_GAMESAVE, m_btnVidoSkill);
	DDX_Control(pDX, IDC_MODIFY, m_btnModify);
	DDX_Control(pDX, IDC_FAVORITE, m_btnFavorite);
	DDX_Control(pDX, IDC_PLUG,	   m_btnPlug);
	DDX_Control(pDX, IDC_LIST_GAME, m_lstGamePlug);
}

BEGIN_MESSAGE_MAP(CUptPrgDlg, CDialog)
	ON_WM_DESTROY()
	ON_WM_NCHITTEST()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_CLOSE,	&CUptPrgDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_RUN,		&CUptPrgDlg::OnBnClickedRun)
	ON_BN_CLICKED(IDC_SEARCH,	&CUptPrgDlg::OnBnClickedSearch)	
	ON_BN_CLICKED(IDC_BUYCARD,	&CUptPrgDlg::OnBnClickedBuycard)
	ON_BN_CLICKED(IDC_VIDEOSKILL, &CUptPrgDlg::OnBnClickedVideoSkill)
	ON_BN_CLICKED(IDC_MODIFY,	&CUptPrgDlg::OnBnClickedModify)
	ON_BN_CLICKED(IDC_FAVORITE, &CUptPrgDlg::OnBnClickedFavorite)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_GAME, OnGetdispinfoList)
	ON_WM_ERASEBKGND()
	ON_NOTIFY(NM_CLICK, IDC_LIST_GAME, &CUptPrgDlg::OnNMClickListGame)
END_MESSAGE_MAP()

BOOL CUptPrgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//���沼�ִ���
	{
		CString str, strUrl;
		CRect rcClient(0, 0, 514, 521), rc;
		CRgn rgn;
		rgn.CreateRoundRectRgn(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom, 10, 10);

		TCHAR szMacAddr[30] = {0};
		AfxGetDbMgr()->GetMacAddr(szMacAddr, sizeof(szMacAddr));
		strUrl.Format(TEXT("http://ads.i8.com.cn/ad/client/adbar09_gx.html?ProductID=%lu&ProductName=%s&nid=%lu&oemid=%lu&cmac=%s"), m_arGameInfo[0].gid, AfxGetDbMgr()->TransChToGBK(m_arGameInfo[0].Name), AfxGetDbMgr()->GetIntOpt(OPT_U_NID), AfxGetDbMgr()->GetIntOpt(OPT_U_OEMID),  szMacAddr);
		m_WebPage.Create(NULL, NULL, WS_VISIBLE|WS_CHILD, CRect(7, 31, 500+7, 250+31), this, AFX_IDW_PANE_FIRST);
		m_WebPage.SetSilent(TRUE);
		m_WebPage.Navigate2(strUrl);

		rc.left = 10; rc.top = 5;
		rc.right = 200; rc.bottom = 24;
		m_btnCaption.MoveWindow(&rc);
		m_btnCaption.SetWindowText(m_arGameInfo[0].Name);
		m_btnCaption.SetTextStyle(DEFAULT_FONT_NAME, 12, RGB(255, 255, 255), RGB(255, 255, 255), 
			RGB(255, 255, 255), RGB(255, 255, 255), CButtonEx::BTEXT_LEFT);

		rc.right = rcClient.right - 15 ; rc.left = rc.right - 41;
		rc.top = 3; rc.bottom = rc.top + 24;
		m_btnClose.SetImage(TEXT("Skin/Wnd/GongGao/��ť_�ر�_Ĭ��״̬.png"), 
			TEXT("Skin/Wnd/GongGao/��ť_�ر�_��꾭��.png"), TEXT("Skin/Wnd/GongGao/��ť_�ر�_����.png"));
		m_btnClose.MoveWindow(&rc);

		//������Ϸ
		rc = CRect(10, 290, 110+10, 20+290);
		m_btnGamePlug.MoveWindow(&rc);

		m_iGamePlug.Create(32, 32, ILC_COLOR32|ILC_MASK, 1, 1);	
		m_lstGamePlug.SetImageList(&m_iGamePlug, LVSIL_NORMAL);
		m_lstGamePlug.SetBkColor(RGB(233, 236, 241));
		m_lstGamePlug.SetTextBkColor(-1);
		m_lstGamePlug.ModifyStyle(LVS_ALIGNLEFT, LVS_ALIGNTOP);
		m_lstGamePlug.InsertColumn(0, TEXT("Name"), 80);
		m_lstGamePlug.SetBkColor(RGB(255, 255, 255));

		m_nGameCount = 1;
		m_nCurrentUptIdx = 0;
		
		for (std::map<DWORD, tagGameInfo*>::iterator it = AfxGetDbMgr()->m_mapGameInfo.begin(); 
			it != AfxGetDbMgr()->m_mapGameInfo.end() && m_nGameCount<6; ++it)
		{
			if (it->second->pid == m_arGameInfo[0].gid)
			{
				m_arGameInfo[m_nGameCount] = *(it->second);
				m_nGameCount++;
			}
		}
		m_iGamePlug.SetImageCount(m_nGameCount);
		m_lstGamePlug.SetItemCount(m_nGameCount);
		m_lstGamePlug.MoveWindow(10, 310, 494, 54);

		//�м�״̬
		rc = CRect(10, 374, 494+10, 26+374);	//������494.
		m_btnProgress.MoveWindow(&rc);
		m_btnProgress.SetProgres(0);
		m_btnProgress.SetImage(TEXT("Skin/Wnd/GongGao/����_������.png"), TEXT("Skin/Wnd/GongGao/����_������_1px.png"));

		rc.OffsetRect(0, 32); rc.bottom -= 2;
		rc.right = rc.left + 350;
		m_btnStatus.MoveWindow(&rc);
		m_btnStatus.SetImage(TEXT("Skin/Wnd/GongGao/bk.png"));
		m_btnStatus.SetTextStyle(DEFAULT_FONT_NAME, 12, RGB(255, 255, 255), RGB(255, 255, 255), 
			RGB(255, 255, 255), RGB(255, 255, 255), CButtonEx::BTEXT_LEFT);		

		rc.left = rc.right; rc.right = rcClient.right - 10;
		m_btnTime.MoveWindow(&rc);
		m_btnTime.SetImage(TEXT("Skin/Wnd/GongGao/bk.png"));
		m_btnTime.SetTextStyle(DEFAULT_FONT_NAME, 12, RGB(255, 255, 255), RGB(255, 255, 255), 
			RGB(255, 255, 255), RGB(255, 255, 255), CButtonEx::BTEXT_LEFT);

		//�²���ť
		rc = CRect(22, 445, 70+22, 60+445);
		m_btnRun.MoveWindow(&rc);
		m_btnRun.SetImage(TEXT("Skin/Wnd/GongGao/��ť_������Ϸ_Ĭ��״̬.png"), 
			TEXT("Skin/Wnd/GongGao/��ť_������Ϸ_��꾭��.png"), TEXT("Skin/Wnd/GongGao/��ť_������Ϸ_����.png"),
			NULL, TEXT("Skin/Wnd/GongGao/��ť_������Ϸ_�ڰ�״̬.png"));		

		rc.OffsetRect(rc.Width() + 10, 0);
		m_btnSearch.MoveWindow(&rc);
		m_btnSearch.SetImage(TEXT("Skin/Wnd/GongGao/��ť_�������_Ĭ��״̬.png"), 
			TEXT("Skin/Wnd/GongGao/��ť_�������_��꾭��.png"), TEXT("Skin/Wnd/GongGao/��ť_�������_����.png"));

		rc.OffsetRect(rc.Width() + 10, 0);
		m_btnBuyCard.MoveWindow(&rc);
		m_btnBuyCard.SetImage(TEXT("Skin/Wnd/GongGao/��ť_����㿨_Ĭ��״̬.png"), 
			TEXT("Skin/Wnd/GongGao/��ť_����㿨_��꾭��.png"), TEXT("Skin/Wnd/GongGao/��ť_����㿨_����.png"));

		rc.OffsetRect(rc.Width() + 10, 0);
		m_btnVidoSkill.MoveWindow(&rc);
		m_btnVidoSkill.SetImage(TEXT("Skin/Wnd/GongGao/��ť_��Ƶ����_Ĭ��״̬.png"), 
			TEXT("Skin/Wnd/GongGao/��ť_��Ƶ����_��꾭��.png"), TEXT("Skin/Wnd/GongGao/��ť_��Ƶ����_����.png"));

		rc.OffsetRect(rc.Width() + 10, 0);
		m_btnModify.MoveWindow(&rc);
		m_btnModify.SetImage(TEXT("Skin/Wnd/GongGao/��ť_�����޸�_Ĭ��״̬.png"), 
			TEXT("Skin/Wnd/GongGao/��ť_�����޸�_��꾭��.png"), TEXT("Skin/Wnd/GongGao/��ť_�����޸�_����.png"));		

		rc.OffsetRect(rc.Width() + 10, 0);
		m_btnFavorite.MoveWindow(&rc);
		m_btnFavorite.SetImage(TEXT("Skin/Wnd/GongGao/��ť_����ղ�_Ĭ��״̬.png"), 
			TEXT("Skin/Wnd/GongGao/��ť_����ղ�_��꾭��.png"), TEXT("Skin/Wnd/GongGao/��ť_����ղ�_����.png"));		

		//m_btnPlug.SetImage(TEXT("Skin/Wnd/GongGao/����_û���.png"));
		//m_btnPlug.MoveWindow(&CRect(7, 312, 500+7, 55+312));

		MoveWindow(&rcClient, FALSE);
		SetWindowRgn(rgn, TRUE);

		CenterWindow();
	}

	m_bAutoRun	= true;
	m_bIsUpdate	= false;
	m_bNeedWait = true;

	SetTimer(1, 1000, NULL);
	SetTimer(2, 7000, NULL);	//ͣ��N������������Ϸ�ļ�����
	m_btnTime.SetWindowText(TEXT(""));

	for (m_nCurrentUptIdx = 0; m_nCurrentUptIdx < m_nGameCount; m_nCurrentUptIdx++)
	{
		if (m_arGameInfo[m_nCurrentUptIdx].RunType == 1)
			break;
	}
	if (m_nCurrentUptIdx < m_nGameCount)
	{
		UpdateGame(&m_arGameInfo[m_nCurrentUptIdx]);
		m_btnRun.EnableWindow(FALSE);
	}
	else
	{
        m_btnStatus.SetWindowText(TEXT("����������Ϸ,����ֹͣ."));
	}

	return TRUE;
}

void CUptPrgDlg::OnDestroy()
{
	CWaitCursor wc;
	if (m_hUpdate != NULL)
	{
		FastCopy_End(m_hUpdate);
		m_hUpdate = NULL;
	}
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_pDlgUptPrg = NULL;
	CDialog::OnDestroy();
}

void CUptPrgDlg::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}

BOOL CUptPrgDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == m_btnStatus.m_hWnd ||
			pMsg->hwnd == m_btnProgress.m_hWnd ||
			pMsg->hwnd == m_btnTime.m_hWnd)
		{
			if (!m_bIsUpdate && m_bNeedWait && m_bAutoRun)
			{
				m_bAutoRun = false;
				m_btnStatus.SetWindowText(TEXT("����ͣ�����ֶ�������Ϸ."));
				m_btnRun.EnableWindow(TRUE);
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CUptPrgDlg::OnNcHitTest(CPoint point)
{
	UINT nHitTest = CDialog::OnNcHitTest(point);
	if (nHitTest == HTCLIENT)
		return HTCAPTION;
	return nHitTest;
}

void CUptPrgDlg::OnOK()
{
	OnBnClickedClose();
}

void CUptPrgDlg::OnCancel()
{
	OnBnClickedClose();
}

void CUptPrgDlg::OnBnClickedClose()
{
	CWaitCursor wc;
	if (m_hUpdate != NULL)
	{
		FastCopy_End(m_hUpdate);
		m_hUpdate = NULL;
	}
	DestroyWindow();
}

CString CUptPrgDlg::RunGame(tagGameInfo* pGame)
{
	CString szStatus;
	CWaitCursor wc;
	CString szWorkDir;
	if (pGame->RunType == 2)	//���������еģ���Ҫת��·��
	{
		szWorkDir = pGame->SvrPath;
		szWorkDir.Trim();
		tagVDiskInfo* pVDisk = AfxGetDbMgr()->FindVDiskInfo(pGame->VID);
		if (pVDisk == NULL)
		{
			AfxMessageBoxEx(TEXT("��������Ϣ��������������Ϸʧ�ܣ�"));
			return CString(TEXT(""));
		}
		if (szWorkDir.GetLength() > 3)
		{
			szWorkDir.SetAt(0, pVDisk->CliDrv);
		}
		if (pVDisk->LoadType == vdStartGame)
		{
			AfxGetDbMgr()->RefreshVDisk(pVDisk->CliDrv);
		}
	}
	else
	{
		szWorkDir = pGame->CliPath;
	}

	if (szWorkDir.GetLength() && szWorkDir.Right(1) != TEXT("\\"))
		szWorkDir += TEXT("\\");

	//������Ϸ
	if (PathFileExists(szWorkDir + pGame->Exe))
	{
		CString szParam = szWorkDir + TEXT("|") + pGame->Exe + TEXT("|") + pGame->Param;
		TCHAR szRunGame[MAX_PATH] = {0};
		GetModuleFileName(NULL, szRunGame, MAX_PATH);
		PathRemoveFileSpec(szRunGame);
		PathAddBackslash(szRunGame);
		lstrcat(szRunGame, TEXT("RunGame.exe"));
		int n = (int)ShellExecute(AfxGetMainWnd()->m_hWnd, TEXT("open"), szRunGame, szParam, TEXT(""), SW_SHOWNORMAL);
		if (n<=32)
		{
			szStatus.Format(TEXT("������Ϸʧ��:%d"), n);
		}		
	}
	else
	{
		szStatus = TEXT("�ļ�������:") + szWorkDir + pGame->Exe;
	}
	return szStatus;
}

void CUptPrgDlg::OnBnClickedRun()
{
	if (m_bIsUpdate )
		return ;

	m_bAutoRun = false;

	CString szStatus = RunGame(&m_arGameInfo[0]);
	if (!szStatus.IsEmpty())
	{
		m_btnStatus.SetWindowText(szStatus);
		m_btnRun.EnableWindow(TRUE);
	}
	else if (m_nGameCount > 1)
	{
		m_btnStatus.SetWindowText(TEXT("��Ϸ�����ɹ��������Ե����Ϸ�������"));
		m_btnProgress.SetProgres(0.0f);
		m_btnModify.EnableWindow(FALSE);
	}
	else
	{
		KillTimer(1);
		m_btnModify.EnableWindow(FALSE);
		if (m_nGameCount == 1)
		{	
			int nAct = AfxGetDbMgr()->GetIntOpt(OPT_M_MENUACT, 0L);
			CWnd* pWnd = AfxGetMainWnd();
			if (nAct != 0 && pWnd != NULL && pWnd->m_hWnd != NULL)
			{
				if (nAct == 1)
				{
					::PostMessage(pWnd->m_hWnd, WM_NAV_CLICK_MESSAGE, 6, 0);
				}
				else
				{
					::PostMessage(pWnd->m_hWnd, WM_CLOSE, 0, 0);
				}			
			}
			OnBnClickedClose();
		}
	}
}

void CUptPrgDlg::OnBnClickedSearch()
{
	CWaitCursor wc;
	CString str;
	str.Format(TEXT("http://www.baidu.com/s?wd=%s&tn=licenseonline_pg"), (LPCTSTR)m_arGameInfo[0].Name);
	ShellExecute(m_hWnd, TEXT("open"), str, TEXT(""), TEXT(""), SW_SHOWNORMAL);
}

void CUptPrgDlg::OnBnClickedBuycard()
{
	CWaitCursor wc;
	CString str;
	str.Format(TEXT("http://desk.i8.com.cn/CybercafeClient/Shop/ProductInfo.aspx?ProductID=%d"), m_arGameInfo[0].gid);
	ShellExecute(m_hWnd, TEXT("open"), str, TEXT(""), TEXT(""), SW_SHOWNORMAL);
}

void CUptPrgDlg::OnBnClickedVideoSkill()
{
	//��Ƶ���ԣ�������ַ
}

void CUptPrgDlg::OnBnClickedModify()
{
	if (m_arGameInfo[0].RunType != 1)
		return ;
	if (m_hUpdate != NULL)
	{
		CWaitCursor wc;
		FastCopy_End(m_hUpdate);
		m_hUpdate = NULL;
		m_btnStatus.SetWindowText(TEXT("������ͣ..."));
	}

	m_bAutoRun = false;
	m_btnTime.SetWindowText(TEXT("ʣ��ʱ��:"));
	try
	{
		CUptOptDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
            m_fcCopyMode = dlg.m_bIsQuick ? FC_COPY_QUICK : FC_COPY_FORE;
		}
		else
		{
			m_fcCopyMode = FC_COPY_VERSION;
		}

		for (m_nCurrentUptIdx = 0; m_nCurrentUptIdx < m_nGameCount; m_nCurrentUptIdx++)
		{
			if (m_arGameInfo[m_nCurrentUptIdx].RunType == 1)
				break;
		}
		if (m_nCurrentUptIdx < m_nGameCount)
		{
			UpdateGame(&m_arGameInfo[m_nCurrentUptIdx]);
			m_btnRun.EnableWindow(FALSE);
		}
		m_bAutoRun = true;
	}
	catch (...) {}
}

void CUptPrgDlg::OnBnClickedFavorite()
{
	return;
	CWaitCursor wc;
	CPersonMgr::RES_AddGame res = AfxGetPersonMgr()->AddGameToFavList(m_arGameInfo[0].gid);
	if (res == CPersonMgr::RES_AddGame_Failed)
	{
		CString strError = TEXT("�Բ����ղ���Ϸʧ�ܣ�");
		AfxMessageBoxEx(strError);
	}
	else if (res == CPersonMgr::RES_AddGame_NotLogin)
	{
		CString strError = TEXT("����û�е�½�����½�Ժ�ʹ����Ϸ�ղع��ܣ�");
		AfxMessageBoxEx(strError);
		CWnd* pParent = AfxGetMainWnd();
		if (pParent != NULL && pParent->m_hWnd != NULL)
		{
			pParent->SendMessage(WM_NAV_CLICK_MESSAGE, 9, 0);
		}
	}
	else
	{
		CString strError = TEXT("�ղ���Ϸ�ɹ���");
		AfxMessageBoxEx(strError);
	}
}

void CUptPrgDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	if (nIDEvent == 2)
	{
		m_bNeedWait = false;
		KillTimer(2);
		return ;
	}
	else if (nIDEvent == 1)
	{
		if (m_nCurrentUptIdx < m_nGameCount 
			&&m_arGameInfo[m_nCurrentUptIdx].RunType == 1) //���ظ��µ���Ϸ��ʾ����
		{
			if (m_hUpdate != NULL)
			{
				CString str;
				FastCopyStatus Status = {0};
				FastCopy_GetSpeedEx(m_hUpdate, &Status);

				if (FCS_FINISH == Status.Progress)
				{
					FastCopy_End(m_hUpdate);
					m_hUpdate = NULL;
					for (m_nCurrentUptIdx++; m_nCurrentUptIdx < m_nGameCount; m_nCurrentUptIdx++)
					{
						if (m_arGameInfo[m_nCurrentUptIdx].RunType == 1)
							break;
					}
					if (m_nCurrentUptIdx < m_nGameCount)
					{		
						UpdateGame(&m_arGameInfo[m_nCurrentUptIdx]);
					}
					else
					{
						m_btnProgress.SetProgres(100);
						m_btnStatus.SetWindowText(TEXT("����������Ϸ, ����ֹͣ..."));
						m_btnTime.SetWindowText(TEXT(""));
						m_hUpdate = NULL;
						m_bIsUpdate = false;
						m_btnRun.EnableWindow(TRUE);
					}
				}
				else if (FCS_ERROR == Status.Progress)
				{
					m_btnProgress.SetProgres(0);
					str.Format(TEXT("%s"), (LPCTSTR)_bstr_t(Status.szCurFile));
					m_btnStatus.SetWindowText(str);
					m_btnTime.SetWindowText(TEXT(""));
					FastCopy_End(m_hUpdate);
					m_hUpdate = NULL;
					m_bIsUpdate = false;
					m_bAutoRun = false;
					m_btnRun.EnableWindow(TRUE);
				}
				else if (FCS_NOROOM == Status.Progress)
				{
					m_btnProgress.SetProgres(0);
					m_btnStatus.SetWindowText(TEXT("�ռ䲻��!"));
					m_btnTime.SetWindowText(TEXT(""));
					FastCopy_End(m_hUpdate);
					m_hUpdate = NULL;
					m_bIsUpdate = false;
					m_bAutoRun = false;
					m_btnRun.EnableWindow(TRUE);
				}
				else if (FCS_PROGRESS_SCAN == Status.Progress)
				{
					m_btnProgress.SetProgres(0);
					m_btnStatus.SetWindowText(TEXT("���ڶԱ��ļ�..."));
					m_btnTime.SetWindowText(TEXT(""));
				}
				else if (FCS_PROGRESS_UPDATE == Status.Progress)
				{
					m_btnProgress.SetProgres(Status.TotalProgress * 1.0f / 10);

					str.Format(TEXT("���ڸ���:[%s][%dMB/%dMB, %dK/S]"), (LPCTSTR)m_arGameInfo[m_nCurrentUptIdx].Name, 
						(DWORD)((Status.TotalFileSize - Status.UpdateFizeSize)/1024/1024), 
						(DWORD)(Status.TotalFileSize/1024/1024),
						Status.AverageSpeed);
					m_btnStatus.SetWindowText(str);

					str.Format(TEXT("ʣ��ʱ��:%02d:%02d:%02d"), 
						Status.LeftSecond / 3600, 
						(Status.LeftSecond % 3600) / 60, 
						Status.LeftSecond % 60);
					m_btnTime.SetWindowText(str);
				}
				else if (FCS_PROGRESS_DELMOREFILE == Status.Progress)
				{
					m_btnProgress.SetProgres(0);
					m_btnStatus.SetWindowText(TEXT("ɾ�������ļ�..."));
					m_btnTime.SetWindowText(TEXT(""));
				}
				else if (FCS_DELGAME == Status.Progress)
				{
					m_btnProgress.SetProgres(0);
					str.Format(TEXT("%s"), (LPCTSTR)_bstr_t(Status.szCurFile));
					m_btnStatus.SetWindowText(str);
					m_btnTime.SetWindowText(TEXT(""));
				}

				CString szMsg;
				szMsg.Format(TEXT("status:0x%x, progress:%0.2f, file:%s\r\n"), 
					Status.Progress, 
					Status.TotalProgress * 1.0f / 10,
					(LPCTSTR)_bstr_t(Status.szCurFile));
				OutputDebugString(szMsg);
			}
		}
	}
	if (!m_bIsUpdate && !m_bNeedWait && m_bAutoRun)
	{
		OnBnClickedRun();
	}
}

BOOL CUptPrgDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rc;
	GetClientRect(&rc);
	AfxDrawImage(pDC, TEXT("Skin/Wnd/GongGao/����_����.png"), rc);
	return TRUE;
}

void CUptPrgDlg::OnGetdispinfoList( NMHDR* pNMHDR, LRESULT* pResult )
{
	LV_DISPINFO* pDispInfo = reinterpret_cast<LV_DISPINFO*>(pNMHDR);
	if (pDispInfo == NULL)
		return ;
	LV_ITEM* pItem= &(pDispInfo->item);
	size_t itemid = pItem->iItem;
	if ((int)itemid >= m_nGameCount - 1)
	{
		*pResult = 0;
		return ;
	}
	tagGameInfo* pGameInfo = &m_arGameInfo[(int)itemid + 1];
	if (pItem->mask & LVIF_TEXT)
	{
		//Which column?
		if (pItem->iSubItem == 0)
		{
			lstrcpyn(pItem->pszText, pGameInfo->Name, pItem->cchTextMax);
		}
	}

	if( pItem->mask & LVIF_IMAGE) 
	{
		HICON hIcon = AfxGetDbMgr()->FindIconOfGame(pGameInfo->gid);
		m_iGamePlug.Replace(itemid, hIcon);
		pItem->iImage = itemid;
	}
	*pResult = 0;
}

BOOL CUptPrgDlg::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message )
{
	if (m_lstGamePlug.m_hWnd && pWnd->m_hWnd == m_lstGamePlug.m_hWnd)
	{
		SetCursor(m_hPlugCursor);
		return TRUE;
	}    
	return FALSE;
}

void CUptPrgDlg::OnNMClickListGame(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	if (m_bIsUpdate)
	{
		AfxMessageBoxEx(TEXT("���ڸ�����ɺ������ò����"));
		return;
	}

	size_t nSel = m_lstGamePlug.GetNextItem(-1, LVIS_SELECTED);
	if ((int)nSel == -1 || (int)nSel >= m_nGameCount - 1)
		return ;

	RunGame(&m_arGameInfo[(int)nSel + 1]);
}

void CUptPrgDlg::SetStartGame( tagGameInfo* pGame )
{
	if (pGame) m_arGameInfo[0] = *pGame;
	m_fcCopyMode = FC_COPY_VERSION;
}

BOOL CUptPrgDlg::UpdateGame( tagGameInfo* pGameInfo)
{
	m_bIsUpdate = TRUE;
	_bstr_t ip1 = AfxGetDbMgr()->LoadIpAddr();
	_bstr_t ip2 = AfxGetDbMgr()->GetUptSvrList();
	m_hUpdate = FastCopy_Start(
		_bstr_t(pGameInfo->SvrPath), 
		_bstr_t(pGameInfo->CliPath), 
		ip1, ip2, pGameInfo->gid, 
		m_fcCopyMode, 
		AfxGetDbMgr()->GetBoolOpt(OPT_M_P2P), 
		0);
	CString str;
	str.Format(TEXT("���ڸ���[%s]"), (LPCTSTR)pGameInfo->Name);
	m_btnStatus.SetWindowText(str);

	return TRUE;
}