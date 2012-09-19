// StartupClient.h : CStartupClient ������

#pragma once
#include "resource.h"       // ������

#include "I8ClientCommunication_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CStartupClient

class ATL_NO_VTABLE CStartupClient :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStartupClient, &CLSID_StartupClient>,
	public IDispatchImpl<IStartupClient, &IID_IStartupClient, &LIBID_I8ClientCommunicationLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
    int m_iTimeOut;
public:
    CStartupClient() : m_iTimeOut(5000)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STARTUPCLIENT)


BEGIN_COM_MAP(CStartupClient)
	COM_INTERFACE_ENTRY(IStartupClient)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

    STDMETHOD(RunGame)(LONG gid, VARIANT_BOOL bRunBackstage, VARIANT_BOOL* bResult);
    STDMETHOD(RunClient)(VARIANT_BOOL* bResult);
    STDMETHOD(IsGameExist)(LONG gid, VARIANT_BOOL* bResult);
    STDMETHOD(SetTimeOut)(LONG iTimeOut, VARIANT_BOOL* bResult);
};

OBJECT_ENTRY_AUTO(__uuidof(StartupClient), CStartupClient)
