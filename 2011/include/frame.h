#ifndef __plug_inc__
#define __plug_inc__

#pragma once
#pragma warning(disable:4200)

#include "define.h"
#include "irtdatasvr.h"

#import "c:\program Files\Common Files\System\ADO\msado15.dll" no_namespace rename("EOF","adoEOF")

namespace i8desk
{


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

//ͳһ�����ݲ����ӿ�.
struct IDatabase 
{
	//�ͷŽӿ�
	virtual void Release()			= 0;

	//�����ݿ�
	virtual bool Open(LPCTSTR lpszConnString, LPCTSTR lpszUser = TEXT(""), LPCTSTR lpszPassword = TEXT("")) = 0;

	//�ر����ݿ�
	virtual void Close()			= 0;

	//�õ����ݿ�����������Ϣ
	virtual LPCTSTR GetErrInfo()	= 0;

	//�õ���Ӧ�õĴ������
	virtual long GetErrCode()		= 0;

	//��ס���ݿ����
	virtual void Lock()				= 0;

	//�������ݿ����
	virtual void UnLock()			= 0;

	//���������ʼ���ύ���ع�����
	virtual void BeginTrans()		= 0;
	virtual void CommitTrans()		= 0;
	virtual void RollbackTrans()	= 0;

	//ִ��SQL���.����Ҫ�õ����ؽ��������ǲ����ɾ�����޸ģ�����ͨ���ڶ��������õ�Ӱ����С�
	//�������Ҫ�ڶ���������ֵ���������ÿգ����߲����Ĭ��ֵ��
	virtual bool ExecSql(LPCTSTR lpszSql, PLONG RecordsAffected = NULL) = 0;

	//ִ��SQL���.��Ҫ�õ����صĽ����.���ص��ǣ��ģϵ�Recordset�ӿڽӿ�.����ɹ���Ҫ�Լ�ִ��prcd->Close();
	//ex. 
	//	CAutoLock<IDatabase> lock(m_pDatabase);
	//  _RecordsetPrt prcd;
	//  if (m_pDatabase->ExecSql(lpszSql, prcd))
	//	{
	//		while (prcd->IsEof() == VARIANT_FALSE)
	//		{
	//			//get line value.	
	//		}
	//		prcd->Close();
	//		prcd.Release();	//���Բ���Ҫ����������������ָ����Լ������ͷŽӿڡ�
	//	}
	//	else
	//		OutputDebugString(m_pDatabase->GetErrInfo());

	virtual bool ExecSql(LPCTSTR lpszSql, _RecordsetPtr& prcd)			= 0;

	//���ߺ���:ѹ�����ݿ�.ֻ��Ҫû�д�����ʱ����ѹ��.
	virtual bool CompactDatabase(LPCTSTR lpszDbFile) = 0;
};

//ϵͳͳһ��ѡ������������Ǵ��������ݿ����һ�����
struct ISysOpt
{
	//�ͷŽӿ�
	virtual void	Release()										= 0;

	//09�����ó����ݿ�������10�����ó����ݿ⻺��������ص�ѡ���ָ�롣(11��10��ͬ)
	virtual void	SetIDatabase(void* pDatabase)					= 0;

	//�õ�ϵͳѡ��.�������û�����ѡ����Զ����룬��д��Ĭ��ֵ
	virtual bool	GetOpt(LPCTSTR optName, bool defValue = true)	= 0;
	virtual long	GetOpt(LPCTSTR optName, long defValue = 0)		= 0;
	virtual __int64 GetOpt(LPCTSTR optName, __int64 defValue = 0)	= 0;
	virtual void	GetOpt(LPCTSTR optName, LPTSTR lpszValue, LPCTSTR defValue = TEXT("")) = 0;

