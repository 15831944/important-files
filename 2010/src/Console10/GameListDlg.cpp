// GameListDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameListDlg.h"
#include "ConsoleDlg.h"

// CGameListDlg �Ի���

IMPLEMENT_DYNAMIC(CGameListDlg, CDialog)

CGameListDlg::CGameListDlg(
		i8desk::DefClassMap& DefClasses,
		i8desk::GameInfoMap& Games,
		int selector, 			
		int partition,
	   CWnd* pParent /*=NULL*/)
	: CDialog(CGameListDlg::IDD, pParent)
	, m_selector(selector)
	, m_partition(partition)
	, m_DefClasses(DefClasses)
{
	if (m_selector == MATCH) 
	{
		i8desk::GameInfoMapItr it = Games.begin();
		for (; it != Games.end(); ++it)
		{
			if (it->second->GID >= MIN_IDC_GID 
				&& it->second->Status == 1)
			{
				it->second->selected = 1;
				m_Games.push_back(it->second);
			}
		}
	}
	else if (m_selector == TODAYUPDATE) 
	{
		CTime now = CTime::GetCurrentTime();
		int nowYear = now.GetYear();
		int nowMonth = now.GetMonth();
		int nowDay = now.GetDay();

		//�õ����ܿ�ʼ��ʱ�̣����ڼ��㱾�����ĸ��µ���Ϸ��
		int nowDayOfWeek = now.GetDayOfWeek();
		CTime ThisWeekStart = now - CTimeSpan(nowDayOfWeek);

		CTime ThisWeekStartDay(ThisWeekStart.GetYear(), 
			ThisWeekStart.GetMonth(), ThisWeekStart.GetDay(), 0, 0, 0);
		DWORD ThisWeekStartTime = (DWORD)ThisWeekStartDay.GetTime();

		i8desk::GameInfoMapItr it = Games.begin();
		for (; it != Games.end(); ++it)
		{
			if (it->second->GID >= MIN_IDC_GID) 
			{
				if (it->second->IdcVer > ThisWeekStartTime)
				{
					CTime IdcUpdateTime = it->second->IdcVer;
					if (IdcUpdateTime.GetDay() == nowDay
						&& IdcUpdateTime.GetMonth() == nowMonth
						&& IdcUpdateTime.GetYear() == nowYear)
					{
						it->second->selected = 1;
						m_Games.push_back(it->second);
					}
				}
			}
		}
	}
	else if (m_selector == VALUENODOWN) 
	{
		i8desk::GameInfoMapItr it = Games.begin();
		for (; it != Games.end(); ++it)
		{
			if (it->second->I8Play == 1 && it->second->Status == 0)
			{
				it->second->selected = 1;
				m_Games.push_back(it->second);
			}
		}
	}
	else if (m_selector == AUTOUPDATE) 
	{
		i8desk::GameInfoMapItr it = Games.begin();
		for (; it != Games.end(); ++it)
		{
			if (it->second->Status == 1 && it->second->AutoUpt == 1)
			{
				it->second->selected = 1;
				m_Games.push_back(it->second);
			}
		}
	}
	else if (m_selector == MAYDELETE) 
	{
		i8desk::GameInfoMapItr it = Games.begin();
		for (; it != Games.end(); ++it)
		{
			if (it->second->Priority < 3 
				&& ::toupper(it->second->SvrPath[0]) == ::toupper(m_partition))
			{
				it->second->selected = 1;
				m_Games.push_back(it->second);
			}
		}
	}
	else if (m_selector == IDCADDNODOWN) 
	{
		CTime now = CTime::GetCurrentTime();
		CTime start(now.GetYear(), now.GetMonth(), now.GetDay(), 0, 0, 0);
		start -= CTimeSpan(30,0,0,0); //30�������
		DWORD StartTime = (DWORD)start.GetTime();

		i8desk::GameInfoMapItr it = Games.begin();
		for (; it != Games.end(); ++it)
		{
			if (it->second->GID >= MIN_IDC_GID 
				&& it->second->Status == 0 
				&& it->second->AddDate > StartTime)
			{
				it->second->selected = 1;
				m_Games.push_back(it->second);
			}
		}
	}
	else if (m_selector == RTLOCALUPDATE) 
	{
		i8desk::GameInfoMapItr it = Games.begin();
		for (; it != Games.end(); ++it)
		{
			if (it->second->Status == 0)
				continue;

			for (size_t i = 0; i < it->second->RunTypes.size(); i++)
			{
				if (it->second->RunTypes[i].RunType == ERT_LOCAL)
				{
					it->second->selected = 1;
					m_Games.push_back(it->second);
					break;
				}
			}

		}
	}
	else if (m_selector == RTVDISK) 
	{
		i8desk::GameInfoMapItr it = Games.begin();
		for (; it != Games.end(); ++it)
		{
			if (it->second->Status == 0)
				continue;

			for (size_t i = 0; i < it->second->RunTypes.size(); i++)
			{
				if (it->second->RunTypes[i].RunType == ERT_VDISK)
				{
					it->second->selected = 1;
					m_Games.push_back(it->second);
					break;
				}
			}

		}
	}
	else if (m_selector == RTDIRECTRUN) 
	{
		i8desk::GameInfoMapItr it = Games.begin();
		for (; it != Games.end(); ++it)
		{
			if (it->second->Status == 0)
				continue;

			for (size_t i = 0; i < it->second->RunTypes.size(); i++)
			{
				if (it->second->RunTypes[i].RunType == ERT_DIRECT)
				{
					it->second->selected = 1;
					m_Games.push_back(it->second);
					break;
				}
			}
		}
	}
}

