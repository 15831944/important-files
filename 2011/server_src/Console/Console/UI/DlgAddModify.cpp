#include "stdafx.h"
#include "../Console.h"
#include "DlgAddModify.h"
#include "../ManagerInstance.h"
#include "../Data/DataHelper.h"
#include "../Data/CustomDataType.h"

#include <vector>
#include <map>

#include "../../../../include/Extend STL/StringAlgorithm.h"
#include "../../../../include/Utility/Utility.h"
#include "../Business/PushGameBusiness.h"
#include "../ui/Skin/SkinMgr.h"
#include "../UI/UIHelper.h"
#include "../../../../include/ui/ImageHelpers.h"
#include "../MessageBox.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CDlgPushGameAddModify, CNonFrameChildDlg)

using namespace i8desk::data_helper;
using namespace std::tr1::placeholders;


CDlgPushGameAddModify::CDlgPushGameAddModify(
	bool isAdd,
	PushGameTraits::ElementType *pushgame,
	CWnd* pParent )
: CNonFrameChildDlg(CDlgPushGameAddModify::IDD, pParent)
, isAdd_(isAdd)
, wndEdittaskName_(_T(""))
, pushgame_( new PushGameTraits::ElementType)
{
	if (isAdd_)
	{
		utility::Strcpy(pushgame_->TID, utility::CreateGuidString());
	}
	else
	{
		memcpy(pushgame_.get(),pushgame,sizeof(PushGameTraits::ElementType));
	}
}

CDlgPushGameAddModify::~CDlgPushGameAddModify()
{
}

void CDlgPushGameAddModify::DoDataExchange(CDataExchange* pDX)
{
	CNonFrameChildDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_PUSHGAME_GAME, wndTreeGame_);
	DDX_Control(pDX, IDC_TREE_PUSHGAME_AREA, wndTreeArea_);
	DDX_Text(pDX, IDC_EDIT_PUSHGAME_TASKNAME, wndEdittaskName_);
	DDX_Control(pDX, IDC_EDIT_PUSHGAME_TASKNAME, wndtaskName_);
	DDX_Text(pDX, IDC_EDIT_PUSHGAME_SPEED, wndEditmaxSpeed_);
	DDX_Control(pDX, IDC_EDIT_PUSHGAME_SPEED, wndmaxSpeed_);

	DDX_Control(pDX, IDC_STATIC_PUSHGAME_TASKNAME, wndlabeltaskName_);
	DDX_Control(pDX, IDC_STATIC_PUSHGAME_GAME, wndlabelGame_);
	DDX_Control(pDX, IDC_STATIC_PUSHGAME_AREA, wndlabelArea_);
	DDX_Control(pDX, IDC_STATIC_PUSHGAME_PARAM, wndlabelParam_);
	DDX_Control(pDX, IDC_STATIC_PUSHGAME_SPEED, wndlabelSpeed_);
	DDX_Control(pDX, IDC_STATIC_PUSHGAME_PRASE, wndlabelPrase_);
	DDX_Control(pDX, IDC_STATIC_PUSHGAME_TYPE, wndlabelType_);

	DDX_Control(pDX, IDC_RADIO_PUSHGAME_INDEX, wndRadioIndex_);
	DDX_Control(pDX, IDC_RADIO_PUSHGAME_FILE, wndRadioFile_);

	DDX_Control(pDX, IDC_BUTTON_PUSHGAME_OK, wndBtnOk_);
	DDX_Control(pDX, IDC_BUTTON_PUSHGAME_CANCEL, wndBtnCancel_);
	
}


BEGIN_MESSAGE_MAP(CDlgPushGameAddModify, CNonFrameChildDlg)
	ON_BN_CLICKED(IDC_BUTTON_PUSHGAME_OK, &CDlgPushGameAddModify::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_PUSHGAME_CANCEL, &CDlgPushGameAddModify::OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_TREE_PUSHGAME_GAME, &CDlgPushGameAddModify::OnNMClickTreeGame)
	ON_BN_CLICKED(IDC_RADIO_PUSHGAME_INDEX, &CDlgPushGameAddModify::OnBnClickedCheckIndex)
	ON_BN_CLICKED(IDC_RADIO_PUSHGAME_FILE, &CDlgPushGameAddModify::OnBnClickedCheckFile)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

