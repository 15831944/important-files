#include "StdAfx.h"
#include "ShortcutsListCtrl.h"



BEGIN_MESSAGE_MAP(CShortcutsListCtrl, CGridListCtrlEx)
	//ON_NOTIFY_REFLECT(NM_CLICK, &CShortcutsListCtrl::OnNMClick)
END_MESSAGE_MAP()



CShortcutsListCtrl::CShortcutsListCtrl(void)
{
}

CShortcutsListCtrl::~CShortcutsListCtrl(void)
{
}


void CShortcutsListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

BOOL CShortcutsListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	
	switch( ((NMHDR*)lParam)->code )
	{
	case HDN_BEGINTRACKW://�϶�
	case HDN_BEGINTRACKA:
	case HDN_DIVIDERDBLCLICKA://˫��
	case HDN_DIVIDERDBLCLICKW:
		*pResult = TRUE;
		return TRUE;
	}



	return CGridListCtrlEx::OnNotify(wParam, lParam, pResult);
}
