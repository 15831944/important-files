
// ViewClientDlg.h : ͷ�ļ�
//

#pragma once


#include <memory>
#include <deque>
#include "../../../include/Utility/SmartHandle.hpp"


namespace view
{
	class DataMgr;
	typedef std::tr1::shared_ptr<DataMgr> DataMgrPtr;
}


// CViewClientDlg �Ի���
class CViewClientDlg : public CDialog
{
// ����
public:
	CViewClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VIEWCLIENT_DIALOG };
	
	struct BitmapInfo
	{
		utility::BITMAPPtr bmp_;
		size_t width_;
		size_t height_;
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual BOOL OnInitDialog();

// ʵ��
protected:
	HICON m_hIcon;
	view::DataMgrPtr dataMgrI_;
	view::DataMgrPtr dataMgrJ_;

	std::deque<BitmapInfo> bitmapHandlesI_;
	std::deque<BitmapInfo> bitmapHandlesJ_;
	ATL::CImage img_;

	ATL::CImage bk_;
	ATL::CImage bkAll_;

public:
	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnRefreshUI_I(WPARAM, LPARAM);
	afx_msg LRESULT OnRefreshUI_J(WPARAM, LPARAM);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
