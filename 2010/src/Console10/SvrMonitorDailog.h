#pragma once
#include "afxcmn.h"

#include <memory>
#include <deque>

// CSvrMonitorDailog �Ի���

class CSvrMonitorDailog : public CDialog
{
	DECLARE_DYNAMIC(CSvrMonitorDailog)

public:
	CSvrMonitorDailog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSvrMonitorDailog();

	void AddLog(i8desk::PluginLogRecord* log);

// �Ի�������
	enum { IDD = IDD_SVR_MONITOR };

protected:

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg void OnLvnCustomDrawSvrLog(NMHDR *pNmHdr, LRESULT *pResult);
	afx_msg void OnLvnGetdispinfoSvrLog(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:

	typedef std::tr1::shared_ptr<i8desk::PluginLogRecord> LogRecord_Ptr;
	typedef std::deque<LogRecord_Ptr> LogList;

	size_t m_nMaxLogNum;
	LogList m_logs;
	CListCtrl m_LogView;

public:
	afx_msg void OnClose();
};
