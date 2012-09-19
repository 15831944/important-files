#include "stdafx.h"

#include "monitorpage.h"
#include "ConsoleDlg.h"
#include "ClientListDlg.h"
#include "GameListDlg.h"
#include "WaitMessageDlg.h"
#include "TJDlg.h"

enum {
	TJ_CLASS_MAINSERVER,
	TJ_CLASS_DISKSPACE,
	TJ_CLASS_MODULESTATUS,
	TJ_CLASS_CPUUSAGE,
	TJ_CLASS_MEMORYUSAGE,
	TJ_CLASS_NETWORKUSAGE,
	TJ_CLASS_DISKIOSPEED,
	TJ_CLASS_BACKUPDATABASE,
};

enum {
	TJ_MODULE_MAIN,
	TJ_MODULE_DNA,
	TJ_MODULE_VDISK,
	TJ_MODULE_UPDATE,
	TJ_MODULE_SHOP,
	TJ_MODULE_LAST = TJ_MODULE_SHOP
};

/////////////////////////////////////////////////////////////////
// CMonitorPage
//
CMonitorPage::CMonitorPage()
	: CFormCtrl(CMonitorPage::IDD)
	, m_nServer(0)
	, m_nJK(0)
	, m_ServerMedicalTime(0)
{
	memset(m_Servers, 0, sizeof(m_Servers));
	memset(&m_GameInfo, 0, sizeof(m_GameInfo));
	memset(&m_ClientInfo, 0, sizeof(m_ClientInfo));
}

CMonitorPage::~CMonitorPage()
{
}

BEGIN_MESSAGE_MAP(CMonitorPage, CFormCtrl)
END_MESSAGE_MAP()

static void my_sleep(DWORD t)
{
	::Sleep(t);
}

void CMonitorPage::NotifyServerMedical()
{
	std::string ErrInfo;
	if (GetConsoleDlg()->m_pDownloadMgr->NotifyServerMedical(ErrInfo))
	{
		CWaitMessageDlg wdlg(_T("�������¶Է��������"));
		wdlg.exec(std::tr1::bind(my_sleep, 15000));
	}
	else
	{
		AfxMessageBox(ErrInfo.c_str());
	}
}

void CMonitorPage::ViewGameList(int type)
{
	CGameListDlg dlg(GetConsoleDlg()->m_ClassInfos, GetConsoleDlg()->m_GameInfos, type);
	dlg.DoModal();
}

void CMonitorPage::ViewDeleteGameList(int partition)
{
	CGameListDlg dlg(GetConsoleDlg()->m_ClassInfos, GetConsoleDlg()->m_GameInfos,
		CGameListDlg::MAYDELETE, partition);
	dlg.DoModal();
}

void CMonitorPage::ViewClientList(int type)
{
	CClientListDlg dlg(GetConsoleDlg()->m_AreaInfos, GetConsoleDlg()->m_Machines, type);
	dlg.DoModal();
}

static LPCTSTR GetModuleStatusDesc(const std::string& status)
{
	if (status == "1") 
		return  _T("����");
	else if (status == "-1") 
		return _T("�쳣");
	else if (status == "2") 
		return _T("δ��װ");
	else if (status == "3") 
		return _T("δ����");
	else
		return _T("δ����");

	return _T("δ����");
}

static LPCTSTR GetModuleStatusDesc(int status)
{
	if (status == 1) 
		return  _T("����");
	else if (status == -1) 
		return _T("�쳣");
	else if (status == 2) 
		return _T("δ��װ");
	else if (status == 3) 
		return _T("δ����");
	else
		return _T("δ����");

	return _T("δ����");
}

void CMonitorPage::SyncServerStatus(const std::map<std::string, std::set<char> >& s,
									const std::string& strMainServerName
									)
{
	std::map<std::string, std::set<char> > servers = s;
	if (servers.size() > _countof(m_Servers))
		return;

	memset(m_Servers, 0, sizeof(m_Servers));
	m_nServer = servers.size();

	if (m_nServer == 0)
		return;

	size_t i = 0;

	//�����������������ǰ��
	std::map<std::string, std::set<char> >::iterator it = servers.find(strMainServerName);
	ASSERT(it != servers.end());

	if (it != servers.end())
	{
		i8desk::SAFE_STRCPY(m_Servers[i].HostName, it->first.c_str());
		std::set<char>::iterator dit = it->second.begin();
		for (size_t j = 0; dit != it->second.end(); ++dit, ++j)
		{
			if (j >= it->second.size())
				break;
			m_Servers[i].Disk[j].Driver = *dit;
		}

		i++;
		servers.erase(it);
	}
	
	for (std::map<std::string, std::set<char> >::iterator it = servers.begin();
		it != servers.end(); ++it, ++i)
	{
		i8desk::SAFE_STRCPY(m_Servers[i].HostName, it->first.c_str());
		std::set<char>::iterator dit = it->second.begin();
		for (size_t j = 0; dit != it->second.end(); ++dit, ++j)
		{
			if (j >= it->second.size())
				break;
			m_Servers[i].Disk[j].Driver = *dit;
		}
	}
}

void CMonitorPage::SyncHealthStatus(const std::map<std::string, std::set<char> >& servers)
{

}

