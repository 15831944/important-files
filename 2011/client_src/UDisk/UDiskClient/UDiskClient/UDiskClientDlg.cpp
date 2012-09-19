
// UDiskClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDiskClient.h"
#include "UDiskClientDlg.h"
#include "ReSetPasswordDlg.h"
#include "UserCusDlg.h"
#include "XZip.h"
#include "XUnzip.h"
#include "I8ClientOfflineFileLock.h"

// #ifdef _DEBUG
// #define new DEBUG_NEW
// #endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
void MekeFileTimeFromTime(DWORD dwTime, FILETIME& ft)
{

	struct tm* ptm = _gmtime32((const __time32_t*)&dwTime);
	if (ptm != NULL)
	{
		SYSTEMTIME st = {0};
		st.wYear = ptm->tm_year + 1900;
		st.wMonth = ptm->tm_mon + 1;
		st.wDay = ptm->tm_mday;
		st.wHour = ptm->tm_hour;
		st.wMinute = ptm->tm_min;
		st.wSecond = ptm->tm_sec;
		SystemTimeToFileTime(&st, &ft);
	}
}

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


// CUDiskClientDlg �Ի���




CUDiskClientDlg::CUDiskClientDlg(CWnd* pParent /*=NULL*/)
: CDialog(CUDiskClientDlg::IDD, pParent),m_Thread(NULL),m_pIconInfo(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	DWORD dwSize = BLOCK+sizeof(FileHeader)+sizeof(_packageheader)+MAX_PATH;
	m_pFileBuf = new char [dwSize];
	m_pSocket = theApp.m_pSocket;
	ZeroMemory(m_szPath,MAX_PATH);
}

void CUDiskClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_wndListCtrl);
	DDX_Control(pDX, IDC_PROGRESS1, m_profress);
	DDX_Control(pDX, IDC_LIST2, m_lstComment);
	DDX_Control(pDX, IDC_Tab, m_ctrlTab);
	DDX_Control(pDX, IDC_LIST3, m_wndGameList);
}

BEGIN_MESSAGE_MAP(CUDiskClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_MSG_PROGRESS,	&CUDiskClientDlg::DrawPorgress)
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, &CUDiskClientDlg::OnBnClickedButton2)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &CUDiskClientDlg::OnNMRClickList2)
	ON_COMMAND(ID_DowndCommFile, &CUDiskClientDlg::OnDowndcommfile)
	ON_NOTIFY(CTCN_SELCHANGE,IDC_Tab,OnSelchangeTab)
	ON_BN_CLICKED(BTN_INFO, &CUDiskClientDlg::OnBnClickedInfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST3, &CUDiskClientDlg::OnNMRClickList3)
	ON_COMMAND(IDM_DeleteRecord, &CUDiskClientDlg::OnDeleteGameRecord)
	ON_COMMAND(IDM_ReadRecord, &CUDiskClientDlg::OnReadrecord)
	ON_MESSAGE(WM_MSG_SAVEGAME,SaveGameRecord)
	ON_MESSAGE(WM_MSG_READGAME,ReadGamerRecord)
END_MESSAGE_MAP()


// CUDiskClientDlg ��Ϣ�������

