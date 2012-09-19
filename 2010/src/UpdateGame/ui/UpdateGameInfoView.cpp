#include "stdafx.h"
#include "ServerUI.h"
#include "UpdateGameInfoView.h"

IMPLEMENT_DYNCREATE(CUpdateGameInfoView, CListView)

CUpdateGameInfoView::CUpdateGameInfoView()
{

}

CUpdateGameInfoView::~CUpdateGameInfoView()
{
}

BEGIN_MESSAGE_MAP(CUpdateGameInfoView, CListView)
	ON_WM_CREATE()
END_MESSAGE_MAP()

#ifdef _DEBUG
void CUpdateGameInfoView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CUpdateGameInfoView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG

int CUpdateGameInfoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CListCtrl& pListCtrl = this->GetListCtrl();
		pListCtrl.ModifyStyle(LVS_TYPEMASK,LVS_REPORT|LVS_SINGLESEL);
	pListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	pListCtrl.InsertColumn(0,_T("�ͻ���IP"),LVCFMT_LEFT,100);
	pListCtrl.InsertColumn(1,_T("��Ϸ���"),LVCFMT_LEFT,80);
	pListCtrl.InsertColumn(2,_T("��Ϸ����"),LVCFMT_LEFT,80);
	pListCtrl.InsertColumn(3,_T("��ǰ״̬"),LVCFMT_LEFT,60);
	pListCtrl.InsertColumn(4,_T("��ǰ����"),LVCFMT_LEFT,80);
	pListCtrl.InsertColumn(5,_T("������(M)"),LVCFMT_LEFT,80);
	pListCtrl.InsertColumn(6,_T("ʣ����(M)"),LVCFMT_LEFT,80);
	pListCtrl.InsertColumn(7,_T("�ٶ�(K/S)"),LVCFMT_LEFT,80);
	return 0;
}
