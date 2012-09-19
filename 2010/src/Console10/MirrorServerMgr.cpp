// MirrorServerMgr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MirrorServerMgr.h"
#include "MirrorServerInfo.h"
#include "ConsoleDlg.h"

// CMirrorServerMgr �Ի���

IMPLEMENT_DYNAMIC(CMirrorServerMgr, CDialog)

CMirrorServerMgr::CMirrorServerMgr(CWnd* pParent /*=NULL*/)
	: CDialog(CMirrorServerMgr::IDD, pParent)
	, m_bMainServerExists(false)
{

}

CMirrorServerMgr::~CMirrorServerMgr()
{
}

void CMirrorServerMgr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MIRROR_SVR, m_lcMirrorServer);
}


BEGIN_MESSAGE_MAP(CMirrorServerMgr, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_MIRROR_SVR, &CMirrorServerMgr::OnBnClickedButtonAddMirrorSvr)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_MIRROR_SVR, &CMirrorServerMgr::OnBnClickedButtonModifyMirrorSvr)
	ON_BN_CLICKED(IDC_BUTTON_DEL_MIRROR_SVR, &CMirrorServerMgr::OnBnClickedButtonDelMirrorSvr)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MIRROR_SVR, &CMirrorServerMgr::OnNMClickListMirrorSvr)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MIRROR_SVR, &CMirrorServerMgr::OnNMDblclkListMirrorSvr)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST_MIRROR_SVR, &CMirrorServerMgr::OnLvnDeleteitemListMirrorSvr)
END_MESSAGE_MAP()


void CMirrorServerMgr::InsertMirrorServerToList(const i8desk::SyncTask *SyncTask, bool bMainServer/* = false*/)
{
	int nItem = m_lcMirrorServer.GetItemCount();

	m_lcMirrorServer.InsertItem(nItem, SyncTask->SID);
	m_lcMirrorServer.SetItemData(nItem, (DWORD_PTR)SyncTask);

	UpdateMirrorServerListItem(nItem, SyncTask, bMainServer);
}


void CMirrorServerMgr::UpdateMirrorServerListItem(int nItem, const i8desk::SyncTask* SyncTask, bool bMainServer/* = false*/)
{
	CString strMirrorServerName;
	if( bMainServer == false )
		strMirrorServerName.Format(_T("���������[%s]"), SyncTask->Name);
	else
		strMirrorServerName.Format(_T("��������[%s]"), SyncTask->Name);

	m_lcMirrorServer.SetItemText(nItem, 1, strMirrorServerName);
	m_lcMirrorServer.SetItemText(nItem, 2, SyncTask->SyncIP);
	m_lcMirrorServer.SetItemText(nItem, 3, SyncTask->VDiskIP);
	m_lcMirrorServer.SetItemText(nItem, 4, SyncTask->UpdateIP);

	if (SyncTask->BalanceType == btDynamic)
		m_lcMirrorServer.SetItemText(nItem, 5, _T("��ѭ����"));
	else
	{
		//m_lcMirrorServer.SetItemText(nItem, 5, _T("��������"));
		std::string str("��������:");

		i8desk::AreaInfoMapItr it = m_AreaInfos.begin();
		for (; it != m_AreaInfos.end(); ++it)
		{
			if (strcmp(it->second->SID, SyncTask->SID) == 0)
			{
				str += it->second->Name;
				str += ",";
			}
		}
		if (str.find(",") == std::string::npos) 
			str += "δ����";
		else 
		{
			std::string t(str.begin(), str.begin() + str.size() - 1);
			std::swap(t, str);
		}

		m_lcMirrorServer.SetItemText(nItem, 5, str.c_str());
	}
}


bool CMirrorServerMgr::_JudgeSameServer(LPCTSTR lpszID, LPCTSTR lpszName)
{
	for(i8desk::SyncTaskMapItr iter = m_MirrorServers.begin();
		iter != m_MirrorServers.end();
		++iter)
	{
		if( _tcsicmp(iter->second->SID, lpszID) != 0 && _tcsicmp(iter->second->Name, lpszName) == 0 )
		{
			AfxMessageBox(_T("��������������ͬ���Ƶľ��������"));

			return true;
		}
	}

	return false;
};


