// WidgetBlacklist.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WidgetBlacklist.h"

#include <regex>

// CWidgetBlacklist �Ի���

IMPLEMENT_DYNAMIC(CWidgetBlacklist, CDialog)

CWidgetBlacklist::CWidgetBlacklist(CWnd* pParent /*=NULL*/)
	: CDialog(CWidgetBlacklist::IDD, pParent)
	, m_strWidget(_T(""))
	, m_strDescription(_T(""))
{

}

CWidgetBlacklist::~CWidgetBlacklist()
{
}

void CWidgetBlacklist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WIDGET, m_strWidget);
	DDX_Text(pDX, IDC_DESCRIPTION, m_strDescription);
}


BEGIN_MESSAGE_MAP(CWidgetBlacklist, CDialog)
	ON_BN_CLICKED(IDOK, &CWidgetBlacklist::OnBnClickedOk)
	ON_EN_CHANGE(IDC_WIDGET, &CWidgetBlacklist::OnEnChangeWidget)
END_MESSAGE_MAP()


// CWidgetBlacklist ��Ϣ�������

void CWidgetBlacklist::OnBnClickedOk()
{
	UpdateData();

	if (m_strWidget.IsEmpty()) 
	{
		AfxMessageBox(_T("����������Ч�Ĵ��ڱ���"));
		return;
	}
	else 
	{
		std::tr1::regex regex("^\\**$");
		if (std::tr1::regex_match((LPCTSTR)m_strWidget, regex))
		{
			AfxMessageBox(_T("���ڱ�������������ȫΪ��*���ַ�"));
			return;
		}
	}

	OnOK();
}

void CWidgetBlacklist::OnEnChangeWidget()
{
	CString old = m_strWidget;
	UpdateData();
	{
		std::tr1::regex regex("^.*\\*{2}.*$");
		if (std::tr1::regex_match((LPCTSTR)m_strWidget, regex))
		{
			AfxMessageBox(_T("��Ҫ�������롰*���ַ�"));
			m_strWidget = old;
			UpdateData(FALSE);
			return;
		}
	}
	{
		std::tr1::regex regex("^.+\\*.+");
		if (std::tr1::regex_match((LPCTSTR)m_strWidget, regex))
		{
			AfxMessageBox(_T("��*���ַ������������������м�"));
			m_strWidget = old;
			UpdateData(FALSE);
			return;
		}
	}
}
