// StartupClient.cpp : CStartupClient ��ʵ��

#include "stdafx.h"
#include "StartupClient.h"
#include <assert.h>
#include <atlstr.h>
#include "../Include/I8ClientPipe.h"
#include "Log.h"

static CLogger s_clLog;

static LPCTSTR C_CLIENT_COMMUNICATION_MUTEX_NAME = _T("__i8_client_communication_mutex_"); //�ͻ������ͨѶ����������

#define KEY_I8DESK TEXT("SOFTWARE\\Goyoo\\i8desk")

template<int iCount>
BOOL GetBarOnlinePath(TCHAR(&atFilePath)[iCount])
{
    DWORD dwSize = iCount, dwType = REG_SZ;
    DWORD dwRet = SHGetValue(HKEY_LOCAL_MACHINE, KEY_I8DESK, TEXT("exec"), &dwType, atFilePath, &dwSize);
    return (dwRet == ERROR_SUCCESS) && PathFileExists(atFilePath);
}


STDMETHODIMP CStartupClient::RunGame(LONG gid, VARIANT_BOOL bRunBackstage, VARIANT_BOOL* bResult)
{
    s_clLog.WriteLog2(bRunBackstage ? _T("��ʽ������Ϸ����ʱʱ��%d") :  _T("������Ϸ����ʱʱ��%d"), m_iTimeOut);
    *bResult = VARIANT_FALSE;
    if (gid <= 0)
    {
        return S_OK;
    }
    async::thread::AutoMutex clMutex(NULL, FALSE, C_CLIENT_COMMUNICATION_MUTEX_NAME);
    async::thread::AutoLock<async::thread::AutoMutex> clLock(clMutex);
    if (!I8_ClientDataCore_ns::IsBarOnlineExist())
    {
        TCHAR atBarOnlinePath[MAX_PATH], atParam[MAX_PATH] = {0};
        if (bRunBackstage)
        {
            lstrcpy(atParam, _T("/hide"));
        }
        if (!GetBarOnlinePath(atBarOnlinePath))
        {
            s_clLog.WriteLog(_T("ʧ�ܣ��ͻ���û����ȷ��װ"));
            return S_OK;
        }
        ShellExecute(NULL, _T("open"), atBarOnlinePath, atParam, NULL, SW_SHOW);
        s_clLog.WriteLog(bRunBackstage ? _T("��ʽ�����ͻ���") :  _T("�����ͻ���"));
    }
    I8_ClientDataCore_ns::RunGameParam_st stParam = {gid, bRunBackstage};
    DWORD dwResult;
    I8_ClientDataCore_ns::PipeMsgResult_en enResult = I8_ClientDataCore_ns::SendPipeMessageToBarOnline(I8_ClientDataCore_ns::E_PIPEMSG_RUN_GAME, &stParam, &dwResult, m_iTimeOut);
    if (enResult == I8_ClientDataCore_ns::E_PMR_SUCCESS)
    {
        if (dwResult)
        {
            *bResult = VARIANT_TRUE;
            s_clLog.WriteLog(_T("�ɹ�������������Ϸ����ɹ�"));
        }
        else
        {
            s_clLog.WriteLog(_T("ʧ�ܣ���Ϸ������/�ͻ��˺�æ"));
        }
    }
    else
    {
        switch (enResult)
        {
        case I8_ClientDataCore_ns::E_PMR_FAIL_TO_WAIT_PIPE:
            s_clLog.WriteLog(_T("ʧ�ܣ����ӿͻ��˲��ɹ�"));
            break;
        case I8_ClientDataCore_ns::E_PMR_FAIL_TO_NO_RESPONSE:
            s_clLog.WriteLog(_T("ʧ�ܣ��ͻ���û�л�Ӧ"));
            break;
        default:
            s_clLog.WriteLog(_T("ʧ�ܣ�δ֪ԭ��"));
            break;
        }
    }
    return S_OK;
}

