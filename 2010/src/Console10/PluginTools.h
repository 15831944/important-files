#pragma once
#include "afxcmn.h"

#include "PlugListCtrlEx.h"

// CPluginTools �Ի���

class CPluginTools 
	: public CDialog
{
	DECLARE_DYNAMIC(CPluginTools)

	enum { UPDATE_MSG = WM_USER + 128, UPDATE_PROGRESS };

public:
	CPluginTools(bool &needList, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPluginTools();

// �Ի�������
	enum { IDD = IDD_DIALOG_PLUGIN_TOOLS };

private:
	std::vector<std::tr1::shared_ptr<Gdiplus::Bitmap>> bmps_;
	CImageList  m_imageList;
	CPlugListCtrlEx m_wndList;

	bool &needList_;	// �Ƿ���Ҫ����б�


protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

private:
	void _UpdateData();
	void _UpdateProgress(long, size_t);

	bool _DownloadPlug(long);
	bool _StartPlug(long);
	bool _StopPlug(long);
	bool _OptionPlug(long);
	void _ButtonClick(UINT uID, int item, int subItem);
	
public:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnUpdateData(WPARAM, LPARAM);
	afx_msg LRESULT OnUpdateProgress(WPARAM, LPARAM);
};
