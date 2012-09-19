
// UDiskServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CUDiskServerDlg �Ի���
class CUDiskServerDlg : public CDialog
{
// ����
public:
	CUDiskServerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	INetLayer*			m_pNetLayer;
// �Ի�������
	enum { IDD = IDD_UDISKSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	SrvConfigInfo* m_pConfigInfo;
	string GetIpAddr(vector<string>& veclst);
	HANDLE m_hExit;
	HANDLE m_hTread;
	NOTIFYICONDATA m_nid; 
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool InitNetLayer(void);
	afx_msg void OnClose();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton3();
	void		autototray();
protected:
	void GetConfigInfo(void);
	bool 	SaveConfig();
	bool ScanDeleteUser(string& str,vector<string>&veclst);
	bool CompareUserLogTime(const string &sztmp,DWORD dwDay);
public:
	void SetConfigInfo(void);
	bool GetConfigFormFile(void);
	CComboBox m_RigstrCombox;
	CButton m_chkAutoStart;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CButton m_ChkCommRes;
	bool AutoStart(bool bStart);
	static UINT _stdcall  WorkThread(LPVOID lparam);
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnNotifyIcon(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	bool Listen(void);
public:
	afx_msg void OnShow();
	afx_msg void OnExit();
};
