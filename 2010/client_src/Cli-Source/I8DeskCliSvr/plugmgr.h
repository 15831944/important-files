#ifndef _i8desk_plugmgr_h_
#define _i8desk_plugmgr_h_

#include "../include/plug.h"
#include <map>

namespace i8desk
{
	//ʵ��ͨ�����.
	class CCommunication :public ICommunication
	{
	private:
		ILogger*	m_pLogger;
		tstring		m_SrvIP;
		SOCKET		m_sckTcp, m_sckUdp;
		HANDLE		m_hTcpThread, m_hUdpThread; 
		HANDLE		m_hExit;
		CLock		m_lockTcp;
		bool		m_bIsFirstPackage;
	public:
		CCommunication(ILogger* pLogger);
		virtual ~CCommunication();
		virtual void	Release()	{ delete this; }
	public:
		//ʵ��ICommunication�ӿڵĺ���(UdpRecvNotify����)
		virtual bool Start();
		virtual void Stop();
		virtual bool IsConnected();
		virtual void Lock()   { m_lockTcp.Lock(); }
		virtual bool ExecCmd(char*pOutData, int nOutLen, char* &pInData, int& nInLen, bool bNeedAck);
		virtual void UnLock() { m_lockTcp.UnLock(); }
		virtual void GetLocMachineInfo(tagLocMachineInfo& info);
		virtual bool IsFirstPackage();
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
	class CPlugMgr : public IPlugMgr, public CCommunication
	{
	private:
		ILogger* m_pLogger;
		std::map<tstring,  IPlug*> m_mapName2Plugs;		//���еĲ��
		typedef std::map<tstring,     IPlug*>::iterator	NAME2PLUGITER;
		CLock m_lock;	
	public:
		CPlugMgr(ILogger* pLogger):CCommunication(pLogger)	{ m_pLogger = pLogger;	}
		virtual	~CPlugMgr()									{						}
		virtual void			Release()					{ delete this;			}
	public:
		//ʵ��IPlugMgr�ӿڳ�Ա����
		virtual ILogger*		CreateLogger();
		virtual ICommunication*	GetCommunication()			{ return this;			}
		virtual IPlug*			FindPlug(LPCTSTR plugName);
		virtual bool			Start();
		virtual void			Stop();
	private:
		//������ʵ��ICommunication��udp֪ͨ����
		virtual void	UdpRecvNotify(char* pData, int length, sockaddr_in& from);
	};
}
#endif