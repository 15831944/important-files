// GameInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Console.h"
#include "GameInfoDlg.h"
#include "BrowseDirDlg.h"

#include <assert.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif // _DEBUG


//ATL::CAutoVectorPtr<std::pair<std::wstring, i8desk::GameInfo_Ptr>> CGameInfoDlg::m_pStrDatabaseGame;

std::pair<std::wstring, i8desk::GameInfo_Ptr> CGameInfoDlg::m_pStrDatabaseGame[3000];


CString CGameInfoDlg::GetGameClass(i8desk::GameInfo *pGameInfo)
{
	i8desk::DefClassMapItr it = m_ClassInfos.find(pGameInfo->DefClass);
	if (it != m_ClassInfos.end())
		return CString(it->second->Name);
	return CString("");
}

std::string CGameInfoDlg::GetAIDByName(const std::string& Name)
{
	for (i8desk::AreaInfoMapItr it = m_AreaInfos.begin();
		it != m_AreaInfos.end(); it ++) 
	{
		if (Name == it->second->Name) {
			return it->first;
		}
	}
	return "";
}

CString CGameInfoDlg::GetAreaRTText(const std::string& AreaName, i8desk::GameRunTypeList& RunType)
{
	for (i8desk::GameRunTypeListItr it = RunType.begin(); 
		it != RunType.end(); it ++)
	{
		if (it->AreaName == AreaName)
		{
			switch (it->RunType)
			{
			case 0:
				return RT_UNKNOWN;
			case 1:
				return RT_LOCAL;
			case 3:
				return RT_DIRECT;
			case 2:
				{
					i8desk::VDiskInfoMapItr VIt = m_VDiskInfos.begin();
					for (; VIt != m_VDiskInfos.end(); VIt++)
					{
						if (strcmp(VIt->second->VID, it->VID) == 0)
						{
							CString info;
							if (VIt->second->Type == VDISK_I8DESK)
							{
								info.Format("%s%c (%s:%C)",
									RT_VDISK,
									(char)VIt->second->CliDrv,
									i8desk::MakeIpString(VIt->second->IP).c_str(),
									(char)VIt->second->SvrDrv);
							}
							else
							{
								info.Format("%s%C", RT_VDISK, (char)VIt->second->CliDrv);
							}
							return info;
						}
					}
				}
				break;
			}
		}
	}

	return RT_UNKNOWN;
}

CString CGameInfoDlg::GetAreaRunType(const std::string& aid, const CString& szAreaRunType)
{
	for (int nIdx=0; ;nIdx++)
	{
		CString Item;
		AfxExtractSubString(Item, szAreaRunType, nIdx, '|');
		if (Item.IsEmpty())
			break;
		CString szAid, szRunType;
		AfxExtractSubString(szAid, Item, 0, ',');
		AfxExtractSubString(szRunType, Item, 1, ',');
		if (szAid == aid.c_str())
		{
			if (szRunType == "0")
				return RT_UNKNOWN;
			else if (szRunType == "1")
				return RT_LOCAL;
			else if (szRunType == "3")
				return RT_DIRECT;
			else
			{
				i8desk::VDiskInfoMapItr it = m_VDiskInfos.find((LPCSTR)szRunType);
				if (it ==  m_VDiskInfos.end())
					return RT_UNKNOWN;
				else
				{
					CString info;
					if (it->second->Type == VDISK_I8DESK)
					{
						info.Format("%s%c (%s:%C)", RT_VDISK, (char)it->second->CliDrv,
							i8desk::MakeIpString(it->second->IP).c_str(), (char)it->second->SvrDrv);
					}
					else
					{
						info.Format("%s%C", RT_VDISK, (char)it->second->CliDrv);
					}
					return info;
				}
			}
		}
	}
	return RT_UNKNOWN;
}


BOOL CGameInfoDlg::ParaseAreaRTTexT(CString szText, i8desk::tagGameRunType& RtType)
{
	CLEAR_CHAR_ARRAY(RtType.VID);

	int nLen = lstrlen(RT_VDISK);
	RtType.RunType = 0;
	if (szText == RT_UNKNOWN)
	{
		RtType.RunType = 0;
		return TRUE;
	}
	else if (szText == RT_LOCAL) {
		RtType.RunType = 1;
		return TRUE;
	}
	else if (szText == RT_DIRECT) {
		RtType.RunType = 3;
		return TRUE;
	}
	else if (szText.Left(nLen) == RT_VDISK && szText.GetLength() > nLen) {
		RtType.RunType = 2;
		char CliDrv = szText.GetAt(nLen);
		i8desk::VDiskInfoMapItr it = m_VDiskInfos.begin();
		for (; it != m_VDiskInfos.end(); it++) {
			if (it->second->CliDrv == CliDrv) {
				strcpy(RtType.VID, it->second->VID);
				return TRUE;
			}
		}
	}
	return TRUE;
}


IMPLEMENT_DYNAMIC(CGameInfoDlg, CDialog)

CGameInfoDlg::CGameInfoDlg(CWnd* pParent /*=NULL*/)
: CDialog(CGameInfoDlg::IDD, pParent)
, m_strGameName(_T(""))
, m_strSvrPath(_T(""))
, m_strExecFile(_T(""))
, m_strCliPath(_T(""))
, m_bIsDrop(false)
, m_bAutoOk(false)
{
	m_hIcon = NULL;
	ZeroMemory(m_IconData, sizeof(m_IconData));
	m_dwIconSize = 0;
}