bool CMirrorServerMgr::_JudgeSameArea(LPCTSTR lpszID)
{
	/*for(i8desk::AreaInfoMapItr iter = m_AreaInfos.begin();
		iter != m_AreaInfos.end();
		++iter)
	{
		if( iter->second->AID)
	}*/

	return true;
}


bool CMirrorServerMgr::_InsertMainServer()
{
	std::string strError;
	using std::tr1::bind;
	using std::tr1::placeholders::_1;

	// �ж��Ƿ��Ѿ������������
	GetConsoleDlg()->m_pDbMgr->GetAllMirrorServer(m_MirrorServers, strError);

	LPCTSTR pszMainServerName = GetConsoleDlg()->GetMainSevrerName().c_str();

	
	/*std::for_each(m_MirrorServers.begin(), m_MirrorServers.end(),
		bind(std::equal_to<int>(), 
		_tcsicmp(bind(&i8desk::tagSyncTask::Name, _1), pszMainServerName), 0)));*/

	for(i8desk::SyncTaskMap::iterator iter = m_MirrorServers.begin();
		iter != m_MirrorServers.end();
		++iter)
	{
		if( _tcsicmp(iter->second->Name, pszMainServerName) == 0 )
		{
			m_strMainServerID = iter->second->SID;
			m_bMainServerExists = true;

			break;
		}
	
		for(std::vector<CString>::const_iterator iterIP = GetConsoleDlg()->GetMainServerIP().begin();
			iterIP != GetConsoleDlg()->GetMainServerIP().end(); ++iterIP)
		{
			if( _tcsicmp(iter->second->SyncIP, *iterIP) == 0 ||
				_tcsicmp(iter->second->UpdateIP, *iterIP) == 0 || 
				_tcsicmp(iter->second->VDiskIP, *iterIP) == 0 )
			{
				m_strMainServerID = iter->second->SID;
				m_bMainServerExists = true;
				break;
			}
		}
	}

	// ����Ҫ���
	if( m_bMainServerExists == true )
		return false;


	// �����������
	i8desk::SyncTask syncTask;
	
	i8desk::SAFE_STRCPY(syncTask.SID,		i8desk::CreateGuidString().c_str());
	i8desk::SAFE_STRCPY(syncTask.Name,		GetConsoleDlg()->GetMainSevrerName().c_str());
	i8desk::SAFE_STRCPY(syncTask.SyncIP,	_T("0.0.0.0"));
	i8desk::SAFE_STRCPY(syncTask.UpdateIP,	_T("0.0.0.0"));
	i8desk::SAFE_STRCPY(syncTask.VDiskIP,	_T("0.0.0.0"));
	syncTask.SyncType			= stMirror;
	syncTask.MaxSyncSpeed		= 0;
	syncTask.DestDrv			= 0;
	
	
	bool bSuc = GetConsoleDlg()->m_pDbMgr->AddSyncTask(syncTask, strError);
	if( bSuc )
		m_strMainServerID = syncTask.SID;

	return bSuc;
}