STDMETHODIMP CStartupClient::RunClient(VARIANT_BOOL* bResult)
{
    s_clLog.WriteLog2(_T("����/��ʾ�ͻ��ˣ���ʱʱ��%d"), m_iTimeOut);
    *bResult = VARIANT_FALSE;
    async::thread::AutoMutex clMutex(NULL, FALSE, C_CLIENT_COMMUNICATION_MUTEX_NAME);
    async::thread::AutoLock<async::thread::AutoMutex> clLock(clMutex);
    if (!I8_ClientDataCore_ns::IsBarOnlineExist())
    {
        TCHAR atBarOnlinePath[MAX_PATH];
        if (!GetBarOnlinePath(atBarOnlinePath))
        {
            s_clLog.WriteLog(_T("ʧ�ܣ��ͻ���û����ȷ��װ"));
            return S_FALSE;
        }
        ShellExecute(NULL, _T("open"), atBarOnlinePath, NULL, NULL, SW_SHOW);
        *bResult = VARIANT_TRUE;
        s_clLog.WriteLog(_T("�ɹ��������ͻ���"));
    }
    else
    {
        DWORD dwResult;
        I8_ClientDataCore_ns::PipeMsgResult_en enResult = I8_ClientDataCore_ns::SendPipeMessageToBarOnline<DWORD, DWORD>(I8_ClientDataCore_ns::E_PIPEMSG_RUN_CLIENT, NULL, &dwResult, m_iTimeOut);
        if (enResult == I8_ClientDataCore_ns::E_PMR_SUCCESS)
        {
            if (dwResult)
            {
                *bResult = VARIANT_TRUE;
                s_clLog.WriteLog(_T("�ɹ�����ͻ��˷�����ʾ����"));
            }
            else
            {
                s_clLog.WriteLog(_T("ʧ�ܣ��ͻ��˺�æ���ܾ���ʾ����"));
            }
        }
        else
        {
            switch (enResult)
            {
            case I8_ClientDataCore_ns::E_PMR_FAIL_TO_WAIT_PIPE:
                s_clLog.WriteLog(_T("ʧ�ܣ����ӿͻ��˲��ɹ�"));
                break;
            case I8_ClientDataCore_ns::E_PMR_FAIL_TO_NO_RESPONSE:
                s_clLog.WriteLog(_T("ʧ�ܣ��ͻ���û�л�Ӧ"));
                break;
            default:
                s_clLog.WriteLog(_T("ʧ�ܣ�δ֪ԭ��"));
                break;
            }
        }
    }
    return S_OK;
}


STDMETHODIMP CStartupClient::SetTimeOut(LONG iTimeOut, VARIANT_BOOL* bResult)
{
    *bResult = VARIANT_FALSE;
    if (iTimeOut <= 0)
    {
        s_clLog.WriteLog2(_T("���ó�ʱʱ��ʧ��%d"), iTimeOut);
        return S_OK;
    }
    m_iTimeOut = iTimeOut;
    s_clLog.WriteLog2(_T("���ó�ʱʱ��ɹ�%d"), iTimeOut);
    *bResult = VARIANT_TRUE;
    return S_OK;
}

STDMETHODIMP CStartupClient::IsGameExist(LONG gid, VARIANT_BOOL* bResult)
{
    s_clLog.WriteLog2(_T("�����Ϸ�Ƿ���ڣ���ʱʱ��%d"), m_iTimeOut);
    *bResult = VARIANT_FALSE;
    if (gid <= 0)
    {
        s_clLog.WriteLog(_T("ʧ�ܣ�gidΪ��"));
        return S_OK;
    }
    async::thread::AutoMutex clMutex(NULL, FALSE, C_CLIENT_COMMUNICATION_MUTEX_NAME);
    async::thread::AutoLock<async::thread::AutoMutex> clLock(clMutex);
    if (!I8_ClientDataCore_ns::IsBarOnlineExist())
    {
        TCHAR atBarOnlinePath[MAX_PATH];
        if (!GetBarOnlinePath(atBarOnlinePath))
        {
            s_clLog.WriteLog(_T("ʧ�ܣ��ͻ���û����ȷ��װ"));
            return S_OK;
        }
        ShellExecute(NULL, _T("open"), atBarOnlinePath, _T("/hide"), NULL, SW_SHOW);
        s_clLog.WriteLog(_T("��ʽ�����ͻ���"));
    }
    DWORD dwParam = gid;
    DWORD dwResult;
    I8_ClientDataCore_ns::PipeMsgResult_en enResult = I8_ClientDataCore_ns::SendPipeMessageToBarOnline(I8_ClientDataCore_ns::E_PIPEMSG_FIND_GAME, &dwParam, &dwResult, m_iTimeOut);
    if (enResult == I8_ClientDataCore_ns::E_PMR_SUCCESS)
    {
        if (dwResult)
        {
            *bResult = VARIANT_TRUE;
            s_clLog.WriteLog(_T("�ɹ�����Ϸ����"));
        }
        else
        {
            s_clLog.WriteLog(_T("�ɹ�����Ϸ������"));
        }
    }
    else
    {
        switch (enResult)
        {
        case I8_ClientDataCore_ns::E_PMR_FAIL_TO_WAIT_PIPE:
            s_clLog.WriteLog(_T("ʧ�ܣ������ͻ���ʧ��/���ӿͻ��˲��ɹ�"));
            break;
        case I8_ClientDataCore_ns::E_PMR_FAIL_TO_NO_RESPONSE:
            s_clLog.WriteLog(_T("ʧ�ܣ��ͻ���û�л�Ӧ"));
            break;
        default:
            s_clLog.WriteLog(_T("ʧ�ܣ�δ֪ԭ��"));
            break;
        }
    }
    return S_OK;
}
