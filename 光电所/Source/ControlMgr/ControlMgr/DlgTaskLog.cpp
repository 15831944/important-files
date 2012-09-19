// DlgTaskLog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ControlMgr.h"
#include "DlgTaskLog.h"

#include <vector>
#include <sstream>
#include "../../Common/DBMgr.hpp"
#include "../../../include/UI/ImageHelpers.h"

#include <odbcinst.h>
#include <afxdb.h>
#include <comdef.h>


typedef std::pair<COleDateTime, CString> LogMsg;
typedef std::vector<LogMsg> LogMsgs;

LogMsgs GetLogMsgs(const std::wstring &sql)
{
	LogMsgs logMsgs;

	try
	{
		_RecordsetPtr &recordset = db::DBMgrInstance().GetRecordSet(sql.c_str());

		while(!recordset->adoEOF)
		{
			LogMsg logInfo;
			logInfo.first		= recordset->GetCollect(_T("date_added"));
			logInfo.second		= recordset->GetCollect(_T("message"));

			logMsgs.push_back(logInfo);

			recordset->MoveNext();
		}
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
	}

	return logMsgs;
}

CString GetExcelDriver()
{
	TCHAR szBuf[2001] = {0};
	WORD cbBufMax = 2000;
	WORD cbBufOut;
	TCHAR *pszBuf = szBuf;
	CString sDriver;

	// ��ȡ�Ѱ�װ����������(������odbcinst.h��)
	if (!SQLGetInstalledDrivers(szBuf, cbBufMax, &cbBufOut))
		return L"";

	// �����Ѱ�װ�������Ƿ���Excel...
	do
	{
		std::wstring driverBuf = pszBuf;
		if (driverBuf.find(L"Excel") != std::wstring::npos )
		{
			//���� !
			sDriver = driverBuf.c_str();
			break;
		}
		
		pszBuf = pszBuf + driverBuf.length() + 1;
	}
	while (pszBuf[1] != '\0');

	return sDriver;

}

void ExportListToExcel(CListCtrl &pList, CString sExcelFile, CString sSheetName)
{
	CString warningStr;
	if (pList.GetItemCount ()>0) 
	{ 
		CDatabase database;
		CString sDriver;
		CString sSql;

		// �����Ƿ�װ��Excel���� "Microsoft Excel Driver (*.xls)" 
		sDriver = GetExcelDriver();
		if (sDriver.IsEmpty())
		{
			// û�з���Excel����
			AfxMessageBox(L"û�а�װExcel!/n���Ȱ�װExcel�������ʹ�õ�������!");
			return;
		}

		// �������д�ȡ���ַ���
		sSql.Format(L"DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver, sExcelFile, sExcelFile);

		// �������ݿ� (��Excel����ļ�)
		if( database.OpenEx(sSql,CDatabase::noOdbcDialog) )
		{
			// ������ṹ
			int i;
			LVCOLUMN columnData;
			CString columnName;
			int columnNum = 0;
			CString strH;
			CString strV;

			sSql = L"";
			strH = L"";
			columnData.mask = LVCF_TEXT;
			columnData.cchTextMax =100;
			columnData.pszText = columnName.GetBuffer (100);
			for(i=0;pList.GetColumn(i,&columnData);i++)
			{
				if (i!=0)
				{
					sSql = sSql + L"," ;
					strH = strH + L"," ;
				}

				sSql = sSql + columnData.pszText +L" TEXT";
				strH = strH + columnData.pszText +L" ";

			}
			columnName.ReleaseBuffer ();
			columnNum = i;

			sSql = L"CREATE TABLE " + sSheetName+ L" (" + sSql +  L")";
			database.ExecuteSQL(sSql);

			// ����������
			int nItemIndex;
			for (nItemIndex=0;nItemIndex<pList.GetItemCount ();nItemIndex++)
			{
				strV = L"";
				for(i=0;i<columnNum;i++)
				{
					if (i!=0)
					{
						strV = strV + L"," ;
					}

					strV = strV + L"'" + pList.GetItemText(nItemIndex,i) + L"'";

				}

				sSql = L"INSERT INTO "+ sSheetName
					+L" ("+ strH + L")"
					+L" VALUES("+ strV + L")";

				database.ExecuteSQL(sSql);
			}

		}      

		// �ر����ݿ�
		database.Close();
		AfxMessageBox(L"�ɹ�������ָ��Ŀ¼");
	}
	else
	{
		//û������
		AfxMessageBox(L"û�����ݣ����ܵ���!");

	}

}


CString GetFolder( HWND hOwner = NULL)
{
	// The BROWSEINFO struct tells the shell 

	// how it should display the dialog.
	CString path;
	BROWSEINFO bi;
	memset(&bi, 0, sizeof(bi));

	bi.ulFlags   = BIF_USENEWUI;
	bi.hwndOwner = hOwner;
	bi.lpszTitle = L"ѡ��Ŀ¼";

	// must call this if using BIF_USENEWUI

	::OleInitialize(NULL);

	// Show the dialog and get the itemIDList for the 

	// selected folder.

	LPITEMIDLIST pIDL = ::SHBrowseForFolder(&bi);

	if(pIDL != NULL)
	{
		// Create a buffer to store the path, then 

		// get the path.

		TCHAR buffer[_MAX_PATH] = {'\0'};
		if(::SHGetPathFromIDList(pIDL, buffer) != 0)
		{
			// Set the string value.

			path = buffer;
		}

		// free the item id list

		CoTaskMemFree(pIDL);
	}

	::OleUninitialize();

	return path;
}


// CDlgTaskLog �Ի���

IMPLEMENT_DYNAMIC(CDlgTaskLog, CDialog)

CDlgTaskLog::CDlgTaskLog(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTaskLog::IDD, pParent)
{

}

CDlgTaskLog::~CDlgTaskLog()
{
}

void CDlgTaskLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TASK_LOG_START, wndTimeStart_);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TASK_LOG_STOP, wndTimeStop_);
	DDX_Control(pDX, IDC_LIST_TASK_LOG, wndListLog_);
}