CGameListDlg::~CGameListDlg()
{
}

void CGameListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}


BEGIN_MESSAGE_MAP(CGameListDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CGameListDlg::OnBnClickedOk)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST, &CGameListDlg::OnLvnGetdispinfoList)
	ON_NOTIFY(NM_CLICK, IDC_LIST, &CGameListDlg::OnNMClickList)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST, &CGameListDlg::OnLvnKeydownList)
	ON_BN_CLICKED(IDC_ALL, &CGameListDlg::OnBnClickedAll)
	ON_BN_CLICKED(IDC_CLEAR, &CGameListDlg::OnBnClickedClear)
END_MESSAGE_MAP()



BOOL CGameListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	switch (m_selector)
	{
	case MATCH:
		SetWindowText(_T("������ƥ�䵽������Դ����Ϸ"));
		GetDlgItem(IDOK)->SetWindowText(_T("ȷ��"));
		GetDlgItem(IDC_ALL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CLEAR)->ShowWindow(SW_HIDE);
		break;
	case RTLOCALUPDATE:
		SetWindowText(_T("���ظ�����Դ"));
		GetDlgItem(IDOK)->SetWindowText(_T("ȷ��"));
		GetDlgItem(IDC_ALL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CLEAR)->ShowWindow(SW_HIDE);
		break;
	case RTVDISK:
		SetWindowText(_T("��������Դ"));
		GetDlgItem(IDOK)->SetWindowText(_T("ȷ��"));
		GetDlgItem(IDC_ALL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CLEAR)->ShowWindow(SW_HIDE);
		break;
	case RTDIRECTRUN:
		SetWindowText(_T("������ֱ��������Դ"));
		GetDlgItem(IDOK)->SetWindowText(_T("ȷ��"));
		GetDlgItem(IDC_ALL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CLEAR)->ShowWindow(SW_HIDE);
		break;
	case TODAYUPDATE:
		SetWindowText(_T("���Ľ��ո�����Ϸ"));
		GetDlgItem(IDOK)->SetWindowText(_T("����"));
		break;
	case VALUENODOWN:
		SetWindowText(_T("����δ������ֵ��Ϸ"));
		GetDlgItem(IDOK)->SetWindowText(_T("����"));
		break;
	case AUTOUPDATE:
		SetWindowText(_T("�����Զ����µ���Ϸ"));
		GetDlgItem(IDOK)->SetWindowText(_T("����"));
		break;
	case MAYDELETE: {
		CString strCaption;
		strCaption.Format(_T("�������[%C:]�Ͽ�ɾ������Ϸ"), m_partition);
		SetWindowText(strCaption);
		GetDlgItem(IDOK)->SetWindowText(_T("ɾ��"));	 
		break; }
	case IDCADDNODOWN: 
		SetWindowText(_T("��������������Դ(δ����)"));
		GetDlgItem(IDOK)->SetWindowText(_T("����"));
		break;
	default:
		ASSERT(0);
		break;
	}

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);

	m_list.InsertColumn(NETBAR_COL_NAME,			TEXT("����"),			LVCFMT_LEFT, 120);
	m_list.InsertColumn(NETBAR_COL_GID,			TEXT("GID"),			LVCFMT_LEFT, 60);
	m_list.InsertColumn(NETBAR_COL_STATUS,		TEXT("��ǰ״̬"),		LVCFMT_LEFT, 70);
	m_list.InsertColumn(NETBAR_COL_AUTOUPT,		TEXT("���·�ʽ"),		LVCFMT_LEFT, 60);
	m_list.InsertColumn(NETBAR_COL_PRIORITY,		TEXT("�ȼ�"),			LVCFMT_LEFT, 80);
	m_list.InsertColumn(NETBAR_COL_RUNTYPE,		TEXT("���з�ʽ"),		LVCFMT_LEFT, 0);
	m_list.InsertColumn(NETBAR_COL_UPDATETIME,	TEXT("���ظ���ʱ��"),	LVCFMT_LEFT, 135);
	m_list.InsertColumn(NETBAR_COL_SVRCLICK,		TEXT("�����"),			LVCFMT_RIGHT,50);
	m_list.InsertColumn(NETBAR_COL_GAMECLASS,	TEXT("���"),			LVCFMT_LEFT, 70);
	m_list.InsertColumn(NETBAR_COL_SIZE,			TEXT("��С(M)"),		LVCFMT_RIGHT,70);
	m_list.InsertColumn(NETBAR_COL_GAMEEXE,		TEXT("ִ�г���"),		LVCFMT_LEFT, 120);
	m_list.InsertColumn(NETBAR_COL_SVRPATH,		TEXT("�����·��"),		LVCFMT_LEFT, 100);
	m_list.InsertColumn(NETBAR_COL_DOWNPRIORITY,	TEXT("���ȼ���"),		LVCFMT_LEFT, 0);
	m_list.InsertColumn(NETBAR_COL_GAMESOURCE,	TEXT("��Ϸ��Դ"),		LVCFMT_LEFT, 100);

	m_list.SetItemCount(m_Games.size());

	GetDlgItem(IDOK)->EnableWindow(m_Games.size() != 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

// CGameListDlg ��Ϣ�������

size_t CGameListDlg::GetSelectedGames(std::vector<DWORD>& games)
{
	for (size_t i = 0; i < m_Games.size(); i++)
	{
		i8desk::GameInfo_Ptr pGameInfo = m_Games[i];
		if (pGameInfo->selected) 
		{
			games.push_back(pGameInfo->GID);
		}
	}

	return games.size();
}

void CGameListDlg::OnBnClickedOk()
{
	i8desk::GameInfoVector GameInfos;
	for (size_t i = 0; i < m_Games.size(); i++)
	{
		i8desk::GameInfo_Ptr pGameInfo = m_Games[i];
		if (pGameInfo->selected) 
		{
			GameInfos.push_back(pGameInfo);
		}
	}

	CConsoleDlg *pMainWnd = static_cast<CConsoleDlg *>(AfxGetMainWnd());
	
	switch (m_selector)
	{
	case MAYDELETE:
		if (!pMainWnd->DelGames(GameInfos))
			return;
		break;
	case MATCH:
		break;
	case RTLOCALUPDATE:
		break;
	case RTVDISK:
		break;
	case RTDIRECTRUN:
		break;
	default:
		pMainWnd->DownGames(GameInfos);
		break;
	}

	OnOK();
}

CString CGameListDlg::GetGameClass(const i8desk::GameInfo& GameInfo)
{
	i8desk::DefClassMapItr it = m_DefClasses.find(GameInfo.DefClass);
	if (it != m_DefClasses.end())
		return CString(it->second->Name);
	return CString("");
}

void CGameListDlg::OnLvnGetdispinfoList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	LV_ITEM* pItem= &(pDispInfo)->item;
	int itemid = pItem->iItem;

	if (itemid >= (int)m_Games.size())
		return ;

	i8desk::GameInfo_Ptr pGameInfo = m_Games[itemid];
	ASSERT(pGameInfo);

	if (pItem->mask & LVIF_TEXT)
	{
		CString szText;
		switch(pItem->iSubItem)
		{			
		case NETBAR_COL_NAME:		szText = pGameInfo->Name;					break;
		case NETBAR_COL_GID:		szText.Format("%05d", pGameInfo->GID);				break;
		case NETBAR_COL_STATUS:		szText = pGameInfo->GetStatusText().c_str();		break;
		case NETBAR_COL_AUTOUPT:	szText = pGameInfo->AutoUpt ? "�Զ�" : "�ֶ�";		break;
		case NETBAR_COL_PRIORITY:	szText = pGameInfo->GetPriority().c_str();			break;
		case NETBAR_COL_UPDATETIME: 
			szText = i8desk::MakeTimeString(pGameInfo->SvrVer).c_str();	
			break;
		case NETBAR_COL_SVRCLICK:	szText.Format("%d", pGameInfo->SvrClick);			break;				
		case NETBAR_COL_GAMECLASS:	szText = GetGameClass(*pGameInfo);					break;
		case NETBAR_COL_SIZE:		szText.Format("%0.2f", pGameInfo->Size*1.0/1024);	break;
		case NETBAR_COL_GAMEEXE:	szText = pGameInfo->GameExe;				break;
		case NETBAR_COL_SVRPATH:		szText = pGameInfo->SvrPath;				break;
		}
		lstrcpyn(pItem->pszText, szText, pItem->cchTextMax);
	}

	pItem->mask |= LVIF_STATE;
	pItem->stateMask = LVIS_STATEIMAGEMASK;

	pItem->state = INDEXTOSTATEIMAGEMASK(pGameInfo->selected ? 2 : 1);
}

void CGameListDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

    LVHITTESTINFO hitinfo;
    hitinfo.pt = pNMItemActivate->ptAction;

    m_list.SubItemHitTest(&hitinfo);
	if(hitinfo.iItem != -1 && hitinfo.iSubItem == 0)
    {
        //��������Ƿ񵥻��� check box������?
        if(hitinfo.flags == LVHT_ONITEMSTATEICON)
        {
			i8desk::GameInfo_Ptr pGameInfo = m_Games[hitinfo.iItem];
			pGameInfo->selected = !pGameInfo->selected;
			m_list.RedrawItems(hitinfo.iItem, hitinfo.iItem);
        }
    }
    
	std::vector<DWORD> clients;
	GetDlgItem(IDOK)->EnableWindow(GetSelectedGames(clients));

	*pResult = 0;
}

void CGameListDlg::OnLvnKeydownList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDown = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);

    if( pLVKeyDown->wVKey == VK_SPACE )
    {
	    int item = m_list.GetSelectionMark();
        if(item != -1)
		{
			i8desk::GameInfo_Ptr pGameInfo = m_Games[item];
			pGameInfo->selected = !pGameInfo->selected;
			m_list.RedrawItems(item, item);
		}
    }

	std::vector<DWORD> games;
	GetDlgItem(IDOK)->EnableWindow(GetSelectedGames(games));

    *pResult = 0;
}

void CGameListDlg::OnBnClickedAll()
{
	for (size_t i = 0; i < m_Games.size(); i++)
	{
		i8desk::GameInfo_Ptr pGameInfo = m_Games[i];
		pGameInfo->selected = true;
	}
	m_list.RedrawWindow();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}

void CGameListDlg::OnBnClickedClear()
{
	for (size_t i = 0; i < m_Games.size(); i++)
	{
		i8desk::GameInfo_Ptr pGameInfo = m_Games[i];
		pGameInfo->selected = false;
	}
	m_list.RedrawWindow();
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}
