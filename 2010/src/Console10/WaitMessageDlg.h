#pragma once

#include <process.h>

#include <functional>

// CWaitMessageDlg �Ի���

class CWaitMessageDlg : public CDialog
{
	DECLARE_DYNAMIC(CWaitMessageDlg)

public:
	CWaitMessageDlg(LPCTSTR lpstr, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWaitMessageDlg();

// �Ի�������
	enum { IDD = IDD_WAIT_MESSAGE };
	
	//����ģ��:exec
	//ִ�в�������ʾ��ʾ�򣬲��������ʾ���Զ���ʧ
	//�������ǰ����ֹ����������������ʾ����ģ̬��
	//ģ�����: Op: �����ĺ����������ͣ���void(void)����
	//������op�������ĺ������󣬳�������ʹ��std::tr1::bind�õ���
	//ע�⣺op����һ����������ʱ�߳���ִ��
	//		����̴߳���ʧ�����˻�Ϊֱ�ӵ��ã���ʾ��Ҳ������ʾ
	//
	template<typename Op> void exec(Op op)
	{
		m_op = op;

		if (HANDLE h = (HANDLE)_beginthreadex(0, 0, work, this, 0, 0)) {
			 //ʹ��ģ̬�����û��Ľ�ֹ����������ֱ��op���
			this->DoModal();
			
 			//�ȴ�����op�Ĺ����߳̽���
			::WaitForSingleObject(h, INFINITE);
			::CloseHandle(h);
		} else {
			//�����߳�ʧ��ʱ���˻�Ϊֱ�ӵ���
			CWaitCursor wc;
			op(); 
		}
	}

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()

private:
	static const int MAX_DOT_NUM = 8;
	int m_progress;
	CString m_strMsg;					//��ʾ��Ϣ
	std::tr1::function<void()> m_op;	//Ҫ���Ĳ���
	CBrush m_brush;

	static UINT __stdcall work(void *p)
	{
		CWaitMessageDlg *pThis = reinterpret_cast<CWaitMessageDlg *>(p);

		::CoInitialize(0);
		pThis->m_op();
		::CoUninitialize();
		
		pThis->WaitForInitialComplete();
		return pThis->PostMessage(WM_CLOSE) ? 0 : -1;
	}

	void WaitForInitialComplete(void)
	{
		::WaitForSingleObject((HANDLE)s_event, INFINITE);
		::Sleep(50);
	}

	static CEvent s_event;
};
