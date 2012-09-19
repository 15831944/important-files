#ifndef _i8desk_plug_h_
#define _i8desk_plug_h_

#include "DbEngine.h"
#include "NetLayer.h"
#include "define.h"
#include "irtdatasvr.h"

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

	template <class T>
	struct CGuard		
	{
	private:
		T& m_lock;
	public:
		CGuard(T &lock) : m_lock(lock) 
		{
			m_lock.Lock();
		}
		~CGuard()
		{
			m_lock.UnLock();
		}
	};

	template <class T>
	void Release_Interface(T &pt)
	{
		if (pt != NULL)
			pt->Release();
		pt = NULL;
	}

	template <typename T>
	void Delete_Pointer(T* & p)
	{
		if (p != NULL)
		{
			delete p;
			p = NULL;
		}
	}
	template <typename T>
	void Delete_Array(T* &p)
	{
		if (p != NULL)
		{
			delete []p;
			p = NULL;
		}
	}

	//forward declare.
	struct IPlug;

	//����ܳ�����ʵ�ָýӿ�.
	struct IPlugMgr
	{
		//�ͷŲ��
		virtual void		Release()					= 0;

		//�õ��ײ�����ݿ�ͳһ����ӿ�.
		virtual IDatabase*	GetDatabase()				= 0;

		//�õ��ײ��ϵͳѡ��ӿ�
		virtual ISysOpt*	GetSysOpt()					= 0;

		//������־���
		virtual ILogger*	CreateLogger()				= 0;

		//ͨ��������ֲ��Ҿ���ϵͳ���ص�һ�����.ÿ�������һ��Ψһ����������ʶ
		virtual IPlug*		FindPlug(LPCTSTR plugName)	= 0;

		//�������������,�������������ϵͳ�ĺ�������Լ������
		virtual bool		Start()						= 0;

		//ֹͣ���������,�������ͷ����м��ص����
		virtual bool		Stop()						= 0;
	};

	//ҵ��������ʵ��һ��IPlug�ӿ��У�������һ����������,�������������
	struct IPlug : public INetLayerEvent	//ÿ�������������INetLayerEvent��������ʵ�������¼��Ĵ���
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

		//��������Ҫ��ܼ���������˿ڣ��������Ҫ�������򷵻�0.
		//������յ��ö˿��¼�ʱ����ص����ýӿڵ�INetLayerEvent��Ӧ���麯��
		virtual DWORD   GetListPort()					= 0;
		
		//����ڲ��ĳ�ʼ������,��IPlugMgr����һ����������øú���
		virtual bool	Initialize(IPlugMgr* pPlugMgr)	= 0;

		//��IPlugMgr�˳�ʱ����ȵ��øú����󣬲ŵ���Release()���ͷŲ����
		virtual bool	UnInitialize() 					= 0;

		//����ܻ��������������ͨ���ú������໥������������Windows����Ϣ����,
		//����cmd�Ĳ�ͬ��param1,parma2ʵ�ʵ������벻ͬ.
		//�����Ҫ�ڲ���ڲ������ڴ淵�ظ������ߡ������ڲ�ͨ��CoTaskMemFree�������ڴ棬
		//������ͨ��CoTaskMemFree���ͷŲ��������ڴ棬��˲���ӿڲ����ṩ�����ڴ�����ͷ��ڴ�.
		virtual DWORD	SendMessage(DWORD cmd, DWORD param1, DWORD param2) = 0;
	};


	//ÿ����������ú������͵ĺ��������Ҹú�����ת�������1.���Һ�������CreatePlug.
	typedef IPlug* (WINAPI *PFNCREATEPLUG)();
}
#endif