void CMonitorPage::UpdateModuleStatus(const std::string& strHostName,
									  const std::string& strI8DeskSvr,
									  const std::string& strI8VDiskSvr,
									  const std::string& strI8UpdateSvr,
									  const std::string& strDNAService,
									  const std::string& strI8MallCashier,
									  const std::string& strLastBackupDBTime,
									  const std::string& strCPUUtilization,
									  const std::string& strMemoryUsage,
									  const std::string& strNetworkSendRate,
									  const std::string& strNetworkRecvRate,
									  const std::string& strRemainMemory
									  )
{
	for (size_t i = 0; i < m_nServer; i++)
	{
		if (strHostName == m_Servers[i].HostName)
		{
			m_Servers[i].MainServer = atoi(strI8DeskSvr.c_str());			//������
			m_Servers[i].ThirdLayerUpdate = atoi(strDNAService.c_str());	//�������
			m_Servers[i].VirtualDisk = atoi(strI8VDiskSvr.c_str());		//�������
			m_Servers[i].InnerUpdate = atoi(strI8UpdateSvr.c_str());		//��������
			m_Servers[i].ShopCity = atoi(strI8MallCashier.c_str());			//�̳�������
			m_Servers[i].cpuusage = atoi(strCPUUtilization.c_str());			//cpuռ����
			m_Servers[i].memoryusage = atoi(strMemoryUsage.c_str());		//�ڴ�ռ����
			m_Servers[i].LastBackupDatabaseTime = atoi(strLastBackupDBTime.c_str());
			return;
		}
	}
}

void CMonitorPage::UpdateClientStatus(const i8desk::MachineMap& Machines)
{
	memset(&m_ClientInfo, 0, sizeof(m_ClientInfo));

	i8desk::MachineMapCItr it = Machines.begin();
	for (; it != Machines.end(); ++it)
	{
		m_ClientInfo.CliNum++;
		if (it->second->online)
		{
			m_ClientInfo.CliOnlineNum++;
			if (it->second->ProtInstall == 0)
				m_ClientInfo.NotProtNum++;
			   
			if (it->second->SCStatus == 0)
				m_ClientInfo.NotSafeNum++;
			if (it->second->IEProt == 0)
				m_ClientInfo.NotIeNum++;
			if (it->second->FDogDriver == 0)
				m_ClientInfo.NotDogNum++;
		}
	}
}


