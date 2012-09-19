// SyncTaskMgr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Console.h"
#include "SyncTaskMgr.h"

#include "SyncTaskInfo.h"
#include "ConsoleDlg.h"

// CSyncTaskMgr �Ի���

IMPLEMENT_DYNAMIC(CSyncTaskMgr, CDialog)

CSyncTaskMgr::CSyncTaskMgr(CWnd* pParent /*=NULL*/)
	: CDialog(CSyncTaskMgr::IDD, pParent)
{

}

CSyncTaskMgr::~CSyncTaskMgr()
{
}

void CSyncTaskMgr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SYNC_TASK, m_lcSyncTask);
}


BEGIN_MESSAGE_MAP(CSyncTaskMgr, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SYNC_TASK, &CSyncTaskMgr::OnBnClickedButtonAddSyncTask)
	ON_BN_CLICKED(IDC_BUTTON_MODIRY_SYNC_TASK, &CSyncTaskMgr::OnBnClickedButtonModirySyncTask)
	ON_BN_CLICKED(IDC_BUTTON_DEL_SYN_TASK, &CSyncTaskMgr::OnBnClickedButtonDelSynTask)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST_SYNC_TASK, &CSyncTaskMgr::OnLvnDeleteitemListSyncTask)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SYNC_TASK, &CSyncTaskMgr::OnNMClickListSyncTask)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SYNC_TASK, &CSyncTaskMgr::OnNMDblclkListSyncTask)
END_MESSAGE_MAP()


// CSyncTaskMgr ��Ϣ�������

