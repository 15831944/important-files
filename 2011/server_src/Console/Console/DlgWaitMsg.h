#pragma once


#include <functional>

// CDlgWaitMsg �Ի���

class CDlgWaitMsg : public CDialog
{
	DECLARE_DYNAMIC(CDlgWaitMsg)

public:
	CDlgWaitMsg(size_t maxTime = -1, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWaitMsg();

// �Ի�������
	enum { IDD = IDD_DIALOG_WAIT_MSG };

private:
	typedef std::tr1::function<void()> Callback;

	size_t progress_;
	size_t maxTime_;
	static const size_t MAX_DOT = 8;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	
public:
	//����ģ��:exec
	//ִ�в�������ʾ��ʾ�򣬲��������ʾ���Զ���ʧ
	//�������ǰ����ֹ����������������ʾ����ģ̬��
	//ģ�����: Op: �����ĺ����������ͣ���void(void)����
	//������op�������ĺ������󣬳�������ʹ��std::tr1::bind�õ���
	//
	void Exec(const Callback &op);

public:
	DECLARE_MESSAGE_MAP()
	
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