BOOL CUDiskClientDlg::OnInitDialog()
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
	theApp. SetMainHWnd(this->m_hWnd);

	ShowWindow(SW_SHOW);
	//CenterWindow();
	m_Thread = (HANDLE)_beginthreadex(NULL,0,WorkThread,this,0,&m_threadID);
	init();
	try
	{
		DWORD gid = atol(theApp.m_lpCmdLine);
		char* ptr = strstr(theApp.m_lpCmdLine,"|");
		if(ptr)
		{
			*ptr++ = '\0';
			gid = atol(theApp.m_lpCmdLine);
			::PostMessage(m_hWnd,*ptr=='1'?WM_MSG_SAVEGAME:WM_MSG_READGAME,gid,0);
		}
	}
	catch(...)
	{
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
bool CUDiskClientDlg::DrawFileList()
{
	GetFileLst(NET_CMD_GETUDISKINFO,m_vecLstPersion);
	GetFileLst(NET_CMD_GETCOMMENTRES,m_vecLstComment);
	m_dwUsedRoom = 0;
	m_wndListCtrl.DeleteAllItems();
	for(size_t i=0; i<m_vecLstPersion.size();i++)
	{
		int count  = m_wndListCtrl.GetItemCount();
		m_wndListCtrl.InsertItem(count,m_vecLstPersion[i].filename.c_str(),0);
		CString strsize;
		strsize.Format("%d KB",(int)ceil(m_vecLstPersion[i].filesize/(double)1024));
		m_wndListCtrl.SetItemText(count,1,strsize);
		FILETIME ft1,ft;
		MekeFileTimeFromTime(m_vecLstPersion[i].dwTime,ft1);
		FileTimeToLocalFileTime(&ft1,&ft);
		CTime t(ft);
		CString strTime;
		strTime.Format("%4d-%02d-%02d %02d:%02d:%02d",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
		m_wndListCtrl.SetItemText(count,2,strTime);
		m_dwUsedRoom += m_vecLstPersion[i].filesize;
	}
	m_lstComment.DeleteAllItems();
	for(size_t i=0; i<m_vecLstComment.size();i++)
	{
		int count  = m_lstComment.GetItemCount();
		m_lstComment.InsertItem(count,m_vecLstComment[i].filename.c_str(),0);
		CString strsize;
		strsize.Format("%d KB",(int)ceil(m_vecLstComment[i].filesize/(double)1024));
		m_lstComment.SetItemText(count,1,strsize);
	}
	UpdataStatic();
	return true;

}
bool CUDiskClientDlg::init()
{
	m_ImageList.Create(32,32,ILC_COLOR32 ,10,1);
	m_wndGameList.ShowWindow(SW_HIDE);
	m_lstComment.ShowWindow(SW_HIDE);

	RECT rt = {0};
	m_wndListCtrl.GetWindowRect(&rt);
	ScreenToClient(&rt);
//	m_wndListCtrl.MoveWindow(&rt,TRUE);
	m_wndGameList.MoveWindow(&rt,TRUE);
	m_lstComment.MoveWindow(&rt,TRUE);
	m_wndGameList.SetImageList(&m_ImageList,LVSIL_SMALL);

	m_ctrlTab.ModifyStyle(0,CTCS_AUTOHIDEBUTTONS,0);
	m_ctrlTab.InsertItem(0,"���˴洢��");
	m_ctrlTab.SetItemData(0,0);

	m_ctrlTab.InsertItem(1,"��Ϸ�浵��");
	m_ctrlTab.SetItemData(1,1);
	m_ctrlTab.InsertItem(2,"�����洢��");
	m_ctrlTab.SetItemData(2,2);

	m_ctrlTab.SetCurSel(0);
	LOGFONT lf = {13, 0, 0, 0, FW_NORMAL, 0, 0, 0,
		DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "����"};

	m_ctrlTab.SetControlFont(lf, TRUE);


	OutputDebugString("step 0");
	m_Imagelst.Create(32,32,ILC_COLOR32|ILC_MASK ,1,1);
	HICON icon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1));
	m_Imagelst.Add(icon);
	DestroyIcon(icon);
	m_wndListCtrl.ModifyStyle(0,LVS_REPORT);
	m_lstComment.ModifyStyle(0,LVS_REPORT);
	m_wndGameList.ModifyStyle(0,LVS_REPORT);
	m_wndListCtrl.SetImageList(&m_Imagelst,LVSIL_SMALL);
	m_lstComment.SetImageList(&m_Imagelst,LVSIL_SMALL);
	m_wndListCtrl.InsertColumn(0,_T("�ļ���"),LVCFMT_LEFT,250);
	m_wndListCtrl.InsertColumn(1,_T("�ļ���С"),LVCFMT_LEFT,100);
	m_wndListCtrl.InsertColumn(2,_T("�ϴ�ʱ��"),LVCFMT_LEFT,160);
	m_lstComment.InsertColumn(0,_T("�ļ���"),LVCFMT_LEFT,250);
	m_lstComment.InsertColumn(1,_T("�ļ���С"),LVCFMT_LEFT,100);
	m_wndGameList.InsertColumn(0,_T("��Ϸ���"),LVCFMT_LEFT,80);
	m_wndGameList.InsertColumn(1,_T("��Ϸ��"),LVCFMT_LEFT,200);
	m_wndGameList.InsertColumn(2,_T("�浵ʱ��"),LVCFMT_LEFT,200);
	m_wndGameList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_profress.SetRange(0,100);
	m_profress.SetStep(1);

	DWORD dwUsed = 0;
	for(size_t i =0; i<m_vecLstPersion.size();i++)
	{
		dwUsed += m_vecLstPersion[i].filesize;
	}
	m_pSrvConfigInfo = new SrvConfigInfo;
	/*
	string			sztitle;		//��ʾ����
	string			szSavePath;		//���˴浵·��
	DWORD			dwAllocSize;	//���˷���ռ��С
	bool			bShowPersion;	//�Ƿ���ʾ���˴洢��
	string			szCustomInfo;	//�û��Զ���˵����
	bool			bAutoStart;		//�Ƿ���ϵͳ����
	bool			bRegist;		//�Ƿ����ע��
	string			szStopRigTitle;	//ֹͣע����ʾ��Ϣ
	DWORD			dwDay;			// ɾ�����첻��½�û�
	DWORD			dwSpace;			//���ÿռ�С�ںö�ֹͣע��
	string			szCommResPath;	//������Դ·��
	bool			bShowCommres;  //�Ƿ���ʾ������Դ��
	*/

	char buf[4096] = {0};
	char* pData = NULL;
	DWORD nRecv = 0;

	if(m_pSocket->ExeCommand(NET_CMD_GETCONFIGINFO,pData,nRecv))
	{
		CPackageHelper outpack(pData);
		outpack.popString(buf);
		m_pSrvConfigInfo->sztitle = string(buf);
		outpack.popString(buf);
		m_pSrvConfigInfo->szSavePath =string(buf);
		m_pSrvConfigInfo->dwAllocSize = outpack.popDWORD();
		m_pSrvConfigInfo->bShowPersion = (outpack.popDWORD() == 1);
		outpack.popString(buf);
		m_pSrvConfigInfo->szCustomInfo = string(buf);
		m_pSrvConfigInfo->bAutoStart = (outpack.popDWORD() == 1);
		m_pSrvConfigInfo->bRegist = (outpack.popDWORD() == 1);
		outpack.popString(buf);
		m_pSrvConfigInfo->szStopRigTitle = string(buf);
		m_pSrvConfigInfo->dwDay = outpack.popDWORD();
		m_pSrvConfigInfo->dwSpace = outpack.popDWORD();
		outpack.popString(buf);
		m_pSrvConfigInfo->szCommResPath = string(buf);
		m_pSrvConfigInfo->bShowCommres = (outpack.popDWORD() == 1);
		delete []pData;
	}


	SetWindowText(m_pSrvConfigInfo->sztitle.c_str());
	GetGameInfo(m_mapGameInfo);
	LoadVDisk();
	LoadIconInfo();

	DrawFileList();
	DrawGameLst();
	return true;

}
void CUDiskClientDlg::UpdataStatic()
{
	m_dwFreeRoom = m_pSrvConfigInfo->dwAllocSize*1024*1024 - m_dwUsedRoom;
	CString str;
	str.Format("%d MB",m_pSrvConfigInfo->dwAllocSize);
	SetDlgItemText(IDC_STATIC1,str);
	str.Format("%d MB",m_dwUsedRoom/(1024*1024));
	SetDlgItemText(IDC_STATIC2,str);

	str.Format("%d MB",m_dwFreeRoom/(1024*1024));
	SetDlgItemText(IDC_STATIC3,str);
}
void CUDiskClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUDiskClientDlg::OnPaint()
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
UINT  CUDiskClientDlg::WorkThread(LPVOID lparam)
{
	CUDiskClientDlg* pthis = reinterpret_cast<CUDiskClientDlg*>(lparam);

	while (1)
	{

		MSG msg;
		PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE);//ǿ�ƽ�����Ϣ���� 
		while(!PeekMessage(&msg,NULL,0,0,PM_REMOVE))//ȡ��Ϣ   
		{   
			Sleep(1000);   
		} 
		switch(msg.message)
		{
		case WM_MSG_POSTFILE:
			{
				pthis->PostFileToServer(msg.wParam,msg.lParam);
				break;

			}
		case WM_MSG_DOWNODFILE:
			{
				vector<string>* PvecLst;
				vector<string> veclst;
				PvecLst = (vector<string>*)msg.lParam;
				if(PvecLst->size() == 0)
					break;

				TCHAR           szDisplayName[MAX_PATH]={0}; 
				if(msg.wParam ==0)
				{
					BROWSEINFO bi;

					LPITEMIDLIST     pidl; 
					LPMALLOC     pMalloc = NULL;  
					ZeroMemory(&bi, sizeof(bi));      
					bi.hwndOwner = pthis->GetSafeHwnd(); 
					bi.pszDisplayName = szDisplayName; 
					bi.lpszTitle = TEXT("��ѡ��һ���ļ���:"); 
					bi.ulFlags = BIF_RETURNONLYFSDIRS;  
					pidl = SHBrowseForFolder(&bi); 
					if (!pidl) 
					{ 
						return 0;
					}
					SHGetPathFromIDList(pidl, szDisplayName);  
				}
				else
				{
					MakeSureDirectoryPathExists("c:\\temp\\");
					lstrcpy(szDisplayName,"C:\\temp");
				}
				copy(PvecLst->begin(),PvecLst->end(),back_inserter(veclst));
				for(size_t i =0; i<veclst.size();i++)
				{
					string str = veclst[i];
					pthis->DowndFile(str.c_str(),szDisplayName);
					if(str.find(".zip") != std::string::npos)
					{
						pthis->UnZipFile(str.c_str(),szDisplayName);
						// string strtmp = string(szDisplayName) +"\\"+ str;
						// DeleteFile(strtmp.c_str());
						ShellExecute(NULL,"open",szDisplayName,NULL,NULL,SW_SHOW);
					}
				}

				break;
			}

		case WM_QUIT:
			{
				return 0;
			}

		}

	}

	return 0;
}
//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CUDiskClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
static bool ScanFile(const string& szfile,int nDir,vector<FileInfo>& vecLst,const string& szfilter)
{
	string szDest(szfile);
	if(*szDest.rbegin() =='\\')
		szDest+= szfilter;
	WIN32_FIND_DATA wfd ={0};
	HANDLE hFile = FindFirstFile(szDest.c_str(),&wfd);
	if(hFile == INVALID_HANDLE_VALUE)
		return false;
	do 
	{
		if(wfd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			if(wfd.cFileName[0] != '.')
			{
				string sztmp = szfile + string(wfd.cFileName)+"\\";
				ScanFile(sztmp,nDir,vecLst,szfilter);
			}

		}
		else
		{
			string strtmp = szfile +string(wfd.cFileName);
			FileInfo fi ;
			fi.filename = strtmp.substr(nDir);
			fi.filesize = wfd.nFileSizeLow;
			vecLst.push_back(fi);

		}
	} while(FindNextFile(hFile,&wfd));
	FindClose(hFile);
	return true;

}
string CUDiskClientDlg::ZipFile(LPCSTR zipName,const char* szFile)
{
	char  cFilePath[MAX_PATH ] ={0};
	lstrcpy(cFilePath,szFile);// �õ��Ϸ��ļ���·��

	SetDlgItemText(IDC_STATUSTEXT,"����ѹ��");
	PostMessage(WM_MSG_PROGRESS,50,1);
	char fileName[_MAX_FNAME];
	_splitpath_s(cFilePath, NULL, 0, NULL, 0, fileName, _MAX_FNAME, NULL, 0);// �õ��ļ���
	char buf[MAX_PATH] = {0};
	GetCurrentDirectory(MAX_PATH,buf);
	sprintf_s(buf,"%c:\\%s.zip",buf[0],(zipName == NULL?fileName:zipName));
	HZIP hz=  CreateZip(buf,0,ZIP_FILENAME);

	if(PathIsDirectory(cFilePath))
	{

		string szDir = string(cFilePath) +"\\" ;
		vector<FileInfo> vecLst;
		ScanFile(szDir,szDir.size(),vecLst,"*.*");
		DWORD dwSize = 0;
		for(size_t i =0; i<vecLst.size(); i++)
		{
			dwSize +=vecLst[i].filesize;
		}
		if(dwSize > m_dwFreeRoom)
		{
			SetDlgItemText(IDC_STATUSTEXT,"");
			PostMessage(WM_MSG_PROGRESS,0,1);
			AfxMessageBox("�ռ䲻�������ϴ����ļ���");
			CloseZip(hz);
			DeleteFile(buf);
			return "";
		}
		for(size_t i = 0; i<vecLst.size(); i++)
		{

			string str = szDir + vecLst[i].filename;
			ZipAdd(hz,vecLst[i].filename.c_str(),(LPVOID)str.c_str(),0,ZIP_FILENAME);
		}
	}
	else
		if(string(cFilePath).find('*') != string::npos)
		{
			char* ext = PathFindFileName(cFilePath);
			string szext(ext);
			PathRemoveFileSpec(cFilePath);
			lstrcat(cFilePath,"\\");
			vector<FileInfo> vecLst;
			ScanFile(cFilePath,string(cFilePath).size(),vecLst,szext.c_str());
			
			if(!vecLst.size())
			{
				SetDlgItemText(IDC_STATUSTEXT,"");
				CloseZip(hz);
				PostMessage(WM_MSG_PROGRESS,0,1);
				DeleteFile(buf);
				return "";
			}
			for(size_t i = 0; i<vecLst.size(); i++)
			{

				string str = string( cFilePath) +"\\"+ vecLst[i].filename;
				ZipAdd(hz,vecLst[i].filename.c_str(),(LPVOID)str.c_str(),0,ZIP_FILENAME);
			}

		}
		else
		{
			WIN32_FILE_ATTRIBUTE_DATA wfd ={0};
			GetFileAttributesEx(cFilePath,GetFileExInfoStandard,&wfd);
			if(wfd.nFileSizeLow > m_dwFreeRoom)
			{
				SetDlgItemText(IDC_STATUSTEXT,"");
				PostMessage(WM_MSG_PROGRESS,0,1);
				AfxMessageBox("�ռ䲻�������ϴ����ļ�");
				CloseZip(hz);
				return "";
			}
			ZipAdd(hz,PathFindFileName(cFilePath),cFilePath,0,ZIP_FILENAME);
		}
		CloseZip(hz);
		PostMessage(WM_MSG_PROGRESS,0,1);
		return string (buf);
}
bool CUDiskClientDlg::SendFile(LPCSTR path,LPCSTR szfile)
{
	SetDlgItemText(IDC_STATUSTEXT,"�����ϴ�");
	HANDLE hFile = CreateFile(szfile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		TRACE("Create file error");
		return false;
	}
	DWORD dwfilesize = GetFileSize(hFile,NULL);
	DWORD dwByteRead,idx=0;
	DWORD leftsize = dwfilesize;
	while(leftsize)
	{
		DWORD dwToRead = leftsize>BLOCK?BLOCK:leftsize;
		CPackageHelper inpack(m_pFileBuf);
		FileHeader  Fheader ={0};
		sprintf_s(Fheader.FilePath,"%s",path);
		lstrcpy(Fheader.filename,PathFindFileName(szfile));

		Fheader.bEnd =((leftsize-dwToRead)==0);
		Fheader.DataSize = dwToRead;
		Fheader.FileSize = dwfilesize;
		Fheader.Num = idx++;

		inpack.pushString((char*)&Fheader,sizeof(FileHeader));


		if(!ReadFile(hFile,m_pFileBuf+inpack.GetOffset(),dwToRead,&dwByteRead,NULL))
		{
			TRACE("read file error");
			return false;
		}
		leftsize-=dwByteRead;

		_packageheader header = {0};
		header.Cmd = NET_CMD_POSTBLOCKFILE;
		header.StartFlag = 0x5e7d;
		header.Length = inpack.GetOffset()+dwToRead;
		inpack.pushPackageHeader(header);

		if(!SendBlockFile(m_pFileBuf,header.Length))
			break;
		SetFilePointer(hFile,dwfilesize-leftsize,0,FILE_BEGIN);

		DWORD dwProgress = DWORD(((float)((dwfilesize-leftsize)/dwfilesize))*100);
		PostMessage(WM_MSG_PROGRESS,dwProgress,0);
	}

	CloseHandle(hFile);
	DeleteFile(szfile);
	PostMessage(WM_MSG_PROGRESS,0,0);
	SetDlgItemText(IDC_STATUSTEXT,"�ϴ����");

	return true;
}
bool CUDiskClientDlg::SendBlockFile(char* pData,DWORD length)
{

	DWORD dwleft = length;
	DWORD dwsend = 0;
	while(dwsend<dwleft)
	{
		int len = send(m_pSocket->GetSocket(),(pData+dwsend),dwleft-dwsend,0);
		if(len < 0)
		{
			m_pSocket->CloseConnect();
			return false;
		}
		dwsend+=len;
	}
	return true;
}
void CUDiskClientDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_pFileBuf)
	{
		delete []m_pFileBuf;
		m_pFileBuf = NULL;
	}
	if(m_pSrvConfigInfo)
	{
		delete m_pSrvConfigInfo;
		m_pSrvConfigInfo = NULL;
	}
	map<DWORD,tagGameInfo*>::iterator it = m_mapGameInfo.begin();
	for(; it != m_mapGameInfo.end(); it++)
	{
		delete it->second;
	}
	map<CString,tagVDiskInfo*>::iterator iter = m_mapVDisk.begin();
	for(; iter != m_mapVDisk.end();iter++)
	{
		delete iter->second;
	}
	if(m_pIconInfo)
	{
		delete[]m_pIconInfo;
		m_pIconInfo = NULL;
	}
	CDialog::OnClose();
}
bool CUDiskClientDlg::GetFileLst(WORD cmd,vector<FileInfo>& veclst)
{

	char* pData = NULL;
	DWORD nrecv = 0;
	if(m_pSocket->ExeCommand(cmd,pData,nrecv,(char*)m_UserName.c_str(),m_UserName.size()))
	{
		veclst.clear();
		CPackageHelper inpack(pData);
		DWORD ncount = inpack.popDWORD();
		for(DWORD i=0; i<ncount; i++)
		{
			char buf[MAX_PATH] = {0};
			inpack.popString(buf);
			FileInfo fInfo;
			fInfo.filename = string(buf);
			fInfo.filesize =inpack.popDWORD();
			fInfo.dwTime = inpack.popDWORD();
			veclst.push_back(fInfo);
		}
		delete[]pData;
		return true;
	}
	return false;
}
bool CUDiskClientDlg::UnZipFile(const char* szfile,char* szDestDir,bool bDir)
{
	if ((szfile == NULL) || (szDestDir ==NULL)) 
	{ 
		//·���쳣���� 
		return FALSE ; 
	}
	char file[MAX_PATH] = {0};
	sprintf_s(file,"%s\\%s",szDestDir,szfile);

	CFileFind tFFind; 
	if (!tFFind.FindFile(file)) 
	{ 
		//ѹ��ʧ��(δ����ѹ���ļ�) 
		return FALSE; 
	}
	char tmp[MAX_PATH] = {0};
	_splitpath_s(file, NULL, 0, NULL, 0, tmp, _MAX_FNAME, NULL, 0);// �õ��ļ���

	HZIP hz=OpenZip(file,0,ZIP_FILENAME); 
	if(hz == 0) 
	{ 
		return FALSE; 
	}
	ZIPENTRY ze;
	ZRESULT zr=GetZipItem(hz,-1,&ze); 
	if(zr != ZR_OK) 
	{ 
		CloseZip(hz); 
		return FALSE; 
	}

	int numitems=ze.index; 
	for (int i=0; i<numitems;i++)
	{ 
		zr=GetZipItem(hz,i,&ze); 
		CString str;
		bDir?str.Format("%s\\%s\\%s",szDestDir,tmp,ze.name):str.Format("%s\\%s",szDestDir,ze.name);
		str.Replace('/','\\');	
		MakeSureDirectoryPathExists(str);
		zr=UnzipItem(hz,i,(LPSTR)(LPCSTR)str,0,ZIP_FILENAME);
		if(zr != ZR_OK) 
		{ 
			CloseZip(hz); 
			return FALSE; 
		} 
	}
	CloseZip(hz); 
	return TRUE; 
}
bool CUDiskClientDlg::DowndFile(const char* szfile,char* szDestDir)
{
	bool bPerSion = true;
	SetDlgItemText(IDC_STATUSTEXT,"��������");
	CFindFile fun(szfile);
	vector<FileInfo>::iterator it  = find_if(m_vecLstPersion.begin(),m_vecLstPersion.end(),fun);
	if(it == m_vecLstPersion.end())
	{	
		bPerSion = false;
		it  = find_if(m_vecLstComment.begin(),m_vecLstComment.end(),fun);
		if(it == m_vecLstComment.end())
			return false;
	}
	DWORD dwSize = it->filesize;
	char szpath[MAX_PATH] = {0};
	sprintf_s(szpath,"%s\\%s",szDestDir,szfile);
	HANDLE hFile = CreateFile(szpath,GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		return false;

	char* pData = NULL;
	DWORD nRecv = 0;
	DWORD dwByteWirite= 0,idx =0;
	DWORD dwWriteSize = 0;

	while(dwWriteSize < dwSize )
	{

		FileHeader  Fheader ={0};
		lstrcpy(Fheader.FilePath,m_UserName.c_str());
		lstrcpy(Fheader.filename,PathFindFileName(szfile));
		Fheader.IsPersion = bPerSion;
		Fheader.DataSize = (dwSize-dwWriteSize) >BLOCK?BLOCK:(dwSize-dwWriteSize);
		Fheader.bEnd =(Fheader.DataSize!=BLOCK);
		Fheader.FileSize = dwSize;
		Fheader.Num = idx++;

		if(!m_pSocket->ExeCommand(MET_CMD_GETBLCOKFILE,pData,nRecv,(char*)&Fheader,sizeof(FileHeader)))
			return false;
		char buf[sizeof(FileHeader)+1] = {0};
		CPackageHelper inpack(pData);
		inpack.popString(buf);
		FileHeader* pheader = (FileHeader*)buf;
		if(pheader->DataSize == 0)
			return false;
		if(!WriteFile(hFile,pData+inpack.GetOffset(),pheader->DataSize,&dwByteWirite,NULL))
		{
			delete[]pData;
			TRACE("read file error");
			return false;
		}
		dwWriteSize+=dwByteWirite;

		delete[]pData;
		SetFilePointer(hFile,dwWriteSize,0,FILE_BEGIN);
		DWORD dwProgress= (DWORD)(((float)dwWriteSize/dwSize)*100);
		PostMessage(WM_MSG_PROGRESS,dwProgress,0);
	}
	CloseHandle(hFile);
	PostMessage(WM_MSG_PROGRESS,0,0);
	SetDlgItemText(IDC_STATUSTEXT,"�������");
	return true;
}
BOOL CUDiskClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(   pMsg->message   ==   WM_KEYDOWN   &&  
		( pMsg->wParam   ==   VK_ESCAPE || pMsg->wParam == VK_CANCEL ||pMsg->wParam == VK_RETURN ) )  
		return   TRUE;  

	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CUDiskClientDlg::DrawPorgress(WPARAM wparam,LPARAM lparam)
{
	int ntype = (int)lparam;
	switch(ntype)
	{
	case 0:
		{
			m_profress.SetPos((DWORD)wparam);
			break;
		}
	case 1:
		{
			m_profress.SetPos((DWORD)wparam);
			break;
		}
	default:break;

	}

	return S_OK;
}


void CUDiskClientDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CReSetPasswordDlg dlg;

	if(dlg.DoModal() == IDOK)
	{
		CString str = CString(m_UserName.c_str()) +"|"+dlg.m_strOldPassword +"|" +dlg.m_strNewPassword;
		char* pData = NULL;
		DWORD nRecv =0;
		if(m_pSocket->ExeCommand(NET_CMD_RESETPASSWORD,pData,nRecv,(LPSTR)(LPCSTR)str,str.GetLength()))
		{
			char buf[1024] = {0};
			CPackageHelper inpack(pData);
			inpack.popString(buf);
			AfxMessageBox(buf);
			delete []pData;
		}
	}
}