CGameInfoDlg::~CGameInfoDlg()
{
}


//
//ͨ���ļ���ȫ·������ȡ���ڵľ���·��
//
bool GetAbsDirName(std::string &str, const char *fullname)
{
	assert(fullname);

	str = fullname;

	size_t pos = str.find_last_of("\\");
	if (pos == std::string::npos) {
		return false; //��Ч��ȫ·����
	}
	str.erase(str.begin() + pos, str.end());

	return true;
}

//
//ͨ���ļ���ȫ·������ȡ����Ŀ¼������,�������ϲ�һ����Ŀ¼��
//
bool GetUpDirName(std::string &str, const char *fullname)
{
	assert(fullname);

	str = fullname;

	size_t pos = str.find_last_of("\\");
	if (pos == std::string::npos) {
		return false; //��Ч��ȫ·����
	}
	str.erase(str.begin() + pos, str.end());

	pos = str.find_last_of("\\");
	if (pos == std::string::npos) {
		return false; //��ʱ����Ϊ��Ŀ¼���ļ�c:\mygame.exe
	}
	str.erase(str.begin(), str.begin() + pos + 1);

	return true;
}



//
//ͨ����Ϸ��Ŀ¼��Ŀ¼�µ��ļ���������Ϸ��
//��Ϸ��ʼ��Ϊ��Ϸ��Ŀ¼��
//����ģ��: �Ϸ������Ϸ
//
BOOL CGameInfoDlg::SetGameFile(const tstring& strName)
{
	ASSERT(m_bIsDrop);
	LPCTSTR filename = strName.c_str();

	CFileFind finder;
	if (!finder.FindFile(filename))
		return FALSE;

	finder.FindNextFile();

	if (finder.IsDirectory()) {
		m_strGameName = finder.GetFileName();
		m_strSvrPath = m_strCliPath = finder.GetFilePath();
	} else {
		std::string dir;
		if (GetUpDirName(dir, filename))
			m_strGameName = dir.c_str();
		else 
			m_strGameName = finder.GetFileName();

		m_strExecFile = finder.GetFileName();

		GetAbsDirName(dir, filename);
		m_strSvrPath = m_strCliPath = dir.c_str();
	}

	//1. ����� �� ����̨ ��һ̨����ʱ��ͬ�������������ڵĹ�������̷��滻��
	//�������һ̨����ʱ����ת���� �ͻ���·��Ĭ��Ϊ�ͷ�����·��һ����
	//����Զ������Ҳ���滻�̷�
	CConsoleDlg *pMainWnd = reinterpret_cast<CConsoleDlg *>(AfxGetMainWnd());
	if (pMainWnd->IsRunOnServer()) {
		CString szDrv = pMainWnd->m_pDbMgr->GetOptString(OPT_M_GAMEDRV, "E").c_str();
		szDrv.MakeUpper();
		if (m_strCliPath.IsEmpty()) {
			m_strCliPath = szDrv + _T(":\\");
		} else if (!m_bAutoOk) {
			m_strCliPath.SetAt(0, szDrv[0]);
		}
	}

	return TRUE;
}

void CGameInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_TOOLBAR, m_btnToolbar);
	DDX_Control(pDX, IDC_DESKLNK, m_btnDeskLnk);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cboClass);
	DDX_Control(pDX, IDC_COMBO_PRIORITY, m_cboPriority);
	DDX_Control(pDX, IDC_GAMEICON, m_staGameIcon);
	DDX_Control(pDX, IDC_COMBO_AUTOUPT, m_cboAutoUpt);
	DDX_Control(pDX, IDC_LIST_RUNTYPE, m_lstRunType);
	DDX_Text(pDX, IDC_GAMENAME, m_strGameName);
	DDX_Text(pDX, IDC_SVRPATH, m_strSvrPath);
	DDX_Text(pDX, IDC_GAMEEXE, m_strExecFile);
	DDX_Text(pDX, IDC_CLIPATH, m_strCliPath);
	DDX_Control(pDX, IDC_COMBO_3UP_PRIORITY, m_cb3upPriority);
}

