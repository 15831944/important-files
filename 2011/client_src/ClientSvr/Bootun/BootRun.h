#ifndef _i8desk_bootrun_h_
#define _i8desk_bootrun_h_

I8_NAMESPACE_BEGIN

ICliPlug* WINAPI CreateClientPlug(DWORD dwReserved);
//������
#define    PLUG_VERSION		          0x01000000L
#define    PLUG_COMPANY		          TEXT("Goyoo")
#define    PLUG_DESCRIPTION	          TEXT("BootRun Plug")
#define    PLUG_PORT			      0
//�������
class CBootRunPlug : public ICliPlug
{
    //��������
public:
	CBootRunPlug();
	virtual ~CBootRunPlug();

	//�ӿ�ʵ��
public:
	virtual LPCTSTR                   GetPlugName();
	virtual DWORD                     GetVersion();
	virtual LPCTSTR                   GetCompany();
	virtual LPCTSTR                   GetDescription();
	virtual bool	                  Initialize(ICliPlugMgr* pPlugMgr);
	virtual bool	                  UnInitialize();
	virtual DWORD	                  SendMessage(DWORD cmd, DWORD param1, DWORD param2);
	virtual bool                      NeedUdpNotity();
	virtual void	                  UdpRecvNotify(char* pData, int length, sockaddr_in& from);
	virtual void	                  Release();

	//�����߳�
public:
	UINT                              WorkThread();
    static UINT __stdcall             WorkThreadEx(PVOID pParam);
    void                              AddTask(CTask* pTask, BOOL bAutoFree = TRUE);

private:
	ICliPlugMgr                       *m_pPlugMgr;
	ILogger                           *m_pLogger;
	HANDLE                            m_hExit;
	//�����߳�
	HANDLE	                		  m_hThread;	
	CDataCenter*                      m_pDataCenter;
};


I8_NAMESPACE_END
#endif