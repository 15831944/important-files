#ifndef _i8desk_client_plug_h_
#define _i8desk_client_plug_h_

#include "DbEngine.h"
#include "NetLayer.h"
#include "define.h"
#include "hy.h"

namespace i8desk
{
	//ͬ��������.
	class CLock
	{
	private:
		CRITICAL_SECTION m_lock;
	public:
		CLock()			{ InitializeCriticalSection(&m_lock);	}
		~CLock()		{ DeleteCriticalSection(&m_lock);		}
		void Lock()		{ EnterCriticalSection(&m_lock);		}
		void UnLock()	{ LeaveCriticalSection(&m_lock);		}
	};

	//ͬ��guard������  ex:CLock m_lock; CAutoLock<CLock> lock(m_lock);
	template <class T>
	struct CAutoLock		
	{
	private:
		T* m_pT;
	public:
		CAutoLock(T* pt): m_pT(pt) 
		{
			if (m_pT != NULL)
				m_pT->Lock();
		}
		~CAutoLock()
		{
			if (m_pT != NULL)
				m_pT->UnLock();
		}
	};

	//�ͷŽӿ�����ĸ�������	
	template <class T>
	void Release_Interface(T &pt)
	{
		if (pt != NULL)
			pt->Release();
		pt = NULL;
	}

	//�ͻ��������˵�ͨ�����.(����tcpͨ�ţ��Լ�udp֪ͨ)
	typedef struct tagLocMachineInfo
	{
		TCHAR szName[MAX_PATH];			//�������
		TCHAR szIp[MAX_PATH];			//IP��ַ
		TCHAR szGate[MAX_PATH];			//����
		TCHAR szSubMask[MAX_PATH];		//��������
		TCHAR szDNS0[MAX_PATH];			//DNS1��ַ
		TCHAR szDNS1[MAX_PATH];			//DNS2��ַ	
		TCHAR szMac[MAX_PATH];			//MAC��ַ
		DWORD ProtInstal;				//�Ƿ�װ��ԭ
		TCHAR ProtArea[MAX_PATH];		//��ԭ����������
		TCHAR AllDrivers[MAX_PATH];		//���з���
		TCHAR ProtVer[MAX_PATH];		//��ԭ�汾
		TCHAR MenuVer[MAX_PATH];		//�˵��汾
		TCHAR CliSvrVer[MAX_PATH];		//�ͻ��˰汾

	}tagLocMachineInfo;
	struct ICommunication
	{
		//�ͷŲ��
		virtual void	Release()									= 0;

		//����ͨ�����(�ڲ���TCP, UDP)
		virtual bool    Start()										= 0;

		//ֹͣͨ�����(�ڲ��ر�TCP, UDP)
		virtual void	Stop()										= 0;

		//�鿴�����Ƿ���(TCP, UDP)
		virtual bool	IsConnected()								= 0;

		//��TCP��ʽ�ͷ���˽���һ��ͨ��
		virtual void	Lock()										= 0;
		virtual bool	ExecCmd(char*pOutData, int nOutLen, char* &pInData, int& nInLen, bool bNeedAck = true) = 0;
		virtual void	UnLock()									= 0;

		//���յ���udp���ݵĻص�����
		virtual void	UdpRecvNotify(char* pData, int length, sockaddr_in& from)	= 0;

		virtual void    GetLocMachineInfo(tagLocMachineInfo& info)	= 0;

		//add by liubin.2009/09/01.��ʾ�Ƿ������ӽ������һ������
		virtual bool	IsFirstPackage()							= 0;
	};
	struct IPlug;

	struct IPlugMgr
	{
		//�ͷŲ��
		virtual void			Release()				= 0;

		//������־���.������Ҫ�ǵõ���ILogger->Release().
		virtual ILogger*		CreateLogger()			= 0;

		//�õ������ʵ�ֵ�ͨ�Žӿ�ָ��
		virtual ICommunication*	GetCommunication()		= 0;

		//ͨ��������ֲ��Ҿ���ϵͳ���ص�һ�����.ÿ�������һ��Ψһ����������ʶ
		virtual IPlug*			FindPlug(LPCTSTR plugName)	= 0;

		//�������������,�������������ϵͳ�ĺ�������Լ������
		virtual bool			Start()					= 0;

		//ֹͣ���������,�������ͷ����м��ص����
		virtual void			Stop()					= 0;
	};

	
	//ҵ��������ʵ��һ��IPlug�ӿ��У�������һ����������,�������������
	struct IPlug
	{
		//�ͷŲ��
		virtual void	Release()						= 0;

		//�õ����������
		virtual LPCTSTR GetPlugName()					= 0;
		//�õ�����İ汾0xaabbccdd.
		virtual DWORD  	GetVersion() 					= 0;
		//�õ���������Ĺ�˾��
		virtual LPCTSTR GetCompany()					= 0;
		//�õ������һЩ����
		virtual LPCTSTR GetDescription() 				= 0;

		virtual bool    NeedUdpNotity()					= 0;

		//����ڲ��ĳ�ʼ������,��IPlugMgr����һ����������øú���
		virtual bool	Initialize(IPlugMgr* pPlugMgr)	= 0;
		//��IPlugMgr�˳�ʱ����ȵ��øú����󣬲ŵ���Release()���ͷŲ����
		virtual bool	UnInitialize() 					= 0;

		//����ܻ��������������ͨ���ú������໥������������Windows����Ϣ����,
		//����cmd�Ĳ�ͬ��param1,parma2ʵ�ʵ������벻ͬ.
		//�����Ҫ�ڲ���ڲ������ڴ淵�ظ������ߡ������ڲ�ͨ��CoTaskMemFree�������ڴ棬
		//������ͨ��CoTaskMemFree���ͷŲ��������ڴ棬��˲���ӿڲ����ṩ�����ڴ�����ͷ��ڴ�.
		virtual DWORD	SendMessage(DWORD cmd, DWORD param1, DWORD param2) = 0;

		//���յ���udp���ݵĻص�����
		virtual void	UdpRecvNotify(char* pData, int length, sockaddr_in& from) = 0;
	};


	//ÿ����������ú������͵ĺ��������Ҹú�����ת�������1.���Һ�������CreatePlug.
	typedef IPlug* (WINAPI *PFNCREATEPLUG)();	
}
#endif