namespace
{
	template< typename TreeCtrlT, typename AreasT >
	void InitAreaTree(TreeCtrlT &tree, const AreasT &areas)
	{
		tree.ModifyStyle(TVS_CHECKBOXES, 0);
		tree.ModifyStyle(0, TVS_CHECKBOXES);

		for(typename AreasT::const_iterator iter = areas.begin();
			iter != areas.end(); ++iter)
		{
			HTREEITEM hItem = tree.InsertItem(iter->second->Name);
			tree.SetItemData(hItem, reinterpret_cast<DWORD_PTR>(iter->second.get()));
		}
	}

	template< typename TreeCtrlT, typename GamesT, typename ClassesT >
	void InitGameTree(TreeCtrlT &tree, const GamesT &games, const ClassesT &classes)
	{
		tree.ModifyStyle(TVS_CHECKBOXES, 0);
		tree.ModifyStyle(0, TVS_CHECKBOXES);

		std::map<stdex::tString, HTREEITEM> classItems;
		for(typename ClassesT::const_iterator iter = classes.begin();
			iter != classes.end(); ++iter)
		{
			HTREEITEM hclassItem = classItems[iter->second->CID];
			hclassItem = tree.InsertItem(iter->second->Name);
			tree.SetItemData(hclassItem, reinterpret_cast<DWORD_PTR>(iter->second.get()));
			classItems[iter->second->CID] = hclassItem;
		}

		TCHAR buf[BUFSIZ] = {0};
		for(size_t i = 0; i != games.size(); ++i)
		{
			HTREEITEM hclassItem = classItems[games[i]->CID];
			::_stprintf(buf, _T("%u:%s"), games[i]->GID, games[i]->Name);
			HTREEITEM hgameItem = tree.InsertItem(buf, hclassItem);
			tree.SetItemData(hgameItem, reinterpret_cast<DWORD_PTR>(games[i].get()));
		}
	}
}