BEGIN_MESSAGE_MAP(CGameInfoDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CGameInfoDlg::OnBnClickedOk)
	ON_STN_CLICKED(IDC_GAMEICON, &CGameInfoDlg::OnStnClickedGameicon)
	ON_BN_CLICKED(IDC_BROWSE_DIR, &CGameInfoDlg::OnBnClickedBrowseDir)
	ON_BN_CLICKED(IDC_BROWSE_FILE, &CGameInfoDlg::OnBnClickedBrowseFile)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CGameInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	std::string ErrInfo;
	i8desk::CDbMgr* pDbMgr = reinterpret_cast<CConsoleDlg*>(AfxGetMainWnd())->m_pDbMgr;

	i8desk::GameRunTypeList lstRunType;
	if (!pDbMgr->GetAllClass(m_ClassInfos, ErrInfo) ||
		!pDbMgr->GetAllArea(m_AreaInfos, ErrInfo) ||
		!pDbMgr->GetGameRunType(m_GameInfo.GID, lstRunType, ErrInfo, m_AreaInfos) ||
		!pDbMgr->GetAllVDisk(m_VDiskInfos, ErrInfo))
	{
		AfxMessageBox(ErrInfo.c_str());
		OnCancel();
		return TRUE;
	}

	((CEdit*)GetDlgItem(IDC_GAMENAME))->LimitText(255);
	((CEdit*)GetDlgItem(IDC_SVRPATH))->LimitText(255);
	((CEdit*)GetDlgItem(IDC_GAMEEXE))->LimitText(255);
	((CEdit*)GetDlgItem(IDC_PARAMETER))->LimitText(255);
	((CEdit*)GetDlgItem(IDC_CLIPATH))->LimitText(255);
	((CEdit*)GetDlgItem(IDC_FILESAVE))->LimitText(255);
	((CEdit*)GetDlgItem(IDC_ASSOID))->LimitText(5);

	GetDlgItem(IDC_UPTDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_TYPE)->EnableWindow(m_GameInfo.GID < MIN_IDC_GID);
	GetDlgItem(IDC_COMBO_AUTOUPT)->EnableWindow(m_GameInfo.GID >= MIN_IDC_GID);

	//������
	m_cboClass.AddString(CLASS_WL_NAME);
	m_cboClass.AddString(CLASS_DJ_NAME);
	m_cboClass.AddString(CLASS_XX_NAME);
	m_cboClass.AddString(CLASS_WY_NAME);
	m_cboClass.AddString(CLASS_DZ_NAME);
	m_cboClass.AddString(CLASS_QP_NAME);
	m_cboClass.AddString(CLASS_PL_NAME);
	m_cboClass.AddString(CLASS_LT_NAME);
	m_cboClass.AddString(CLASS_CY_NAME);
	m_cboClass.AddString(CLASS_YY_NAME);
	m_cboClass.AddString(CLASS_GP_NAME);
	for (i8desk::DefClassMapItr it = 
		m_ClassInfos.begin(); it != m_ClassInfos.end(); it++)
	{
		if (!i8desk::IsI8DeskClassGUID(it->first))
			m_cboClass.AddString(it->second->Name);
	}

	m_cboAutoUpt.AddString("�Զ�����");
	m_cboAutoUpt.AddString("�ֶ�����");
	m_cboAutoUpt.SetCurSel(2);

	m_cboPriority.AddString("��:��ɾ");
	m_cboPriority.AddString("��:��ɾ");
	m_cboPriority.AddString("�ϸ�:�ݲ�ɾ");
	m_cboPriority.AddString("��:��ɾ");
	m_cboPriority.SetCurSel(2);

	SetDlgItemText(IDC_GAMENAME, m_GameInfo.Name);
	SetDlgItemText(IDC_SVRPATH,	 m_GameInfo.SvrPath);
	SetDlgItemText(IDC_GAMEEXE,	 m_GameInfo.GameExe);
	SetDlgItemText(IDC_PARAMETER,m_GameInfo.Param);
	SetDlgItemText(IDC_CLIPATH,	 m_GameInfo.CliPath);

	if (STRING_ISEMPTY(m_GameInfo.SaveFilter))
		SetDlgItemText(IDC_FILESAVE, m_GameInfo.SaveFilter2);
	else 
		SetDlgItemText(IDC_FILESAVE, m_GameInfo.SaveFilter);

	if (!m_bIsAdd)
		m_cboClass.SelectString(-1,  GetGameClass(&m_GameInfo));
	else
		m_cboClass.SelectString(-1, reinterpret_cast<CConsoleDlg*>(AfxGetMainWnd())->GetTreeSelNodeText());

	if (m_cboClass.GetCurSel() == -1)
		m_cboClass.SetCurSel(0);

	if (m_GameInfo.GID >= MIN_IDC_GID)
		m_cboAutoUpt.SetCurSel(m_GameInfo.AutoUpt ? 0 : 1);
	else
		m_cboAutoUpt.SetCurSel(1);
	if (!m_bIsAdd)
		m_cboPriority.SetCurSel(m_GameInfo.Priority-1);
	SetDlgItemText(IDC_UPTDATE, i8desk::MakeTimeString(m_GameInfo.SvrVer).c_str());

	SetDlgItemInt(IDC_ASSOID, m_GameInfo.PID);
	m_btnToolbar.SetCheck(m_GameInfo.Toolbar);
	m_btnDeskLnk.SetCheck(m_GameInfo.DeskLnk);

	if (!m_bIsAdd)
	{
		if (pDbMgr->GetIconData(m_GameInfo.GID, "", m_IconData, m_dwIconSize, ErrInfo))
			m_hIcon = i8desk::LoadIconFromBuffer(m_IconData, m_dwIconSize);
	}
	if (m_hIcon == NULL)
	{
		m_hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_AREAMGR));
		i8desk::SaveIconToBuffer(m_hIcon, reinterpret_cast<BYTE *>(m_IconData), m_dwIconSize);
	}
	m_staGameIcon.SetIcon(m_hIcon);	

	m_cb3upPriority.AddString(_T("���"));
	m_cb3upPriority.AddString(_T("�ϵ�"));
	m_cb3upPriority.AddString(_T("һ��"));
	m_cb3upPriority.AddString(_T("�ϸ�"));
	m_cb3upPriority.AddString(_T("���"));
	if (m_bIsAdd)
		m_cb3upPriority.SetCurSel(0);
	else 
		m_cb3upPriority.SetCurSel(m_GameInfo.DownPriority - 1);

	//�����ͷ���������һ�������У��ڣ��У���
	m_lstRunType.InsertHiddenLabelColumn();
	m_lstRunType.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lstRunType.InsertColumn(1, "����", LVCFMT_LEFT, 80);

	//�����Ͽ���������з�ʽ
	CGridColumnTraitCombo* pComboTrait = new CGridColumnTraitCombo;
	pComboTrait->SetStyle( pComboTrait->GetStyle() | CBS_DROPDOWNLIST);
	pComboTrait->AddItem(0, RT_UNKNOWN);
	pComboTrait->AddItem(1, RT_LOCAL);
	int loop = 2;
	for (i8desk::VDiskInfoMapItr it = m_VDiskInfos.begin();
		it != m_VDiskInfos.end(); it ++)
	{
		CString info;
		if (it->second->Type == VDISK_I8DESK)
		{
			info.Format("%s%c (%s:%C)", RT_VDISK, (char)it->second->CliDrv,
				i8desk::MakeIpString(it->second->IP).c_str(), (char)it->second->SvrDrv);
		}
		else
		{
			info.Format("%s%C", RT_VDISK, (char)it->second->CliDrv);
		}
		pComboTrait->AddItem(loop, info);
		loop ++;
	}
	pComboTrait->AddItem(loop, RT_DIRECT);

	m_lstRunType.InsertColumnTrait(2, "���з�ʽ", LVCFMT_LEFT, 200, 1, pComboTrait);

	//�����Ϸ��ÿ�����������з�ʽ
	m_lstRunType.InsertItem(m_lstRunType.GetItemCount(), DEFAULT_AREA_NAME);
	CString szRunType = pDbMgr->GetOptString(OPT_D_AREADEFRUNTYPE).c_str();
	m_lstRunType.SetItemText(0, 1, DEFAULT_AREA_NAME);

	if (!m_bAutoOk) {
		if (m_bIsAdd)
			m_lstRunType.SetItemText(0, 2, GetAreaRunType(DEFAULT_AREA_GUID, szRunType));
		else
			m_lstRunType.SetItemText(0, 2, GetAreaRTText(std::string(DEFAULT_AREA_NAME), lstRunType));
	}
	else {
		m_lstRunType.SetItemText(0, 2, RT_DIRECT);
	}

	i8desk::AreaInfoMapItr it = m_AreaInfos.begin();
	for (; it != m_AreaInfos.end(); it ++)
	{
		if (it->first != DEFAULT_AREA_GUID)
		{
			int nIdx = m_lstRunType.InsertItem(
				m_lstRunType.GetItemCount(), it->second->Name);
			m_lstRunType.SetItemText(nIdx, 1, it->second->Name);
			if (!m_bAutoOk) {
				if (m_bIsAdd)
					m_lstRunType.SetItemText(nIdx, 2, GetAreaRunType(it->first, szRunType));
				else {
					m_lstRunType.SetItemText(nIdx, 2, GetAreaRTText(it->second->Name, lstRunType));
				}
			}
			else {
				//�Զ����ʱ���ò����£�ֱ������
				m_lstRunType.SetItemText(nIdx, 2, RT_DIRECT);
			}
		}
	}
	CenterWindow();

	//�Ϸ������Ϸʱ��Ҫ����ĳ�ʼ��
	if (m_bIsDrop) {
		if (!InitGameInfoForDrop()) {
			OnCancel();
			return TRUE;
		}
		UpdateData( FALSE );
	}

	if (m_bAutoOk) {
		this->OnBnClickedOk();
	}

	return TRUE;
}

