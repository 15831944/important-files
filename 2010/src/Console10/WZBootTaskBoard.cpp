// WZBootTaskBoard.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WZBootTaskBoard.h"

static int g_nLastSelItem = 0;
static int g_nLastCol = 0;
static std::vector<std::string> m_lstExecFile;

// CWZBootTaskBoard �Ի���

IMPLEMENT_DYNAMIC(CWZBootTaskBoard, CDialog)

CWZBootTaskBoard::CWZBootTaskBoard(CWnd* pParent /*=NULL*/)
	: CDialog(CWZBootTaskBoard::IDD, pParent)
	, m_bModify(FALSE)
	, m_bModify2(FALSE)
{

}

CWZBootTaskBoard::~CWZBootTaskBoard()
{
}

void CWZBootTaskBoard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EXEC, m_lstFile);
	DDX_Control(pDX, IDC_COMBO1, m_cboCell);
}


BOOL CWZBootTaskBoard::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lstFile.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_lstFile.InsertColumn(0, "����",		LVCFMT_LEFT, 90);
	m_lstFile.InsertColumn(1, "ִ���ļ�",	LVCFMT_LEFT, 220);

	i8desk::CDbMgr* pDbMgr = GetDbMgr();
	i8desk::AreaInfoMap AreaInfos;
	std::map<std::string, i8desk::tagBootTask*> BootTasks;
	std::string ErrInfo;
	m_lstFile.InsertItem(0, DEFAULT_AREA_NAME);
	char* pGuid = new char[lstrlen(DEFAULT_AREA_GUID) +1];
	lstrcpy(pGuid, DEFAULT_AREA_GUID);
	m_lstFile.SetItemData(0, reinterpret_cast<DWORD>(pGuid));

	if (!pDbMgr->GetAllArea(AreaInfos, ErrInfo) || 
		!pDbMgr->GetBootTask(brSvrFile, BootTasks, ErrInfo))
	{
		CString str;
		str.Format(_T("��ʼ���������񴰿�����ʱ:%s"), ErrInfo.c_str());
		AfxMessageBox(str);
	}
	
	for (i8desk::AreaInfoMapItr it = AreaInfos.begin();
		it != AreaInfos.end(); it++)
	{
		if (it->first != DEFAULT_AREA_GUID)
		{
			int nItem = m_lstFile.InsertItem(m_lstFile.GetItemCount(), it->second->Name);
			pGuid = new char[it->first.size() + 1];
			lstrcpy(pGuid, it->first.c_str());
			m_lstFile.SetItemData(nItem, reinterpret_cast<DWORD>(pGuid));
		}
	}
	AreaInfos.clear();

	for (int idx=0; idx<m_lstFile.GetItemCount(); idx++)
	{
		pGuid = reinterpret_cast<char*>(m_lstFile.GetItemData(idx));
		std::map<std::string, i8desk::tagBootTask*>::iterator Iter = BootTasks.begin();
		for (; Iter != BootTasks.end(); Iter++)
		{
			if (Iter->second->AreaType == i8desk::TASK_AREA_AREA 
				&& strcmp(pGuid, Iter->second->AreaParam) == 0)
			{
				CString szFile, szWallType;
				AfxExtractSubString(szFile,		Iter->second->Content, 0, '|');
				AfxExtractSubString(szWallType, Iter->second->Content, 1, '|');
				szFile.Delete(0, lstrlen(EXEC_DIR)+1);
				m_lstFile.SetItemText(idx, 1, szFile);
				break;
			}
		}
	}

	for (std::map<std::string, i8desk::tagBootTask*>::iterator Iter = BootTasks.begin();
		Iter != BootTasks.end(); Iter++)
	{
		delete Iter->second;
	}
	BootTasks.clear();

	if (!pDbMgr->GetBootTask(brCltFile, BootTasks, ErrInfo))
	{
		CString str;
		str.Format(_T("��ʼ�������������ô�������ʱ:%s"), ErrInfo.c_str());
		AfxMessageBox(ErrInfo.c_str());
	}

	if (BootTasks.size() == 1)
	{
		CString szFile, szParam;
		std::map<std::string, i8desk::tagBootTask*>::iterator it = BootTasks.begin();
		AfxExtractSubString(szFile, it->second->Content, 0, '|');
		AfxExtractSubString(szParam, it->second->Content, 1, '|');
		SetDlgItemText(IDC_CLI_FILE, szFile);
		SetDlgItemText(IDC_RUN_PARAM, szParam);
	}

	for (std::map<std::string, i8desk::tagBootTask*>::iterator Iter = BootTasks.begin();
		Iter != BootTasks.end(); Iter++)
	{
		delete Iter->second;
	}
	BootTasks.clear();

	((CButton*)GetDlgItem(IDC_CHECK_TIMEUPT))->SetCheck(pDbMgr->GetOptInt(OPT_M_SYNTIME));

	return TRUE;
}