BOOL CDlgPushGameAddModify::OnInitDialog()
{
	CNonFrameChildDlg::OnInitDialog();

	SetTitle(_T("��Ϸ���͹�����"));
	//�ñ�����Ϸ��ʼ��GameTree
	GameTraits::VectorType localgames;
	i8desk::business::PushGame::LocalAllFilter(localgames);

	ClassTraits::MapType classes ;
	//i8desk::business::PushGame::ClassFilter(localgames, classes);

	i8desk::GetDataMgr().GetAllData(classes);

	InitGameTree(wndTreeGame_, localgames, classes);

	//��ʼ������AreaTree
	AreaTraits::MapType &areas = i8desk::GetDataMgr().GetAreas();
	i8desk::GetDataMgr().GetAllData(areas);

	InitAreaTree(wndTreeArea_, areas);

	if (isAdd_)
	{//���
		//Ĭ�ϲ�����
		SetDlgItemInt(IDC_EDIT_PUSHGAME_SPEED,0);
		//Ĭ��ѡ��Ա�������ʽ
		OnBnClickedCheckIndex();
	}
	else
	{//�޸�
		//��ʼ����������
		wndEdittaskName_ = pushgame_->Name;
		SetDlgItemText(IDC_EDIT_PUSHGAME_TASKNAME,pushgame_->Name);
		//Parameter ��ʽΪ: ��������ٶ�|�Աȷ�ʽ: 0_�Ա�����(�Ƽ�) 1_�Ա��ļ�|gid
		stdex::tString parame = pushgame_->Parameter;
		std::vector<i8desk::ulong> gids;
		stdex::Split(gids, parame, _T('|'));

		//��ʼ������ٶ�
		SetDlgItemInt(IDC_EDIT_PUSHGAME_SPEED,gids[0]);

		//��ʼ���Աȷ�ʽ
		switch(gids[1])
		{
		case FC_COPY_VERSION:			//�Ա�����
			OnBnClickedCheckIndex();
			break;
		case FC_COPY_QUICK:				//�Ա��ļ�
			OnBnClickedCheckFile();
			break;
		}

		//��ʼ��GameTree��ѡ�е���Ϸ
		for (HTREEITEM hclassItem = wndTreeGame_.GetRootItem(); 
			hclassItem != NULL; hclassItem = wndTreeGame_.GetNextSiblingItem(hclassItem)) 
		{
			bool bChecked = false;
			bool bCheckedClass = false;
			for (HTREEITEM hgameItem = wndTreeGame_.GetChildItem(hclassItem); 
				hgameItem != NULL; hgameItem = wndTreeGame_.GetNextSiblingItem(hgameItem)) 
			{
			
				GameTraits::ElementType *game = reinterpret_cast<GameTraits::ElementType *>(wndTreeGame_.GetItemData(hgameItem));
				//Parameter ��ʽΪ: ��������ٶ�|�Աȷ�ʽ: 3_�Ա�����(�Ƽ�) 1_�Ա��ļ�|gid
				//��gids������ƫ��2������gid
				bChecked = std::find_if(gids.begin()+2,gids.end(),
								std::bind2nd(std::equal_to<i8desk::ulong>(),game->GID))!= gids.end();

				if(bChecked)
				{
					wndTreeGame_.SetCheck(hgameItem, bChecked);
					wndTreeGame_.SetCheck(hclassItem, true);
				}
			}
		}

		//��ʼ��AreaTree��ѡ�еķ���
		curTaskareas_.clear();
		i8desk::business::PushGame::TaskAreaFilter(pushgame_->TID,curTaskareas_);

		for(BootTaskAreaTraits::VecConstIterator iter = curTaskareas_.begin();
			iter != curTaskareas_.end(); ++iter)
		{
			aids_.insert((*iter)->AID);
		}	

		for (HTREEITEM hareaItem = wndTreeArea_.GetRootItem(); 
			hareaItem != NULL; hareaItem = wndTreeArea_.GetNextSiblingItem(hareaItem))  
		{
			AreaTraits::ElementType *area = reinterpret_cast<AreaTraits::ElementType *>(wndTreeArea_.GetItemData(hareaItem));
			bool bChecked = std::find_if(curTaskareas_.begin(), curTaskareas_.end(), [area](const BootTaskAreaTraits::ValueType &val)->bool
			{
				return utility::Strcmp(val->AID, area->AID) == 0;
			}) != curTaskareas_.end();

			wndTreeArea_.SetCheck(hareaItem, bChecked);
		}
	}

	// Out Line

	outboxLine_.Attach(CopyBitmap(i8desk::ui::SkinMgrInstance().GetSkin(_T("Common/ControlOutBox.png"))));

	return TRUE;
}

void CDlgPushGameAddModify::OnNMClickTreeGame(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	CPoint pt;
	GetCursorPos(&pt);
	wndTreeGame_.ScreenToClient(&pt);

	UINT flags;
	HTREEITEM hItem = wndTreeGame_.HitTest(pt, &flags);
	if (!hItem || flags != TVHT_ONITEMSTATEICON)
		return;

	BOOL bChecked = !wndTreeGame_.GetCheck(hItem);
	if (HTREEITEM hclassItem = wndTreeGame_.GetParentItem(hItem)) 
	{
		if (bChecked)
			wndTreeGame_.SetCheck(hclassItem, TRUE);
	}
	else 
	{
		for (HTREEITEM hgameItem = wndTreeGame_.GetChildItem(hItem);
			hgameItem != NULL; hgameItem = wndTreeGame_.GetNextSiblingItem(hgameItem))
		{
			wndTreeGame_.SetCheck(hgameItem, bChecked);
		}
	}
}

void CDlgPushGameAddModify::OnBnClickedCheckIndex()
{
	wndRadioIndex_.SetCheck(TRUE);
	wndRadioFile_.SetCheck(FALSE);
}

void CDlgPushGameAddModify::OnBnClickedCheckFile()
{
	wndRadioIndex_.SetCheck(FALSE);
	wndRadioFile_.SetCheck(TRUE);
}

