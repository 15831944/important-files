// WZWelcomeBoard.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WZWelcomeBoard.h"


// CWZWelcomeBoard �Ի���

IMPLEMENT_DYNAMIC(CWZWelcomeBoard, CDialog)

CWZWelcomeBoard::CWZWelcomeBoard(CWnd* pParent /*=NULL*/)
	: CDialog(CWZWelcomeBoard::IDD, pParent)
{

}

CWZWelcomeBoard::~CWZWelcomeBoard()
{
}

void CWZWelcomeBoard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BOOL CWZWelcomeBoard::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	return TRUE;
}

BEGIN_MESSAGE_MAP(CWZWelcomeBoard, CDialog)
	ON_REGISTERED_MESSAGE(i8desk::g_nOptApplyMsg, &CWZWelcomeBoard::OnApplyMessage)
END_MESSAGE_MAP()


// CWZWelcomeBoard ��Ϣ�������
LRESULT CWZWelcomeBoard::OnApplyMessage(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}