BEGIN_MESSAGE_MAP(CWZBootTaskBoard, CDialog)
	ON_REGISTERED_MESSAGE(i8desk::g_nOptApplyMsg, &CWZBootTaskBoard::OnApplyMessage)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_LIST_EXEC, &CWZBootTaskBoard::OnNMClickListExec)
	ON_CBN_KILLFOCUS(IDC_COMBO1, &CWZBootTaskBoard::OnCbnKillfocusCombo1)
	ON_EN_CHANGE(IDC_CLI_FILE, &CWZBootTaskBoard::OnEnChangeCliFile)
	ON_EN_CHANGE(IDC_RUN_PARAM, &CWZBootTaskBoard::OnEnChangeRunParam)
	ON_BN_CLICKED(IDC_CHECK_TIMEUPT, &CWZBootTaskBoard::OnBnClickedCheckTimeupt)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_OPEN_DIR, &CWZBootTaskBoard::OnBnClickedOpenDir)
END_MESSAGE_MAP()


// CWZBootTaskBoard ��Ϣ�������
LRESULT CWZBootTaskBoard::OnApplyMessage(WPARAM wParam, LPARAM lParam)
{
	std::string ErrInfo;
	i8desk::CDbMgr* pDbMgr = GetDbMgr();

	if (m_bModify)
	{
		if (!pDbMgr->DelBootTask(brSvrFile, ErrInfo))
		{
			AfxMessageBox(ErrInfo.c_str());
			return FALSE;
		}
		for (int idx=0;idx<m_lstFile.GetItemCount();idx++)
		{
			CString szFile = m_lstFile.GetItemText(idx, 1);
			if (!szFile.IsEmpty())
			{
				szFile = CString(EXEC_DIR) + "\\" + szFile;
				i8desk::tagBootTask Task;
				i8desk::SAFE_STRCPY(Task.UID, i8desk::CreateGUIDString().c_str());
				Task.AreaType = i8desk::TASK_AREA_AREA;
				i8desk::SAFE_STRCPY(Task.AreaParam, reinterpret_cast<const char*>(m_lstFile.GetItemData(idx)));
				Task.Type = brSvrFile;
				Task.Flag = 2;
				i8desk::SAFE_STRCPY(Task.Content, szFile);
				if (!pDbMgr->AddBootTask(&Task, ErrInfo))
				{
					AfxMessageBox(ErrInfo.c_str());
					return FALSE;
				}				
			}
		}
		m_bModify = FALSE;
	}

	if (m_bModify2)
	{
		if (!pDbMgr->DelBootTask(brCltFile, ErrInfo))
		{
			AfxMessageBox(ErrInfo.c_str());
			return FALSE;
		}
		CString szFile, szParam;
		GetDlgItemText(IDC_CLI_FILE, szFile);
		GetDlgItemText(IDC_RUN_PARAM, szParam);
		if (!szFile.IsEmpty())
		{
			szFile += "|" + szParam;
			i8desk::tagBootTask Task;
			i8desk::SAFE_STRCPY(Task.UID, i8desk::CreateGUIDString().c_str());
			Task.AreaType = i8desk::TASK_AREA_ALL;
			CLEAR_STRING(Task.AreaParam);
			Task.Type = brCltFile;
			Task.Flag = 2;
			i8desk::SAFE_STRCPY(Task.Content, szFile);
			if (!pDbMgr->AddBootTask(&Task, ErrInfo))
			{
				AfxMessageBox(ErrInfo.c_str());
				return FALSE;				
			}
		}
		pDbMgr->SetOption(OPT_M_SYNTIME, ((CButton*)GetDlgItem(IDC_CHECK_TIMEUPT))->GetCheck() == BST_CHECKED ? 1 : 0);
		m_bModify2 = FALSE;
	}
	
	return TRUE;
}