void CUDiskClientDlg::OnNMRClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	CPoint pt ( GetMessagePos() );
	menu.GetSubMenu(1)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);

	*pResult = 0;
}

void CUDiskClientDlg::OnDowndcommfile()
{
	CUDiskClientDlg* pthis =((CUDiskClientDlg*)AfxGetMainWnd());
	POSITION pos = m_lstComment.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		m_vecFileLst.clear();
		while (pos)
		{
			int nItem = m_lstComment.GetNextSelectedItem(pos);
			TRACE1("Item %d was selected!\n", nItem);
			CString str = m_lstComment.GetItemText(nItem,0);
			m_vecFileLst.push_back(string(str));
		}
	}
	LPARAM lParam = (LPARAM)(&m_vecFileLst);
	::PostThreadMessage(m_threadID,
		WM_MSG_DOWNODFILE,0,lParam);
}

void CUDiskClientDlg::OnBnClickedAbout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������



}


void CUDiskClientDlg::OnBnClickedInfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CUserCusDlg dlg;
	dlg.DoModal();
}
void CUDiskClientDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TRACE("Notify(CTCN_SELCHANGE): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
		((CTC_NMHDR*)pNMHDR)->nItem,
		((CTC_NMHDR*)pNMHDR)->pszText,
		((CTC_NMHDR*)pNMHDR)->lParam,
		((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
		((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
		((CTC_NMHDR*)pNMHDR)->rItem.left,
		((CTC_NMHDR*)pNMHDR)->rItem.top,
		((CTC_NMHDR*)pNMHDR)->rItem.right,
		((CTC_NMHDR*)pNMHDR)->rItem.bottom,
		((CTC_NMHDR*)pNMHDR)->fSelected,
		((CTC_NMHDR*)pNMHDR)->fHighlighted);

	switch(((CTC_NMHDR*)pNMHDR)->nItem )
	{
	case 0:
		{
			m_wndListCtrl.ShowWindow(SW_SHOW);
			m_wndGameList.ShowWindow(SW_HIDE);
			m_lstComment.ShowWindow(SW_HIDE);
		}
		break;
	case 1:
		{
			m_wndListCtrl.ShowWindow(SW_HIDE);
			m_wndGameList.ShowWindow(SW_SHOW);
			m_lstComment.ShowWindow(SW_HIDE);
		}
		break;
	case 2:
		{
			m_wndListCtrl.ShowWindow(SW_HIDE);
			m_wndGameList.ShowWindow(SW_HIDE);
			m_lstComment.ShowWindow(SW_SHOW);
		}
		break;
	default:
		break;
	}

	*pResult = 0;
}
void CUDiskClientDlg::OnNMRClickList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	CPoint pt ( GetMessagePos() );
	menu.GetSubMenu(2)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	*pResult = 0;
}
void CUDiskClientDlg::LoadVDisk()
{
	DWORD dwReadByte = 0;
	TCHAR Path[MAX_PATH] = {0};
	GetModuleFileName(NULL,Path,MAX_PATH);
	PathRemoveFileSpec(Path);


    I8_ClientDataCore_ns::CI8ClientOfflineFileLock clLock;
	CString szFile = CString(Path) + TEXT("\\Data\\VDisk2.dat");
	HANDLE hFile = CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
    {
        return ;
	}

	DWORD dwSize = GetFileSize(hFile, NULL);
	char* pData = new char[dwSize+1];
	DWORD dwReadBytes = 0;
	if (!ReadFile(hFile, pData, dwSize, &dwReadBytes, NULL) || dwReadBytes != dwSize)
	{

		CloseHandle(hFile);
		delete[] pData;
		return ;
	}
	pData[dwReadBytes] = 0;
	try
	{
		CPackageHelper package(pData);
		if (1 == package.popDWORD())
		{
			DWORD dwCount = package.popDWORD();
			for (DWORD idx=0; idx<dwCount; idx++)
			{
				tagVDiskInfo* pVDisk = new tagVDiskInfo;
				char szValue[4096] = {0};
				package.popStringEx(szValue); pVDisk->VID = szValue;
				pVDisk->IP = package.popDWORD();
				pVDisk->Port = package.popDWORD();
				pVDisk->SvrDrv = (TCHAR)package.popDWORD();
				pVDisk->CliDrv = (TCHAR)package.popDWORD();
				pVDisk->Serial = package.popDWORD();
				pVDisk->Type = package.popDWORD();
				pVDisk->LoadType = package.popDWORD();
				package.popStringEx(szValue); pVDisk->SID = szValue;
				m_mapVDisk.insert(std::make_pair(pVDisk->VID, pVDisk));
				in_addr addr;
				addr.s_addr = pVDisk->IP;
				CString szIP(inet_ntoa(addr));
			
			}
		}
	}
	catch (...) {  }

	CloseHandle(hFile);
	delete []pData;

}

bool CUDiskClientDlg::GetGameInfo(map<DWORD,tagGameInfo*> &mapGameInfoLst)
{
	DWORD dwReadByte = 0;
	TCHAR Path[MAX_PATH] = {0};
	GetModuleFileName(NULL,Path,MAX_PATH);
	PathRemoveFileSpec(Path);
	lstrcat(Path,"\\Data\\GamesInfo.dat");

    I8_ClientDataCore_ns::CI8ClientOfflineFileLock clLock;
	HANDLE hFile = CreateFile(Path,GENERIC_READ,FILE_SHARE_WRITE|FILE_SHARE_READ,NULL,OPEN_EXISTING,0x80,0);
	if(hFile == INVALID_HANDLE_VALUE)
		return false;
	DWORD dwsize = GetFileSize(hFile,NULL);
	char* pData = new char[dwsize +1];
	ReadFile(hFile,pData,dwsize,&dwReadByte,0);
	CloseHandle(hFile);
	CPackageHelper inpackage(pData);
	DWORD flag = inpackage.popDWORD();

	DWORD dwCount   = inpackage.popDWORD();
	if(dwCount == 0)
	{
		delete[]pData;
		return false;
	}
	for(DWORD idx = 0;idx <dwCount;idx++)
	{
		tagGameInfo *pGameInfo = new tagGameInfo;
		pGameInfo->GID = inpackage.popDWORD();//��ϷID��
		pGameInfo->PID = inpackage.popDWORD();//��ID
		inpackage.popStringEx(pGameInfo->NAME);//��Ϸ���ƣ�
		inpackage.popStringEx(pGameInfo->IDCCLASS);//�ٷ���Ϸ���
		inpackage.popStringEx(pGameInfo->GAMEEXE);//��Ϸ�ٷ�EXE
		inpackage.popStringEx(pGameInfo->PARAM);//��Ϸ���в���
		pGameInfo->SIZE = inpackage.popDWORD();//��Ϸ��С;
		pGameInfo->DESKLNK = inpackage.popDWORD();//��Ϸ�Ƿ���ʾ�������ݷ�ʽ
		pGameInfo->TOOLBAR = inpackage.popDWORD();//�Ƿ���ʾ�ڹ�������;
		inpackage.popStringEx(pGameInfo->SVRPATH);//��Ϸ�ڷ������ϵ�·��
		PathAddBackslash(pGameInfo->SVRPATH);
		inpackage.popStringEx(pGameInfo->CLIPATH);//��Ϸ�ڿͻ����ϵ�·��
		PathAddBackslash(pGameInfo->CLIPATH);
        pGameInfo->dwDeleteFlg = inpackage.popDWORD();//��Ϸ�ռ䲻��ʱ����ɾ��
		inpackage.popStringEx(pGameInfo->MATCHFILE);//��Ϸ�Զ����������ļ�
		inpackage.popStringEx(pGameInfo->SAVEFILTER);//��Ϸ�浵��Ϣ
		pGameInfo->IDCUPTDATE =inpackage.popDWORD();//��Ϸ�����ķ������ĸ���ʱ��
		pGameInfo->IDCVER =inpackage.popDWORD();//��Ϸ�����ķ������ϵİ汾
		pGameInfo->SVRVER =inpackage.popDWORD();//��Ϸ�����ɷ������ϵİ汾
		pGameInfo->AUTOUPT =inpackage.popDWORD();//��Ϸ�Ƿ��Զ��ӷ������ϸ���
		pGameInfo->I8PLAY =inpackage.popDWORD();//��Ϸ��Ҫǿ�Ƹ���
		pGameInfo->IDCCLICK =inpackage.popDWORD();//��Ϸȫ������
		pGameInfo->SVRCLICK = inpackage.popDWORD();//��Ϸ���ɵ���
		pGameInfo->RUNTYPE = inpackage.popDWORD();//��Ϸ���з�ʽ
		inpackage.popStringEx(pGameInfo->VID); //��Ϸ����������ID
		pGameInfo->STATUS = inpackage.popDWORD();//��Ϸ����״̬��
        inpackage.popStringEx(pGameInfo->COMMENT); //comment;
        pGameInfo->dwRepair = inpackage.popDWORD();//������Ϸʱ��CRC�Ƚ�
		mapGameInfoLst.insert(make_pair(pGameInfo->GID,pGameInfo));
	}
	delete []pData;
	return true;

}
void splitString(string strSource, vector<string>& plugs, char ch)
{
	size_t first = 0;
	size_t second = 0;
	do
	{
		second = strSource.find_first_of(ch, first);
		if (second != string::npos)
		{
			plugs.push_back(strSource.substr(first, second-first));
			first = second+1;
		}
		else
		{
			if (first < strSource.size())
			{
				plugs.push_back(strSource.substr(first));
			}
		}
	}while (second != string::npos);
}
bool CUDiskClientDlg::ConvertPath(DWORD gid,vector<string>&veclst)
{
	map<DWORD,tagGameInfo*>::iterator it = m_mapGameInfo.find(gid);
	if(it != m_mapGameInfo.end())
	{	
		tagGameInfo* pGameInfo = it->second;
		vector<string >veclst1;
		splitString(pGameInfo->SAVEFILTER,veclst1,'|');
		for(size_t i =0; i<veclst1.size();i++)
		{
			char path[MAX_PATH] = {0};
			CString file =CString(veclst1[i].c_str());
			int pos = file.FindOneOf("%");
			if(pos == -1)
			{
				veclst.push_back(string(file));
				continue;
			}
			 pos = file.FindOneOf("\\");
			CString var = file.Left(pos);
			CString tmp (var);
			var.Remove('%');
			if(var.CompareNoCase("path") == 0)
			{
				if(pGameInfo->RUNTYPE == 2) //���������� ��ת��·����
				{
					map<CString,tagVDiskInfo*>::iterator iter = m_mapVDisk.find(it->second->VID);
					if(iter != m_mapVDisk.end())
					{
						pGameInfo->SVRPATH[0] = iter->second->CliDrv;
						strncpy_s(path,pGameInfo->SVRPATH,lstrlen(pGameInfo->SVRPATH)-1);
					}
				}
				else
				strncpy_s(path,pGameInfo->CLIPATH,lstrlen(pGameInfo->CLIPATH)-1);

			}else
			{
				GetEnvironmentVariable(var,path,MAX_PATH);
			}
			file.Replace(tmp,path);
			veclst.push_back(string(file));
		}
		return true;
	}
	return false;
}
LRESULT CUDiskClientDlg::SaveGameRecord(WPARAM wparam,LPARAM lparam)
{
	if(wparam == 0)
		return true;
	m_ctrlTab.SetCurSel(1);
	m_wndGameList.ShowWindow(SW_SHOW);
	m_wndListCtrl.ShowWindow(SW_HIDE);

	m_vecFileLst.clear();
	ConvertPath(wparam,m_vecFileLst);
	if(m_vecFileLst.size())
	{
		LPARAM lParam = (LPARAM)(&m_vecFileLst);
		::PostThreadMessage(m_threadID,WM_MSG_POSTFILE,wparam,lParam);
	}		
	return true;
}
bool CUDiskClientDlg::PostFileToServer(WPARAM wparam,LPARAM lparam)
{

	char Path[MAX_PATH] = {0};
	vector<string>* PvecLst;
	vector<string> veclst;
	PvecLst = (vector<string>*)lparam;
	copy(PvecLst->begin(),PvecLst->end(),back_inserter(veclst));
	string strfile;
	if(wparam ==0)
	{
		for(size_t i =0 ; i<veclst.size();i++)
		{
			string szPath =veclst.at(i);
			sprintf_s(Path,"%s\\u��\\",m_UserName.c_str());
			strfile = ZipFile(NULL,szPath.c_str());
			if(strfile =="")
				continue;
			if(SendFile(Path,(char*)strfile.c_str()))
				DrawFileList();
		}
	}
	else
	{
		string zipname;
		sprintf_s(Path,"%s\\game\\%d\\",m_UserName.c_str(),wparam);
		for(size_t i =0 ; i<veclst.size();i++)
		{
			string szPath =veclst.at(i);
			OutputDebugString(szPath.c_str());
			size_t pos = szPath.find("My Documents");
			if(pos != std::string::npos)
			{
				zipname = "Documents";
			}else
			{
				size_t pos = szPath.find("Application Data");
				if(pos != std::string::npos)
				{
					zipname = "Application";
				}
				else
				{
					zipname = "Path";
				}
			}
			char buf[MAX_PATH] = {0};
			strfile = ZipFile(zipname.c_str(),szPath.c_str());
			map<DWORD,tagGameInfo*>::iterator it = m_mapGameInfo.find(wparam);
			if(it != m_mapGameInfo.end())
			{
				sprintf_s(buf,"%s",it->second->NAME);
			}
			if(strfile =="")
			{
				sprintf_s(buf,"[%s] û���ҵ��浵�ļ�:%s",it->second->NAME,szPath.c_str());
				AfxMessageBox(buf);
				continue;
			}
			if(SendFile(Path,(char*)strfile.c_str()))
			{
				DrawGameLst();
				lstrcat(buf," �浵�ɹ�");
				AfxMessageBox(buf);
			}
		}

	}
	return true;
}
void CUDiskClientDlg::DrawGameLst()
{

	char* pData = NULL;
	DWORD nRecv = 0;
	if(m_pSocket->ExeCommand(NET_CMD_GETSAVEGAMELST,pData,nRecv,(char*)m_UserName.c_str(),m_UserName.size()))
	{
		m_wndGameList.DeleteAllItems();
		CPackageHelper inpack(pData);
		DWORD nCount = inpack.popDWORD();
		for(DWORD i =0; i<nCount;i++)
		{
			DWORD gid= inpack.popDWORD();
			DWORD dwTime = inpack.popDWORD();
			map<DWORD,tagGameInfo*>::iterator it = m_mapGameInfo.find(gid);
			if(it != m_mapGameInfo.end())
			{
				char szgid[32] = {0};
				int nCount = m_wndGameList.GetItemCount();
				sprintf_s(szgid,"%d",it ->second->GID);
				int nIdx = m_ImageList.Add(FindIconOfGame_(it->second->GID));
				m_wndGameList.InsertItem(nCount,szgid,nIdx);
				m_wndGameList.SetItemText(nCount,1,it->second->NAME);
				FILETIME ft, ftlocal;
				MekeFileTimeFromTime(dwTime,ft);
				FileTimeToLocalFileTime(&ft,&ftlocal);
				CTime t(ftlocal); 
				CString s;
				s.Format("%04d-%02d-%02d %02d:%02d:%02d",
					t.GetYear(), t.GetMonth(), t.GetDay(), 
					t.GetHour(), t.GetMinute(), t.GetSecond());
					//= t.Format("%Y-%m-%d  %H:%M:%S");
				m_wndGameList.SetItemText(nCount,2,s);
			}
		}
		delete[]pData;
	}

}
void CUDiskClientDlg::OnDeleteGameRecord()
{
	char* pData = NULL;
	DWORD nRecv = 0;
	POSITION pos = m_wndGameList.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		if(MessageBox("ȷ��Ҫɾ������Ϸ�浵��","ɾ����Ϸ�浵",MB_OKCANCEL) == IDOK)
		{
			while (pos)
			{
				int nItem = m_wndGameList.GetNextSelectedItem(pos);
				CString strgid = m_wndGameList.GetItemText(nItem,0);
				char buf[MAX_PATH] = {0};
				sprintf_s(buf,"%s\\game\\%s\\",m_UserName.c_str(),strgid);
				if(m_pSocket->ExeCommand(NET_CMD_DELETEGAMERECORD,pData,nRecv,buf,strlen(buf)))
				{
					delete[]pData;
				}
			}
		}
	}

	DrawGameLst();
}

void CUDiskClientDlg::OnReadrecord()
{
	string strError;
	bool bFail = true;
	POSITION pos = m_wndGameList.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;
	else
	{
		while (pos)
		{
			int nItem = m_wndGameList.GetNextSelectedItem(pos);
			CString strgid = m_wndGameList.GetItemText(nItem,0);
			if(!DowndGameRecord(atol(strgid),strError))
			{
				bFail = false;
			}
		}
	}
	if(bFail)
		AfxMessageBox("��Ϸ�����ɹ�");
	else
	{
		strError += "��Ϸ����ʧ�ܣ�";
		AfxMessageBox(strError.c_str());
	}
}
bool CUDiskClientDlg::DowndGameRecord(DWORD gid,string& strError)
{
	DWORD ByteWrite;
	vector<string>veclst;
	char* pData = NULL;
	DWORD nRecv = 0;
	char path[MAX_PATH] = {0};
	char szDest[MAX_PATH] = {0};
	ConvertPath(gid,veclst);
	for(size_t i =0; i<veclst.size() ;i++)
	{
		string file = veclst[i];
		sprintf_s(szDest,"%s",file.c_str());
		if(file.find("My Documents")!= string::npos)
		{
			sprintf_s(path,"%s\\game\\%d\\Documents.zip",m_UserName.c_str(),gid);
			PathRemoveFileSpec(szDest);
			lstrcat(szDest,"\\Documents.zip");
		}
		else  if(file.find("Application Data") != string::npos)
		{
			sprintf_s(path,"%s\\game\\%d\\Application.zip",m_UserName.c_str(),gid);
			PathRemoveFileSpec(szDest);
			lstrcat(szDest,"\\Application.zip");
		}
		else
		{
			sprintf_s(path,"%s\\game\\%d\\path.zip",m_UserName.c_str(),gid);
			PathRemoveFileSpec(szDest);
			lstrcat(szDest,"\\path.zip");
		}
		if(m_pSocket->ExeCommand(NET_CMD_GETGAMERECORD,pData,nRecv,path,strlen(path)))
		{
			if(((_packageheader*)pData)->Cmd == NET_CMD_GETGAMERECORD)
			{
				CPackageHelper inpack(pData);
				DWORD dwSize = inpack.popDWORD();
				MakeSureDirectoryPathExists(szDest);
				HANDLE hFile = CreateFile(szDest,GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
				if(hFile == INVALID_HANDLE_VALUE)
				{
					DWORD dwError = WSAGetLastError();
					char buf[32] = {0};
					sprintf_s(buf,"%d",dwError);
					strError = "�򿪴浵·���ļ�ʧ��\r\n"+string(szDest)+" ������룺"+string(buf);
					delete[]pData; 
					return false;
				}
				WriteFile(hFile,pData+inpack.GetOffset(),dwSize,&ByteWrite,NULL);
				SetEndOfFile(hFile);
				CloseHandle(hFile);
				string DestFile(szDest);
				string ext (PathFindFileName(szDest));
				PathRemoveFileSpec(szDest);
				if(!UnZipFile(ext.c_str(),szDest,false))
				{
					strError = "��ѹ�ļ�ʧ��";
					delete[]pData;
					return false;
				}
				DeleteFile(DestFile.c_str());
				delete[]pData;
				return true;
			}
			delete[]pData;
			return false;
		}
	}
	return false;
}

void CUDiskClientDlg::LoadIconInfo()
{
	DWORD dwReadByte = 0;
	TCHAR Path[MAX_PATH] = {0};
	GetModuleFileName(NULL,Path,MAX_PATH);
	PathRemoveFileSpec(Path);
	CString File = CString(Path) + TEXT("\\Data\\gameicon.zip");
	HANDLE hFile = CreateFile(File, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return ;
	}

	DWORD dwSize = GetFileSize(hFile, NULL);
	m_pIconInfo = new char[dwSize+1];
	DWORD dwReadBytes = 0;
	if (!ReadFile(hFile, m_pIconInfo, dwSize, &dwReadBytes, NULL) || dwReadBytes != dwSize || dwSize < 30)
	{
	
		CloseHandle(hFile);
		delete[] m_pIconInfo;
		m_pIconInfo = NULL;
		return ;
	}
	m_pIconInfo[dwReadBytes] = 0;

	try
	{
		DWORD dwLastPackage = 0;
		char* pTemp = m_pIconInfo;
		DWORD dwTotal = 0;
		while (dwLastPackage == 0 && pTemp < m_pIconInfo + dwSize)	//dwLastPackage=1�������һ��
		{
			CPackageHelper package(pTemp);
			DWORD dwflag  = package.popDWORD();			//״̬
			dwLastPackage = package.popDWORD();			//�Ƿ������һ��
			DWORD dwCount = package.popDWORD();			//����ICON��
			dwTotal += dwCount;
			for (DWORD idx=0; idx<dwCount; idx++)
			{
				char gid[20] = {0};
				package.popString(gid);
				int nOffset = package.GetOffset();
				int nLength = package.popDWORD();
				m_mapIconInfo.insert(std::make_pair(atol(gid), pTemp + nOffset));
				package.SetOffset(nOffset + nLength + 4);
			}
			pTemp += package.GetOffset();
		}
	}
	catch (...) {  }

	CloseHandle(hFile);
	
}
HICON CUDiskClientDlg::FindIconOfGame_(DWORD gid)
{
	HICON hIcon = NULL;
	std::map<DWORD, char*>::iterator it = m_mapIconInfo.find(gid);
	if (m_pIconInfo != NULL && it != m_mapIconInfo.end() && it->second != NULL)
	{
		char *pData = it->second;
		DWORD dwSize = *(DWORD*)pData;
		pData += 4;
		HGLOBAL hGlobal = GlobalAlloc(GMEM_FIXED, dwSize);
		if (hGlobal != NULL)
		{
			void* pv = GlobalLock(hGlobal);
			memcpy(pv, pData, dwSize);
			GlobalUnlock(hGlobal);

			IStream* pIStream = NULL;
			Gdiplus::Bitmap* pImage = NULL;
			DWORD dwError = CreateStreamOnHGlobal(hGlobal, FALSE, &pIStream);
			if (pIStream != NULL && (pImage = new Gdiplus::Bitmap(pIStream)) != NULL)
			{
				pImage->GetHICON(&hIcon);
				delete pImage;
			}
			if (pIStream != NULL)
			{
				pIStream->Release();
			}

			GlobalFree(hGlobal);
		}
	}
	if (hIcon == NULL)
		hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	return hIcon;
}


LRESULT CUDiskClientDlg::ReadGamerRecord(WPARAM wparam,LPARAM lparam)
{
	if(wparam == 0)
		return S_FALSE;

	m_ctrlTab.SetCurSel(1);
	m_wndGameList.ShowWindow(SW_SHOW);
	m_wndListCtrl.ShowWindow(SW_HIDE);


	string str(_T("��Ϸ: "));
	map<DWORD,tagGameInfo*>::iterator it  =m_mapGameInfo.find(wparam);
	if(it != m_mapGameInfo.end())
	{
		str = str+string(it->second->NAME);
	}

	char buf[64] = {0};
	sprintf_s(buf,"%d",wparam);
	LVFINDINFO lvItem;
	lvItem.flags = LVFI_PARTIAL|LVFI_STRING;
	lvItem.psz = buf;
	int nItem = m_wndGameList.FindItem(&lvItem,-1);
	if(nItem == -1)
	{
		str+=" �޴浵��¼��";
		AfxMessageBox(str.c_str());
		return S_FALSE;
	}
	string strError;

	if(DowndGameRecord(wparam,strError))
	{
		str+=" �����ɹ�!";	
	}
	else
	{
		str+=" ����ʧ�ܣ�"+strError;
	}
	AfxMessageBox(str.c_str());
	return S_OK;

}