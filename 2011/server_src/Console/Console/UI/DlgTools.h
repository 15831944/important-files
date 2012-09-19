#pragma once

#include "../EasySize.h"
#include "../ui/WindowManager.h"

#include "Skin/SkinListCtrl.h"

// CDlgTools ������ͼ

class CDlgTools 
	: public i8desk::ui::BaseWnd
{
	DECLARE_EASYSIZE
	DECLARE_DYNCREATE(CDlgTools)

public:
	CDlgTools(CWnd* pParent = NULL);           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDlgTools();

public:
	enum { IDD = IDD_DLG_TOOLS };

private:
	typedef std::tr1::shared_ptr<ATL::CImage> ImagePtr;
	ImagePtr area_[5];
	ImagePtr workOutLine_;
	i8desk::ui::SkinListCtrl wndList_;


public:
	virtual void Register();
	virtual void UnRegister();
	virtual void OnRealDataUpdate();
	virtual void OnReConnect();
	virtual void OnAsyncData();
	virtual void OnDataComplate();

public:
	void OnBtnClick(size_t row, size_t btnPos);
	void OnInitCallback(size_t row);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

private:
	void _Init();
	void _PlugComplate(i8desk::TaskNotify taskNotify, DWORD gid);

private:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnLvnGetdispinfoListTools(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg LRESULT OnApplySelect(WPARAM, LPARAM);
};