BOOL CWZBootTaskBoard::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->hwnd == m_cboCell.m_hWnd && pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		m_lstFile.SetFocus();
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CWZBootTaskBoard::OnDestroy()
{
	for (int idx=0; idx<m_lstFile.GetItemCount(); idx++)
	{
		char *pGuid = reinterpret_cast<char*>(m_lstFile.GetItemData(idx));
		delete []pGuid;
	}
	CDialog::OnDestroy();
}

void CWZBootTaskBoard::OnNMClickListExec(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	int nSelItem = m_lstFile.GetNextItem(-1, LVIS_SELECTED);
	if (nSelItem == -1) return ;

	CPoint pt( ::GetMessagePos() ); 
	ScreenToClient(&pt);

	CRect rc;
	m_lstFile.GetSubItemRect(nSelItem, 1, LVIR_BOUNDS, rc);
	m_lstFile.ClientToScreen(&rc);
	ScreenToClient(&rc);
	if (rc.PtInRect(pt))
	{
		g_nLastSelItem = nSelItem;
		g_nLastCol     = 1;
		CString szText = m_lstFile.GetItemText(nSelItem, 1);

		rc.DeflateRect(0, 0, 1, 1);
		m_cboCell.ResetContent();
		m_cboCell.AddString("������");

		std::string ErrInfo;
		m_lstExecFile.clear();
		i8desk::CDbMgr* pDbMgr = reinterpret_cast<CConsoleDlg*>(AfxGetMainWnd())->m_pDbMgr;
		if (!pDbMgr->GetFileOrDir(EXEC_DIR, GET_FILELIST, false, m_lstExecFile, ErrInfo))
		{
			AfxMessageBox(ErrInfo.c_str());
		}
		for (size_t idx=0; idx<m_lstExecFile.size(); idx++)
		{
			m_cboCell.AddString(m_lstExecFile[idx].c_str());
		}

		m_cboCell.MoveWindow(&rc);
		m_cboCell.BringWindowToTop();
		m_cboCell.ShowWindow(TRUE);
		if (-1 == m_cboCell.SelectString(-1, szText))
			m_cboCell.SetCurSel(0);
		m_cboCell.SetFocus();
	}
}

void CWZBootTaskBoard::OnCbnKillfocusCombo1()
{
	CString szText;
	m_cboCell.GetWindowText(szText);
	
	if (szText == "������")
		szText = "";

	if (m_lstFile.GetItemText(g_nLastSelItem, 1) != szText)
	{
		m_lstFile.SetItemText(g_nLastSelItem, 1, szText);
		if (m_lstFile.GetItemText(g_nLastSelItem, 2).IsEmpty())
			m_lstFile.SetItemText(g_nLastSelItem, 2, "����");
		m_bModify = TRUE;
	}
	m_cboCell.ShowWindow(FALSE);
}

void CWZBootTaskBoard::OnEnChangeCliFile()
{
	m_bModify2 = TRUE;
}

