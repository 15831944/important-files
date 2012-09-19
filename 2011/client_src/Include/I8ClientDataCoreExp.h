/*******************************************************************************
*   Filename:       I8ClientDataCoreExp.h                                      *
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
*   1.1.0       2011-7-4            ����            1.���ĺ�������Լ��         *
*                                                   2.����GetInputMethod��ע�� *
*                                                   3.�޸�UG_UpdateGame������  *
*                                                   4.ɾ��UG_GetUpdateStatus   *
*                                                   5.������ͬ������ReleaseData*
*                                                     ����ΪReleaseData��      *
*                                                     ReleaseIconData          *
*                                                   6.������ͬ������FindGame�� *
*                                                     ��ΪFindGameByGame       *
*                                                     ��FindGameByChar         *
*   1.2.0       2011-7-6            ����            ���Ӻ���GetCommnet��       *
*                                                   GetClientMenu              *
*   1.3.0       2011-7-14           ����            1.����GetCommnet���Ӳ���   *
*                                                   2.ɾ��ReleaseIconData,     *
*                                                     ������ReleaseData���    *
*                                                   3.�޸�GetAllGameInfo       *
*                                                     ΪGetAllGameBaseInfo     *
*                                                   4.ɾ��GetGameExtendInfo,   *
*                                                     ������GetGameInfo���    *
*                                                   5.��FindGameByString��Ϊ   *
*                                                     FindGame,��ǿ������      *
*   1.4.0       2011-7-27           ����            1.����C++������Ϊ����C���� *
*                                                   2.���к�������             *
*   1.5.0       2011-8-1            ����            1.���Ӻ���I8CD_IsVisible   *
*                                                   2.����I8CD_RemoteControl   *
*   1.6.0       2011-8-2            ����            �޸�I8CD_CheckGameMatching *
*                                                   ΪI8CD_IsGameEnableRun     *
*   1.7.0       2011-8-10           ����            ɾ��I8CD_GetCommnet        *
*   1.7.1       2011-8-15           ����            �޸�I8CD_UpdateGame�Ĳ���  *
*   1.7.2       2011-8-23           ����            ����I8CD_ReportClickInfo   *
*   1.8.0       2011-10-12          ����            1.���ӽӿ�I8CD_GetAllDriver*
*                                                   2.����I8CD_IsVisible       *
*                                                   3.����I8CD_RemoteControl   *
*   1.9.0       2011-10-20          ����            ����I8CD_GetStartupInfo    *
*   1.9.1       2011-11-14          ����            ����I8CD_GetGameByClassName*
*                                                   ��I8CD_FindGameByChar�Ĳ���*
*   1.10.0      2012-1-11           ����            ����I8CD_RefreshGameVDisk��*
*                                                   I8CD_IsNeedRefreshGameVDisk*
*******************************************************************************/

/*----------------------------------------------------------------------------*/
/*                            Compilation Control                             */
/*----------------------------------------------------------------------------*/
#pragma once

#ifdef I8CLIENTDATACORE_EXPORTS
#define DLL_API_EXPORT extern "C" __declspec(dllexport)
#else
#define DLL_API_EXPORT extern "C" __declspec(dllimport)
#endif

/*----------------------------------------------------------------------------*/
/*                               Include Files                                */
/*----------------------------------------------------------------------------*/
#include "I8ClientDefine.h"