	//����ϵͳѡ��.�������û�����ѡ����Զ����룬��д�����õ�ֵ
	virtual void	SetOpt(LPCTSTR optName, bool optValue)			= 0;
	virtual void	SetOpt(LPCTSTR optName, long optValue)			= 0;
	virtual void	SetOpt(LPCTSTR optName, __int64 optValue)		= 0;
	virtual void	SetOpt(LPCTSTR optName, LPCTSTR optValue)		= 0;
};

//ϵͳͨ��д��־����������������һ��Ҫ�����Լ�����־�ļ������������ļ������ڣ������ļ�����-yyyymmdd.log��
enum I8_Log_Priority
{
	LM_DEBUG	= 0,		//������Ϣ
	LM_INFO		= 1,		//��������־���
	LM_WARNING	= 2,		//��ʾ�п����������⣬������ȷ��
	LM_ERROR	= 3			//��ʾ����ʱ������������־����Ҫ�û��ֹ�����
};

struct ILogger
{
	virtual void Release()	= 0;

	//������־�ļ���.����Ҫ�ļ���(��Ҫ��·���Լ���չ��).����log,������ɵ��ļ�����\log\log-yyymmdd.log.
	//�ڲ����Զ����ݵ��������������־���������Զ����ļ�������ӵ�������ڣ���������չ��.log,��ͳһ�ŵ�logĿ¼��
	//�����Բ������Ϊ��־�ļ���.���������е���־�ļ��������ظ���Ҳ����鿴
	virtual void SetLogFileName(LPCTSTR lpszLogFile)	= 0;

	//������־�ļ����Ĵ�С��(�ֽ�Ϊ��λ)
	virtual void SetMaxLogSize(DWORD dwMaxSize)			= 0;

	//��ÿ����־ǰ�����־���������
	virtual void SetAddDateBefore(bool bAddDate)		= 0;

	//��ÿ����־�����һ���س����з�
	virtual void SetAddCrLfAfter(bool bAddCrLf)			= 0;

	//���ö���ڲ����ԡ�
	virtual void SetProptery(LPCTSTR lpszLogFile, DWORD dwMaxLogSize, bool bAddDate) = 0;

	//������־���������̨��ip,port.�ڲ�ͨ��udp��������̨��//������
	virtual void SetConsole(DWORD ip, DWORD port)		= 0;

	//�õ����������
	virtual LPCTSTR GetLogFileName()					= 0;
	virtual DWORD	GetMaxLogSize()						= 0;
	virtual bool	GetAddCrLfAfter()					= 0;
	virtual bool	GetAddDateBefore()					= 0;

	//дһ����־������
	virtual void __cdecl WriteLog(DWORD level, LPCTSTR lpszFormater, ...)		= 0;

	//������е���־
	virtual void CleanLog()								= 0;
};

BOOL WINAPI CreateDatabase(IDatabase** ppIDatabase);
BOOL WINAPI CreateSysOpt(ISysOpt** ppISysOpt);
BOOL WINAPI CreateLogger(ILogger** ppILogger);


//���ݰ�Э��ͷ
#define START_FLAG		0x5E7D
typedef struct pkgheader
{
	WORD  StartFlag;
	WORD  Cmd;
	DWORD Length;
	WORD  Version;
	BYTE  Resv[6];
	BYTE  data[0];
}pkgheader;

//�ڴ�������ʹ��INetLayer���������ͨ�����ڴ����������գ����ͻ�����
struct IMemPool
{
	virtual void  Release() = 0;

	//��ʼ���з���Ľڵ���,ÿ������Ĵ�С,��������
	virtual void  SetDefault(DWORD dwdefPoolSize, DWORD dwdefBlockSize, DWORD dwdefIncrease) = 0;
	virtual DWORD GetDefPoolSize() = 0;		
	virtual DWORD GetDefBlockSize() = 0;
	virtual DWORD GetDefIncrease() = 0;

	//���䣬�ͷţ��ͷ������ڴ���нڵ�
	virtual char* Alloc(DWORD dwSize=0) = 0;	//����������Ĭ�ϵĽڵ���Сʱ����Ҫ������Ҫ����Ĵ�С
	virtual void  Free(void* pBlock) = 0;
	virtual void  FreeAll() = 0;

