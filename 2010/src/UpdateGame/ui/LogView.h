#pragma once


// CLogView ��ͼ

class CLogView : public CListView
{
	DECLARE_DYNCREATE(CLogView)

protected:
	CLogView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CLogView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClearlog();
};


