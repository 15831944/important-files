#pragma once

#include <vector>
// CCheckDiskDlg �Ի���

class CCheckDiskDlg : public CDialog
{

private:
	CListBox m_lstUnProt;
	CListBox m_lstProt;	

	CString m_strCheckArea;					// ��Ҫ�޸��ķ���
	CString m_strUnCheckArea;				// ���޸��ķ���

	DECLARE_DYNAMIC(CCheckDiskDlg)

public:
	CCheckDiskDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCheckDiskDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_CHECKDISK };


public:
	const CString &GetCheckArea() const		// ��ȡ��Ҫ�޸��ķ���
	{
		return m_strCheckArea;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();


public:
	DECLARE_MESSAGE_MAP()

	
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedAddAll();
	afx_msg void OnBnClickedRemove();
	afx_msg void OnBnClickedRemoveAll();
	afx_msg void OnBnClickedOk();
};