	//�õ������һ���ڵ�Ĵ�С
	virtual DWORD GetBufSize(void* pBlock) = 0; 
	//����ڴ�ڵ��Ƿ���ڴ���з���
	virtual BOOL  IsAllocFrom(void* pBlock) = 0;
};

struct INetLayerEvent;

//���ݰ�ͷ������������ڷְ��������û����INetLayer����һ��ʵ����������ڲ���һ��Ĭ��ʵ�֡�
struct IPackageParse
{
	virtual void  Release() = 0;
	virtual DWORD ParasePackage(char* package, DWORD length) = 0;
};

//��������
struct INetLayer
{
	virtual void Release() = 0;

	//���ã�ȡ��������¼�����ӿ�ָ��
	virtual void SetINetLayerEvent(INetLayerEvent* pINetLayerEvent) = 0;
	virtual INetLayerEvent* GetINetLayerEvent() = 0;

	//���ã�ȡ���ڴ�ؽӿ�ָ��
	virtual void SetIMemPool(IMemPool* pIMemPool) = 0;
	virtual IMemPool* GetIMemPool() = 0;

	//���ã�ȡ�ð������ӿ�ָ��
	virtual void SetIPackageParse(IPackageParse* pPackageParse) = 0;
	virtual IPackageParse* GetIPackageParse() = 0;

	//��������㣬ֹͣ��������
	virtual DWORD Start(WORD wPort = 7918) = 0; //��������Ҫ�����Ķ˿�
	virtual void  Stop() = 0;
	virtual WORD  GetPort() = 0;

	//���͸��ͻ���һ�����ݰ�
	virtual void  SendPackage(SOCKET sck, LPSTR pPackage, DWORD length) = 0;

	//����������Ͽ�һ���ͻ���
	virtual void  DisConnect(SOCKET sck) = 0;
};

struct INetLayerEvent
{
	virtual void Release() = 0;

	//���ͻ�����������ʱ���������¼�
	virtual void OnAccept(INetLayer*pNetLayer, SOCKET sck, DWORD param) = 0;

	//������˷��ͻ��˷������һ�����ݰ�ʱ�������¼�
	virtual void OnSend(INetLayer*pNetLayer, SOCKET sck, LPCSTR lpPackage, DWORD param) = 0; 

	//������˽��յ��ͻ���һ�����������ʱ���������¼���Ӧ�ò㴦��һ������
	virtual void OnRecv(INetLayer*pNetLayer, SOCKET sck, LPCSTR lpPackage, DWORD param) = 0;

	//���ͻ��˶Ͽ�ʱ�������¼�.
	virtual void OnClose(INetLayer*pNetLayer, SOCKET sck, DWORD param) = 0;
};

BOOL __stdcall CreateIMemPool(IMemPool** pIMemPool);
BOOL __stdcall CreateINetLayer(INetLayer** pINetLayer);

//����˲�������������Ľӿڶ���
//forward declare.
struct ISvrPlug;

struct ISvrPlugMgr
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
	virtual ISvrPlug*	FindPlug(LPCTSTR plugName)	= 0;

	//�������������,�������������ϵͳ�ĺ�������Լ������
	virtual bool		Start()						= 0;

	//ֹͣ���������,�������ͷ����м��ص����
	virtual bool		Stop()						= 0;
};

//ҵ��������ʵ��һ��ISvrPlug�ӿ��У�������һ����������,�������������
struct ISvrPlug : public INetLayerEvent	//ÿ�������������INetLayerEvent��������ʵ�������¼��Ĵ���
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

	//����ڲ��ĳ�ʼ������,��ISvrPlugMgr����һ����������øú���
	virtual bool	Initialize(ISvrPlugMgr* pPlugMgr)	= 0;

	//��ISvrPlugMgr�˳�ʱ����ȵ��øú����󣬲ŵ���Release()���ͷŲ����
	virtual bool	UnInitialize() 					= 0;

	//����ܻ��������������ͨ���ú������໥������������Windows����Ϣ����,
	//����cmd�Ĳ�ͬ��param1,parma2ʵ�ʵ������벻ͬ.
	//�����Ҫ�ڲ���ڲ������ڴ淵�ظ������ߡ������ڲ�ͨ��CoTaskMemFree�������ڴ棬
	//������ͨ��CoTaskMemFree���ͷŲ��������ڴ棬��˲���ӿڲ����ṩ�����ڴ�����ͷ��ڴ�.
	virtual DWORD	SendMessage(DWORD cmd, DWORD param1, DWORD param2) = 0;
};

