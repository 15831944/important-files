#pragma once
#include "explorer.h"

#include "UI.h"

// CRepairDialog �Ի���

class CRepairDialog : public CDialog
{
	DECLARE_DYNAMIC(CRepairDialog)

public:
	CRepairDialog(const CString& nid, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRepairDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_REPAIR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CString m_strNid;
	CDockHtmlCtrl m_WebPage;
};
