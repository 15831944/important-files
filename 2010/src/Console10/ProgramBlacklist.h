#pragma once

#include "resource.h"

// CProgramBlacklist �Ի���

class CProgramBlacklist : public CDialog
{
	DECLARE_DYNAMIC(CProgramBlacklist)

public:
	CProgramBlacklist(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProgramBlacklist();

// �Ի�������
	enum { IDD = IDD_PROGRAM_BLACKLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strProgram;
	CString m_strDescription;
	afx_msg void OnBnClickedSelect();
	afx_msg void OnBnClickedOk();
};
