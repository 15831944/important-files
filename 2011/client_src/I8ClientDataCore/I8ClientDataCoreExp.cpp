/*******************************************************************************
*   Filename:       I8ClientDataCoreExp.cpp                                    *
*   Author:         ����                                                       *
*   eMail:          None.                                                      *
*   Tel:            None.                                                      *
*   Date:           2011-6-23                                                  *
*   Description:    �ͻ������ݽӿ�����                                         *
*   Reference:      None.                                                      *
*   Module:         �ͻ������ݲ�                                               *
*   Version history:                                                           *
*------------------------------------------------------------------------------*
*   Version     YYYY-MM-DD-INDEX    Modified By     Description                *
*   1.0.0       2011-6-23           ����            ������ʼ�汾               *
*******************************************************************************/

/*----------------------------------------------------------------------------*/
/*                               Include Files                                */
/*----------------------------------------------------------------------------*/
#include "StdAfx.h"
#include "I8ClientDataCoreExp.h"
#include "I8ClientDataCore.h"

/*----------------------------------------------------------------------------*/
/*                             Global Variables                               */
/*----------------------------------------------------------------------------*/
CI8ClientDataCore g_clDataCore;

/*----------------------------------------------------------------------------*/
/*                            Function Declaration                            */
/*----------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
// FunctionName: I8CD_Init
// Description:  ��ʼ���ͻ������ݲ㣬�������ʱ���ã��������ڵ�����֮ǰ�����������ݲ㺯��
//-----------------------------------------------------------------------------
void _stdcall
I8CD_Init(void)
{
    g_clDataCore.Init();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_Release
// Description:  �ͷſͻ������ݲ㣬������˳�ʱ�������������������ú�����������ݲ㺯��
//-----------------------------------------------------------------------------
void _stdcall
I8CD_Release(void)
{
    g_clDataCore.Release();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetVersion
// Description:  ȡ�ÿͻ������ݲ�İ汾����֤��̬��İ汾��ͷ�ļ��İ汾һ�¡�
//               ���ڳ�ʼ���ͻ������ݲ��ȡ�ð汾��C_CLIENT_DATA_CORE_VERSION�Ƚϣ�
//               ��һ�µĻ�����Ҫ�������ݲ�Ķ�̬���ͷ�ļ�
//-----------------------------------------------------------------------------
UINT _stdcall //�ͻ������ݲ�汾
I8CD_GetVersion(void)
{
    return g_clDataCore.GetVersion();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_CheckRepeatedProcess
// Description:  �ظ����̼�飬��֤ͬһ̨����ֻ��һ���ͻ������������ڳ�ʼ���ͻ������ݲ�����
//-----------------------------------------------------------------------------
BOOL _stdcall              //����FALSE��ʾ��һ���ͻ��˴��ڣ���Ҫ�رյ�ǰ�ͻ���
I8CD_CheckRepeatedProcess(
    IN LPCTSTR lpszCmdLine //��������������������ͻ��˴��ڽ��Ѳ��������ÿͻ���ִ��
)
{
    return g_clDataCore.CheckRepeatedWindow(lpszCmdLine);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_SetUICallBack
// Description:  ������Ϣ�ص��������������ݲ㷢���������ͨѶ�����ڽ��������������������
//-----------------------------------------------------------------------------
void _stdcall
I8CD_SetUICallBack(
    IN I8CD_UICallBack_pfn pfnCallBack,    //��Ϣ�ص�����
    IN void*               pCallBackParam  //�ص������õĲ��������Դ���
)
{
    g_clDataCore.SetUICallBack(pfnCallBack, pCallBackParam);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetSkinInfo
// Description:  ȡ�ÿͻ��˽����Ƥ���ļ�
//-----------------------------------------------------------------------------
LPCTSTR _stdcall //��ʽ��e:\Ƥ���ļ�.zip��
I8CD_GetSkinFile(void)
{
    return g_clDataCore.GetSkinFile();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_WriteLog
// Description:  ����ַ�������־
//-----------------------------------------------------------------------------
void _stdcall
I8CD_WriteLog(
    IN LPCTSTR lpszLog,  //����ַ���
    IN BOOL    bAddDate  //�������ʱ��
)
{
    g_clDataCore.WriteLog(lpszLog, bAddDate == TRUE);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_IsShowPost
// Description:  �Ƿ���ʾ����
//-----------------------------------------------------------------------------
BOOL _stdcall //��ʾ����
I8CD_IsShowPost(void)
{
    return g_clDataCore.IsShowPost();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetMacAddr
// Description:  ȡ��MAC��ַ
//-----------------------------------------------------------------------------
LPCTSTR _stdcall //MAC��ַ
I8CD_GetMacAddr(void)
{
    return g_clDataCore.GetMacAddr();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetInternetBarID
// Description:  ȡ������ID
//-----------------------------------------------------------------------------
long _stdcall //����ID
I8CD_GetInternetBarID(void)
{
    return g_clDataCore.GetInternetBarID();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetChannelsID
// Description:  ȡ������ID
//-----------------------------------------------------------------------------
long _stdcall //����ID
I8CD_GetChannelsID(void)
{
    return g_clDataCore.GetChannelsID();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetPostInfo
// Description:  ȡ�ù�����Ϣ
//-----------------------------------------------------------------------------
void _stdcall
I8CD_GetPostInfo(
    OUT I8CD_PostInfo_st* pstPostInfo //������Ϣ
)
{
    return g_clDataCore.GetPostInfo(pstPostInfo);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetInternetBarInfo
// Description:  ȡ��������Ϣ
//-----------------------------------------------------------------------------
void _stdcall
I8CD_GetInternetBarInfo(
    OUT I8CD_InternetBarInfo_st* pstInternetBarInfo //������Ϣ
)
{
    return g_clDataCore.GetInternetBarInfo(pstInternetBarInfo);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_IsEnableBrowseGameDirectory
// Description:  �Ƿ����������ϷĿ¼
//-----------------------------------------------------------------------------
BOOL _stdcall //���������ϷĿ¼
I8CD_IsEnableBrowseGameDirectory(void)
{
    return g_clDataCore.IsEnableBrowseDirectory();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_ReleaseData
// Description:  �ͷ����ݣ������ͷ������ݲ��ڷ���ֵ�����ɵ�����
//-----------------------------------------------------------------------------
void _stdcall
I8CD_ReleaseData(
    IN void* pData //Ҫ�ͷŵ�����ָ��
)
{
    return g_clDataCore.ReleaseData(pData);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetAllGameBaseInfo
// Description:  ȡ��ȫ����Ϸ������Ϣ
//-----------------------------------------------------------------------------
I8CD_GameBaseInfoArray_st* _stdcall //ȫ����Ϸ������Ϣ����Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
I8CD_GetAllGameBaseInfo(void)
{
    return g_clDataCore.GetAllGameBaseInfo();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetAllIconInfo
// Description:  ȡ��ȫ��ͼ����Ϣ
//-----------------------------------------------------------------------------
I8CD_IconInfoArray_st* _stdcall //ȫ��ͼ����Ϣ����Ҫ��ReleaseIconData�ͷŷ��ص�ָ��
I8CD_GetAllIconInfo(void)
{
    return g_clDataCore.GetAllIconInfo();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetAllNav
// Description:  ȡ�õ�������ť��
//-----------------------------------------------------------------------------
I8CD_NavArray_st* _stdcall //ȫ����������ť��Ϣ����Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
I8CD_GetAllNav(void)
{
    return g_clDataCore.GetAllNav();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetGameBaseInfo
// Description:  ȡ����Ϸ������Ϣ
//-----------------------------------------------------------------------------
BOOL _stdcall                             //ȡ�óɹ�
I8CD_GetGameBaseInfo(
    IN  DWORD                 gid,             //��ϷID
    OUT I8CD_GameBaseInfo_st* pstGameBaseInfo  //��Ϸ������Ϣ
)
{
    return g_clDataCore.GetGameBaseInfo(gid, pstGameBaseInfo);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetGameInfo
// Description:  ȡ����Ϸ��Ϣ
//-----------------------------------------------------------------------------
I8CD_GameInfo_st* _stdcall //��Ϸ��Ϣ��Ϊ�ձ�ʾ��Ϸ�����ڣ���Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
I8CD_GetGameInfo(
    IN DWORD gid      //��ϷID
)
{
    return g_clDataCore.GetGameInfo(gid);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetClientServiceState
// Description:  ȡ�ÿͻ��˷���״̬
//-----------------------------------------------------------------------------
void _stdcall
I8CD_GetClientServiceState(
    OUT BOOL* pbOnline, //������
    OUT BOOL* pbProt    //��ԭ��������
)
{
    g_clDataCore.GetClientServiceState(pbOnline, pbProt);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_ReportClickInfo
// Description:  ��������ϱ������Ϣ
//-----------------------------------------------------------------------------
BOOL _stdcall                                       //�����ɹ�
I8CD_ReportClickInfo(
    IN const I8CD_NavClickInfo_st*    pstNavClickInfo,      //�����������Ϣ
    IN int                            iNavClickInfoCount,   //�����������Ϣ����
    IN const I8CD_GameClickInfo_st*   pstGameClickInfo,     //��Ϸ�����Ϣ
    IN int                            iGameClickInfoCount,  //��Ϸ�����Ϣ����
    IN const I8CD_NavTabClickInfo_st* pstNavTabClickInfo,   //�����˵������Ϣ
    IN int                            iNavTabClickInfoCount,//�����˵������Ϣ����
    IN BOOL                           bWaitAnswer           //��Ҫ�ȴ���Ӧ
)
{
    return g_clDataCore.ReportClickInfoToServer(pstNavClickInfo, iNavClickInfoCount, pstGameClickInfo, iGameClickInfoCount, pstNavTabClickInfo, iNavTabClickInfoCount, bWaitAnswer);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetNavTab
// Description:  ȡ�õ����������ı�ǩҳ
//-----------------------------------------------------------------------------
I8CD_NavTabArray_st* _stdcall    //��ǩҳ��Ϣ����Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
I8CD_GetNavTab(
    IN I8CD_NavType_en enNavType //��������ť����
)
{
    return g_clDataCore.GetNavTab(enNavType);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_FindGame
// Description:  ������Ϸ
//-----------------------------------------------------------------------------
I8CD_GameIDArray_st* _stdcall         //ƥ�����Ϸ��Ϣ����Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
I8CD_FindGame(
    IN LPCTSTR             lpszKey,   //�ؼ���,����Ϊ��
    IN I8CD_FindFilter_st* pstFilter, //ɸѡ��,����Ϊ��
    IN I8CD_Order_en       enOrder    //����ʽ
)
{
    return g_clDataCore.FindGame(lpszKey, pstFilter, enOrder);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_FindGameByChar
// Description:  ������ĸ������Ϸ
//-----------------------------------------------------------------------------
I8CD_GameIDArray_st* _stdcall //ƥ�����Ϸ��Ϣ����Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
I8CD_FindGameByChar(
    IN TCHAR         tKey,    //��ĸ(A-Z)
    IN I8CD_Order_en enOrder  //����ʽ
    )
{
    return g_clDataCore.FindGame(tKey, enOrder);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetGameByClassName
// Description:  ������������Ϸ
//-----------------------------------------------------------------------------
I8CD_GameIDArray_st* _stdcall       //ƥ�����Ϸ��Ϣ����Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
I8CD_GetGameByClassName(
    IN LPCTSTR       lpszClassName, //��Ϸ���
    IN I8CD_Order_en enOrder        //����ʽ
)
{
    return g_clDataCore.GetGameByClassName(lpszClassName, enOrder);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetGameOnToolBar
// Description:  ȡ�ù������ϵ���Ϸ
//-----------------------------------------------------------------------------
I8CD_GameIDArray_st* _stdcall //ƥ�����Ϸ��Ϣ����Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
I8CD_GetGameOnToolBar(void)
{
    return g_clDataCore.GetGameOnToolBar();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_CheckAdvancedPassword
// Description:  ���ͻ��˸߼����������Ƿ���ȷ
//-----------------------------------------------------------------------------
BOOL _stdcall               //�ͻ��˸߼���������ƥ��ɹ�
I8CD_CheckAdvancedPassword(
    IN LPCTSTR lpszPassword //�ͻ��˸߼���������
)
{
    return g_clDataCore.CheckAdvancedPassword(lpszPassword);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetGBKFromString
// Description:  ȡ�ú��ֹ�����չ��
//-----------------------------------------------------------------------------
void _stdcall
I8CD_GetGBKFromString(
    OUT LPTSTR  lpszOutString, //���ɵĺ��ֹ�����չ��
    IN  int     iOutMaxCount,  //�����ַ���������ַ���
    IN  LPCTSTR lpszString     //�ַ���
)
{
    return g_clDataCore.GetGBKFromString(lpszOutString, iOutMaxCount, lpszString);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetServerIP
// Description:  ȡ�÷�����IP
//-----------------------------------------------------------------------------
LPCTSTR _stdcall //������IP
I8CD_GetServerIP(void)
{
    return g_clDataCore.GetServerIP();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_SetServerIP
// Description:  ���÷�����IP
//-----------------------------------------------------------------------------
void _stdcall
I8CD_SetServerIP(
    IN LPCTSTR lpszServerIP //������IP
)
{
    g_clDataCore.SetServerIP(lpszServerIP);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetOperatorAfterRunGame
// Description:  ȡ��������Ϸ�����ִ�еĲ���
//-----------------------------------------------------------------------------
I8CD_OperatorAfterRunGame_en _stdcall //������Ϸ�������Ҫִ�еĲ���
I8CD_GetOperatorAfterRunGame(void)
{
    return g_clDataCore.GetOperatorAfterRunGame();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_IsInitializeHy
// Description:  ��ԭ�����Ƿ����
//-----------------------------------------------------------------------------
BOOL _stdcall //��ԭ��������
I8CD_IsInitializeHy(void)
{
    return g_clDataCore.IsInitializeHy();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_IsInstallHy
// Description:  �Ƿ�װ��ԭ����
//-----------------------------------------------------------------------------
BOOL _stdcall //��ԭ�����Ѱ�װ
I8CD_IsInstallHy(void)
{
    return g_clDataCore.IsInstallHy();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetProtectedDriver
// Description:  ȡ�ÿ�����ԭ�����Ĵ���
//-----------------------------------------------------------------------------
LPCTSTR _stdcall //������ԭ�����Ĵ��̣���ʽ��CDE��
I8CD_GetProtectedDriver(void)
{
    return g_clDataCore.GetProtectedDriver();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetUnProtectedDriver
// Description:  ȡ��δ������ԭ�����Ĵ���
//-----------------------------------------------------------------------------
LPCTSTR _stdcall //δ������ԭ�����Ĵ��̣���ʽ��CDE��
I8CD_GetUnProtectedDriver(void)
{
    return g_clDataCore.GetUnProtectedDriver();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_ProtectDriver
// Description:  �Դ��̿�����ԭ�����͹رջ�ԭ����(��ʽ��CDE)
//-----------------------------------------------------------------------------
BOOL _stdcall                          //�����ɹ�
I8CD_ProtectDriver(
    IN  LPCTSTR lpszProtectedDriver,   //��Ҫ������ԭ�����Ĵ���
    IN  LPCTSTR lpszUnProtectedDriver, //��Ҫ�رջ�ԭ�����Ĵ���
    OUT BOOL*   pbNeedRestart          //��Ҫ���������
)
{
    return g_clDataCore.ProtectDriver(lpszProtectedDriver, lpszUnProtectedDriver, pbNeedRestart);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_CheckDisk
// Description:  ���̼��
//-----------------------------------------------------------------------------
void _stdcall
I8CD_CheckDisk(
    IN LPCTSTR lpszDriver //��Ҫ���Ĵ��̣���ʽ��CDE��
)
{
    g_clDataCore.CheckDisk(lpszDriver);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_SaveArchiveToFlashDisk
// Description:  �������̴浵
//-----------------------------------------------------------------------------
BOOL _stdcall    //�����ɹ�
I8CD_SaveArchiveToFlashDisk(
    IN DWORD gid //��ϷID
)
{
    return g_clDataCore.SaveArchiveToFlashDisk(gid);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_ReadArchiveToFlashDisk
// Description:  ��������ȡ��
//-----------------------------------------------------------------------------
BOOL _stdcall    //�����ɹ�
I8CD_ReadArchiveToFlashDisk(
    IN DWORD gid //��ϷID
)
{
    return g_clDataCore.ReadArchiveToFlashDisk(gid);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_ShowFlashDisk
// Description:  ��ʾ��������
//-----------------------------------------------------------------------------
BOOL _stdcall //�����ɹ�
I8CD_ShowFlashDisk(void)
{
    return g_clDataCore.ShowFlashDisk();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_LockComputer
// Description:  ���������
//-----------------------------------------------------------------------------
void _stdcall
I8CD_LockComputer(void)
{
    g_clDataCore.LockComputer();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_SetResolution
// Description:  ������Ļ�ֱ���
//-----------------------------------------------------------------------------
void _stdcall
I8CD_SetResolution(void)
{
    g_clDataCore.SetResolution();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_SetSysMouse
// Description:  ����ϵͳ���
//-----------------------------------------------------------------------------
void _stdcall
I8CD_SetSysMouse(void)
{
    g_clDataCore.SetSysMouse();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_SetVolume
// Description:  ��������
//-----------------------------------------------------------------------------
void _stdcall
I8CD_SetVolume(void)
{
    g_clDataCore.SetVolume();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_OpenGameDirectory
// Description:  ����Ϸ����Ŀ¼
//-----------------------------------------------------------------------------
BOOL _stdcall    //�����ɹ�
I8CD_OpenGameDirectory(
    IN DWORD gid //��ϷID
)
{
    return g_clDataCore.OpenGameDirectory(gid);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_IsGameEnableRun
// Description:  �����Ϸ�Ƿ�����У�û������Ϊɾ����Ϸ�ļ�����Ϸ�汾�������µ�����
//-----------------------------------------------------------------------------
BOOL _stdcall    //��Ϸ������
I8CD_IsGameEnableRun(
    IN DWORD gid //��ϷID
)
{
    return g_clDataCore.IsGameEnableRun(gid);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetInputMethod
// Description:  ȡ�����뷨����ϷID���������ʾ����û��������������������뷨
//-----------------------------------------------------------------------------
DWORD _stdcall //���뷨����ϷID
I8CD_GetInputMethod(void)
{
    return g_clDataCore.GetInputMethod();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_UpdateGame
// Description:  ������Ϸ
//-----------------------------------------------------------------------------
HANDLE _stdcall                                   //�����������������ͷţ��������ֵΪ�ձ�ʾ��Ϸ������£�����ֱ������
I8CD_UpdateGame(
    IN DWORD                   gid,               //��ϷID
    IN I8CD_DownloadMode_en    enDownloadMode,    //���ط�ʽ
    IN I8CD_UpdateCallBack_pfn pfnUpdateCallBack, //���»ص����������Դ���
    IN void*                   pCallBackParam     //���»ص������õĲ��������Դ���
)
{
    return g_clDataCore.UG_UpdateGame(gid, enDownloadMode, pfnUpdateCallBack, pCallBackParam);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_StopUpdate
// Description:  ֹͣ����
//-----------------------------------------------------------------------------
void _stdcall
I8CD_StopUpdate(
    IN HANDLE hUpdate //����������
)
{
    g_clDataCore.UG_StopUpdate(hUpdate);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetPertinentGame
// Description:  ȡ����Ϸ��ع���
//-----------------------------------------------------------------------------
I8CD_GameIDArray_st* _stdcall //ƥ�����Ϸ��Ϣ����Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
I8CD_GetPertinentGame(
    IN DWORD gid         //��ϷID
)
{
    return g_clDataCore.GetPertinentGame(gid);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_RunGame
// Description:  ������Ϸ��������Ϸǰ��Ҫ"������Ϸ"��"�����Ϸ��Ϣ����Ϸ�ļ��Ƿ�ƥ��"��
//               "������Ϸ"Ҫ�ȴ���������Ϊ��ɣ�"�����Ϸ��Ϣ����Ϸ�ļ��Ƿ�ƥ��"Ҫ��֤�汾һ��
//-----------------------------------------------------------------------------
I8CD_RunGameResult_en _stdcall //������Ϸ���
I8CD_RunGame(
    IN DWORD gid          //��ϷID
)
{
    return g_clDataCore.RunGame(gid);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetClientMenu
// Description:  ȡ�ò˵��ּ���Ϣ�����û�з���NULL
//-----------------------------------------------------------------------------
LPCTSTR _stdcall //�˵��ּ���Ϣ��XML���ݸ�ʽ
I8CD_GetClientMenu(void)
{
    return g_clDataCore.GetClientMenu();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_IsVisible
// Description:  ��鴰���Ƿ�ɼ���������ɼ����ͻ��˽�����Բ��ɼ���ʽ������ֱ���ص������յ���ʾ����
//-----------------------------------------------------------------------------
BOOL _stdcall  //����/��ʽ�����ͻ���
I8CD_IsVisible(void)
{
    return g_clDataCore.IsVisible();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_RemoteControl
// Description:  ��������˵�Զ�̿���
//-----------------------------------------------------------------------------
BOOL _stdcall  //�����ɹ�
I8CD_RemoteControl(void)
{
    return g_clDataCore.RemoteControl();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetAllDriver
// Description:  ȡ�������������
//-----------------------------------------------------------------------------
LPCTSTR _stdcall //����������̣���ʽ��CDE��
I8CD_GetAllDriver(void)
{
    return g_clDataCore.GetAllDriver();
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetStartupInfo
// Description:  ȡ�ò˵�������Ϣ
//-----------------------------------------------------------------------------
void _stdcall
I8CD_GetStartupInfo(
    OUT I8CD_StartupInfo_st* pstStartupInfo //�˵�������Ϣ
)
{
    return g_clDataCore.GetStartupInfo(pstStartupInfo);
}

//-----------------------------------------------------------------------------
// FunctionName: I8CD_IsNeedRefreshGameVDisk
// Description:  ����Ƿ���ҪΪ��Ϸˢ��������
//-----------------------------------------------------------------------------
BOOL _stdcall    //��Ҫˢ��������
I8CD_IsNeedRefreshGameVDisk(
    IN DWORD gid //��ϷID
)
{
    return g_clDataCore.IsNeedRefreshGameVDisk(gid);
}
//-----------------------------------------------------------------------------
// FunctionName: I8CD_RefreshGameVDisk
// Description:  Ϊ��Ϸˢ��������
//-----------------------------------------------------------------------------
void _stdcall
I8CD_RefreshGameVDisk(
    IN DWORD gid //��ϷID
)
{
    g_clDataCore.RefreshGameVDisk(gid);
}
