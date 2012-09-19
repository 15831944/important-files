#ifndef _SAFECENTER_H
#define _SAFECENTER_H
#pragma pack(1)
//��������
enum ATTACH_TYPE
{ 
	ATTACH_NONE = 0,			                      // �޹�����Ϊ
	GATEWAY_ARP_QUERY_ATTACH,                         // α�����ز�ѯ������
	GATEWAY_ARP_REPLY_ATTACH,                         // α�����ػ�Ӧ������
	LAN_SAMEIP_ATTACH,		                          // ������IP��ͻ����
	WAN_SAMEIP_ATTACH,		                          // ������IP��ͻ����
	WRONG_PROTOCOL_ATTACH,	                          // �����Э�鹥��
	UNKNOWN_ATTACH
};

//IP MAC�ṹ
typedef struct  _IP_MAC
{
	DWORD                   Ip;                       //IP��ַ
	BYTE                    Mac[6];                   //MAC��ַ��������"-"
}IP_MAC, *PIP_MAC;

//������Ϣ
typedef struct _ATTACK_INFO
{
    ATTACH_TYPE             AType;                    //��������
	BYTE                    AttackByMac[6];           //����ԴMAC
	BYTE                    AttackByIp[6];            //����ԴIP
}ATTACK_INFO, *PATTACK_INFO;
#pragma pack ()
//��ʼ��ARP�Ļص���������
typedef void (__stdcall *ARP_ATTACK_CALLBACK)(PATTACK_INFO AttackInfo, BOOL IsKnownIP);

//ARP���������ӿ����Ͷ���
typedef BOOL (__stdcall *PFNINITARPMOD)(ARP_ATTACK_CALLBACK pfnAttackCallback, PIP_MAC LocalIpMac, DWORD Count, PIP_MAC GatewayIpMac);
typedef BOOL (__stdcall *PFNARPMODISOK)();
typedef BOOL (__stdcall *PFNSTARTPROTECT)();
typedef BOOL (__stdcall *PFNDISABLESIGN)();
typedef BOOL (__stdcall *PFNENABLESIGN)();
typedef BOOL (__stdcall *PFNINSTALLDRIVER)();
typedef BOOL (__stdcall *PFNREMOVEDRIVER)();
typedef BOOL (__stdcall *PFNGETGATEWAYMAC)(DWORD GatewayAddr, TCHAR MacAddr[]);
typedef BOOL (__stdcall *PFNSTOPPROTECT)();
HMODULE g_hI8NEModule = NULL;
//ARP�����ӿڵ���
BOOL __stdcall InitArpMod(ARP_ATTACK_CALLBACK pfnAttackCallback, PIP_MAC LocalIpMac, DWORD Count, PIP_MAC GatewayIpMac)
{
	if (g_hI8NEModule == NULL)
	{
		TCHAR path[MAX_PATH] = {0};
    	GetModuleFileName(NULL, path, MAX_PATH);
    	PathRemoveFileSpec(path);
    	PathAddBackslash(path);
    	lstrcat(path, TEXT("SafeClt\\i8NE.dll"));
		g_hI8NEModule = LoadLibrary(path);
	}
	if (g_hI8NEModule != NULL)
	{
		PFNINITARPMOD pfnInitArpMod = (PFNINITARPMOD)GetProcAddress(g_hI8NEModule, (char*)1);
		if (pfnInitArpMod != NULL)
		{
			return pfnInitArpMod(pfnAttackCallback, LocalIpMac, Count, GatewayIpMac);
		}
	}
	return FALSE;
}

BOOL __stdcall ArpModIsOK()
{
	if (g_hI8NEModule != NULL)
	{
		PFNARPMODISOK pfnArpModIsOK = (PFNARPMODISOK)GetProcAddress(g_hI8NEModule, (char*)9);
		if (pfnArpModIsOK != NULL)
		{
			return pfnArpModIsOK();
		}
	}
	return FALSE;
}

BOOL __stdcall StartProtect()
{
	if (g_hI8NEModule != NULL)
	{
		PFNSTARTPROTECT pfnStartProtect = (PFNSTARTPROTECT)GetProcAddress(g_hI8NEModule, (char*)2);
		if (pfnStartProtect != NULL)
		{
			return pfnStartProtect();
		}
	}
	return FALSE;
}

void __stdcall DisableSign()
{
	if (g_hI8NEModule != NULL)
	{
		PFNDISABLESIGN pfnDisableSign = (PFNDISABLESIGN)GetProcAddress(g_hI8NEModule, (char*)5);
		if (pfnDisableSign != NULL)
		{
			pfnDisableSign();
		}
	}
}

void __stdcall EnableSign()
{
	if (g_hI8NEModule != NULL)
	{
		PFNENABLESIGN pfnEnableSign = (PFNENABLESIGN)GetProcAddress(g_hI8NEModule, (char*)6);
		if (pfnEnableSign != NULL)
		{
			pfnEnableSign();
		}
	}
}

BOOL __stdcall InstallDriver()
{
	if (g_hI8NEModule != NULL)
	{
		PFNINSTALLDRIVER pfnInstallDriver = (PFNINSTALLDRIVER)GetProcAddress(g_hI8NEModule, (char*)7);
		if (pfnInstallDriver != NULL)
		{
			return pfnInstallDriver();
		}
	}
	return FALSE;
}

BOOL __stdcall RemoveDriver()
{
	if (g_hI8NEModule != NULL)
	{
		PFNREMOVEDRIVER pfnRemoveDriver = (PFNREMOVEDRIVER)GetProcAddress(g_hI8NEModule, (char*)8);
		if (pfnRemoveDriver != NULL)
		{
			return pfnRemoveDriver();
		}
	}
	return FALSE;
}

BOOL __stdcall GetGatewayMac(DWORD GatewayAddr, TCHAR MacAddr[])
{
	if (g_hI8NEModule != NULL)
	{
		PFNGETGATEWAYMAC pfnGetGatewayMac = (PFNGETGATEWAYMAC)GetProcAddress(g_hI8NEModule, (char*)10);
		if (pfnGetGatewayMac != NULL)
		{
			return pfnGetGatewayMac(GatewayAddr, MacAddr);
		}
	}
	return FALSE;
}

BOOL __stdcall StopProtect()
{
	if (g_hI8NEModule != NULL)
	{
		PFNSTOPPROTECT pfnStopProtect = (PFNSTOPPROTECT)GetProcAddress(g_hI8NEModule, (char*)11);
		if (pfnStopProtect != NULL)
		{
			return pfnStopProtect();
		}
	}
	return FALSE;
}

void __stdcall UnInitArpMod()
{
	if (g_hI8NEModule != NULL)
	{
		FreeLibrary(g_hI8NEModule);
		g_hI8NEModule = NULL;
	}
}

#endif