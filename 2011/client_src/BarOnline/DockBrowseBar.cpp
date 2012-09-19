#include "stdafx.h"
#include "DockBrowseBar.h"

#define DOCK_BROWSE_INDEX			0x00002200

IMPLEMENT_DYNAMIC(CDockBrowseBar, CStatic)

BEGIN_MESSAGE_MAP(CDockBrowseBar, CStatic)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_COMMAND_RANGE(DOCK_BROWSE_INDEX, DOCK_BROWSE_INDEX + 0xff, OnClickButton)
END_MESSAGE_MAP()

CDockBrowseBar::CDockBrowseBar()
{
	m_pbkImage = I8SkinCtrl_ns::I8_GetSkinImage(TEXT("Skin/BrowseBar/����_�����������_1px.png"));
}

CDockBrowseBar::~CDockBrowseBar()
{
	if (m_pbkImage)
	{
		m_pbkImage->DeleteObject();
		delete m_pbkImage;
	}
}

CString CDockBrowseBar::GetText()
{
	CString str = m_CtrlUrl.GetText();
	if (str.CompareNoCase(DEFAULT_TIP_TEXT2) == 0)
		str = TEXT("");
	return str;
}

void CDockBrowseBar::SetText(CString &str)
{
	if (m_CtrlUrl.GetSafeHwnd() != NULL)
	{
		CString old = GetText();
		if (str.CompareNoCase(old) != 0)
		{
			m_CtrlUrl.SetWindowText(str);
		}
	}
}

void CDockBrowseBar::SetListText(std::vector<CString>& lst)
{
	if (m_CtrlUrl.GetSafeHwnd() != NULL)
	{
		m_CtrlUrl.ResetContent();
		for (size_t idx=0; idx<lst.size(); idx++)
		{
			m_CtrlUrl.AddString(lst[idx]);
		}
	}
}

BOOL CDockBrowseBar::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		OnClickButton(DOCK_BROWSE_INDEX + 10);
		return TRUE;
	}
	return CStatic::PreTranslateMessage(pMsg);
}

void CDockBrowseBar::DrawItem(LPDRAWITEMSTRUCT lpDis)
{
	CRect rc(lpDis->rcItem);
	CDC* pDC = CDC::FromHandle(lpDis->hDC);
	I8SkinCtrl_ns::I8_DrawImage(pDC, m_pbkImage, rc);
}

BOOL CDockBrowseBar::OnEraseBkgnd(CDC* pDC)
{
	//CStatic::OnEraseBkgnd(pDC);
	return TRUE;
}

int  CDockBrowseBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	HCURSOR hCursor = LoadCursor(NULL, IDC_HAND);
	if (-1 == CStatic::OnCreate(lpCreateStruct))
		return -1;

	BOOL b = ModifyStyle(0, SS_OWNERDRAW);

	long lStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	lStyle |= WS_CLIPCHILDREN;
	lStyle |= WS_CLIPSIBLINGS;
	SetWindowLong(m_hWnd, GWL_STYLE, lStyle);

	for (int idx=0; idx<_countof(m_BtnGroup); idx++)
	{
		m_BtnGroup[idx].Create(TEXT(""), WS_VISIBLE|WS_CHILD, CRect(0, 0, 0, 0), this, DOCK_BROWSE_INDEX + idx);
		m_BtnGroup[idx].SetCursor(hCursor);
	}

	m_BtnGroup[0].SetImage(TEXT("Skin/BrowseBar/����_�����������_��.png"));
	m_BtnGroup[1].SetImage(TEXT("Skin/BrowseBar/��ť_�����������_��ҳ�ղؼ�_Ĭ��״̬.png"), 
		TEXT("Skin/BrowseBar/��ť_�����������_��ҳ�ղؼ�_��꾭��.png"), TEXT("Skin/BrowseBar/��ť_�����������_��ҳ�ղؼ�_����.png"));

	m_BtnGroup[2].SetImage(TEXT("Skin/BrowseBar/��ť_�����������_����_Ĭ��״̬.png"), 
		TEXT("Skin/BrowseBar/��ť_�����������_����_��꾭��.png"), TEXT("Skin/BrowseBar/��ť_�����������_����_����.png"));
	m_BtnGroup[3].SetImage(TEXT("Skin/BrowseBar/��ť_�����������_ǰ��_Ĭ��״̬.png"), 
		TEXT("Skin/BrowseBar/��ť_�����������_ǰ��_��꾭��.png"), TEXT("Skin/BrowseBar/��ť_�����������_ǰ��_����.png"));
	m_BtnGroup[4].SetImage(TEXT("Skin/BrowseBar/��ť_�����������_��ҳ_Ĭ��״̬.png"), 
		TEXT("Skin/BrowseBar/��ť_�����������_��ҳ_��꾭��.png"), TEXT("Skin/BrowseBar/��ť_�����������_��ҳ_����.png"));

	m_BtnGroup[5].SetImage(TEXT("Skin/BrowseBar/����_��ַ��_��.png"));
	m_BtnGroup[6].SetImage(TEXT("Skin/BrowseBar/����_��ַ��_1px.png"));
	m_CtrlUrl.Create(CBS_DROPDOWN|WS_CHILD|CBS_HASSTRINGS|WS_VISIBLE|CBS_AUTOHSCROLL, CRect(0, 0, 0, 0), &m_BtnGroup[6], DOCK_BROWSE_INDEX + sizeof(m_BtnGroup));
	m_CtrlUrl.AddString(TEXT(""));
	m_CtrlUrl.AddString(TEXT(""));
	m_CtrlUrl.AddString(TEXT(""));

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(lf), &lf);
	m_font.CreateFontIndirect(&lf);
	m_CtrlUrl.SetFont(&m_font);
	m_CtrlUrl.SetWindowText(DEFAULT_TIP_TEXT2);

	m_BtnGroup[7].SetImage(TEXT("Skin/BrowseBar/��ť_��ַ��_�����б�_Ĭ��״̬.png"));
	m_BtnGroup[8].SetImage(TEXT("Skin/BrowseBar/��ť_��ַ��_ˢ��_Ĭ��״̬.png"), 
		TEXT("Skin/BrowseBar/��ť_��ַ��_ˢ��_��꾭��.png"), TEXT("Skin/BrowseBar/��ť_��ַ��_ˢ��_����.png"));
	m_BtnGroup[9].SetImage(TEXT("Skin/BrowseBar/��ť_��ַ��_�ر�_Ĭ��״̬.png"), 
		TEXT("Skin/BrowseBar/��ť_��ַ��_�ر�_��꾭��.png"), TEXT("Skin/BrowseBar/��ť_��ַ��_�ر�_����.png"));
	m_BtnGroup[10].SetImage(TEXT("Skin/BrowseBar/��ť_��ַ��_GO_Ĭ��״̬.png"), 
		TEXT("Skin/BrowseBar/��ť_��ַ��_GO_��꾭��.png"), TEXT("Skin/BrowseBar/��ť_��ַ��_GO_����.png"));
	
	m_BtnGroup[11].SetImage(TEXT("Skin/BrowseBar/��ť_�����������_��ַ����_Ĭ��״̬.png"), 
		TEXT("Skin/BrowseBar/��ť_�����������_��ַ����_��꾭��.png"), TEXT("Skin/BrowseBar/��ť_�����������_��ַ����_����.png"));
	m_BtnGroup[12].SetImage(TEXT("Skin/BrowseBar/����_�����������_��.png"));

	return 0;
}

