#ifndef __i8desk_cltsvrdef_inc__
#define __i8desk_cltsvrdef_inc__

#include <string>
#include "define.h"
#include "Extend STL/UnicodeStl.h"
#include "i8type.hpp"

#define    KEY_I8DESK			      TEXT("SOFTWARE\\Goyoo\\i8desk")
#define    KEY_I8DESK_GID		      TEXT("SOFTWARE\\Goyoo\\i8desk\\gidinfo")
#define    KEY_I8DESK_TASK		      TEXT("SOFTWARE\\Goyoo\\i8desk\\task")

//������������Խ��ܵ�����
enum CliPlugMgrCmd_en
{
	E_CPMC_LOAD_LOCAL_PLUG = 1, //���ر��ز��
};

#ifndef MAX_GUID_LEN
#define MAX_GUID_LEN 64
#endif

#ifndef MAX_NAME_LEN
#define MAX_NAME_LEN		64
#endif

#ifndef MAX_PARAM_LEN
#define MAX_PARAM_LEN		280
#endif

enum BootTask_RunDate_en
{
    E_BTRD_MONDAY    = 0x1,
    E_BTRD_TUESDAY   = 0x2,
    E_BTRD_WEDNESDAY = 0x4,
    E_BTRD_THURSDAY  = 0x8,
    E_BTRD_FRIDAY    = 0x10,
    E_BTRD_SATURDAY  = 0x20,
    E_BTRD_SUNDAY    = 0x40,
};

enum BootTask_RunType_en
{
    E_BTRT_SERVICE     = 0, //��������
    E_BTRT_BARONLINE   = 1, //�����˵�����
};

//�����������
typedef struct tagSTBootTaskParam
{
    TCHAR szTaskId[MAX_GUID_LEN]; //����ID
    DWORD dwTaskType;             //��������
	DWORD dwFlag;                 //ֻ�ڰ�װ�˻�ԭ������ϵͳ��������
    DWORD dwRunDate;              //ִ������ �����ڱ�ʾ ����һ��1�� ���ڶ���2 ... �����ߣ�64�����ǿ�����ϵģ����磺65 = (����һ��������)��
    DWORD dwRunBeginTime;         //��ʼ����ʱ�� ��HH:MM:SS��
    DWORD dwDelayTime;            //�ӳ�����ʱ�� ��SS��
    DWORD dwRunEndTime;           //��ֹ����ʱ�� ��HH:MM:SS��
	DWORD dwOutofTime;            //����ʱ�� ��YY:MM:DD:HH:MM:SS��
    DWORD dwRunType;              //�������� ���������У�0�������˵����У�1��
    DWORD dwStatus;               //����״̬ ��δ���ã�0�� ���ã�1��
	TCHAR szAppendParam[2048];    //���Ӳ���
}STBootTaskParam;

//�����̽ṹ
typedef struct tagSTVirtualDiskInfo
{
	TCHAR                              szVDiskId[40];                                       //������ID  
	DWORD                              dwServerIP;                                          //������IP	
	DWORD                              dwServerPort;                                        //�������˿�
	DWORD                              dwServerDrive;                                       //������̷�
	DWORD                              dwClientDrive;                                       //�ͻ����̷�
	DWORD                              dwDiskType;                                          //������
	DWORD                              dwStartType;                                         //ˢ������
    TCHAR                              szServerId[MAX_PATH];                                //SID
    DWORD                              dwSize;                                              //����ռ��С
    DWORD                              dwSsdDrv;                                            //SSD�̷���д��ĸ��ASCII��
 
	tagSTVirtualDiskInfo()
	{
		ZeroMemory(this, sizeof(STVirtualDiskInfo));
	}
}STVirtualDiskInfo;

//��Ϸ������Ϣ
typedef struct tagSTGameIndexInfo
{
	DWORD	            			  dwGameId;                                            //��ϷID
	DWORD                             dwGameIndex;                                         //��Ϸ����
	DWORD                             dwRunTypeIndex;                                      //���з�ʽ

	tagSTGameIndexInfo()
	{
		dwGameId = dwGameIndex = dwRunTypeIndex = 0;
	}
}STGameIndexInfo;