void CWZBootTaskBoard::OnEnChangeRunParam()
{
	m_bModify2 = TRUE;
}

void CWZBootTaskBoard::OnBnClickedCheckTimeupt()
{
	m_bModify2 = TRUE;
}

void CWZBootTaskBoard::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	i8desk::CDbMgr* pDbMgr = GetDbMgr();
	i8desk::AreaInfoMap AreaInfos;
	std::map<std::string, i8desk::tagBootTask*> BootTasks;
	std::string ErrInfo;

	if (!pDbMgr->GetAllArea(AreaInfos, ErrInfo) || 
		!pDbMgr->GetBootTask(brSvrFile, BootTasks, ErrInfo))
	{
		CString str;
		str.Format(_T("��ʼ���������񴰿�����ʱ:%s"), ErrInfo.c_str());
		AfxMessageBox(str);
	}

	//ɾ���������Ŀ
	for (int nItem = m_lstFile.GetItemCount() - 1; nItem >= 0; nItem--)
	{
		const char *pGuid = reinterpret_cast<const char *>(m_lstFile.GetItemData(nItem));
		ASSERT(pGuid);
		if (AreaInfos.find(pGuid) == AreaInfos.end() 
			&& strcmp(pGuid, DEFAULT_AREA_GUID) != 0)
		{
			delete[] pGuid;
			m_lstFile.DeleteItem(nItem);
		}
	}

	//���벻���ڵ���Ŀ
	for (i8desk::AreaInfoMapItr it = AreaInfos.begin(); it != AreaInfos.end(); it++)
	{
		BOOL bExists = FALSE;
		for (int nItem = 0; nItem < m_lstFile.GetItemCount(); nItem++)
		{
			const char *pGuid = reinterpret_cast<const char *>(m_lstFile.GetItemData(nItem));
			if (it->first == pGuid)
			{
				bExists = TRUE;
				m_lstFile.SetItemText(nItem, 0, it->second->Name);
				break;
			}
		}

		if (!bExists)
		{
			int nItem = m_lstFile.InsertItem(m_lstFile.GetItemCount(), it->second->Name);
			char *pGuid = new char[it->first.size() + 1];
			lstrcpy(pGuid, it->first.c_str());
			m_lstFile.SetItemData(nItem, reinterpret_cast<DWORD>(pGuid));
		}
	}

	AreaInfos.clear();

	for (int idx=0; idx<m_lstFile.GetItemCount(); idx++)
	{
		const char *pGuid = reinterpret_cast<char*>(m_lstFile.GetItemData(idx));
		std::map<std::string, i8desk::tagBootTask*>::iterator Iter = BootTasks.begin();
		for (; Iter != BootTasks.end(); Iter++)
		{
			if (Iter->second->AreaType == i8desk::TASK_AREA_AREA 
				&& strcmp(pGuid, Iter->second->AreaParam) == 0)
			{
				CString szFile, szWallType;
				AfxExtractSubString(szFile,		Iter->second->Content, 0, '|');
				AfxExtractSubString(szWallType, Iter->second->Content, 1, '|');
				szFile.Delete(0, lstrlen(EXEC_DIR)+1);
				m_lstFile.SetItemText(idx, 1, szFile);
				break;
			}
		}
	}

	for (std::map<std::string, i8desk::tagBootTask*>::iterator Iter = BootTasks.begin();
		Iter != BootTasks.end(); Iter++)
	{
		delete Iter->second;
	}
}

void CWZBootTaskBoard::OnBnClickedOpenDir()
{
	CString szSvrPath = reinterpret_cast<CConsoleDlg*>(AfxGetMainWnd())->GetI8DeskSvrPath();
	if (szSvrPath.IsEmpty())
		return ;

	szSvrPath += EXEC_DIR;
	CreateDirectory(szSvrPath, NULL);
	ShellExecute(m_hWnd, "open", szSvrPath, "", NULL, SW_SHOWNORMAL);
}