//ÿ����������ú������͵ĺ��������뱣֤��������CreateSvrPlug.
typedef ISvrPlug* (WINAPI *PFNCREATESVRPLUG)(DWORD Reserved);

//�ͻ��˲�������������Ľӿڶ���
struct ICommunication
{
	//�ͷŲ��
	virtual void	Release()									= 0;

	//����ͨ�����(�ڲ���TCP, UDP)
	virtual bool    Start()										= 0;

	//ֹͣͨ�����(�ڲ��ر�TCP, UDP)
	virtual void	Stop()										= 0;

	//��ȡTCP�����׽��֡�����INVALID_SOCKET��ʾû��������
	virtual SOCKET	GetTcpSocket()								= 0;

	//��TCP��ʽ�ͷ���˽���һ��ͨ��
	virtual void	Lock()										= 0;
	virtual bool	ExecCmd(char*pOutData, int nOutLen, char* &pInData, int& nInLen, bool bNeedAck = true) = 0;
	virtual void	Unlock()									= 0;

	//���յ���udp���ݵĻص�����
	virtual void	UdpRecvNotify(char* pData, int length, sockaddr_in& from)	= 0;
};

//forward decalre.
struct ICliPlug;

struct ICliPlugMgr
{
	//�ͷŲ��
	virtual void			Release()				= 0;

	//������־���.������Ҫ�ǵõ���ILogger->Release().
	virtual ILogger*		CreateLogger()			= 0;

	//�õ������ʵ�ֵ�ͨ�Žӿ�ָ��
	virtual ICommunication*	GetCommunication()		= 0;

	//ͨ��������ֲ��Ҿ���ϵͳ���ص�һ�����.ÿ�������һ��Ψһ����������ʶ
	virtual ICliPlug*		FindPlug(LPCTSTR plugName)	= 0;

	//�������������,�������������ϵͳ�ĺ�������Լ������
	virtual bool			Start()					= 0;

	//ֹͣ���������,�������ͷ����м��ص����
    virtual void			Stop()					= 0;

    //������������������������
    virtual DWORD           SendMessage(DWORD cmd, DWORD param1, DWORD param2) = 0;
};


//ҵ��������ʵ��һ��IPlug�ӿ��У�������һ����������,�������������
struct ICliPlug
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

	//����ڲ��ĳ�ʼ������,��ICliPlugMgr����һ����������øú���
	virtual bool	Initialize(ICliPlugMgr* pPlugMgr)	= 0;
	//��ICliPlugMgr�˳�ʱ����ȵ��øú����󣬲ŵ���Release()���ͷŲ����
	virtual bool	UnInitialize() 					= 0;

	//����ܻ��������������ͨ���ú������໥������������Windows����Ϣ����,
	//����cmd�Ĳ�ͬ��param1,parma2ʵ�ʵ������벻ͬ.
	//�����Ҫ�ڲ���ڲ������ڴ淵�ظ������ߡ������ڲ�ͨ��CoTaskMemFree�������ڴ棬
	//������ͨ��CoTaskMemFree���ͷŲ��������ڴ棬��˲���ӿڲ����ṩ�����ڴ�����ͷ��ڴ�.
	virtual DWORD	SendMessage(DWORD cmd, DWORD param1, DWORD param2) = 0;

	//���յ���udp���ݵĻص�����
	virtual void	UdpRecvNotify(char* pData, int length, sockaddr_in& from) = 0;
};


//ÿ����������ú������͵ĺ��������Ҹú�����ת�������1.���Һ�������CreateClientPlug.
typedef ICliPlug* (WINAPI *PFNCREATECLIENTPLUG)(DWORD Reserved);