//��Ϸ��Ϣ
typedef struct tagSTGameInfo
{
	DWORD                             dwGameId;                                            //��ϷID
	DWORD                             dwAssociatedId;                                      //����ID
	TCHAR                             szGameName[MAX_PATH];
	TCHAR                             szClassName[MAX_PATH];                               //��������
	TCHAR                             szExeName[MAX_PATH];                                 //�����ļ�
	TCHAR                             szExeParam[MAX_PATH];                                //���в���
	DWORD                             dwGameSize;                                          //��Ϸ��С��K��
	DWORD                             dwDesktopLink;                                       //��ݷ�ʽ
	DWORD                             dwMenuToolBar;                                       //�˵�������
	TCHAR                             szServerPath[MAX_PATH];                              //�����·��
	TCHAR                             szClientPath[MAX_PATH];                              //�ͻ���·��
	DWORD                             dwDeleteFlg;                                          //��Ϸ�ռ䲻��ʱ����ɾ��
	TCHAR                             szFeatureFile[MAX_PATH];                             //�����ļ�
	TCHAR                             szArchiveInfo[MAX_PATH];                             //�浵��Ϣ
	DWORD                             dwIDCUpdateTime;                                     //IDC����ʱ��
	DWORD                             dwIDCVersion;                                        //IDC�汾
	DWORD                             dwServerVersion;                                     //�������汾
	DWORD                             dwUpdate;                                            //�Ƿ����
    DWORD                             dwI8Pay;                                              //��ֵ��Ϸ
	DWORD                             dwIDCClickNum;                                       //IDC�����
	DWORD                             dwServerClickNum;                                    //���������
	DWORD                             dwRunType;                                           //���з�ʽ
	TCHAR                             szVDiskID[MAX_PATH];                                 //������ID
	DWORD                             dwStatus;
	TCHAR                             szComment[MAX_PATH];                                 //��Ϸ����
	TCHAR                             szVDiskPath[MAX_PATH];                               //������·��
    DWORD                             dwRepair;                                            //������Ϸʱ��CRC�Ƚ�
	tagSTGameInfo()
	{
		ZeroMemory(this, sizeof(tagSTGameInfo));
	}
}STGameInfo;

//��Ϸͼ����Ϣ
typedef struct tagSTIconItem
{
	char                              *pIconData;                                          //ͼ������
	DWORD                             dwIconCRC;                                           //ͼ��CRC

	tagSTIconItem()
	{
		pIconData  = NULL;
		dwIconCRC  = 0;
	}
}STIconItem;

//�ͻ���Ӳ����Ϣ
typedef struct tagSTCltHardwareInfo
{
	TCHAR                              szCPU[MAX_PATH];		            		           //CPU��Ϣ
	TCHAR                              szMemory[MAX_PATH];		    	                   //�ڴ���Ϣ
	TCHAR                              szDisk[MAX_PATH];		    	                       //������Ϣ
	TCHAR                              szSoundCard[MAX_PATH];
	TCHAR                              szGraphics[MAX_PATH];	    	                       //�Կ���Ϣ
	TCHAR                              szMainboard[MAX_PATH];	    	                   //������Ϣ
	TCHAR                              szNIC[MAX_PATH];				                       //������Ϣ
	TCHAR                              szWebcam[MAX_PATH];		    	                   //����ͷ��Ϣ

	tagSTCltHardwareInfo()
	{
		ZeroMemory(this, sizeof(tagSTCltHardwareInfo));
	}

	BOOL operator==(const tagSTCltHardwareInfo& rParam) const
	{
		if (lstrcmp(szCPU, rParam.szCPU) != 0
			|| lstrcmp(szMemory, rParam.szMemory) != 0
			|| lstrcmp(szDisk, rParam.szDisk) != 0
			|| lstrcmp(szSoundCard, rParam.szSoundCard) != 0
			|| lstrcmp(szGraphics, rParam.szGraphics) != 0
			|| lstrcmp(szMainboard, rParam.szMainboard) != 0
            || lstrcmp(szNIC, rParam.szNIC) != 0
			|| lstrcmp(szWebcam, rParam.szWebcam) != 0)
		{
			return FALSE;
		}
		return TRUE;
	}
}STCltHardwareInfo;

//�ͻ���ϵͳ��Ϣ
typedef struct tagSTSysCfgInfo
{
	TCHAR                              szName[MAX_PATH];			       				           //�������
	TCHAR                              szOptSystem[MAX_PATH];		    	                       //����ϵͳ
	TCHAR                              szMacAddr[MAX_PATH];			    		                   //MAC��ַ
	DWORD                              dwIP;    
	DWORD                              dwGate;
	DWORD                              dwDns0;
	DWORD                              dwDns1;
	DWORD                              dwSubMask;

	tagSTSysCfgInfo()
	{
		ZeroMemory(this, sizeof(tagSTSysCfgInfo));
	}

	BOOL operator==(const tagSTSysCfgInfo& rParam) const
	{
		if (lstrcmp(szName, rParam.szName) != 0
			|| lstrcmp(szOptSystem, rParam.szOptSystem) != 0
			|| lstrcmp(szMacAddr, rParam.szMacAddr) != 0
			|| dwIP != rParam.dwIP
			|| dwGate != rParam.dwGate
			|| dwDns0 != rParam.dwDns0
			|| dwDns1 != rParam.dwDns1
			|| dwSubMask != rParam.dwSubMask)
		{
			return FALSE;
		}
		return TRUE;
	}
}STSysCfgInfo;

