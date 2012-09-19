#pragma once

class CVirtualDiskDll
{
    typedef DWORD (WINAPI *PFNDISKMOUNT)(UINT index, ULONG addr,USHORT port,CHAR driver,LPCSTR tempfile);
    typedef DWORD (WINAPI *PFNDISKUMOUNT)(char driver);
    typedef DWORD (WINAPI *PFNUPDATEEXEC)(LPCSTR ChannelID);
private:
    HMODULE       m_hModule;
    PFNDISKMOUNT  m_pfnDiskMount;
    PFNDISKUMOUNT m_pfnDiskUmount;
    PFNUPDATEEXEC m_pfnUpdateExec;
public:
    CVirtualDiskDll()
        : m_hModule(NULL)
        , m_pfnDiskMount(NULL)
        , m_pfnDiskUmount(NULL)
        , m_pfnUpdateExec(NULL)
    {
    }
    ~CVirtualDiskDll()
    {
        if (m_hModule)
        {
            FreeLibrary(m_hModule);
        }
    }
    BOOL Load(LPCTSTR pDllFile)
    {
        assert(m_hModule == NULL);
        assert(pDllFile != NULL);
        m_hModule = LoadLibrary(pDllFile);
        assert(m_hModule != NULL);
        m_pfnDiskMount = reinterpret_cast<PFNDISKMOUNT>(GetProcAddress(m_hModule, "iDiskMount"));
        m_pfnDiskUmount = reinterpret_cast<PFNDISKUMOUNT>(GetProcAddress(m_hModule, "iDiskUmount"));
        m_pfnUpdateExec = reinterpret_cast<PFNUPDATEEXEC>(GetProcAddress(m_hModule, "UpdateExec")); //����û�иú���
        
        return m_hModule != NULL;
    }
    DWORD DiskMount(UINT index, ULONG addr,USHORT port,CHAR driver,LPCSTR tempfile)
    {
        assert(m_hModule != NULL && "û�м��������̶�̬�⡣");
        assert(m_pfnDiskMount != NULL && "�������̶�̬�ⲻ֧��DiskMount��������");
        return (*m_pfnDiskMount)(index, addr, port, driver, tempfile);
    }
    DWORD DiskUmount(char driver)
    {
        assert(m_hModule != NULL && "û�м��������̶�̬�⡣");
        assert(m_pfnDiskUmount != NULL && "�������̶�̬�ⲻ֧��DiskUmount��������");
        return (*m_pfnDiskUmount)(driver);
    }
    DWORD UpdateExec(LPCSTR ChannelID)
    {
        assert(m_hModule != NULL&& "û�м��������̶�̬�⡣");
        assert(m_pfnUpdateExec != NULL && "�������̶�̬�ⲻ֧��UpdateExec������");
        return (*m_pfnUpdateExec)(ChannelID);
    }
    BOOL IsCanUpdateExec()
    {
        return m_pfnUpdateExec != NULL;
    }
};