class CPkgHelper
{
private:
	LPSTR  m_lpPackage;
	size_t m_nBufSize;
	DWORD  m_dwPosition;
public:
	//for push construct.
	CPkgHelper(LPSTR lpPackage, size_t nBufSize) : m_lpPackage(lpPackage), m_nBufSize(nBufSize),
		m_dwPosition(sizeof(pkgheader))
	{
		GetHeader()->StartFlag	= START_FLAG;
		GetHeader()->Version	= PRO_VERSION;
		GetHeader()->Length		= sizeof(pkgheader);
	}

	CPkgHelper(LPSTR lpPackage, size_t nBufSize, WORD cmd, OBJECT_TYPE type) 
		: m_lpPackage(lpPackage)
		, m_nBufSize(nBufSize)
		, m_dwPosition(sizeof(pkgheader))
	{
		GetHeader()->StartFlag	= START_FLAG;
		GetHeader()->Version	= PRO_VERSION;
		GetHeader()->Length		= sizeof(pkgheader);
		GetHeader()->Cmd		= cmd;
		GetHeader()->Resv[0]	= (BYTE)type;
	}

	template<size_t N>
	explicit CPkgHelper(char (&arr)[N]) 
		: m_lpPackage(arr)
		, m_nBufSize(N)
		, m_dwPosition(sizeof(pkgheader))
	{
		GetHeader()->StartFlag	= START_FLAG;
		GetHeader()->Version	= PRO_VERSION;
		GetHeader()->Length		= sizeof(pkgheader);
	}

	template<size_t N>
	CPkgHelper(char (&arr)[N], WORD cmd, OBJECT_TYPE type) 
		: m_lpPackage(arr)
		, m_nBufSize(N)
		, m_dwPosition(sizeof(pkgheader))
	{
		GetHeader()->StartFlag	= START_FLAG;
		GetHeader()->Version	= PRO_VERSION;
		GetHeader()->Cmd        = cmd;
		GetHeader()->Length		= sizeof(pkgheader);
		GetHeader()->Resv[0]	= type;
	}

	//for pop construct.
	explicit CPkgHelper(LPCSTR lpPackage) 
		: m_lpPackage(const_cast<LPSTR>(lpPackage))
		, m_nBufSize(0)
		, m_dwPosition(sizeof(pkgheader))
	{
		m_nBufSize = GetHeader()->Length;
	}
public:	
	pkgheader* GetHeader()				{ return reinterpret_cast<pkgheader*>(m_lpPackage); }
	LPCSTR	GetBuffer(void) const		{ return m_lpPackage;				}
	void	SetLength(DWORD dwLength)	{ GetHeader()->Length = dwLength;	}
	DWORD	GetLength()					{ return GetHeader()->Length;		}

	void	pushHeader(pkgheader& header)  { *GetHeader() = header;			}
	void	popHeader(pkgheader& header)   { header = *GetHeader();			}

	template <typename T>
	void Push(const T& Elem)
	{
		int nSize = sizeof(T);
		memcpy(m_lpPackage + m_dwPosition, (void*)&Elem, nSize);
		m_dwPosition += nSize;
		GetHeader()->Length = m_dwPosition;
	}

	template <typename T>
	void PushPointer(const T* pointer, int nCount = 1)
	{
		int nSize = sizeof(T) * nCount;
		memcpy(&m_lpPackage[m_dwPosition], (void*)pointer, nSize);
		m_dwPosition += nSize;
		GetHeader()->Length = m_dwPosition;
	}
	
	template <typename T>
	void PushString(const T* pString, int nCharNums)
	{
		Push(nCharNums);
		PushPointer(pString, nCharNums);
		Push(T(0));
	}

	template <typename T, size_t N>
	void PushString(const T (&arr)[N])
	{
		struct StringLenHelper
		{
			size_t len_;

			StringLenHelper(const char *str)
			{ len_ = strlen(str);	}
			StringLenHelper(const wchar_t *str)
			{ len_ = wcslen(str);	}

			size_t operator()() const
			{ return len_;			}
		};
		size_t len = StringLenHelper(arr)();

		PushString(arr, len);
    }
    void PushDWORD(const DWORD& Elem)
    {
        int nSize = sizeof(DWORD);
        memcpy(m_lpPackage + m_dwPosition, (void*)&Elem, nSize);
        m_dwPosition += nSize;
        GetHeader()->Length = m_dwPosition;
    }