void CMonitorPage::UpdateGameStatus(const i8desk::GameInfoMap& GameInfos)
{
	int nIdcCount = 0, nSvrCount = 0, nMatchCount = 0;
	int nAutoUptCount = 0, nNeedUptCount = 0;
	int nIdcAddInThisWeekCount = 0, nIdcUpdateCount = 0;
	int nIdcI8PlayCount = 0, nIdcI8PlayNotDownloadCount = 0;
	unsigned __int64 ullIdcSize = 0, ullSvrSize = 0;
	unsigned __int64 ullIdcI8PlaySize = 0, ullIdcI8PlayNotDownloadSize = 0;
	
	int nAddGameNoDownNum = 0; //����������Դ(δ����)

	int nConVirRunGameNum = 0;	//����Ϊ���������е���Դ��
	unsigned __int64 ullConVirRunGameSize = 0;

	int nConLocRunGameNum = 0;	//����Ϊ���ظ������е���Դ��
	unsigned __int64 ullConLocRunGameSize = 0;	

	int nConRunNotUptGameNum = 0;//����Ϊ�����£�ֱ�����е���Դ��
	unsigned __int64 ullConRunNotUptGameSize = 0;

	CTime now = CTime::GetCurrentTime();
	int nowYear = now.GetYear();
	int nowMonth = now.GetMonth();
	int nowDay = now.GetDay();

	CTime start(now.GetYear(), now.GetMonth(), now.GetDay(), 0, 0, 0);
	start -= CTimeSpan(30,0,0,0); //30�������
	DWORD StartTime = (DWORD)start.GetTime();

	//�õ����ܿ�ʼ��ʱ�̣����ڼ��㱾�����ĸ��µ���Ϸ��
	int nowDayOfWeek = now.GetDayOfWeek();
	CTime ThisWeekStart = now - CTimeSpan(nowDayOfWeek);

	CTime ThisWeekStartDay(ThisWeekStart.GetYear(), 
		ThisWeekStart.GetMonth(), ThisWeekStart.GetDay(), 0, 0, 0);
	DWORD ThisWeekStartTime = (DWORD)ThisWeekStartDay.GetTime();

	i8desk::GameInfoMapCItr it = GameInfos.begin();
	for (; it != GameInfos.end(); ++it) 
	{
		if (it->second->GID >= MIN_IDC_GID) 
		{
			nIdcCount++;
			ullIdcSize += it->second->Size;

			if (it->second->Status == 1)
				nMatchCount++;

			if (it->second->AddDate > StartTime && it->second->Status == 0)
			{
				nAddGameNoDownNum++;
			}

			if (it->second->IdcVer > ThisWeekStartTime)
			{
				nIdcAddInThisWeekCount++;

				CTime IdcUpdateTime = it->second->IdcVer;
				if (IdcUpdateTime.GetDay() == nowDay
					&& IdcUpdateTime.GetMonth() == nowMonth
					&& IdcUpdateTime.GetYear() == nowYear)
				{
					nIdcUpdateCount++;
				}
			}

			if (it->second->I8Play == 1)
			{
				nIdcI8PlayCount++;
				ullIdcI8PlaySize += it->second->Size;

				if (it->second->Status == 0) 
				{
					nIdcI8PlayNotDownloadCount++;
					ullIdcI8PlayNotDownloadSize += it->second->Size;
				}
			}
		}

		if (it->second->Status == 1)
		{
			nSvrCount++;
			ullSvrSize += it->second->Size;

			if (it->second->AutoUpt == 1)
				nAutoUptCount++;
			if (it->second->GID >= MIN_IDC_GID 
				&& it->second->IdcVer != it->second->SvrVer)
				nNeedUptCount++;

			bool bConLocRunGame = false;
			bool bConVirRunGame = false;
			bool bConRunNotUptGame = false;

			for (size_t i = 0; i < it->second->RunTypes.size(); i++)
			{
				switch (it->second->RunTypes[i].RunType)
				{
				case ERT_LOCAL: 
					bConLocRunGame = true; 
					break;
				case ERT_VDISK:
					bConVirRunGame = true; 
					break;
				case ERT_DIRECT: 
					bConRunNotUptGame = true; 
					break;
				default: 
					break;
				}
			}

			if (bConLocRunGame)
			{
				nConLocRunGameNum++;
				ullConLocRunGameSize += it->second->Size;
			}

			if (bConVirRunGame)
			{
				nConVirRunGameNum++;
				ullConVirRunGameSize += it->second->Size;
			}

			if (bConRunNotUptGame)
			{
				nConRunNotUptGameNum++;
				ullConRunNotUptGameSize += it->second->Size;
			}
		}
	}

	sprintf(m_GameInfo.CGameNum, "%d��/%.2fG", nIdcCount, ullIdcSize/1024.0/1024.0);			//������Ϸ��
	sprintf(m_GameInfo.MatchGameNum, "%d��", nMatchCount);		//���ؼ�ƥ�䵽������Դ����Ϸ
	sprintf(m_GameInfo.LGameNum, "%d��/%.2fG", nSvrCount, ullSvrSize/1024.0/1024.0);			//������Ϸ��
	
	sprintf(m_GameInfo.CAddGameNum, "%d��", nAddGameNoDownNum);	//����������Դ(δ����)

	sprintf(m_GameInfo.ConLocRunGameNum, "%d��/%.2fG", nConLocRunGameNum, ullConLocRunGameSize/1024.0/1024.0);	//��ֵ��Ϸ����δ������
	sprintf(m_GameInfo.ConVirRunGameNum, "%d��/%.2fG", nConVirRunGameNum, ullConVirRunGameSize/1024.0/1024.0);	//��ֵ��Ϸ����δ������
	sprintf(m_GameInfo.ConRunNotUptGameNum, "%d��/%.2fG", nConRunNotUptGameNum, ullConRunNotUptGameSize/1024.0/1024.0);	//��ֵ��Ϸ����δ������

	sprintf(m_GameInfo.HaveUptGameNum, "%d��", nNeedUptCount);		//�и��µ���Ϸ��
}

void CMonitorPage::UpdateDownload3upListCount(int count)
{
	sprintf(m_GameInfo.ThirdDwnListNum, "%d��", count);	//����������ض�����
}

void CMonitorPage::UpdateDownload3upTotalSpeed(float speed)
{
	sprintf(m_GameInfo.ThirdDwnSpeed, "%.2fKB/S", speed);		//�����������ٶ�
}

void CMonitorPage::UpdateDownloadUpdateGameCount(int count)
{
	sprintf(m_GameInfo.InnerUptListNum, "%d��", count);	//�������¶�����
}

void CMonitorPage::UpdateDownloadUpdateTotalSpeed(float speed)
{
	sprintf(m_GameInfo.InnerUptSpeed, "%.2fMB/S", speed); 		//�����������ٶ�
}


void CMonitorPage::UpdateDiskStatus(
				const std::string& strHostName,
				const std::string& strPartition,
				const std::string& strType,
				const std::string& strCapacity,
				const std::string& strUsedSize,
				const std::string& strFreeSize,
				const std::string& strReadDataRate
				)
{
	for (size_t i = 0; i < m_nServer; i++)
	{
		if (strHostName == m_Servers[i].HostName)
		{
			for (size_t j = 0; j < _countof(m_Servers[i].Disk); j++)
			{
				if (atoi(strPartition.c_str()) == m_Servers[i].Disk[j].Driver)
				{
					m_Servers[i].Disk[j].total = atol(strCapacity.c_str()) / 1024.0f / 1024;
					m_Servers[i].Disk[j].userd = atol(strUsedSize.c_str()) / 1024.0f / 1024;
					m_Servers[i].Disk[j].speed = atol(strReadDataRate.c_str()) / 1024.0f;
					return;
				}
			}
		}
	}
}