// ����ת��
const wchar_t BChar[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
const wchar_t AChar[] = {L'��', L'��', L'��', L'��', L'��', L'��', L'��', L'��', L'��', L'��'};
const std::wstring Roman[] = {L"I", L"II", L"III", L"IV", L"V", L"VI", L"VII", L"VIII", L"IX"};

// ת����Ϸ����
void Transform(std::wstring &strSrc)
{
	// ȥ���ո�
	std::wstring::iterator iter = std::remove_if(strSrc.begin(), strSrc.end(), 
		std::bind2nd(std::equal_to<wchar_t>(), ' '));
	strSrc.erase(iter, strSrc.end());

	// ��ȫ�ǰ���������ת��Ϊ��ǰ���������
	struct MatchDBC
		: public std::unary_function<std::wstring, void>
	{
		argument_type &m_arg;

		MatchDBC(argument_type &arg)
			: m_arg(arg)
		{}

		result_type operator()(wchar_t &val)
		{
			for(int i = 0; i != _countof(AChar); ++i)
			{
				if( val == AChar[i] )
				{
					val = BChar[i];
					break;
				}
			}
		}
	};

	std::for_each(strSrc.begin(), strSrc.end(), MatchDBC(strSrc));


	// ����������ת��Ϊ����������
	/*for(int i = _countof(Roman) - 1; i >= 0; --i)
	{
		std::wstring::size_type nPos = strSrc.find(Roman[i]);

		if( nPos != std::wstring::npos )
		{
			std::wstring str(1, BChar[i]);
			strSrc.replace(nPos, Roman[i].length(), str);
		}
	}*/

	static std::wstring str(L"����2");
	if( strSrc == str )
	{
		strSrc = L"����II";
	}

}



//�Ϸ������Ϸʱ����ĳ�ʼ������
BOOL CGameInfoDlg::InitGameInfoForDrop()
{
	ASSERT(m_bIsDrop && !m_strGameName.IsEmpty());

	//�����ݿ��в�����Ϸ,�ҵ������ݿ���������ʼ����Ϸ��Ϣ
	CConsoleDlg* pMainWnd = reinterpret_cast<CConsoleDlg*>(AfxGetMainWnd());
	{
		extern i8desk::CLock g_Lock;
		i8desk::CAutoLock<i8desk::CLock> lock(&g_Lock);

		i8desk::GameInfo_Ptr pGameInfo;

		static bool bFirst = true;
		static size_t nCount = 0;

		// ��һ����Ҫת�����ݿ���Ϸ����
		if( bFirst )
		{
			nCount = pMainWnd->m_GameInfos.size();
			//m_pStrDatabaseGame.Allocate(nCount);

			i8desk::GameInfoMapItr it = pMainWnd->m_GameInfos.begin();

			size_t i = 0;
			for (; it != pMainWnd->m_GameInfos.end(); ++it) 
			{
				std::wstring strGame = CT2W(it->second->Name);
				Transform(strGame);
				m_pStrDatabaseGame[i].first	 = strGame;
				m_pStrDatabaseGame[i].second = it->second;	

				++i;
			}

			bFirst = false;
		}

		// ת��Ŀ����Ϸ����
		std::wstring strCurGame = CT2W(m_strGameName);
		Transform(strCurGame);

		// �Ƚ�
		for(size_t i = 0; i != nCount; ++i)
		{
			if( m_pStrDatabaseGame[i].first == strCurGame )
			{
				pGameInfo = m_pStrDatabaseGame[i].second;

				m_bIsAdd = false;
				break;
			}
		}


		if (!pGameInfo) {
			HICON hIcon = i8desk::LoadIconFromFile((LPCTSTR)(m_strSvrPath + _T("\\") + m_strExecFile));
			if (hIcon) 
			{
				if (m_hIcon) 
				{
					::DestroyIcon(m_hIcon);
				}
				m_hIcon = hIcon;
				i8desk::SaveIconToBuffer(m_hIcon, reinterpret_cast<BYTE *>(m_IconData), m_dwIconSize);
				m_staGameIcon.SetIcon(m_hIcon);	
			}
			return TRUE; //���ڲ����ڴ���Ϸ
		}

		if (pGameInfo->Status) {
			if (!m_bAutoOk) {
				CString str;
				str.Format(_T("��Ϸ<<%s>>��ӹ�,��ʹ����Ϸ�޸Ĺ���!"), m_strGameName);
				AfxMessageBox(str);
			}
			return FALSE; //�Ѿ���ӹ�
		}

		m_GameInfo = *pGameInfo;
	}

	if (m_GameInfo.GID >= MIN_IDC_GID)
		m_GameInfo.AutoUpt = TRUE;

	m_cboClass.SelectString(-1,  GetGameClass(&m_GameInfo));
	if (m_cboClass.GetCurSel() == -1)
		m_cboClass.SetCurSel(0);

	if (m_GameInfo.GID >= MIN_IDC_GID)
		m_cboAutoUpt.SetCurSel(m_GameInfo.AutoUpt ? 0 : 1);
	else
		m_cboAutoUpt.SetCurSel(1);

	m_cboPriority.SetCurSel(m_GameInfo.Priority-1);
	m_cb3upPriority.SetCurSel(m_GameInfo.DownPriority-1);
	SetDlgItemText(IDC_UPTDATE, i8desk::MakeTimeString(m_GameInfo.SvrVer).c_str());

	SetDlgItemInt(IDC_ASSOID, m_GameInfo.PID);
	m_btnToolbar.SetCheck(m_GameInfo.Toolbar);
	m_btnDeskLnk.SetCheck(m_GameInfo.DeskLnk);

	if (!m_strExecFile.IsEmpty())
	{
		i8desk::SAFE_STRCPY(m_GameInfo.GameExe, (LPCTSTR)m_strExecFile);
		SetDlgItemText(IDC_GAMEEXE,	 m_GameInfo.GameExe);
	}

	//������Ϸ��ͼ��
	std::string ErrInfo;
	if (pMainWnd->m_pDbMgr->GetIconData(m_GameInfo.GID,
		(const char *)(m_strSvrPath + _T("\\") + m_strExecFile),
		m_IconData, m_dwIconSize, ErrInfo)) 
	{
		if (m_hIcon) {
			::DestroyIcon(m_hIcon);
			m_hIcon = 0;
		}
		m_hIcon = i8desk::LoadIconFromBuffer(m_IconData, m_dwIconSize);
	} 
	else 
	{
		HICON hIcon = i8desk::LoadIconFromFile((LPCTSTR)(m_strSvrPath + _T("\\") + m_strExecFile));
		if (hIcon) {
			if (m_hIcon) {
				::DestroyIcon(m_hIcon);
			}
			m_hIcon = hIcon;
			i8desk::SaveIconToBuffer(m_hIcon, reinterpret_cast<BYTE *>(m_IconData), m_dwIconSize);
		}
	}
	m_staGameIcon.SetIcon(m_hIcon);	
	//*/

	return TRUE;
}


static char s_buf[MAX_PATH] = {0};	//����������Ŀ¼.

static int CALLBACK   SetSelect_CB(HWND   win,   UINT   msg,   LPARAM   param,   LPARAM   data)   
{   
	if (msg == BFFM_INITIALIZED)
	{
		::SendMessage(win, BFFM_SETSELECTION, TRUE, (LPARAM)s_buf);
	}
	return 0;
}   

CString CGameInfoDlg::OpenLocMachineDir()
{
	BROWSEINFO info;
	memset(&info, 0, sizeof(info));
	info.hwndOwner = m_hWnd;
	info.lpszTitle = "ѡ����Ϸ�ĸ�Ŀ¼:";
	CString xPath;
	GetDlgItemText(IDC_SVRPATH, xPath);
	if (!xPath.IsEmpty())
		lstrcpy(s_buf, xPath);
	//GetDlgItemText(IDC_SVRPATH, s_buf, MAX_PATH);
	info.lpfn = SetSelect_CB;

	LPITEMIDLIST lst = SHBrowseForFolder(&info);
	if (lst != NULL)
	{
		SHGetPathFromIDList(lst, s_buf);
		LPMALLOC pMalloc = NULL;
		SHGetMalloc(&pMalloc);
		pMalloc->Free(lst);
		pMalloc->Release();
		return s_buf;
	}
	return "";	
}

CString CGameInfoDlg::OpenRemMachineDir()
{
	CBrowseDirDlg dlg;
	GetDlgItemText(IDC_SVRPATH, dlg.m_strDirOrFile);
	dlg.m_strDirOrFile;
	if (dlg.DoModal() == IDOK)
		return dlg.m_strDirOrFile;
	return "";
}

void CGameInfoDlg::OnBnClickedBrowseDir()
{
	CConsoleDlg* pDlg = reinterpret_cast<CConsoleDlg*>(AfxGetMainWnd());
	//CString szDir = pDlg->IsLocMachineIP() ?  OpenLocMachineDir() : OpenRemMachineDir();
	CString szDir = OpenLocMachineDir();

	if (szDir.IsEmpty())
		return ;

	if (szDir.Right(1) == "\\")
		szDir.Delete(szDir.GetLength()-1);
	int pos = szDir.ReverseFind('\\');
	if (pos != -1)
	{
		SetDlgItemText(IDC_GAMENAME, szDir.Mid(pos + 1));
	}
	szDir += "\\";
	szDir.Trim();
	SetDlgItemText(IDC_SVRPATH, szDir);

	//1. ����� �� ����̨ ��һ̨����ʱ��ͬ�������������ڵĹ�������̷��滻��
	//�������һ̨����ʱ����ת���� �ͻ���·��Ĭ��Ϊ�ͷ�����·��һ����	
	if (szDir.GetLength() > 1 && pDlg->IsRunOnServer()) {
		szDir.SetAt(0, pDlg->m_pDbMgr->GetOptString(OPT_M_GAMEDRV, "E")[0]);
	}
	SetDlgItemText(IDC_CLIPATH, szDir);
}

CString CGameInfoDlg::BrowseLocFile(CString szDir)
{
	CFileDialog Open(TRUE, "", "", 4|2, "�����ļ�(*.*)|*.*||");	
	Open.m_ofn.lpstrInitialDir = szDir;
	if (Open.DoModal() == IDOK)
	{
		return Open.GetPathName();
	}
	return "";
}

CString CGameInfoDlg::BrowseRemFile(CString szDir)
{
	CBrowseDirDlg dlg;
	dlg.m_bBrowseDir = FALSE;
	dlg.m_strDirOrFile = szDir;
	if (dlg.DoModal() == IDOK)
		return dlg.m_strDirOrFile;
	return "";
}

void CGameInfoDlg::OnBnClickedBrowseFile()
{
	CConsoleDlg* pDlg = reinterpret_cast<CConsoleDlg*>(AfxGetMainWnd());
	CString szDir;
	GetDlgItemText(IDC_SVRPATH, szDir);
	if (szDir.IsEmpty())
	{
		AfxMessageBox("����������Ϸ��Ŀ¼!");
		GetDlgItem(IDC_SVRPATH)->SetFocus();
		return ;
	}

	if (szDir.Right(1) == "\\")
		szDir.Delete(szDir.GetLength()-1);

	//CString szFileName = pDlg->IsLocMachineIP() ? BrowseLocFile(szDir) : BrowseRemFile(szDir);
	CString szFileName = BrowseLocFile(szDir);

	if (szFileName.IsEmpty())
		return ;
	if (szDir.Right(1) != "\\")
		szDir += "\\";

	if (szDir != szFileName.Left(szDir.GetLength()))
	{
		AfxMessageBox("��Ϸִ���ļ�����ϷĿ¼��һ��!");
		return ;
	}
	SetDlgItemText(IDC_GAMEEXE, szFileName.Mid(szDir.GetLength()));

	std::string ErrInfo;
	if (!pDlg->m_pDbMgr->GetIconData(m_GameInfo.GID,
		(LPCSTR)szFileName, m_IconData, m_dwIconSize, ErrInfo))
	{
		HICON hIcon = i8desk::LoadIconFromFile(szFileName);
		if (hIcon) {
			::DestroyIcon(m_hIcon);
			m_hIcon = hIcon;
			i8desk::SaveIconToBuffer(m_hIcon, reinterpret_cast<BYTE *>(m_IconData), m_dwIconSize);
			m_staGameIcon.SetIcon(m_hIcon);	
		}
	}
	else
	{
		if (m_hIcon != NULL)
			DestroyIcon(m_hIcon);
		m_hIcon = i8desk::LoadIconFromBuffer(m_IconData, m_dwIconSize);
		if (m_hIcon != NULL)
		{
			m_staGameIcon.SetIcon(m_hIcon);
		}
	}
}

void CGameInfoDlg::OnStnClickedGameicon()
{
	CConsoleDlg* pDlg = reinterpret_cast<CConsoleDlg*>(AfxGetMainWnd());
	if (1) //pDlg->IsLocMachineIP())
	{
		CString szFilter = "��ִ���ļ�(*.exe,*.com)|*.exe; *.com; *.bat|��ݷ�ʽ(*.lnk)|*.lnk|�����ļ�(*.*)|*.*||";
		CFileDialog openFile(TRUE, "", "", OFN_HIDEREADONLY, szFilter, NULL);
		CString szDir;
		GetDlgItemText(IDC_SVRPATH, szDir);
		openFile.m_ofn.lpstrInitialDir = szDir;
		if (openFile.DoModal() == IDOK)
		{
			CString szFileName;
			if (openFile.GetFileExt().CompareNoCase("lnk") == 0)
			{
				IShellLink* pIShellLink = NULL;
				IPersistFile* pIPersistFile = NULL;

				CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, 
					IID_IShellLink, (LPVOID*)&pIShellLink);
				pIShellLink->QueryInterface(IID_IPersistFile, (LPVOID*)&pIPersistFile);
				_bstr_t path(openFile.GetPathName());
				pIPersistFile->Load(path, STGM_READ | STGM_WRITE);

				pIShellLink->GetPath(szFileName.GetBuffer(MAX_PATH), MAX_PATH, NULL, 0);
				szFileName.ReleaseBuffer();

				pIPersistFile->Release();
				pIShellLink->Release();
			}
			else
			{
				szFileName = openFile.GetPathName();
			}
			if (m_hIcon != NULL) 
				DestroyIcon(m_hIcon);


			m_hIcon = i8desk::LoadIconFromFile(szFileName);
			if (m_hIcon == NULL)
			{
				if (GetFileAttributes(szFileName) & FILE_ATTRIBUTE_DIRECTORY)
				{
					m_hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));	
				}
				else
				{
					m_hIcon = i8desk::LoadIconFromFile(szFileName);
				}
			}
			m_staGameIcon.SetIcon(m_hIcon);
			i8desk::SaveIconToBuffer(m_hIcon, reinterpret_cast<BYTE *>(m_IconData), m_dwIconSize);
		}
	}
	else
	{
		CString path;
		GetDlgItemText(IDC_SVRPATH, path);
		if (path.IsEmpty())
		{
			AfxMessageBox("������������·��.");
			return ;
		}
		path = BrowseRemFile(path);
		if (path.IsEmpty())
			return ;
		if (m_hIcon != NULL)
		{
			DestroyIcon(m_hIcon);
			m_hIcon = NULL;
		}
		std::string ErrInfo;
		if (!pDlg->m_pDbMgr->GetIconData(m_GameInfo.GID, 
			(LPCSTR)path, m_IconData, m_dwIconSize, ErrInfo))
		{
			AfxMessageBox(ErrInfo.c_str());
		}
		else
		{
			m_hIcon = i8desk::LoadIconFromBuffer(m_IconData, m_dwIconSize);
		}
		if (m_hIcon != NULL)
		{
			m_staGameIcon.SetIcon(m_hIcon);
		}
	}
}