	template <typename T>
	T Pop(T& Elem)
	{
		memcpy((void*)&Elem, m_lpPackage + m_dwPosition, sizeof(T));
		m_dwPosition += sizeof(T);
		return Elem;
	}

	template <typename T>
	void PopPointer(T* pointer, int nCount = 1)
	{
		int nSize = nCount * sizeof(T);
		memcpy((void*)pointer, m_lpPackage + m_dwPosition, nSize);
		m_dwPosition += nSize;
	}

	template <typename T>
	DWORD PopString(T* pString, int nCharNums)
	{
		DWORD length = 0;
		Pop(length);
		
		if( nCharNums < (int)length )
			throw std::out_of_range("package out of range");

		PopPointer(pString, length + 1);
		return length;
	}

	template <typename T, size_t N>
	DWORD PopString(T (&arr)[N])
	{
		DWORD length = 0;
		Pop(length);

		if( N < length  )
			throw std::out_of_range("package out of range");

		PopPointer(arr, (length+1));
		return length;
    }
    DWORD PopDWORD()
    {
        DWORD dwData;
        memcpy((void*)&dwData, m_lpPackage + m_dwPosition, sizeof(DWORD));
        m_dwPosition += sizeof(DWORD);
        return dwData;
    }
};

namespace detail
{
	template < typename T >
	struct Select
	{
		static CPkgHelper &Dispacth(CPkgHelper &package, const T &val)
		{
			package.Push(val);
			return package;
		}
	};

	template < typename T >
	struct Select<T *>
	{
		static CPkgHelper &Dispacth(CPkgHelper &package, const T *val)
		{
			package.PushPointer(val);
			return package;
		}
	};


	template <>
	struct Select<char *>
	{
		static CPkgHelper &Dispacth(CPkgHelper &package, const char* const val)
		{
			package.PushString(val, strlen(val));
			return package;
		}
	};

	template <>
	struct Select<const char *>
	{
		static CPkgHelper &Dispacth(CPkgHelper &package, const char* const val)
		{
			return Select<char *>::Dispacth(package, val);
		}
	};


	template <>
	struct Select<wchar_t *>
	{
		static CPkgHelper &Dispacth(CPkgHelper &package, const wchar_t* const val)
		{
			package.PushString(val, wcslen(val));
			return package;
		}
	};

	template <>
	struct Select<const wchar_t *>
	{
		static CPkgHelper &Dispacth(CPkgHelper &package, const wchar_t* const val)
		{
			return Select<wchar_t *>::Dispacth(package, val);
		}
	};
}

//CPkgHelper stream operator.
template <typename T>
inline CPkgHelper& operator<<(CPkgHelper& package, const T& Value)
{
	return detail::Select<T>::Dispacth(package, Value);
}


// -----------
template<typename CharT>
inline CPkgHelper& operator<<(CPkgHelper& package, const std::basic_string<CharT>& Value)
{
	package.PushString(Value.c_str(), Value.length());
	return package;
}

template<typename CharT, size_t N>
inline CPkgHelper &operator<<(CPkgHelper &package, const CharT (&arr)[N])
{
	package.PushString(arr);
	return package;
}


template <typename T>
inline CPkgHelper& operator>>(CPkgHelper& package, T& Value)
{
	package.Pop(Value);
	return package;
}

template<typename CharT>
inline CPkgHelper& operator>>(CPkgHelper& package, std::basic_string<CharT>& Value)
{
	int length = 0;
	CharT end = 0;

	package.Pop(length);
	Value.resize(length);
	package.PopPointer<CharT>(&Value[0], length);
	package.Pop(end);
	return package;
}

template<typename CharT, size_t N>
inline CPkgHelper &operator>>(CPkgHelper &package, CharT (&arr)[N])
{
	package.PopString(arr);
	return package;
}

}

#endif