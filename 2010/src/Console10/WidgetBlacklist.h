#pragma once

#include "resource.h"

// CWidgetBlacklist �Ի���

class CWidgetBlacklist : public CDialog
{
	DECLARE_DYNAMIC(CWidgetBlacklist)

public:
	CWidgetBlacklist(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWidgetBlacklist();

// �Ի�������
	enum { IDD = IDD_WIDGET_BLACKLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strWidget;
	CString m_strDescription;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeWidget();
};