void CDockBrowseBar::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);
	if (m_BtnGroup[0].m_hWnd == NULL)
		return ;

	//��߰�ť
	CRect rc(0, 0, 6, 37);
	m_BtnGroup[0].MoveWindow(&rc);

	rc.OffsetRect(rc.Width(), 6);
	rc.bottom -= 12;
	rc.right = rc.left + 94;
	m_BtnGroup[1].MoveWindow(&rc);
	
	rc.OffsetRect(rc.Width() + 4, 0);
	rc.right = rc.left + 34;
	m_BtnGroup[2].MoveWindow(&rc);
	rc.OffsetRect(rc.Width(), 0);
	m_BtnGroup[3].MoveWindow(&rc);
	rc.OffsetRect(rc.Width()+4, 0);
	rc.right = rc.left + 32;
	m_BtnGroup[4].MoveWindow(&rc);

	//��ַ��
	rc.OffsetRect(rc.Width() + 4, 0);
	rc.right = rc.left + 30;
	m_BtnGroup[5].MoveWindow(&rc);
	rc.OffsetRect(rc.Width(), 0);
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		rc.right = rc.left + rcClient.Width() - (1024 - 530) + 26;
	}
	m_BtnGroup[6].MoveWindow(&rc);
	{
		CRect rx;
		m_BtnGroup[6].GetClientRect(&rx);
		m_CtrlUrl.MoveWindow(&rx);
	}
// 	rc.OffsetRect(rc.Width(), 0);
// 	rc.right = rc.left + 26;
// 	m_BtnGroup[7].MoveWindow(&rc);	//����
	rc.OffsetRect(rc.Width(), 0);
	rc.right = rc.left + 26;
	m_BtnGroup[8].MoveWindow(&rc);	//ˢ��
	rc.OffsetRect(rc.Width(), 0);
	rc.right = rc.left + 26;
	m_BtnGroup[9].MoveWindow(&rc);	//ֹͣ
	rc.OffsetRect(rc.Width(), 0);
	rc.right = rc.left + 65;
	m_BtnGroup[10].MoveWindow(&rc);	//GO.

	//��ַ������ť
	rc.OffsetRect(rc.Width()+4, 0);
	rc.right = rc.left + 99;
	m_BtnGroup[11].MoveWindow(&rc);

	rc.OffsetRect(rc.Width(), 0);		//�ұ߽���
	rc.right = rc.left + 6;
	rc.top = 0; rc.bottom +=6;
	m_BtnGroup[12].MoveWindow(&rc);
}

void CDockBrowseBar::OnClickButton(UINT id)
{
	CWnd* pParent = AfxGetMainWnd();
	if (pParent != NULL && pParent->m_hWnd != NULL)
	{
		id = id - DOCK_BROWSE_INDEX;
		pParent->SendMessage(WM_BROWSE_CLICK_MESSAGE, id, 0);
	}
}