BOOL CSyncTaskMgr::OnInitDialog()
{
	CDialog::OnInitDialog();

	CConsoleDlg *pMainWnd = (CConsoleDlg *)::AfxGetMainWnd();
	std::string ErrInfo;

	CWaitCursor wc;
	if (!pMainWnd->m_pDbMgr->GetAllSyncTask(m_SyncTasks, ErrInfo)) {
		AfxMessageBox(ErrInfo.c_str());
		OnCancel();
		return TRUE;
	}
	m_lcSyncTask.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_lcSyncTask.InsertColumn(0, "����ID",		LVCFMT_LEFT, 0);
	m_lcSyncTask.InsertColumn(1, "��������",	LVCFMT_LEFT, 120);
	m_lcSyncTask.InsertColumn(2, "ͬ����ʽ",	LVCFMT_LEFT, 80);
	m_lcSyncTask.InsertColumn(3, "Ŀ��IP",		LVCFMT_LEFT, 80);
	m_lcSyncTask.InsertColumn(4, "Ŀ���̷�",	LVCFMT_LEFT, 80);
	m_lcSyncTask.InsertColumn(5, "ͬ����Դ",	LVCFMT_LEFT, 80);

	for (i8desk::SyncTaskMapItr it = m_SyncTasks.begin(); 
		it != m_SyncTasks.end(); ++it) 
	{
		InsertSyncTaskToList(&*it->second);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSyncTaskMgr::OnBnClickedButtonAddSyncTask()
{
	CWaitCursor wc;

	CSyncTaskInfo dlg;
	dlg.m_bAdd = TRUE;
	dlg.m_GameInfos = m_GameInfos;
	dlg.m_ClassInfos = m_ClassInfos;

	wc.Restore();

	if (dlg.DoModal() == IDOK) {
		i8desk::SyncTask_Ptr SyncTask = i8desk::SyncTask_Ptr(new i8desk::SyncTask);
		*SyncTask = dlg.m_SyncTask;
		m_SyncTasks[dlg.m_SyncTask.SID] = SyncTask;
		InsertSyncTaskToList(&*SyncTask);
	}
	//*/
}

void CSyncTaskMgr::OnBnClickedButtonModirySyncTask()
{
	CWaitCursor wc;

	POSITION pos = m_lcSyncTask.GetFirstSelectedItemPosition();
	ASSERT(pos);

	int nItem = m_lcSyncTask.GetNextSelectedItem(pos);
	i8desk::SyncTask *svr = reinterpret_cast<i8desk::SyncTask *>
		(m_lcSyncTask.GetItemData(nItem));
	ASSERT(svr);


	CSyncTaskInfo dlg;
	dlg.m_bAdd = FALSE;

	dlg.m_GameInfos = m_GameInfos;
	dlg.m_ClassInfos = m_ClassInfos;

	dlg.m_SyncTask = *svr;

	wc.Restore();

	if (dlg.DoModal() == IDOK) {
		i8desk::SyncTask_Ptr SyncTask = m_SyncTasks[dlg.m_SyncTask.SID];
		ASSERT(SyncTask);
		*SyncTask = dlg.m_SyncTask;
		UpdateSyncTaskListItem(nItem, &*SyncTask);
	}
	//*/
}

void CSyncTaskMgr::OnBnClickedButtonDelSynTask()
{
	POSITION pos = m_lcSyncTask.GetFirstSelectedItemPosition();
	ASSERT(pos);

	int nItem = m_lcSyncTask.GetNextSelectedItem(pos);
	i8desk::SyncTask *svr = reinterpret_cast<i8desk::SyncTask *>
		(m_lcSyncTask.GetItemData(nItem));
	ASSERT(svr);

	if (::MessageBox(m_hWnd, "ȷ��Ҫɾ��ѡ����ͬ����������?", svr->Name, 
		MB_ICONQUESTION|MB_OKCANCEL) == IDOK)
	{
		CConsoleDlg *pMainWnd = (CConsoleDlg *)::AfxGetMainWnd();
		std::string ErrInfo;

		CWaitCursor wc;
		if (!pMainWnd->m_pDbMgr->DelSyncTask(svr->SID, ErrInfo)) {
			AfxMessageBox(ErrInfo.c_str());
			return;
		}

		m_lcSyncTask.DeleteItem(nItem);
		m_SyncTasks.erase(svr->SID);
	}
	//*/
}

void CSyncTaskMgr::OnLvnDeleteitemListSyncTask(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	POSITION pos = m_lcSyncTask.GetFirstSelectedItemPosition();
	bool b = pos != NULL;

	this->GetDlgItem(IDC_BUTTON_MODIRY_SYNC_TASK)->EnableWindow(b);
	this->GetDlgItem(IDC_BUTTON_DEL_SYN_TASK)->EnableWindow(b);

	*pResult = 0;
	//*/
}

void CSyncTaskMgr::OnNMClickListSyncTask(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	POSITION pos = m_lcSyncTask.GetFirstSelectedItemPosition();
	bool b = pos != NULL;

	this->GetDlgItem(IDC_BUTTON_MODIRY_SYNC_TASK)->EnableWindow(b);
	this->GetDlgItem(IDC_BUTTON_DEL_SYN_TASK)->EnableWindow(b);

	*pResult = 0;
	//*/
}

void CSyncTaskMgr::OnNMDblclkListSyncTask(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	int nItem = pNMItemActivate->iItem;
	if (nItem == -1) {
		return;
	}
	OnBnClickedButtonModirySyncTask();
	//*/
}

void CSyncTaskMgr::InsertSyncTaskToList(const i8desk::SyncTask *SyncTask)
{
	int nItem = m_lcSyncTask.GetItemCount();
	
	m_lcSyncTask.InsertItem(nItem, SyncTask->SID);
	m_lcSyncTask.SetItemData(nItem, (DWORD_PTR)SyncTask);

	UpdateSyncTaskListItem(nItem, SyncTask);
}


void CSyncTaskMgr::UpdateSyncTaskListItem(int nItem, const i8desk::SyncTask* SyncTask)
{
	m_lcSyncTask.SetItemText(nItem, 1, SyncTask->Name);
	m_lcSyncTask.SetItemText(nItem, 2, _T("ͬ�����"));
	m_lcSyncTask.SetItemText(nItem, 3, SyncTask->SyncIP);
	if (SyncTask->DestDrv == 0) {
		m_lcSyncTask.SetItemText(nItem, 4, _T("Դ·��һ��"));
	} 
	else {
		TCHAR drv[] = { static_cast<TCHAR>(SyncTask->DestDrv), 0 };
		m_lcSyncTask.SetItemText(nItem, 4, drv);
	}

	switch (SyncTask->SyncType) {
	case stVDisk:
		m_lcSyncTask.SetItemText(nItem, 5, _T("��������Դ"));
		break;
	case stUpdate:
		m_lcSyncTask.SetItemText(nItem, 5, _T("���ظ�����Դ"));
		break;
	case stCustom:
		m_lcSyncTask.SetItemText(nItem, 5, _T("�û��Զ���"));
		break;
	case stAllRes:
		m_lcSyncTask.SetItemText(nItem, 5, _T("ȫ����Դ"));
		break;
	default:
		break;
	}
}

