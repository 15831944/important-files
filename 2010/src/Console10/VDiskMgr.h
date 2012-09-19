#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ConsoleDlg.h"

// CVDiskMgr �Ի���

class CVDiskMgr : public CDialog
{
	DECLARE_DYNAMIC(CVDiskMgr)

public:
	CVDiskMgr(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVDiskMgr();

// �Ի�������
	enum { IDD = IDD_DIALOG_VDISKMGR };
	CConsoleDlg* pDlg;

	bool VDiskChanged(void) const { return m_bChanged; }

protected:
	void AppendMsg(LPCTSTR msg);
	void CheckVDisk(LPCTSTR lpIPAddress, DWORD port, CString *result);
	void RefleshVDisk(LPCTSTR lpIPAddress, DWORD por, CString *result);

	//nIdx = -1��ʾ��ӣ������ʾ�޸�
	void ShowVDiskToList(int nIdx, const i8desk::VDiskInfo& vdisk);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnDestroy();
	afx_msg void OnLvnItemchangedListVdisk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboType();
	afx_msg void OnBnClickedCheck();
	afx_msg void OnBnClickedReflesh();
	afx_msg void OnBnClickedVdiskRefleshAll();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()

private:
	bool m_bChanged;
	CString m_msg;
	CListCtrl m_lstVDisk;
	CComboBox m_cboVdType;
	CComboBox m_cboSvrDrv;
	CComboBox m_cboCliDrv;
	CIPAddressCtrl m_IP;
	CComboBox m_cboLoadType;
public:
	afx_msg void OnNMClickListVdisk(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_cbVDiskMode;
	afx_msg void OnLvnDeleteitemListVdisk(NMHDR *pNMHDR, LRESULT *pResult);
};