void CDlgPushGameAddModify::OnBnClickedOk()
{
	UpdateData(TRUE);
	// ������ֲ�дname
	if(!writeName())return;

	pushgame_->Type = i8desk::brUpdateGame;

	// ��������дParam
	if(!writeParam())return;

	// ���ѡ������
	AIDs aids;
	bool bCheckArea = false;
	for(HTREEITEM hItem = wndTreeArea_.GetRootItem(); 
		hItem != NULL; hItem = wndTreeArea_.GetNextSiblingItem(hItem)) 
	{
		if (wndTreeArea_.GetCheck(hItem) == TRUE)
		{
			typedef AreaTraits::ElementType AreaType;
			AreaType *area = reinterpret_cast<AreaType *>(wndTreeArea_.GetItemData(hItem));
			
			aids.insert(area->AID);
			bCheckArea = true;
		}
	}

	if(!bCheckArea)
	{
		CMessageBox msgDlg(_T("��ʾ"),_T("��ѡ������һ������"));
		msgDlg.DoModal();
		return;
	}

	if( isAdd_ )
	{
		if( !i8desk::business::PushGame::Add(pushgame_, aids) )
			return;
	}
	else
	{
		if( !i8desk::business::PushGame::Modify(pushgame_, aids_, aids) )
			return;
	}

	OnOK();
}

void CDlgPushGameAddModify::OnBnClickedCancel()
{
	OnCancel();
}

bool CDlgPushGameAddModify::writeName()
{
	if (wndEdittaskName_.IsEmpty()) 
	{
		CMessageBox msgDlg(_T("��ʾ"),_T("û���趨��������"));
		msgDlg.DoModal();
		return false;
	}
	utility::Strcpy(pushgame_->Name, (LPCTSTR)wndEdittaskName_);


	// ��������Ƿ��ظ�
	if( i8desk::business::PushGame::HasSameName(pushgame_))
	{
		stdex::tString msg = _T("�Ѿ����ڸ�����: ");
		msg += pushgame_->Name;
		CMessageBox msgDlg(_T("��ʾ"),msg);
		msgDlg.DoModal();
		return false;
	}

	return true;
}

bool CDlgPushGameAddModify::writeParam()
{
	int speed = GetDlgItemInt(IDC_EDIT_PUSHGAME_SPEED);
	int iSel = -1;
	iSel = wndRadioIndex_.GetCheck();
	if(iSel == 0) 
		iSel = -1;

	stdex::tOstringstream param;
	param << speed << _T('|') << iSel+2 << _T('|') ;

	BOOL bCheck = FALSE;
	//  ������Ϸ���������ܳ���300������ΪParameter���2048
	int  maxgid = 300;
	int  index = 0;

	for (HTREEITEM hclassItem = wndTreeGame_.GetRootItem(); 
		hclassItem != NULL; hclassItem = wndTreeGame_.GetNextSiblingItem(hclassItem)) 
	{
		for (HTREEITEM hgameItem = wndTreeGame_.GetChildItem(hclassItem); 
			hgameItem != NULL; hgameItem = wndTreeGame_.GetNextSiblingItem(hgameItem)) 
		{
			if(wndTreeGame_.GetCheck(hgameItem))
			{
				GameTraits::ElementType *game = reinterpret_cast<GameTraits::ElementType *>(wndTreeGame_.GetItemData(hgameItem));
				param << game->GID << _T('|');
				index++;
				if( index > maxgid )
					break;
				bCheck = TRUE;
			}
		}
	}

	param << std::ends;

	if( index > maxgid )
	{
		CMessageBox msg(_T("��ʾ"), _T("���������Ϸ������������300������! ���������ֻ���ǰ300����Ϸ��"));
		msg.DoModal();
	}

	utility::Strcpy(pushgame_->Parameter,param.str().c_str());

	// ����Ƿ�ѡ������һ����Ϸ
	if(!bCheck)
	{
		CMessageBox msgDlg(_T("��ʾ"),_T("��ѡ������һ����Ϸ��"));
		msgDlg.DoModal();
		return false;
	}

	return true;
}

BOOL CDlgPushGameAddModify::OnEraseBkgnd(CDC* pDC)
{
	__super::OnEraseBkgnd(pDC);

	CRect rcMultiText;
	wndTreeGame_.GetWindowRect(rcMultiText);
	i8desk::ui::DrawFrame(this, *pDC, rcMultiText, &outboxLine_);
	wndTreeArea_.GetWindowRect(rcMultiText);
	i8desk::ui::DrawFrame(this, *pDC, rcMultiText, &outboxLine_);

	return TRUE;
}