void CMonitorPage::InvalidateMonitorData()
{
	if (m_nJK == 0)
	{
		m_nJK = ::GetDbMgr()->GetOptInt(OPT_M_LASTJKZS);
		m_ServerMedicalTime = ::GetDbMgr()->GetOptInt(OPT_M_LASTTJTIME);
		if (m_nJK == 0 || m_ServerMedicalTime == 0)
			CalcJKZS();
	}

	CString strServerMedicalTime;
	if (m_ServerMedicalTime)
	{
		tm *tm = ::_localtime32(&m_ServerMedicalTime);
		strServerMedicalTime.Format(
			"%04d/%02d/%02d %02d:%02d:%02d",
			tm->tm_year + 1900, 
			tm->tm_mon + 1, 
			tm->tm_mday, 
			tm->tm_hour, 
			tm->tm_min, 
			tm->tm_sec);
	}
	else
	{
		strServerMedicalTime = "��δ���";
	}
	UpdateJKZS(m_nJK, strServerMedicalTime);

	UpdateServer(m_Servers, m_nServer);
	UpdateClient(&m_ClientInfo);
	UpdateGameInfo(&m_GameInfo);
}

int CMonitorPage::CalcJKZS()
{
	int nJK = 100;
	for (size_t i = 0; i < m_nServer; i++)
	{
		if (m_Servers[i].cpuusage > 30)
			nJK -= 10;
		if (m_Servers[i].memoryusage > 90)
			nJK -= 10;
		if (m_Servers[i].networkusage > 50)
			nJK -= 10;
		if (m_Servers[i].InnerUpdate == -2)
			nJK -= 20;
		if (i == 0 && m_Servers[i].MainServer != 1)
			nJK -= 20;
		if (m_Servers[i].ShopCity == -2)
			nJK -= 20;
		if (m_Servers[i].VirtualDisk != 1)
			nJK -= 20;
		if (i == 0 && m_Servers[i].ThirdLayerUpdate != 1)
			nJK -= 20;
		if (i == 0 && m_Servers[i].LastBackupDatabaseTime == 0)
			nJK -= 10;
		for (size_t j = 0; j < _countof(m_Servers[i].Disk); j++)
		{
			if (m_Servers[i].Disk[j].Driver)
			{
				if (m_Servers[i].Disk[j].total - m_Servers[i].Disk[j].userd < 30.0f)
					nJK -= 10;
				if (i == 0 && m_Servers[i].Disk[j].speed < 50.0f)
					nJK -= 10;
			}
		}
	}

	if (nJK < 30)
		nJK = 30;

	m_nJK = nJK;
	m_ServerMedicalTime = ::_time32(0);

	::GetDbMgr()->SetOption(OPT_M_LASTTJTIME, m_ServerMedicalTime);
	::GetDbMgr()->SetOption(OPT_M_LASTJKZS, m_nJK);

	return m_nJK;
}