//����汾��Ϣ
typedef struct tagSTI8Version
{  
    TCHAR                              szProtVer[MAX_PATH];
    TCHAR                              szVirtualDiskVer[MAX_PATH];
    TCHAR                              szCltUIVer[MAX_PATH];
    TCHAR                              szCltDataVer[MAX_PATH];
	TCHAR                              szCltSvrVer[MAX_PATH];

	tagSTI8Version()
	{
		ZeroMemory(this, sizeof(tagSTI8Version));
	}
}STI8Version;

//��ԭ��Ϣ
typedef struct tagSTHyInfo
{
	DWORD                              dwInstall;
	TCHAR                              szAllDriver[MAX_PATH];
	TCHAR                              szProtDriver[MAX_PATH];

	tagSTHyInfo()
	{
		ZeroMemory(this, sizeof(tagSTHyInfo));
	}
}STHyInfo;

//��������
typedef struct tagSTServerInfo
{
    DWORD                             dwUpdateIP;                                //����IP
    DWORD                             dwVDiskIPCount;                            //������IP����
	DWORD                             adwVDiskIP[10];                            //������IP

	tagSTServerInfo()
	{
		ZeroMemory(this, sizeof(tagSTServerInfo));
	}
}STServerInfo;

typedef struct tagUpGameinfo        //�������ͼ�¼��Ϸ������Ϣ
{
	DWORD			GID;				//��ϷGID
    i8desk::FC_COPY_MODE	Flag;		//��Ϸ�ĶԱȷ�ʽ
	DWORD			Srvip;				//��������ip 
	DWORD			speed;				//�����ٶ�ֵ
    DWORD           resv;				//�����ֶ�
    TCHAR           szTaskId[MAX_GUID_LEN]; //��������ID
	TCHAR			SVRPATH[MAX_PATH]; //��Ϸ�ڷ������ϵ�·��
	TCHAR			CLIPATH[MAX_PATH]; //��Ϸ�ڿͻ����ϵ�·��
	tagUpGameinfo()
	{
		ZeroMemory(this,sizeof(tagUpGameinfo)); 
	}
}UpGameinfo;


//�����ļ���Ϣ
typedef struct tagSTUpdateFileInfo
{
	stdex::tString                            strFilePath;                                         //�ļ�·��
	stdex::tString                            strTempFilePath;                                     //��ʱ·��
	stdex::tString                            strRelativePath;                                     //���·��
	DWORD                                     dwFileCRC;                                           //�ļ�CRC
    tagSTUpdateFileInfo() : dwFileCRC(0)
	{
	}

}STUpdateFileInfo;

//�ļ���Ϣ
typedef struct tagSTUptFileItem
{
	DWORD                             dwFileCRC;                                           //�ļ�CRC
	char                              szFileName[MAX_PATH];                                //�ļ�����, ASCLLֵ���������˼��ݾɰ汾

	tagSTUptFileItem()
	{
		ZeroMemory(this, sizeof(tagSTUptFileItem));
	}
}STUptFileItem;

//�ļ��б�
typedef struct tagSTUptFileIdx
{
	DWORD                             dwFileListCRC;                                       //�ļ��б�CRC
	DWORD                             dwVersion;                                           //���°汾��
	DWORD                             dwFileCount;                                         //�����ļ���

	tagSTUptFileIdx()
	{
		ZeroMemory(this, sizeof(tagSTUptFileIdx));
	}
}STUptFileIdx;

//��ݷ�ʽ
typedef struct tagSTShortcut
{
	TCHAR                              szName[MAX_PATH];                                    //����
	TCHAR                              szTargetPath[MAX_PATH];                              //Ŀ��·��
	TCHAR                              szParam[MAX_PATH];                                   //����
	TCHAR                              szValue[MAX_PATH];                                   //����ֵ
	TCHAR                              szIconPath[MAX_PATH];                                //ͼ��·��

	tagSTShortcut()
	{
		ZeroMemory(this, sizeof(tagSTShortcut));
	}
}STShortcut;



struct PlugInIndex_st //�������
{
    DWORD    gid;                           //����ID
    DWORD    dwVersion;                     //����汾
    PlugInIndex_st() : gid(0), dwVersion(0)
    {
    }
};


#define I8_AUTO_TRY       try {
#define I8_AUTO_CATCH     } catch (...) {}
#define I8_NAMESPACE_BEGIN         namespace i8desk{
#define I8_NAMESPACE_END           }


#endif