/*----------------------------------------------------------------------------*/
/*                            Function Prototypes                             */
/*----------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
// FunctionName: I8CD_Init
// Description:  ��ʼ���ͻ������ݲ㣬�������ʱ���ã��������ڵ�����֮ǰ�����������ݲ㺯��
// Parameters:   None.
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_Init(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_Release
// Description:  �ͷſͻ������ݲ㣬������˳�ʱ�������������������ú�����������ݲ㺯��
// Parameters:   None.
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_Release(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetVersion
// Description:  ȡ�ÿͻ������ݲ�İ汾����֤��̬��İ汾��ͷ�ļ��İ汾һ�¡����ڳ�ʼ���ͻ������ݲ��ȡ�ð汾��C_CLIENT_DATA_CORE_VERSION�Ƚϣ���һ�µĻ�����Ҫ�������ݲ�Ķ�̬���ͷ�ļ�
// Parameters:   None.
// Return:       �ͻ������ݲ�汾
//-----------------------------------------------------------------------------
DLL_API_EXPORT UINT _stdcall I8CD_GetVersion(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_CheckRepeatedProcess
// Description:  �ظ����̼�飬��֤ͬһ̨����ֻ��һ���ͻ������������ڳ�ʼ���ͻ������ݲ�����
// Parameters:   1) LPCTSTR lpszCmdLine [IN] ��������������������ͻ��˴��ڽ��Ѳ��������ÿͻ���ִ��
// Return:       ����FALSE��ʾ��һ���ͻ��˴��ڣ���Ҫ�رյ�ǰ�ͻ���
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_CheckRepeatedProcess(IN LPCTSTR lpszCmdLine);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_SetUICallBack
// Description:  ������Ϣ�ص��������������ݲ㷢���������ͨѶ�����ڽ��������������������
// Parameters:   1) I8CD_UICallBack_pfn pfnCallBack    [IN] ��Ϣ�ص�����
//               2) void*               pCallBackParam [IN] �ص������õĲ��������Դ���
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_SetUICallBack(IN I8CD_UICallBack_pfn pfnCallBack, IN void* pCallBackParam);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetSkinFile
// Description:  ȡ�ÿͻ��˽����Ƥ���ļ�
// Parameters:   None.
// Return:       ��ʽ��e:\Ƥ���ļ�.zip��
//-----------------------------------------------------------------------------
DLL_API_EXPORT LPCTSTR _stdcall I8CD_GetSkinFile(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_WriteLog
// Description:  ����ַ�������־
// Parameters:   1) LPCTSTR lpszLog  [IN] ����ַ���
//               2) BOOL    bAddDate [IN] �������ʱ��
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_WriteLog(IN LPCTSTR lpszLog, IN BOOL bAddDate);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_IsShowPost
// Description:  �Ƿ���ʾ����
// Parameters:   None.
// Return:       ��ʾ����
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_IsShowPost(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetMacAddr
// Description:  ȡ��MAC��ַ
// Parameters:   None.
// Return:       MAC��ַ
//-----------------------------------------------------------------------------
DLL_API_EXPORT LPCTSTR _stdcall I8CD_GetMacAddr(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetInternetBarID
// Description:  ȡ������ID
// Parameters:   None.
// Return:       ����ID
//-----------------------------------------------------------------------------
DLL_API_EXPORT long _stdcall I8CD_GetInternetBarID(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetChannelsID
// Description:  ȡ������ID
// Parameters:   None.
// Return:       ����ID
//-----------------------------------------------------------------------------
DLL_API_EXPORT long _stdcall I8CD_GetChannelsID(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetPostInfo
// Description:  ȡ�ù�����Ϣ
// Parameters:   1) I8CD_PostInfo_st* pstPostInfo [OUT] ������Ϣ
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_GetPostInfo(OUT I8CD_PostInfo_st* pstPostInfo);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetInternetBarInfo
// Description:  ȡ��������Ϣ
// Parameters:   1) I8CD_InternetBarInfo_st* pstInternetBarInfo [OUT] ������Ϣ
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_GetInternetBarInfo(OUT I8CD_InternetBarInfo_st* pstInternetBarInfo);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_IsEnableBrowseGameDirectory
// Description:  �Ƿ����������ϷĿ¼
// Parameters:   None.
// Return:       ���������ϷĿ¼
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_IsEnableBrowseGameDirectory(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_ReleaseData
// Description:  �ͷ����ݣ������ͷ������ݲ��ڷ���ֵ�����ɵ�����
// Parameters:   1) void* pData [IN] Ҫ�ͷŵ�����ָ��
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_ReleaseData(IN void* pData);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetAllGameBaseInfo
// Description:  ȡ��ȫ����Ϸ������Ϣ
// Parameters:   None.
// Return:       ȫ����Ϸ������Ϣ����Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
//-----------------------------------------------------------------------------
DLL_API_EXPORT I8CD_GameBaseInfoArray_st* _stdcall I8CD_GetAllGameBaseInfo(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetAllIconInfo
// Description:  ȡ��ȫ��ͼ����Ϣ
// Parameters:   None.
// Return:       ȫ��ͼ����Ϣ����Ҫ��ReleaseIconData�ͷŷ��ص�ָ��
//-----------------------------------------------------------------------------
DLL_API_EXPORT I8CD_IconInfoArray_st* _stdcall I8CD_GetAllIconInfo(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetAllNav
// Description:  ȡ�õ�������ť��
// Parameters:   None.
// Return:       ȫ����������ť��Ϣ����Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
//-----------------------------------------------------------------------------
DLL_API_EXPORT I8CD_NavArray_st* _stdcall I8CD_GetAllNav(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetGameBaseInfo
// Description:  ȡ����Ϸ������Ϣ
// Parameters:   1) DWORD                 gid             [IN]  ��ϷID
//               2) I8CD_GameBaseInfo_st* pstGameBaseInfo [OUT] ��Ϸ������Ϣ
// Return:       ȡ�óɹ�
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_GetGameBaseInfo(IN DWORD gid, OUT I8CD_GameBaseInfo_st* pstGameBaseInfo);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetGameInfo
// Description:  ȡ����Ϸ��Ϣ
// Parameters:   1) DWORD gid [IN] ��ϷID
// Return:       ��Ϸ��Ϣ��Ϊ�ձ�ʾ��Ϸ�����ڣ���Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
//-----------------------------------------------------------------------------
DLL_API_EXPORT I8CD_GameInfo_st* _stdcall I8CD_GetGameInfo(IN DWORD gid);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetClientServiceState
// Description:  ȡ�ÿͻ��˷���״̬
// Parameters:   1) BOOL* pbOnline [OUT] ������
//               2) BOOL* pbProt   [OUT] ��ԭ��������
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_GetClientServiceState(OUT BOOL* pbOnline, OUT BOOL* pbProt);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_ReportClickInfo
// Description:  ��������ϱ������Ϣ
// Parameters:   1) const I8CD_NavClickInfo_st*    pstNavClickInfo       [IN] �����������Ϣ
//               2) int                            iNavClickInfoCount    [IN] �����������Ϣ����
//               3) const I8CD_GameClickInfo_st*   pstGameClickInfo      [IN] ��Ϸ�����Ϣ
//               4) int                            iGameClickInfoCount   [IN] ��Ϸ�����Ϣ����
//               5) const I8CD_NavTabClickInfo_st* pstNavTabClickInfo    [IN] �����˵������Ϣ
//               6) int                            iNavTabClickInfoCount [IN] �����˵������Ϣ����
//               7) BOOL                           bWaitAnswer           [IN] ��Ҫ�ȴ���Ӧ
// Return:       �����ɹ�
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_ReportClickInfo(IN const I8CD_NavClickInfo_st* pstNavClickInfo, IN int iNavClickInfoCount, IN const I8CD_GameClickInfo_st* pstGameClickInfo, IN int iGameClickInfoCount, IN const I8CD_NavTabClickInfo_st* pstNavTabClickInfo, IN int iNavTabClickInfoCount, IN BOOL bWaitAnswer);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetNavTab
// Description:  ȡ�õ����������ı�ǩҳ
// Parameters:   1) I8CD_NavType_en enNavType [IN] ��������ť����
// Return:       ��ǩҳ��Ϣ����Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
//-----------------------------------------------------------------------------
DLL_API_EXPORT I8CD_NavTabArray_st* _stdcall I8CD_GetNavTab(IN I8CD_NavType_en enNavType);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_FindGame
// Description:  ������Ϸ
// Parameters:   1) LPCTSTR             lpszKey   [IN] �ؼ���,����Ϊ��
//               2) I8CD_FindFilter_st* pstFilter [IN] ɸѡ��,����Ϊ��
//               3) I8CD_Order_en       enOrder   [IN] ����ʽ
// Return:       ƥ�����Ϸ��Ϣ����Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
//-----------------------------------------------------------------------------
DLL_API_EXPORT I8CD_GameIDArray_st* _stdcall I8CD_FindGame(IN LPCTSTR lpszKey, IN I8CD_FindFilter_st* pstFilter, IN I8CD_Order_en enOrder);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_FindGameByChar
// Description:  ������ĸ������Ϸ
// Parameters:   1) TCHAR    tKey    [IN] ��ĸ(A-Z)
//               2) Order_en enOrder [IN] ����ʽ
// Return:       ƥ�����Ϸ��Ϣ����Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
//-----------------------------------------------------------------------------
DLL_API_EXPORT I8CD_GameIDArray_st* _stdcall I8CD_FindGameByChar(IN TCHAR tKey, IN I8CD_Order_en enOrder);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetGameByClassName
// Description:  ������������Ϸ
// Parameters:   1) LPCTSTR  lpszClassName [IN] ��Ϸ���
//               2) Order_en enOrder       [IN] ����ʽ
// Return:       ƥ�����Ϸ��Ϣ����Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
//-----------------------------------------------------------------------------
DLL_API_EXPORT I8CD_GameIDArray_st* _stdcall I8CD_GetGameByClassName(IN LPCTSTR lpszClassName, IN I8CD_Order_en enOrder);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetGameOnToolBar
// Description:  ȡ�ù������ϵ���Ϸ
// Parameters:   None.
// Return:       ƥ�����Ϸ��Ϣ����Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
//-----------------------------------------------------------------------------
DLL_API_EXPORT I8CD_GameIDArray_st* _stdcall I8CD_GetGameOnToolBar(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_CheckAdvancedPassword
// Description:  ���ͻ��˸߼����������Ƿ���ȷ
// Parameters:   1) LPCTSTR lpszPassword [IN] �ͻ��˸߼���������
// Return:       �ͻ��˸߼���������ƥ��ɹ�
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_CheckAdvancedPassword(IN LPCTSTR lpszPassword);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetGBKFromString
// Description:  ȡ�ú��ֹ�����չ��
// Parameters:   1) LPTSTR  lpszOutString [OUT] ���ɵĺ��ֹ�����չ��
//               2) int     iOutMaxCount  [IN]  �����ַ���������ַ���
//               3) LPCTSTR lpszString    [IN]  �ַ���
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_GetGBKFromString(OUT LPTSTR lpszOutString, IN int iOutMaxCount, IN LPCTSTR lpszString);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetServerIP
// Description:  ȡ�÷�����IP
// Parameters:   None.
// Return:       ������IP
//-----------------------------------------------------------------------------
DLL_API_EXPORT LPCTSTR _stdcall I8CD_GetServerIP(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_SetServerIP
// Description:  ���÷�����IP
// Parameters:   1) LPCTSTR lpszServerIP [IN] ������IP
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_SetServerIP(IN LPCTSTR lpszServerIP);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetOperatorAfterRunGame
// Description:  ȡ��������Ϸ�����ִ�еĲ���
// Parameters:   None.
// Return:       ������Ϸ�������Ҫִ�еĲ���
//-----------------------------------------------------------------------------
DLL_API_EXPORT I8CD_OperatorAfterRunGame_en _stdcall I8CD_GetOperatorAfterRunGame(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_IsInitializeHy
// Description:  ��ԭ�����Ƿ����
// Parameters:   None.
// Return:       ��ԭ��������
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_IsInitializeHy(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_IsInstallHy
// Description:  �Ƿ�װ��ԭ����
// Parameters:   None.
// Return:       ��ԭ�����Ѱ�װ
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_IsInstallHy(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetProtectedDriver
// Description:  ȡ�ÿ�����ԭ�����Ĵ���
// Parameters:   None.
// Return:       ������ԭ�����Ĵ��̣���ʽ��CDE��
//-----------------------------------------------------------------------------
DLL_API_EXPORT LPCTSTR _stdcall I8CD_GetProtectedDriver(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetUnProtectedDriver
// Description:  ȡ��δ������ԭ�����Ĵ���
// Parameters:   None.
// Return:       δ������ԭ�����Ĵ��̣���ʽ��CDE��
//-----------------------------------------------------------------------------
DLL_API_EXPORT LPCTSTR _stdcall I8CD_GetUnProtectedDriver(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_ProtectDriver
// Description:  �Դ��̿�����ԭ�����͹رջ�ԭ����(��ʽ��CDE)
// Parameters:   1) LPCTSTR lpszProtectedDriver   [IN]  ��Ҫ������ԭ�����Ĵ���
//               2) LPCTSTR lpszUnProtectedDriver [IN]  ��Ҫ�رջ�ԭ�����Ĵ���
//               3) BOOL*   pbNeedRestart         [OUT] ��Ҫ���������
// Return:       �����ɹ�
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_ProtectDriver(IN LPCTSTR lpszProtectedDriver, IN LPCTSTR lpszUnProtectedDriver, OUT BOOL* pbNeedRestart);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_CheckDisk
// Description:  ���̼��
// Parameters:   1) LPCTSTR lpszDriver [IN] ��Ҫ���Ĵ��̣���ʽ��CDE��
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_CheckDisk(IN LPCTSTR lpszDriver);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_SaveArchiveToFlashDisk
// Description:  �������̴浵
// Parameters:   1) DWORD gid [IN] ��ϷID
// Return:       �����ɹ�
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_SaveArchiveToFlashDisk(IN DWORD gid);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_ReadArchiveToFlashDisk
// Description:  ��������ȡ��
// Parameters:   1) DWORD gid [IN] ��ϷID
// Return:       �����ɹ�
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_ReadArchiveToFlashDisk(IN DWORD gid);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_ShowFlashDisk
// Description:  ��ʾ��������
// Parameters:   None.
// Return:       �����ɹ�
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_ShowFlashDisk(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_LockComputer
// Description:  ���������
// Parameters:   None.
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_LockComputer(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_SetResolution
// Description:  ������Ļ�ֱ���
// Parameters:   None.
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_SetResolution(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_SetSysMouse
// Description:  ����ϵͳ���
// Parameters:   None.
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_SetSysMouse(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_SetVolume
// Description:  ��������
// Parameters:   None.
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_SetVolume(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_OpenGameDirectory
// Description:  ����Ϸ����Ŀ¼
// Parameters:   1) DWORD gid [IN] ��ϷID
// Return:       �����ɹ�
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_OpenGameDirectory(IN DWORD gid);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_IsGameEnableRun
// Description:  �����Ϸ�Ƿ�����У�û������Ϊɾ����Ϸ�ļ�����Ϸ�汾�������µ�����
// Parameters:   1) DWORD gid [IN] ��ϷID
// Return:       ��Ϸ������
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_IsGameEnableRun(IN DWORD gid);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetInputMethod
// Description:  ȡ�����뷨����ϷID���������ʾ����û��������������������뷨
// Parameters:   None.
// Return:       ���뷨����ϷID�����û�з���0
//-----------------------------------------------------------------------------
DLL_API_EXPORT DWORD _stdcall I8CD_GetInputMethod(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_UpdateGame
// Description:  ������Ϸ
// Parameters:   1) DWORD                   gid               [IN] ��ϷID
//               2) I8CD_DownloadMode_en    enDownloadMode    [IN] ���ط�ʽ
//               3) I8CD_UpdateCallBack_pfn pfnUpdateCallBack [IN] ���»ص����������Դ���
//               4) void*                   pCallBackParam    [IN] ���»ص������õĲ��������Դ���
// Return:       �����������������ͷţ��������ֵΪ�ձ�ʾ��Ϸ������£�����ֱ������
//-----------------------------------------------------------------------------
DLL_API_EXPORT HANDLE _stdcall I8CD_UpdateGame(IN DWORD gid, IN I8CD_DownloadMode_en enDownloadMode, IN I8CD_UpdateCallBack_pfn pfnUpdateCallBack, IN void* pCallBackParam);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_StopUpdate
// Description:  ֹͣ����
// Parameters:   1) HANDLE hUpdate [IN] ����������
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_StopUpdate(IN HANDLE hUpdate);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetPertinentGame
// Description:  ȡ����Ϸ��ع���
// Parameters:   1) DWORD gid [IN] ��ϷID
// Return:       ƥ�����Ϸ��Ϣ����Ҫ��I8CD_ReleaseData�ͷŷ��ص�ָ��
//-----------------------------------------------------------------------------
DLL_API_EXPORT I8CD_GameIDArray_st* _stdcall I8CD_GetPertinentGame(IN DWORD gid);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_RunGame
// Description:  ������Ϸ��������Ϸǰ��Ҫ"������Ϸ"��"�����Ϸ��Ϣ����Ϸ�ļ��Ƿ�ƥ��"��"������Ϸ"Ҫ�ȴ���������Ϊ��ɣ�"�����Ϸ��Ϣ����Ϸ�ļ��Ƿ�ƥ��"Ҫ��֤�汾һ��
// Parameters:   1) DWORD gid [IN] ��ϷID
// Return:       ������Ϸ���
//-----------------------------------------------------------------------------
DLL_API_EXPORT I8CD_RunGameResult_en _stdcall I8CD_RunGame(IN DWORD gid);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetClientMenu
// Description:  ȡ�ò˵��ּ���Ϣ�����û�з���NULL
// Parameters:   None.
// Return:       �˵��ּ���Ϣ��XML���ݸ�ʽ
//-----------------------------------------------------------------------------
DLL_API_EXPORT LPCTSTR _stdcall I8CD_GetClientMenu(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_IsVisible
// Description:  ��鴰���Ƿ�ɼ���������ɼ����ͻ��˽�����Բ��ɼ���ʽ������ֱ���ص������յ���ʾ����
// Parameters:   None.
// Return:       ����/��ʽ�����ͻ���
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_IsVisible(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_RemoteControl
// Description:  ��������˵�Զ�̿���
// Parameters:   None.
// Return:       �����ɹ�
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_RemoteControl(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetAllDriver
// Description:  ȡ�������������
// Parameters:   None.
// Return:       ����������̣���ʽ��CDE��
//-----------------------------------------------------------------------------
DLL_API_EXPORT LPCTSTR _stdcall I8CD_GetAllDriver(void);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_GetStartupInfo
// Description:  ȡ�ò˵�������Ϣ
// Parameters:   1) I8CD_StartupInfo_st* pstStartupInfo [OUT] �˵�������Ϣ
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_GetStartupInfo(OUT I8CD_StartupInfo_st* pstStartupInfo);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_IsNeedRefreshGameVDisk
// Description:  ����Ƿ���ҪΪ��Ϸˢ��������
// Parameters:   1) DWORD gid [IN] ��ϷID
// Return:       ��Ҫˢ��������
//-----------------------------------------------------------------------------
DLL_API_EXPORT BOOL _stdcall I8CD_IsNeedRefreshGameVDisk(IN DWORD gid);
//-----------------------------------------------------------------------------
// FunctionName: I8CD_RefreshGameVDisk
// Description:  Ϊ��Ϸˢ��������
// Parameters:   1) DWORD gid [IN] ��ϷID
// Return:       None.
//-----------------------------------------------------------------------------
DLL_API_EXPORT void _stdcall I8CD_RefreshGameVDisk(IN DWORD gid);