//���������CTJDlg::OnTimer�е��ã����ƽ�������
BOOL CMonitorPage::PerformTJ(CTJDlg *pTJDlg)
{
	if (m_nServer == 0)
	{
		return TRUE;
	}

	switch (m_nCurTJServer)
	{
	case 0:
		switch (m_nCurClass)
		{
		case TJ_CLASS_MAINSERVER: {
			//��������
			{
				CTJDlg::tagList_Item item = {0};
				sprintf_s(item.Caption, "%s(��������)", m_Servers[m_nCurTJServer].HostName);
				pTJDlg->AddLine(&item);
			}

			CFormCtrl::tagDisk& disk = m_Servers[m_nCurTJServer].Disk[0];
			if (int Driver = disk.Driver)
			{
				//���̿ռ�
				{
					CTJDlg::tagList_Item item = {1, "���̿ռ�" };
					pTJDlg->AddLine(&item);
				}

				//��һ������
				{
					CTJDlg::tagList_Item item = {2};
					float fFreeSpace = disk.total - disk.userd;
					sprintf(item.Caption, "%C:���̿���:%.2fG", Driver, fFreeSpace);
					if (fFreeSpace > 30.0f)
					{
						item.Status = TRUE;
						sprintf(item.StatusText, "����");
					}
					else
					{
						item.Status = FALSE;
						sprintf(item.StatusText, "�ռ䲻�㣬�Ƽ���������");
					}
					pTJDlg->AddLine(&item);
				}

				m_nCurClass = TJ_CLASS_DISKSPACE;
				m_nCurTJDisk = 0;
			}
			else
			{
				//���״̬
				{
					CTJDlg::tagList_Item item = {1, "���״̬" };
					pTJDlg->AddLine(&item);
				}

				//��һ�����״̬
				{
					CTJDlg::tagList_Item item = {2};
					sprintf(item.Caption, "�������", Driver);
					item.Status = m_Servers[m_nCurTJServer].MainServer == 1;
					sprintf(item.StatusText, GetModuleStatusDesc(m_Servers[m_nCurTJServer].MainServer));
					pTJDlg->AddLine(&item);
				}

				m_nCurClass = TJ_CLASS_MODULESTATUS;
				m_nCurModule = TJ_MODULE_MAIN;
			}
			break; }
		case TJ_CLASS_DISKSPACE: {
			m_nCurTJDisk++;
			int Driver = 0;
			if (m_nCurTJDisk < _countof(m_Servers[m_nCurTJServer].Disk))
				Driver = m_Servers[m_nCurTJServer].Disk[m_nCurTJDisk].Driver;
			if (Driver)
			{
				//��һ������
				CFormCtrl::tagDisk& disk = m_Servers[m_nCurTJServer].Disk[m_nCurTJDisk];
				{
					CTJDlg::tagList_Item item = {2};
					float fFreeSpace = disk.total - disk.userd;
					sprintf(item.Caption, "%C:���̿���:%.2fG", Driver, fFreeSpace);
					if (fFreeSpace > 30.0f)
					{
						item.Status = TRUE;
						sprintf(item.StatusText, "����");
					}
					else
					{
						item.Status = FALSE;
						sprintf(item.StatusText, "�ռ䲻�㣬�Ƽ���������");
					}
					pTJDlg->AddLine(&item);
				}
			}
			else
			{
				//���״̬
				{
					CTJDlg::tagList_Item item = {1, "���״̬" };
					pTJDlg->AddLine(&item);
				}

				//��һ�����״̬
				{
					CTJDlg::tagList_Item item = {2};
					sprintf(item.Caption, "�������", Driver);
					item.Status = m_Servers[m_nCurTJServer].MainServer == 1;
					sprintf(item.StatusText, GetModuleStatusDesc(m_Servers[m_nCurTJServer].MainServer));
					pTJDlg->AddLine(&item);
				}

				m_nCurClass = TJ_CLASS_MODULESTATUS;
				m_nCurModule = TJ_MODULE_MAIN;
			}
			break; }
		case TJ_CLASS_MODULESTATUS: 
			m_nCurModule++;
			if (m_nCurModule <= TJ_MODULE_LAST)
			{
				switch (m_nCurModule)
				{
				case TJ_MODULE_DNA:
					//һ�����״̬
					{
						CTJDlg::tagList_Item item = {2};
						sprintf(item.Caption, "����������");
						item.Status = m_Servers[m_nCurTJServer].ThirdLayerUpdate == 1;
						sprintf(item.StatusText, GetModuleStatusDesc(m_Servers[m_nCurTJServer].ThirdLayerUpdate));
						pTJDlg->AddLine(&item);
					}
					break;
				case TJ_MODULE_VDISK:
					//һ�����״̬
					{
						CTJDlg::tagList_Item item = {2};
						sprintf(item.Caption, "���������");
						item.Status = m_Servers[m_nCurTJServer].VirtualDisk == 1;
						sprintf(item.StatusText, GetModuleStatusDesc(m_Servers[m_nCurTJServer].VirtualDisk));
						pTJDlg->AddLine(&item);
					}
					break;
				case TJ_MODULE_UPDATE:
					//һ�����״̬
					{
						CTJDlg::tagList_Item item = {2};
						sprintf(item.Caption, "�����������");
						item.Status = m_Servers[m_nCurTJServer].InnerUpdate == 1;
						sprintf(item.StatusText, GetModuleStatusDesc(m_Servers[m_nCurTJServer].InnerUpdate));
						pTJDlg->AddLine(&item);
					}
					break;
				case TJ_MODULE_SHOP:
					//һ�����״̬
					{
						CTJDlg::tagList_Item item = {2};
						sprintf(item.Caption, "�̳�������");
						item.Status = m_Servers[m_nCurTJServer].ShopCity == 1;
						sprintf(item.StatusText, GetModuleStatusDesc(m_Servers[m_nCurTJServer].ShopCity));
						pTJDlg->AddLine(&item);
					}
					break;
				}
			}
			else
			{
				//CPUռ����
				{
					CTJDlg::tagList_Item item = {1};
					sprintf(item.Caption, "CPUռ����:%d%%", m_Servers[m_nCurTJServer].cpuusage);
					if (m_Servers[m_nCurTJServer].cpuusage < 30)
					{
						item.Status = TRUE;
						sprintf(item.StatusText, "����");
					}
					else
					{
						item.Status = FALSE;
						sprintf(item.StatusText, "�ϸߣ��Ƽ����м��");
					}
					pTJDlg->AddLine(&item);
				}
				m_nCurClass = TJ_CLASS_CPUUSAGE;
			}
			break;
		case TJ_CLASS_CPUUSAGE: 
			//����ʹ����
			{
				CTJDlg::tagList_Item item = {1};
				sprintf(item.Caption, "�ڴ�ʹ����:%d%%", m_Servers[m_nCurTJServer].memoryusage);
				if (m_Servers[m_nCurTJServer].memoryusage < 90)
				{
					item.Status = TRUE;
					sprintf(item.StatusText, "����");
				}
				else
				{
					item.Status = FALSE;
					sprintf(item.StatusText, "�ϸߣ��Ƽ����м��");
				}
				pTJDlg->AddLine(&item);
			}
			m_nCurClass = TJ_CLASS_MEMORYUSAGE;
			break;
		case TJ_CLASS_MEMORYUSAGE: 
			//����ʹ����
			{
				CTJDlg::tagList_Item item = {1};
				sprintf(item.Caption, "����ʹ����:%d%%", m_Servers[m_nCurTJServer].networkusage);
				if (m_Servers[m_nCurTJServer].networkusage < 50)
				{
					item.Status = TRUE;
					sprintf(item.StatusText, "����");
				}
				else
				{
					item.Status = FALSE;
					sprintf(item.StatusText, "�ϸߣ��Ƽ����м��");
				}
				pTJDlg->AddLine(&item);
			}
			m_nCurClass = TJ_CLASS_NETWORKUSAGE;
			break;
		case TJ_CLASS_NETWORKUSAGE: 
			if (int Driver = m_Servers[m_nCurTJServer].Disk[0].Driver)
			{
				//����IO�ٶ�
				{
					CTJDlg::tagList_Item item = {1};
					sprintf(item.Caption, "����IO�ٶ�");
					pTJDlg->AddLine(&item);
				}
				{
					CTJDlg::tagList_Item item = {2};
					sprintf(item.Caption, "%C:��ȡ����ƽ���ٶ�:%.2fMB/S", 
						Driver, m_Servers[m_nCurTJServer].Disk[0].speed);
					if (m_Servers[m_nCurTJServer].Disk[0].speed > 50.0f)
					{
						item.Status = TRUE;
						sprintf(item.StatusText, "����");
					}
					else
					{
						item.Status = FALSE;
						sprintf(item.StatusText, "�ٶȽ������Ƽ���������");
					}
					pTJDlg->AddLine(&item);
				}

			}
			else
			{
			}
			m_nCurClass = TJ_CLASS_DISKIOSPEED;
			m_nCurTJDisk = 0;
			break;
		case TJ_CLASS_DISKIOSPEED: {
			m_nCurTJDisk++;
			int Driver = 0;
			if (m_nCurTJDisk < _countof(m_Servers[m_nCurTJServer].Disk))
				Driver = m_Servers[m_nCurTJServer].Disk[m_nCurTJDisk].Driver;
			if (Driver)
			{
				//��һ������
				{
					CTJDlg::tagList_Item item = {2};
					sprintf(item.Caption, "%C:��ȡ����ƽ���ٶ�:%.2fMB/S", 
						Driver, m_Servers[m_nCurTJServer].Disk[m_nCurTJDisk].speed);
					if (m_Servers[m_nCurTJServer].Disk[m_nCurTJDisk].speed > 50.0f)
					{
						item.Status = TRUE;
						sprintf(item.StatusText, "����");
					}
					else
					{
						item.Status = FALSE;
						sprintf(item.StatusText, "�ٶȽ������Ƽ���������");
					}
					pTJDlg->AddLine(&item);
				}
			}
			else
			{
				//���ݿ��Զ�����
				{
					CTJDlg::tagList_Item item = {1};
					time_t t = m_Servers[m_nCurTJServer].LastBackupDatabaseTime;
					if (t)
					{
						tm *tm = ::localtime(&t);
						sprintf(item.Caption, 
							"�Զ��������ݿ�(�ϴα���:"
							"%04d/%02d/%02d %02d:%02d:%02d)",
							tm->tm_year + 1900, 
							tm->tm_mon + 1, 
							tm->tm_mday, 
							tm->tm_hour, 
							tm->tm_min, 
							tm->tm_sec);
					}
					else
					{
						sprintf(item.Caption, "�Զ��������ݿ�");
					}
					item.Status = TRUE;
					sprintf(item.StatusText, "������");
					pTJDlg->AddLine(&item);
				}

				m_nCurTJServer++; //��һ��������
				m_nCurClass = TJ_CLASS_MAINSERVER;
			}
			break; }
		default:
			m_nCurTJServer++; //��һ��������
			m_nCurClass = TJ_CLASS_MAINSERVER;
			break;
		}
		break;
	default:
		if (m_nCurTJServer >= m_nServer)
		{
			if (!pTJDlg->m_bIsOnlyView)
				m_nJK = CalcJKZS();
			pTJDlg->TJOver(m_nJK);

			tm *tm = ::_localtime32(&m_ServerMedicalTime);
			CString strServerMedicalTime;
			strServerMedicalTime.Format(
				"%04d/%02d/%02d %02d:%02d:%02d",
				tm->tm_year + 1900, 
				tm->tm_mon + 1, 
				tm->tm_mday, 
				tm->tm_hour, 
				tm->tm_min, 
				tm->tm_sec);
			UpdateJKZS(m_nJK, strServerMedicalTime);
			return TRUE;
		}
		switch (m_nCurClass)
		{
		case TJ_CLASS_MAINSERVER: {
			//��������
			{
				CTJDlg::tagList_Item item = {0};
				sprintf_s(item.Caption, "%s", m_Servers[m_nCurTJServer].HostName);
				pTJDlg->AddLine(&item);
			}

			CFormCtrl::tagDisk& disk = m_Servers[m_nCurTJServer].Disk[0];
			if (int Driver = disk.Driver)
			{
				//���̿ռ�
				{
					CTJDlg::tagList_Item item = {1, "���̿ռ�" };
					pTJDlg->AddLine(&item);
				}

				//��һ������
				{
					CTJDlg::tagList_Item item = {2};
					float fFreeSpace = disk.total - disk.userd;
					sprintf(item.Caption, "%C:���̿���:%.2fG", Driver, fFreeSpace);
					if (fFreeSpace > 30.0f)
					{
						item.Status = TRUE;
						sprintf(item.StatusText, "����");
					}
					else
					{
						item.Status = FALSE;
						sprintf(item.StatusText, "�ռ䲻�㣬�Ƽ���������");
					}
					pTJDlg->AddLine(&item);
				}

				m_nCurClass = TJ_CLASS_DISKSPACE;
				m_nCurTJDisk = 0;
			}
			else
			{
				//���״̬
				{
					CTJDlg::tagList_Item item = {1, "���״̬" };
					pTJDlg->AddLine(&item);
				}

				//��һ�����״̬
				{
					CTJDlg::tagList_Item item = {2};
					sprintf(item.Caption, "�������", Driver);
					item.Status = m_Servers[m_nCurTJServer].MainServer == 1;
					sprintf(item.StatusText, GetModuleStatusDesc(m_Servers[m_nCurTJServer].MainServer));
					pTJDlg->AddLine(&item);
				}

				m_nCurClass = TJ_CLASS_MODULESTATUS;
				m_nCurModule = TJ_MODULE_MAIN;
			}
			break; }
		case TJ_CLASS_DISKSPACE: {
			m_nCurTJDisk++;
			int Driver = 0;
			if (m_nCurTJDisk < _countof(m_Servers[m_nCurTJServer].Disk))
				Driver = m_Servers[m_nCurTJServer].Disk[m_nCurTJDisk].Driver;
			if (Driver)
			{
				//��һ������
				CFormCtrl::tagDisk& disk = m_Servers[m_nCurTJServer].Disk[m_nCurTJDisk];
				{
					CTJDlg::tagList_Item item = {2};
					float fFreeSpace = disk.total - disk.userd;
					sprintf(item.Caption, "%C:���̿���:%.2fG", Driver, fFreeSpace);
					if (fFreeSpace > 30.0f)
					{
						item.Status = TRUE;
						sprintf(item.StatusText, "����");
					}
					else
					{
						item.Status = FALSE;
						sprintf(item.StatusText, "�ռ䲻�㣬�Ƽ���������");
					}
					pTJDlg->AddLine(&item);
				}
			}
			else
			{
				//���״̬
				{
					CTJDlg::tagList_Item item = {1, "���״̬" };
					pTJDlg->AddLine(&item);
				}

				m_nCurClass = TJ_CLASS_MODULESTATUS;
				m_nCurModule = TJ_MODULE_MAIN;
			}
			break; }
		case TJ_CLASS_MODULESTATUS: 
			m_nCurModule++;
			if (m_nCurModule <= TJ_MODULE_LAST)
			{
				switch (m_nCurModule)
				{
				case TJ_MODULE_VDISK:
					//һ�����״̬
					{
						CTJDlg::tagList_Item item = {2};
						sprintf(item.Caption, "���������");
						item.Status = m_Servers[m_nCurTJServer].VirtualDisk == 1;
						sprintf(item.StatusText, GetModuleStatusDesc(m_Servers[m_nCurTJServer].VirtualDisk));
						pTJDlg->AddLine(&item);
					}
					break;
				case TJ_MODULE_UPDATE:
					//һ�����״̬
					{
						CTJDlg::tagList_Item item = {2};
						sprintf(item.Caption, "�����������");
						item.Status = m_Servers[m_nCurTJServer].InnerUpdate == 1;
						sprintf(item.StatusText, GetModuleStatusDesc(m_Servers[m_nCurTJServer].InnerUpdate));
						pTJDlg->AddLine(&item);
					}
					break;
				case TJ_MODULE_SHOP:
					//һ�����״̬
					{
						CTJDlg::tagList_Item item = {2};
						sprintf(item.Caption, "�̳�������");
						item.Status = m_Servers[m_nCurTJServer].ShopCity == 1;
						sprintf(item.StatusText, GetModuleStatusDesc(m_Servers[m_nCurTJServer].ShopCity));
						pTJDlg->AddLine(&item);
					}
					break;
				}
			}
			else
			{
				//CPUռ����
				{
					CTJDlg::tagList_Item item = {1};
					sprintf(item.Caption, "CPUռ����:%d%%", m_Servers[m_nCurTJServer].cpuusage);
					if (m_Servers[m_nCurTJServer].cpuusage < 30)
					{
						item.Status = TRUE;
						sprintf(item.StatusText, "����");
					}
					else
					{
						item.Status = FALSE;
						sprintf(item.StatusText, "�ϸߣ��Ƽ����м��");
					}
					pTJDlg->AddLine(&item);
				}
				m_nCurClass = TJ_CLASS_CPUUSAGE;
			}
			break;
		case TJ_CLASS_CPUUSAGE: 
			//����ʹ����
			{
				CTJDlg::tagList_Item item = {1};
				sprintf(item.Caption, "�ڴ�ʹ����:%d%%", m_Servers[m_nCurTJServer].memoryusage);
				if (m_Servers[m_nCurTJServer].memoryusage < 90)
				{
					item.Status = TRUE;
					sprintf(item.StatusText, "����");
				}
				else
				{
					item.Status = FALSE;
					sprintf(item.StatusText, "�ϸߣ��Ƽ����м��");
				}
				pTJDlg->AddLine(&item);
			}
			m_nCurClass = TJ_CLASS_MEMORYUSAGE;
			break;
		case TJ_CLASS_MEMORYUSAGE: 
			//����ʹ����
			{
				CTJDlg::tagList_Item item = {1};
				sprintf(item.Caption, "����ʹ����:%d%%", m_Servers[m_nCurTJServer].networkusage);
				if (m_Servers[m_nCurTJServer].networkusage < 50)
				{
					item.Status = TRUE;
					sprintf(item.StatusText, "����");
				}
				else
				{
					item.Status = FALSE;
					sprintf(item.StatusText, "�ϸߣ��Ƽ����м��");
				}
				pTJDlg->AddLine(&item);
			}

			m_nCurTJServer++; //��һ��������
			m_nCurClass = TJ_CLASS_MAINSERVER;
			break;
		default:
			m_nCurTJServer++; //��һ��������
			m_nCurClass = TJ_CLASS_MAINSERVER;
			break;
		}
		break;
	}

	m_nTJProgress += 4;
	pTJDlg->SetCheckProgress(m_nTJProgress);

	return FALSE;
}