void CGameInfoDlg::OnDestroy()
{
	if (m_hIcon)
		DestroyIcon(m_hIcon);

	m_ClassInfos.clear();
	m_AreaInfos.clear();
	m_VDiskInfos.clear();

	CDialog::OnDestroy();
}

void CGameInfoDlg::OnBnClickedOk()
{
	if (m_hIcon == NULL)
	{
		AfxMessageBox("û������ͼ��.");
		return ;
	}
	char buf[MAX_PATH] = {0};
	GetDlgItemText(IDC_GAMENAME, buf, MAX_PATH);
	i8desk::SAFE_STRCPY(m_GameInfo.Name, buf);
	i8desk::TrimString(m_GameInfo.Name);

	GetDlgItemText(IDC_SVRPATH,  buf, MAX_PATH);
	i8desk::SAFE_STRCPY(m_GameInfo.SvrPath, buf);
	i8desk::TrimString(m_GameInfo.SvrPath);

	GetDlgItemText(IDC_GAMEEXE,  buf, MAX_PATH);
	i8desk::SAFE_STRCPY(m_GameInfo.GameExe, buf);
	i8desk::TrimString(m_GameInfo.GameExe);

	GetDlgItemText(IDC_PARAMETER,buf, MAX_PATH);
	i8desk::SAFE_STRCPY(m_GameInfo.Param, buf);
	i8desk::TrimString(m_GameInfo.Param);

	GetDlgItemText(IDC_CLIPATH,  buf, MAX_PATH);
	i8desk::SAFE_STRCPY(m_GameInfo.CliPath, buf);
	i8desk::TrimString(m_GameInfo.CliPath);

	GetDlgItemText(IDC_FILESAVE, buf, MAX_PATH);
	//ֻ���������ù����û��޸���ȱʡֵ��д�뵽SaveFilter
	//�û������޸�SaveFilter2
	if (STRING_ISEMPTY(m_GameInfo.SaveFilter)) {
		if (strcmp(m_GameInfo.SaveFilter2, buf))
			i8desk::SAFE_STRCPY(m_GameInfo.SaveFilter, buf);
	}
	else
		i8desk::SAFE_STRCPY(m_GameInfo.SaveFilter, buf);

	i8desk::TrimString(m_GameInfo.SaveFilter);

	m_GameInfo.AutoUpt = (m_cboAutoUpt.GetCurSel() == 0);
	m_GameInfo.Priority = m_cboPriority.GetCurSel()+1;
	m_GameInfo.DownPriority = m_cb3upPriority.GetCurSel()+1;

	m_GameInfo.PID     = GetDlgItemInt(IDC_ASSOID);
	m_GameInfo.Toolbar = (m_btnToolbar.GetCheck() == BST_CHECKED);
	m_GameInfo.DeskLnk = (m_btnDeskLnk.GetCheck() == BST_CHECKED);

	int nSel = m_cboClass.GetCurSel();
	m_cboClass.GetLBText(nSel, buf);
	i8desk::DefClassMapItr it = m_ClassInfos.begin(); 
	for (; it != m_ClassInfos.end(); it++)
	{
		if (strcmp(it->second->Name, buf) == 0)
		{
			i8desk::SAFE_STRCPY(m_GameInfo.DefClass, it->first.c_str());
			break;
		}
	}	

	m_lstRT.resize(0);
	for (int nIdx=0;nIdx<m_lstRunType.GetItemCount(); nIdx++)
	{
		i8desk::tagGameRunType RtType;
		RtType.AreaName = m_lstRunType.GetItemText(nIdx, 1);
		strcpy(RtType.AID, GetAIDByName(RtType.AreaName).c_str());
		RtType.GID = m_GameInfo.GID;
		if (ParaseAreaRTTexT(m_lstRunType.GetItemText(nIdx, 2), RtType))
			m_lstRT.push_back(RtType);
	}
	if (STRING_ISEMPTY(m_GameInfo.Name))
	{
		AfxMessageBox("û��������Ϸ��!");
		((CEdit*)GetDlgItem(IDC_GAMENAME))->SetFocus();
		return ;
	}
	if (!i8desk::IsValidDirName(m_GameInfo.SvrPath))
	{
		AfxMessageBox("�����·������һ���Ϸ���·����.");
		((CEdit*)GetDlgItem(IDC_SVRPATH))->SetFocus();
		return ;
	}
	if (!i8desk::IsValidDirName(m_GameInfo.CliPath))
	{
		AfxMessageBox("�ͻ���·������һ���Ϸ���·����.");
		((CEdit*)GetDlgItem(IDC_CLIPATH))->SetFocus();
		return ;
	}
	if (STRING_ISEMPTY(m_GameInfo.GameExe))
	{
		AfxMessageBox("û��������Ϸ��ִ���ļ�!");
		((CEdit*)GetDlgItem(IDC_GAMEEXE))->SetFocus();
		return ;
	}

	CConsoleDlg* pDlg = reinterpret_cast<CConsoleDlg*>(AfxGetMainWnd());

	if (!STRING_ISEMPTY(m_GameInfo.SvrPath) && LAST_CHAR(m_GameInfo.SvrPath) != '\\')
		i8desk::SAFE_STRCAT(m_GameInfo.SvrPath, "\\");

	if (!STRING_ISEMPTY(m_GameInfo.CliPath) && LAST_CHAR(m_GameInfo.CliPath) != '\\')
		i8desk::SAFE_STRCAT(m_GameInfo.CliPath, "\\");

	CWaitCursor wc;
	if (!pDlg->ProcessAddModifyGame(&m_GameInfo, m_bIsAdd, m_bIsDrop)) {
		return ;
	}

	std::string ErrInfo;
	if (!pDlg->m_pDbMgr->SetGameRunType(m_GameInfo.GID, m_lstRT, ErrInfo) || 
		!pDlg->m_pDbMgr->AddIcon(m_GameInfo.GID, m_IconData, m_dwIconSize, ErrInfo))
	{
		AfxMessageBox(ErrInfo.c_str());
	}

	i8desk::AreaInfoMap AreaInfos;
	if (!pDlg->m_pDbMgr->GetAllArea(AreaInfos, ErrInfo)) {
		AfxMessageBox(ErrInfo.c_str());
		return;
	}

	pDlg->m_pDbMgr->GetGameRunType(m_GameInfo.GID,
		m_GameInfo.RunTypes, ErrInfo, AreaInfos);

	OnOK();
}