BEGIN_MESSAGE_MAP(CDlgTaskLog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TASK_LOG_SEARCH, &CDlgTaskLog::OnBnClickedButtonTaskLogSearch)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_TASK_LOG_REFRESH, &CDlgTaskLog::OnBnClickedButtonTaskLogRefresh)
	ON_BN_CLICKED(IDC_BUTTON_TASK_LOG_EXPORT, &CDlgTaskLog::OnBnClickedButtonTaskLogExport)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


BOOL CDlgTaskLog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	
	wndListLog_.InsertColumn(0, _T("ʱ��"),	LVCFMT_LEFT, 150);
	wndListLog_.InsertColumn(1, _T("����"),	LVCFMT_LEFT, 300);


	wndListLog_.SetCellMargin(1.5);
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgTaskLog::OnDestroy()
{
	CDialog::OnDestroy();


}

// CDlgTaskLog ��Ϣ�������

void CDlgTaskLog::OnBnClickedButtonTaskLogSearch()
{
	COleDateTime start, stop;
	wndTimeStart_.GetTime(start);
	wndTimeStop_.GetTime(stop);

	std::wostringstream os;
	os << _T("SELECT * FROM log_t WHERE date_added >= '")
		<< (LPCTSTR)start.Format(L"%Y-%m-%d %H:%M:%S") << L"' AND date_added <= '"
		<< (LPCTSTR)stop.Format(L"%Y-%m-%d %H:%M:%S") << L"'";
	LogMsgs logMsgs = GetLogMsgs(os.str());

	wndListLog_.DeleteAllItems();

	int index = 0;
	for(LogMsgs::const_iterator iter = logMsgs.begin(); iter != logMsgs.end(); ++iter)
	{
		index = wndListLog_.InsertItem(index, iter->first.Format(_T("%Y-%m-%d %H:%M:%S")));
		wndListLog_.SetItemText(index, 1, iter->second);
		index++;
	}
}


void CDlgTaskLog::OnBnClickedButtonTaskLogRefresh()
{
	LogMsgs logMsgs = GetLogMsgs(_T("SELECT * FROM log_t ORDER BY id desc LIMIT 5"));

	wndListLog_.DeleteAllItems();

	int index = 0;
	for(LogMsgs::const_iterator iter = logMsgs.begin(); iter != logMsgs.end(); ++iter)
	{
		index = wndListLog_.InsertItem(index, iter->first.Format(_T("%Y-%m-%d %H:%M:%S")));
		wndListLog_.SetItemText(index, 1, iter->second);
		index++;
	}
}

void CDlgTaskLog::OnBnClickedButtonTaskLogExport()
{
	if( wndListLog_.GetItemCount() == 0 )
	{
		AfxMessageBox(L"�б���û������,���ܵ���");
		return;
	}

	CString path = GetFolder();
	if( path.IsEmpty() )
		return;

	path += _T("\\������־");
	ExportListToExcel(wndListLog_, path, _T("��־�ļ�"));
}


void CDlgTaskLog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CMemDC memDC(dc, this);


	HBRUSH tmp = ui::draw::AtlGetBackgroundBrush(GetSafeHwnd(), GetParent()->GetSafeHwnd());
	CBrush brush;
	brush.Attach(tmp);
	CRect rcClient;
	GetClientRect(rcClient);
	memDC.GetDC().FillRect(rcClient, &brush);
}

HBRUSH CDlgTaskLog::OnCtlColor(CDC   *   pDC,CWnd   *   pWnd,UINT   nCtlColor) 
{ 
	HBRUSH   hbr = CDialog::OnCtlColor(pDC,pWnd,nCtlColor); 
	if   (nCtlColor==CTLCOLOR_STATIC ) 
	{ 
		pDC-> SetBkMode(TRANSPARENT); 
		return   (HBRUSH)::GetStockObject(NULL_BRUSH); 
	} 
	return   hbr; 
} 