void CMirrorServerMgr::_InitList()
{
	m_lcMirrorServer.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_lcMirrorServer.InsertColumn(0, _T("����ID"),		LVCFMT_LEFT, 0);
	m_lcMirrorServer.InsertColumn(1, _T("����������"),	LVCFMT_LEFT, 150);
	m_lcMirrorServer.InsertColumn(2, _T("ͬ��IP"),		LVCFMT_LEFT, 100);
	m_lcMirrorServer.InsertColumn(3, _T("������IP"),		LVCFMT_LEFT, 100);
	m_lcMirrorServer.InsertColumn(4, _T("��������IP"),	LVCFMT_LEFT, 100);
	m_lcMirrorServer.InsertColumn(5, _T("���ط���"),		LVCFMT_LEFT, 280);



	// �����������,�������޸�
	if( m_bMainServerExists == false )
	{
		CString strServerName;
		strServerName.Format(_T("��������[%s]"), m_MirrorServers[m_strMainServerID]->Name);

		m_lcMirrorServer.InsertItem(0, m_MirrorServers[m_strMainServerID]->SID);
		m_lcMirrorServer.SetItemData(0, (DWORD_PTR)m_MirrorServers[m_strMainServerID].get());
		m_lcMirrorServer.SetItemText(0, 1, strServerName);
		m_lcMirrorServer.SetItemText(0, 2, _T("�Զ�"));
		m_lcMirrorServer.SetItemText(0, 3, _T("�Զ�"));
		m_lcMirrorServer.SetItemText(0, 4, _T("�Զ�"));
		m_lcMirrorServer.SetItemText(0, 5, _T("�Զ�"));
	}
	else
	{
		InsertMirrorServerToList(m_MirrorServers[m_strMainServerID].get(), true);
	}

	for (i8desk::SyncTaskMapItr it = m_MirrorServers.begin(); 
		it != m_MirrorServers.end(); ++it) 
	{
		if( _tcsicmp(it->second->Name, m_MirrorServers[m_strMainServerID]->Name) == 0 )
			continue;

		InsertMirrorServerToList(&*it->second, false);
	}
}


void CMirrorServerMgr::_UpdateListCtrl()
{
	// ����
	for(int i = 0; i != m_lcMirrorServer.GetItemCount(); ++i)
	{
		i8desk::SyncTask *svr = reinterpret_cast<i8desk::SyncTask *>(m_lcMirrorServer.GetItemData(i));

		if( i == 0 )
			UpdateMirrorServerListItem(i, svr, true);
		else
			UpdateMirrorServerListItem(i, svr, false);
	}
}
// CMirrorServerMgr ��Ϣ�������
BOOL CMirrorServerMgr::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_EDIT_DESC)->SetWindowText(_T("����Ҫ�����������������Ӿ����������Ϣ���±����ھ����������װ�ڵ����\r\n��ӵ�Ⱥ������еķ����������Զ�����������������Դͬ����"));

	CConsoleDlg *pMainWnd = GetConsoleDlg();
	std::string ErrInfo;

	// ������������
	_InsertMainServer();

	CWaitCursor wc;
	if (!pMainWnd->m_pDbMgr->GetAllMirrorServer(m_MirrorServers, ErrInfo)) 
	{
		AfxMessageBox(ErrInfo.c_str());
		OnCancel();
		return TRUE;
	}

	// ��ʼ��list ctrl
	_InitList();

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CMirrorServerMgr::SetAreaInfo(const i8desk::AreaInfoMap &areaInfos)
{
	m_AreaInfos = areaInfos;
}

void CMirrorServerMgr::OnBnClickedButtonAddMirrorSvr()
{
	//POSITION pos = m_lcMirrorServer.GetFirstSelectedItemPosition();
	//int nItem = m_lcMirrorServer.GetNextSelectedItem(pos);

	do
	{
		CMirrorServerInfo dlg(m_strMainServerID);
		dlg.m_AreaInfos		= m_AreaInfos;
		dlg.m_MirrorServers = m_MirrorServers;
		dlg.m_bAdd			= TRUE;
		dlg.m_bServerMachine= false;

		if (dlg.DoModal() == IDOK) 
		{
			i8desk::SyncTask_Ptr SyncTask = i8desk::SyncTask_Ptr(new i8desk::SyncTask);
			*SyncTask = dlg.m_SyncTask;

			// ���������������ͬ�����
			if( _JudgeSameServer(SyncTask->SID, SyncTask->Name) == true )
				continue;

			i8desk::std_string strError;
			bool bOk = GetConsoleDlg()->m_pDbMgr->AddSyncTask(*SyncTask, strError);
			if (!bOk) 
			{
				AfxMessageBox(strError.c_str());
				continue;
			}

			m_MirrorServers[dlg.m_SyncTask.SID] = SyncTask;
			InsertMirrorServerToList(&*SyncTask, false);

			// ����ListCtrl
			_UpdateListCtrl();
		}
		
		break;

	}while(1);
}

