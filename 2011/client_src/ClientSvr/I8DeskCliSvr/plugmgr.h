#ifndef _i8desk_plugmgr_h_
#define _i8desk_plugmgr_h_

#include <map>
#include "MultiThread/Lock.hpp"

namespace i8desk
{
	//ʵ��ͨ�����.
	class CCommunication :public ICommunication
	{
	private:
		ILogger*	m_pLogger;
		stdex::tString		m_SrvIP;
		SOCKET		m_sckTcp, m_sckUdp;
		HANDLE		m_hTcpThread, m_hUdpThread; 
		HANDLE		m_hExit;
        async::thread::AutoCriticalSection m_lockTcp;
	public:
		CCommunication(ILogger* pLogger);
		virtual ~CCommunication();
		virtual void	Release()	{ delete this; }
	public:
		//ʵ��ICommunication�ӿڵĺ���(UdpRecvNotify����)
		virtual bool Start();
		virtual void Stop();
		virtual SOCKET	GetTcpSocket() {return m_sckTcp;};
		virtual void Lock()   { m_lockTcp.Lock(); }
		virtual bool ExecCmd(char*pOutData, int nOutLen, char* &pInData, int& nInLen, bool bNeedAck);
		virtual void Unlock() { m_lockTcp.Unlock(); }
	private:
		//����,�ر�TCP,UDP.
		SOCKET _CreateUdpSocket();	//�����ɹ��󷵻�һ���µ�socket
		void   _CloseUdpSocket();
		SOCKET _ConnectTcpServer();	//���ӳɹ��󷵻�һ���µ�socket.
		void   _CloseTcpSocket();

		//���TCP�Ƿ�Ͽ�����������Ͽ�����Ҫ��������
		static UINT __stdcall TcpWorkThread(LPVOID lpVoid);

		//����UDP������,�����в���Ļص�
		static UINT __stdcall UdpWorkThread(LPVOID lpVoid);
	};

	//ʵ�ֲ��������
    typedef BOOL (WINAPI * PFNCREATELOGGER)(ILogger** ppILogger);
	class CPlugMgr : public ICliPlugMgr, public CCommunication
	{
	private:
		ILogger* m_pLogger;
		std::map<stdex::tString,  ICliPlug*> m_mapName2Plugs;		//���еĲ��
		typedef std::map<stdex::tString, ICliPlug*>::iterator	NAME2PLUGITER;
        async::thread::AutoCriticalSection m_lock;	
		PFNCREATELOGGER               pfnCreateLogger;
		HMODULE                       m_hFrame;
        BOOL                          m_bLoadLocalPlug;
	public:
		CPlugMgr(ILogger* pLogger):CCommunication(pLogger)	
		{ 
			m_pLogger = pLogger;	
			pfnCreateLogger = NULL;
			m_hFrame = NULL;
            m_bLoadLocalPlug = FALSE;
		}
		virtual	~CPlugMgr()									{						}
		virtual void			Release()					{ delete this;			}
        void LoadLocalPlug();
	public:
		//ʵ��IPlugMgr�ӿڳ�Ա����
		virtual ILogger*		CreateLogger();
		virtual ICommunication*	GetCommunication()			{ return this;			}
		virtual ICliPlug*		FindPlug(LPCTSTR plugName);
		virtual bool			Start();
        virtual void			Stop();
        virtual DWORD           SendMessage(DWORD cmd, DWORD param1, DWORD param2);
	private:
		//������ʵ��ICommunication��udp֪ͨ����
        virtual void	UdpRecvNotify(char* pData, int length, sockaddr_in& from);
	};
}
#endif