void CMonitorPage::OnJkzsCxtj()
{
	std::string ErrInfo;
	if (!GetConsoleDlg()->m_pDownloadMgr->NotifyServerMedical(ErrInfo))
	{
		AfxMessageBox(ErrInfo.c_str());
		return;
	}

	m_nJK = 0;
	m_nCurTJServer = 0;
	m_nCurClass = 0;
	m_nCurModule = 0;
	m_nCurTJDisk = 0;
	m_nTJProgress = 0;

	CTJDlg dlg(this, this);
	if (dlg.DoModal() == IDOK)
	{
	}
}

void CMonitorPage::OnJkzsView()
{
	m_nCurTJServer = 0;
	m_nCurClass = 0;
	m_nCurModule = 0;
	m_nCurTJDisk = 0;
	m_nTJProgress = 0;

	CTJDlg dlg(this, this);
	dlg.m_bIsOnlyView = TRUE;
	if (dlg.DoModal() == IDOK)
	{
	}
}

void CMonitorPage::HandleEvent(DWORD id, LPVOID p)
{
	switch (id)
	{
	case ID_JKZS_CXTJ:
		OnJkzsCxtj();	
		break;
	case ID_JKZS_VIEW:
		OnJkzsView();
		break;
		
    case ID_SERVER_SVR1:
    case ID_SERVER_SVR2:
    case ID_SERVER_SVR3:
    case ID_SERVER_SVR4:
		break;
    case ID_CLIENT_CLITOTAL:
		GetConsoleDlg()->SelectPage(TN_MACHINE);
		break;
    case ID_CLIENT_ONLINECLI:
		ViewClientList(CClientListDlg::ONLINE);
		break;
    case ID_CLIENT_HYNOTUSE:
		ViewClientList(CClientListDlg::NORESTOREPROT);
		break;
    case ID_CLIENT_SAFENOTUSE:
		ViewClientList(CClientListDlg::NOSAFECENTER);
		break;
    case ID_CLIENT_IENOTPROT:
		ViewClientList(CClientListDlg::NOIEPROT);
		break;
    case ID_CLIENT_DOTNOTUSE:
		ViewClientList(CClientListDlg::NODOGPROT);
		break;
    case ID_CLIENT_HARDCHANGE:
		break;

    case ID_GAME_CENTERNUM:
		GetConsoleDlg()->SelectPage(TN_CENTER);
		break;
    case ID_GAME_NEWADDNUM:
		ViewGameList(CGameListDlg::IDCADDNODOWN);
		break;
    case ID_GAME_LOCALNUM:
		GetConsoleDlg()->SelectPage(TN_NETBAR);
		break;
    case ID_GAME_VIRTUAL:
		ViewGameList(CGameListDlg::RTVDISK);
		break;
    case ID_GAME_LOCALUPT:
		ViewGameList(CGameListDlg::RTLOCALUPDATE);
		break;
    case ID_GAME_DIRECTRUN:
		ViewGameList(CGameListDlg::RTDIRECTRUN);
		break;

    case ID_GAME_MATCHNUM:
		ViewGameList(CGameListDlg::MATCH);
		break;
    case ID_GAME_HAVEUPT:
		GetConsoleDlg()->SelectPage(TN_NEEDUPDATE);
		break;
    case ID_GAME_THIRDLIST:
		GetConsoleDlg()->SelectPage("ʵʱ���", "�������");
		break;
    case ID_GAME_THIRDSPEED:
		GetConsoleDlg()->SelectPage("ʵʱ���", "�������");
		break;
    case ID_GAME_INNERLIST:
		GetConsoleDlg()->SelectPage("ʵʱ���", "��������");
		break;
	case ID_GAME_INNERSPEED:
		GetConsoleDlg()->SelectPage("ʵʱ���", "��������");
		break;
	default:
		break;
	}
}