void CMirrorServerMgr::OnBnClickedButtonModifyMirrorSvr()
{
	POSITION pos = m_lcMirrorServer.GetFirstSelectedItemPosition();
	if( pos == NULL )
		return;

	int nItem = m_lcMirrorServer.GetNextSelectedItem(pos);
	i8desk::SyncTask *svr = reinterpret_cast<i8desk::SyncTask *>(m_lcMirrorServer.GetItemData(nItem));
	ASSERT(svr);

	i8desk::tagSyncTask tmpSyncTask = *svr;

	do
	{
		CMirrorServerInfo dlg(m_strMainServerID);
		dlg.m_AreaInfos		= m_AreaInfos;
		dlg.m_MirrorServers = m_MirrorServers;
		dlg.m_bAdd			= FALSE;
		dlg.m_bServerMachine= (nItem == 0) ? true : false;
		dlg.m_SyncTask		= tmpSyncTask;


		if (dlg.DoModal() == IDOK) 
		{
			i8desk::SyncTask_Ptr SyncTask = m_MirrorServers[dlg.m_SyncTask.SID];
			ASSERT(SyncTask);


			// ���������������ͬ�����,�ع�
			if( _JudgeSameServer(dlg.m_SyncTask.SID, dlg.m_SyncTask.Name) == false )
			{
				i8desk::std_string strError;
				bool bOK = GetConsoleDlg()->m_pDbMgr->ModifySyncTask(dlg.m_SyncTask, strError);
				if (!bOK) 
				{
					AfxMessageBox(strError.c_str());
					continue;
				}

				*SyncTask = dlg.m_SyncTask;
			}
			else
				continue;

			_UpdateListCtrl();
		}

		break;
	}while(1);
}


void CMirrorServerMgr::OnBnClickedButtonDelMirrorSvr()
{
	POSITION pos = m_lcMirrorServer.GetFirstSelectedItemPosition();
	ASSERT(pos);

	int nItem = m_lcMirrorServer.GetNextSelectedItem(pos);
	i8desk::SyncTask *svr = reinterpret_cast<i8desk::SyncTask *>
		(m_lcMirrorServer.GetItemData(nItem));
	ASSERT(svr);

	// ����ɾ����������
	if( nItem == 0 && _tcsicmp(svr->Name, m_MirrorServers[m_strMainServerID]->Name) == 0 )
	{
		AfxMessageBox(_T("����ɾ����������"));
		return;
	}

	if (::MessageBox(m_hWnd, "ȷ��Ҫɾ��ѡ���ľ������������?", svr->Name, 
		MB_ICONQUESTION|MB_OKCANCEL) == IDOK)
	{
		CConsoleDlg *pMainWnd = (CConsoleDlg *)::AfxGetMainWnd();
		std::string ErrInfo;

		CWaitCursor wc;
		if (!pMainWnd->m_pDbMgr->DelSyncTask(svr->SID, ErrInfo)) {
			AfxMessageBox(ErrInfo.c_str());
			return;
		}

		m_lcMirrorServer.DeleteItem(nItem);
		m_MirrorServers.erase(svr->SID);
	}
}



void CMirrorServerMgr::OnNMClickListMirrorSvr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	POSITION pos = m_lcMirrorServer.GetFirstSelectedItemPosition();
	bool b = pos != NULL;

	this->GetDlgItem(IDC_BUTTON_MODIFY_MIRROR_SVR)->EnableWindow(b);
	this->GetDlgItem(IDC_BUTTON_DELETE_MIRROR_SVR)->EnableWindow(b);

	*pResult = 0;
}

void CMirrorServerMgr::OnNMDblclkListMirrorSvr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	int nItem = pNMItemActivate->iItem;
	if (nItem == -1) 
	{
		return;
	}
	OnBnClickedButtonModifyMirrorSvr();
}

void CMirrorServerMgr::OnLvnDeleteitemListMirrorSvr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	POSITION pos = m_lcMirrorServer.GetFirstSelectedItemPosition();
	bool b = pos != NULL;

	this->GetDlgItem(IDC_BUTTON_MODIFY_MIRROR_SVR)->EnableWindow(b);
	this->GetDlgItem(IDC_BUTTON_DELETE_MIRROR_SVR)->EnableWindow(b);

	*pResult = 0;
}

