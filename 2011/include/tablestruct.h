#ifndef I8TYPE_H
#define I8TYPE_H

#include <string>
#include <memory>
#include <winsock2.h>


namespace i8desk {
	typedef short int16;
	typedef unsigned short uint16;
	typedef unsigned short ushort;
	typedef int int32;
	typedef unsigned int uint32;
	typedef unsigned int uint;
	typedef unsigned long ulong;
	typedef long long int64;
	typedef long long longlong;
	typedef unsigned long long uint64;
	typedef unsigned long long ulonglong;
//-----------------------------------------

const UINT MAX_LOG_LEN = 1024 * 8;
const UINT MAX_PLUGIN_NAME_LEN = MAX_PATH;
}

//////////////////////////////////////////////////
//for database
namespace i8desk {
namespace db {
	
#pragma pack(push, 8)

static const long MAX_AREA_NUM  = 32;
static const long MAX_GAME_GID = 1024*64;

#define MAX_NAME_LEN		64
#define MAX_GUID_LEN		64
#define MAX_PARAM_LEN		280
#define MAX_REMARK_LEN		280
#define MAX_SYSOPT_LEN		1024
#define MAX_IPSTRING_LEN	16
#define MAX_MACSTRING_LEN	32
#define MAX_VERSTRING_LEN	32
#define MAX_DISKPARTION_LEN	64
#define MAX_TEXT_LEN		255

struct tClass {
	TCHAR	CID[ MAX_GUID_LEN ];
	TCHAR	Name[ MAX_NAME_LEN ];
	TCHAR	SvrPath[ MAX_PATH ];

	tClass(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tClass> TClassPtr;


#define MASK_TCLASS_DEFCLASS		(1LL << 1L)
#define MASK_TCLASS_NAME			(1LL << 2L)
#define MASK_TCLASS_SVRPATH			(1LL << 3L)

struct tGame {
	uint32	GID;								//��ϷID
	uint32	PID;								//������ϷID
	TCHAR	CID[ MAX_GUID_LEN ];				//���ID
	TCHAR	Name[ MAX_NAME_LEN ];				//��Ϸ����
	TCHAR	Exe[ MAX_PATH ];					//��Ϸ��ִ���ļ�����(GameExe)
	TCHAR	Param[ MAX_PARAM_LEN ];				//��Ϸ���в���
	ulong	Size;								//��Ϸ�ļ���С(KBΪ��λ)	
	TCHAR	SvrPath[ MAX_PATH ];				//��Ϸ�����·��
	TCHAR	CliPath[ MAX_PATH ];				//��Ϸ�ͷ���·��
	TCHAR	TraitFile[ MAX_PATH ];				//��Ϸ�����ļ�
	TCHAR	SaveFilter[ MAX_REMARK_LEN ];		//��Ϸ�浵�ļ�(��|�ָ�����������base64����)
	int		DeskLink;							//0|1�����ݷ�ʽ
	int		Toolbar;							//0|1�˵���������ʾ
	TCHAR	Memo[ MAX_REMARK_LEN ];				//��ע(commemt)
	TCHAR	GameSource[ MAX_REMARK_LEN ];		//��Ϸ��Դ
	ulong	IdcAddDate;							//������Ϸ���ʱ��
	int		EnDel;								//0|1�ռ䲻��ʱ������ɾ��
	ulong	IdcVer;								//���İ汾��
	ulong	SvrVer;								//���ط���˰汾��
	ulong	IdcClick;							//���Ŷ�
	ulong	SvrClick;							//������Ϸ�������
	ulong	SvrClick2;							//�ϱ���Ϸ�������
	int		I8Play;								//��ֵ��Ϸ
	int		AutoUpt;							//�ֶ�,�Զ�����
	int		Priority;							//���ȼ�
	int		Force;								//ǿ��(Auto)
	TCHAR	ForceDir[ MAX_PATH ];				//ǿ��Ŀ¼
	int		Status;								//�Ƿ񱾵���Ϸ
	int		StopRun;							//�Ƿ�����ͣ����Ϸ
	int		Repair;								//�Ƿ�ǿ�Ƹ�����Ϸ
	int		Hide;								//�Ƿ�������Ϸ

	tGame(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tGame> TGamePtr;


#define MASK_TGAME_GID				(1LL << 1L)
#define MASK_TGAME_PID				(1LL << 2L)
#define MASK_TGAME_CID				(1LL << 3L)
#define MASK_TGAME_NAME				(1LL << 4L)
#define MASK_TGAME_EXE				(1LL << 5L)
#define MASK_TGAME_PARAM			(1LL << 6L)
#define MASK_TGAME_SIZE				(1LL << 7L)	
#define MASK_TGAME_SVRPATH			(1LL << 8L)	
#define MASK_TGAME_CLIPATH			(1LL << 9L)
#define MASK_TGAME_TRAITFILE		(1LL << 10L)
#define MASK_TGAME_SAVEFILTER		(1LL << 11L)
#define MASK_TGAME_DESKLINK			(1LL << 12L)
#define MASK_TGAME_TOOLBAR			(1LL << 13L)
#define MASK_TGAME_MEMO				(1LL << 14L)
#define MASK_TGAME_GAMESOURCE		(1LL << 15L)
#define MASK_TGAME_IDCADDDATE		(1LL << 16L)
#define MASK_TGAME_ENDEL			(1LL << 17L)
#define MASK_TGAME_IDCVER			(1LL << 18L)
#define MASK_TGAME_SVRVER			(1LL << 19L)
#define MASK_TGAME_IDCCLICK			(1LL << 20L)
#define MASK_TGAME_SVRCLICK			(1LL << 21L)
#define MASK_TGAME_SVRCLICK2		(1LL << 22L)
#define MASK_TGAME_I8PLAY			(1LL << 23L)
#define MASK_TGAME_AUTOUPT			(1LL << 24L)
#define MASK_TGAME_PRIORITY			(1LL << 25L)
#define MASK_TGAME_FORCE			(1LL << 26L)
#define MASK_TGAME_FORCEDIR			(1LL << 27L)
#define MASK_TGAME_STATUS			(1LL << 28L)
#define MASK_TGAME_STOPRUN			(1LL << 29L)
#define MASK_TGAME_REPAIR			(1LL << 30L)
#define MASK_TGAME_HIDE				(1LL << 31L)


struct tArea {
	TCHAR	AID[MAX_GUID_LEN];		//����ID
	TCHAR	Name[MAX_NAME_LEN];		//��������
	TCHAR   SvrID[MAX_GUID_LEN];	//������ID 

	tArea(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tArea>	TAreaPtr;

#define MASK_TAREA_AID				(1LL << 1L)
#define MASK_TAREA_NAME				(1LL << 2L)
#define MASK_TAREA_SVRID			(1LL << 3L)


struct tRunType {
	TCHAR	AID[MAX_GUID_LEN];	//����ID
	uint32	GID;				//��ϷID
	int		Type;				//���з�ʽ
	TCHAR	VID[MAX_GUID_LEN];	//������ID

	tRunType(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tRunType>	TRunTypePtr;


#define MASK_TRUNTYPE_GID			(1LL << 1L)
#define MASK_TRUNTYPE_AID			(1LL << 2L)
#define MASK_TRUNTYPE_TYPE			(1LL << 3L)
#define MASK_TRUNTYPE_VID			(1LL << 4L)


struct tClient 
{
	TCHAR Name[MAX_NAME_LEN];				//�ͷ�������
	TCHAR AID[MAX_GUID_LEN];				//�ͷ�����������
	ulong IP;								//�ͷ���IP
	TCHAR MAC[MAX_MACSTRING_LEN];			//�ͷ���MAC��ַ
	ulong Mark;								//�������룬������
	ulong Gate;								//����
	ulong DNS;								//����������1
	ulong DNS2;								//����������2
	int  ProtInstall;						//�Ƿ�װ������ԭ
	TCHAR Partition[MAX_DISKPARTION_LEN];	//��������	
	TCHAR ProtVer[MAX_VERSTRING_LEN];		//��ԭ�汾��
	TCHAR VDiskVer[MAX_VERSTRING_LEN];		//������汾��
	TCHAR MenuVer[MAX_VERSTRING_LEN];		//�˵��汾��
	TCHAR CliSvrVer[MAX_VERSTRING_LEN];		//�ͷ��˷���汾��
	TCHAR System[ MAX_REMARK_LEN ];			//����ϵͳ��Ϣ
	TCHAR CPU[ MAX_REMARK_LEN ];			//CPU��Ϣ
	TCHAR Mainboard[ MAX_REMARK_LEN ];		//������Ϣ
	TCHAR Memory[ MAX_REMARK_LEN ];			//�ڴ���Ϣ
	TCHAR Disk[ MAX_REMARK_LEN ];			//������Ϣ
	TCHAR Video[ MAX_REMARK_LEN ];			//�Կ���Ϣ
	TCHAR Audio[ MAX_REMARK_LEN ];			//������Ϣ
	TCHAR Network[ MAX_REMARK_LEN ];		//������Ϣ
	TCHAR Camera[ MAX_REMARK_LEN ];			//����ͷ��Ϣ
	int		Online;							// 1:ONLINE,0:OFFLINE
	SOCKET	Socket;
	int   Temperature;						// �¶�

	tClient(){ memset(this,0,sizeof(*this)); }
};

typedef std::tr1::shared_ptr<tClient>	TClientPtr;


#define MASK_TCLIENT_NAME			(1LL << 1L)
#define MASK_TCLIENT_AID			(1LL << 2L)	
#define MASK_TCLIENT_IP				(1LL << 3L)
#define MASK_TCLIENT_MAC			(1LL << 4L)	
#define MASK_TCLIENT_MARK			(1LL << 5L)
#define MASK_TCLIENT_GATE			(1LL << 6L)
#define MASK_TCLIENT_DNS			(1LL << 7L)
#define MASK_TCLIENT_DNS2			(1LL << 8L)
#define MASK_TCLIENT_PROTINSTALL	(1LL << 9L)
#define MASK_TCLIENT_PARTITION		(1LL << 10L)	
#define MASK_TCLIENT_PROTVER		(1LL << 11L)
#define MASK_TCLIENT_VDISKVER		(1LL << 12L)
#define MASK_TCLIENT_MENUVER		(1LL << 13L)
#define MASK_TCLIENT_CLISVRVER		(1LL << 14L)
#define MASK_TCLIENT_SYSTEM			(1LL << 15L)
#define MASK_TCLIENT_CPU			(1LL << 16L)
#define MASK_TCLIENT_MAINBOARD		(1LL << 17L)
#define MASK_TCLIENT_MEMORY			(1LL << 18L)
#define MASK_TCLIENT_DISK			(1LL << 19L)
#define MASK_TCLIENT_VIDEO			(1LL << 20L)
#define MASK_TCLIENT_AUDIO			(1LL << 21L)
#define MASK_TCLIENT_NETWORK		(1LL << 22L)	
#define MASK_TCLIENT_CAMERA			(1LL << 23L)
#define MASK_TCLIENT_ONLINE			(1LL << 24L)
#define MASK_TCLIENT_SOCKET			(1LL << 25L)
#define MASK_TCLIENT_TEMPERATURE	(1LL << 26L)



struct tVDisk {
	TCHAR	VID[MAX_GUID_LEN];		//�����ID
	TCHAR	SvrID[MAX_GUID_LEN];	//������ID
	ulong	SoucIP;					//ԴIP
	int		Port;					//������˿�
	int		SvrDrv;					//�̷���д��ĸ��ASCII��
	int		CliDrv;					//�̷���д��ĸ��ASCII��
	int		Type;					//0:I8Desk�����̣�1:������������
	int		LoadType;				//0:����ˢ�̣�1�����в˵�ˢ�̣�2��������Ϸˢ��
	TCHAR   SvrMode[MAX_NAME_LEN];	//����ģʽ
	ulong   Size;					// ����ռ��С
	int     SsdDrv;					// SSD�̷���д��ĸ��ASCII��

	tVDisk(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tVDisk>	TVDiskPtr;

#define MASK_TVDISK_VID				(1LL << 1L)
#define MASK_TVDISK_SVRID			(1LL << 2L)
#define MASK_TVDISK_SOUCIP			(1LL << 3L)
#define MASK_TVDISK_PORT			(1LL << 4L)
#define MASK_TVDISK_SVRDRV			(1LL << 5L)
#define MASK_TVDISK_CLIDRV			(1LL << 6L)
#define MASK_TVDISK_TYPE			(1LL << 7L)	
#define MASK_TVDISK_LOADTYPE		(1LL << 8L)
#define MASK_TVDISK_SVRMODE			(1LL << 9L)
#define MASK_TVDISK_SIZE			(1LL << 10L)
#define MASK_TVDISK_SSDDRV			(1LL << 11L)



struct tVDiskStatus {
	ulong		VDiskIP;
	TCHAR		VID[MAX_GUID_LEN];
	ulong		Version;
	ulong		ClientCount;
	TCHAR       HostName[MAX_NAME_LEN];

	tVDiskStatus(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tVDiskStatus>	TVDiskStatusPtr;


#define MASK_TVDISKSTATUS_VDISKIP			(1LL << 1L)
#define MASK_TVDISKSTATUS_VID				(1LL << 2L)
#define MASK_TVDISKSTATUS_VERSION			(1LL << 3L)
#define MASK_TVDISKSTATUS_CLIENTCOUNT		(1LL << 4L)
#define MASK_TVDISKSTATUS_HOSTNAME			(1LL << 5L)

struct tVDiskClient {
	ulong		ClientIP;					//���ͻ���IP
	TCHAR		VID[MAX_GUID_LEN];			//��������ID
	ulong		VDiskIP;					//�������IP
	uint64		ReadCount;					//����ȡ������				
	ulong		ReadSpeed;					//����ȡ�ٶ�
	ulong		ReadMax;					//����ȡ��ֵ
	ulong		ConnectTime;				//������ʱ��
	ulong		CacheShooting;				//������������
	ulong		OnlineTime;					//������ʱ��
	tVDiskClient(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tVDiskClient>	TVDiskClientPtr;


#define MASK_TVDISKCLIENT_CLIENTIP				(1LL << 1L)
#define MASK_TVDISKCLIENT_VID					(1LL << 2L)
#define MASK_TVDISKCLIENT_SVRNAME				(1LL << 3L)
#define MASK_TVDISKCLIENT_VDISKIP				(1LL << 4L)
#define MASK_TVDISKCLIENT_CLIENTNAME			(1LL << 5L)
#define MASK_TVDISKCLIENT_READCOUNT				(1LL << 6L)
#define MASK_TVDISKCLIENT_READSPEED				(1LL << 7L)
#define MASK_TVDISKCLIENT_READMAX				(1LL << 8L)
#define MASK_TVDISKCLIENT_CONNECTTIME			(1LL << 9L)
#define MASK_TVDISKCLIENT_CACHESHOOTING			(1LL << 10L)
#define MASK_TVDISKCLIENT_ONLINETIME			(1LL << 11L)

//SELECT a.AID as aid, a.Name as name, r.GID, r.RunType, v.VID, v.CliDrv
//FROM rGameArea r, tArea a, tVDisk v
//WHERE a.AID=r.AID AND v.VID=r.VID AND r.GID=%u
//2011��ע��
//struct vRunType {
//	TCHAR	AID[MAX_GUID_LEN];		//����ID
//	TCHAR	AName[MAX_NAME_LEN];	//������
//	int		GID;					//��ϷID
//	int		RunType;				//���з�ʽ
//	TCHAR	VID[MAX_GUID_LEN];		//������ID
//	TCHAR	VCliDrv;				//�����̿ͻ����̷�
//};

//�˵�Ƥ��
struct tBarSkin {
	TCHAR	Style[ MAX_NAME_LEN ];	//�����
	TCHAR	PathName[ MAX_PATH ];	//�ļ���
	TCHAR	Version[ MAX_GUID_LEN ];//�汾��

	tBarSkin(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tBarSkin>	TBarSkinPtr;

#define MASK_TBARSKIN_STYLE				(1LL << 1L)
#define MASK_TBARSKIN_PATHNAME			(1LL << 2L)
#define MASK_TBARSKIN_VERSION			(1LL << 3L)

//����̨ͨ��IP��UpDateGame��ѯ�ͻ�������Щ��Ϸ�����CMD_UPT_SM_IPHAVEGAME = 0x03
struct tViewGame
{
	TCHAR			GameName[MAX_NAME_LEN];	
	unsigned long   UpdateTime;	//version			
	long			GID;					

	tViewGame(){ ::memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tViewGame>	TViewGamePtr;

#define MASK_TVIEWGAME_GAMENAME				(1LL << 1L)
#define MASK_TVIEWGAME_UPDATETIME			(1LL << 2L)
#define MASK_TVIEWGAME_GID					(1LL << 3L)

//����̨ͨ��GID��UpDateGame��ѯ��Ϸ��������Щ�ͻ����ϡ����CMD_UPT_SM_GAMEINIP = 0x04
struct tViewClient
{
	TCHAR			ClientName[MAX_NAME_LEN];	
	unsigned long   UpdateTime;	//version	
	unsigned long   Ip;

	tViewClient(){ ::memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tViewClient>	TViewClientPtr;

#define MASK_TVIEWCLIENT_CLIENTNAME			(1LL << 1L)
#define MASK_TVIEWCLIENT_UPDATETIME			(1LL << 2L)
#define MASK_TVIEWCLIENT_IP					(1LL << 3L)


struct tFavorite {
	TCHAR FID[MAX_GUID_LEN];		//�ղؼ�ID(GUID)
	int	  Type;						//0:��վ��1:��Ӱ��2:����
	TCHAR Name[MAX_NAME_LEN];
	TCHAR URL[MAX_PATH];
	uint32 Serial;					//˳����������

	tFavorite(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tFavorite>	TFavoritePtr;

#define MASK_TFAVORITE_FID				(1LL << 1L)
#define MASK_TFAVORITE_TYPE				(1LL << 2L)
#define MASK_TFAVORITE_NAME				(1LL << 3L)
#define MASK_TFAVORITE_URL				(1LL << 4L)
#define MASK_TFAVORITE_SERIAL			(1LL << 5L)

struct tCmpBootTask {
	TCHAR TID[MAX_GUID_LEN];
	TCHAR Name[MAX_NAME_LEN];		// ��������
	int Type;						// brPushGame :��Ϸ���ͣ� ��brPushGame :��������
	int Flag;						// �Ƿ�ԭ����
	int RunDate;					// �������ڣ����ڱ�ʾ ����һ��1LL<<1L�� ���ڶ���1LL<<2L ... �����ߣ�1LL<<7L�����ǿ�����ϵģ����磺3 = (����һ�����ڶ�)��
	ulong StartTime;				// ��ʼʱ��� ��HH:MM:SS��
	ulong DelayTime;				// �ӳ�ʱ�� ��SS��
	ulong EndTime;					// ����ʱ�� ��HH:MM:SS��
	ulong EndDate;					// ����ʱ�� ��YY:MM:DD:HH:MM:SS��
	int RunType;					// �������� ���������У�0�������˵����У�1��
	int Status;						// ����״̬ ��δ���ã�0�� ���ã�1��
	TCHAR Parameter[2048];			// ����

	tCmpBootTask(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tCmpBootTask>	TCmpBootTaskPtr;


#define MASK_TCMPBOOTTASK_TID			(1LL << 1L)
#define MASK_TCMPBOOTTASK_NAME			(1LL << 2L)
#define MASK_TCMPBOOTTASK_TYPE			(1LL << 3L)
#define MASK_TCMPBOOTTASK_FLAG			(1LL << 4L)
#define MASK_TCMPBOOTTASK_RUNDATE		(1LL << 5L)
#define MASK_TCMPBOOTTASK_STARTTIME		(1LL << 6L)
#define MASK_TCMPBOOTTASK_DELAYTIME		(1LL << 7L)
#define MASK_TCMPBOOTTASK_ENDTIME		(1LL << 8L)
#define MASK_TCMPBOOTTASK_ENDDATE		(1LL << 9L)
#define MASK_TCMPBOOTTASK_RUNTYPE		(1LL << 10L)
#define MASK_TCMPBOOTTASK_STATUS		(1LL << 11L)
#define MASK_TCMPBOOTTASK_PARAMETER		(1LL << 12L)


struct tSysOpt {
	TCHAR key[MAX_NAME_LEN];
	TCHAR value[MAX_SYSOPT_LEN];

	tSysOpt(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tSysOpt>	TSysOptPtr;

#define MASK_TSYSOPT_KEY			(1LL << 1L)
#define MASK_TSYSOPT_VALUE			(1LL << 2L)


#define MAX_ICON_DATA_SIZE (11*1024)

struct tIcon {
	uint32 gid;
	ulong size;
	unsigned char data[MAX_ICON_DATA_SIZE];

	tIcon(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tIcon>	TIconPtr;


#define MASK_TICON_GID					(1LL << 1L)
#define MASK_TICON_DATA					(1LL << 2L)
#define MASK_TICON_SIZE					(1LL << 3L)

struct tSyncTask {
	TCHAR	SID[ MAX_GUID_LEN ];			//����ID
	TCHAR	SvrID[ MAX_GUID_LEN ];			//������ID
	TCHAR	Name[ MAX_NAME_LEN ];			//��������
	TCHAR	SvrDir[MAX_PATH];				//��������Ŀ¼
	TCHAR	NodeDir[MAX_PATH];				//�ڵ��Ŀ¼
	ulong	SoucIp;							//ԴIP
	ulong	DestIp;							//Ŀ��IP
	int		Speed;							//���ͬ���ٶ�
	int		SyncType;						//ͬ����������
	int		Status;							//ͬ������״̬
	TCHAR	NameID[ MAX_GUID_LEN ];			//��������ID�Ǹ�ʱ��ֵ

	tSyncTask(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tSyncTask>	TSyncTaskPtr;

#define MASK_TSYNCTASK_SID			(1LL << 1L)
#define MASK_TSYNCTASK_SVRID		(1LL << 2L)
#define MASK_TSYNCTASK_NAME			(1LL << 3L)
#define MASK_TSYNCTASK_SVRDIR		(1LL << 4L)
#define MASK_TSYNCTASK_NODEDIR		(1LL << 5L)
#define MASK_TSYNCTASK_SOUCIP		(1LL << 6L)
#define MASK_TSYNCTASK_DESTIP		(1LL << 7L)
#define MASK_TSYNCTASK_SPEED		(1LL << 8L)
#define MASK_TSYNCTASK_SYNCTYPE		(1LL << 9L)
#define MASK_TSYNCTASK_STATUS		(1LL << 10L)
#define MASK_TSYNCTASK_NAMEID		(1LL << 11L)


struct tSyncGame {
	TCHAR	SID[ MAX_GUID_LEN ];			//����ID
	uint32	GID;							//GID

	tSyncGame(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tSyncGame>	TSyncGamePtr;

#define MASK_TSYNCGAME_SID			(1LL << 1L)
#define MASK_TSYNCGAME_GID			(1LL << 2L)


struct tServer {
	TCHAR	SvrID[ MAX_GUID_LEN ];			//������ID
	TCHAR	SvrName[ MAX_NAME_LEN ];		//����������
	int		SvrType;						//����������
	ulong	SvrIP;							//��������IP
	ulong	Ip1;							//IP1
	ulong	Ip2;							//IP2
	ulong	Ip3;							//IP3
	ulong	Ip4;							//IP4
	int		Speed;							//���ͬ���ٶ�
	int		BalanceType;					//����ƽ������

	tServer(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tServer>	TServerPtr;

#define MASK_TSERVER_SVRID			(1LL << 1L)
#define MASK_TSERVER_SVRNAME		(1LL << 2L)
#define MASK_TSERVER_SVRTYPE		(1LL << 3L)
#define MASK_TSERVER_SVRIP			(1LL << 4L)
#define MASK_TSERVER_IP1			(1LL << 5L)
#define MASK_TSERVER_IP2			(1LL << 6L)
#define MASK_TSERVER_IP3			(1LL << 7L)
#define MASK_TSERVER_IP4			(1LL << 8L)
#define MASK_TSERVER_SPEED			(1LL << 9L)
#define MASK_TSERVER_BALANCETYPE	(1LL << 10L)

struct tBootTaskArea {
	TCHAR	TID[ MAX_GUID_LEN ];		//����ID
	TCHAR	AID[ MAX_GUID_LEN ];		//����ID

	tBootTaskArea(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tBootTaskArea>	TBootTaskAreaPtr;


#define MASK_TBOOTTASKAREA_TID			(1LL << 1L)
#define MASK_TBOOTTASKAREA_AID			(1LL << 2L)

struct tPushGameStatic {
	uint32	GID;			//��ϷGID
	ulong	Size;			//��Ϸ��С
	ulong	BeginDate;		//��ʼ������Ϸʱ��
	ulong	EndDate;		//����������Ϸʱ��

	tPushGameStatic(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tPushGameStatic>	TPushGameStaticPtr;


#define MASK_TPUSHGAMESTATIC_GID			(1LL << 1L)
#define MASK_TPUSHGAMESTATIC_SIZE			(1LL << 2L)
#define MASK_TPUSHGAMESTATIC_BEGINDATE		(1LL << 3L)
#define MASK_TPUSHGAMESTATIC_ENDDATE		(1LL << 4L)

struct tModuleUsage {
	TCHAR	Name[ MAX_NAME_LEN ];			//�ͻ�����������ID
	TCHAR	MAC[ MAX_MACSTRING_LEN ];		//�ͻ���MAC��ַ
	uint32	MID;							//ģ����
	ulong	ClickCount;						//�����
	ulong	UsedTime;						//ͣ��ʱ��

	tModuleUsage(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tModuleUsage>	TModuleUsagePtr;


#define MASK_TMODULEUSAGE_NAME			(1LL << 1L)
#define MASK_TMODULEUSAGE_MAC			(1LL << 2L)
#define MASK_TMODULEUSAGE_MID			(1LL << 3L)
#define MASK_TMODULEUSAGE_CLICKCOUNT	(1LL << 4L)
#define MASK_TMODULEUSAGE_USEDTIME		(1LL << 5L)

struct tModule2Usage {
	TCHAR	MAC[ MAX_MACSTRING_LEN ];		//�ͻ���MAC��ַ
	uint32	MID;							//ģ����
	ulong	ClickCount;						//�����
	ulong	UsedTime;						//ͣ��ʱ��
	TCHAR	Name[MAX_NAME_LEN];				// ��������
	tModule2Usage(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tModule2Usage>	TModule2UsagePtr;

#define MASK_TMODULE2USAGE_MAC			(1LL << 1L)
#define MASK_TMODULE2USAGE_MID			(1LL << 2L)
#define MASK_TMODULE2USAGE_CLICKCOUNT	(1LL << 3L)
#define MASK_TMODULE2USAGE_USEDTIME		(1LL << 4L)
#define MASK_TMODULE2USAGE_NAME			(1LL << 5L)

#define MAX_DEVICEINFO_LEN      4096

//����״̬���
struct tServerStatus {
	TCHAR SvrID[ MAX_GUID_LEN ];			//������ID
	TCHAR SvrName[ MAX_NAME_LEN ];			//����������
	int I8DeskSvr;							//������״̬
	int I8VDiskSvr;							//�����̷���״̬
	int I8UpdateSvr;						//�������·���״̬
	int DNAService;							//�������ط���״̬
	int I8MallCashier;						//�̳�������״̬
	ulong LastBackupDBTime;					//�ϴα������ݿ�ʱ��
	size_t CPUUtilization;					//CPU������
	size_t MemoryUsage;						//�ڴ�ʹ����
	size_t DeadCounter;						//��������
	ulonglong RemainMemory;					//ʣ���ڴ�,kB
	uint32 NetworkSendRate;					//���緢��ƽ���ٶ�,kB/s
	uint32 NetworkRecvRate;					//�������ƽ���ٶ�,kB/s
	TCHAR DeviceInfo[ MAX_DEVICEINFO_LEN ];  //�豸��Ϣ
	int SvrType;							//1:������0���ӷ���
	tServerStatus(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tServerStatus>	TServerStatusPtr;

#define MASK_TSERVERSTATUS_SVRID			(1LL << 1L)
#define MASK_TSERVERSTATUS_SVRNAME			(1LL << 2L)
#define MASK_TSERVERSTATUS_I8DESKSVR		(1LL << 3L)
#define MASK_TSERVERSTATUS_I8VDISKSVR		(1LL << 4L)
#define MASK_TSERVERSTATUS_I8UPDATESVR		(1LL << 5L)
#define MASK_TSERVERSTATUS_DNASERVICE		(1LL << 6L)
#define MASK_TSERVERSTATUS_I8MALLCASHIER	(1LL << 7L)
#define MASK_TSERVERSTATUS_LASTBACKUPDBTIME	(1LL << 8L)
#define MASK_TSERVERSTATUS_CPUUTILIZATION	(1LL << 9L)
#define MASK_TSERVERSTATUS_MEMORYUSAGE		(1LL << 10L)
#define MASK_TSERVERSTATUS_DEADCOUNTER		(1LL << 11L)
#define MASK_TSERVERSTATUS_REMAINMEMORY		(1LL << 12L)
#define MASK_TSERVERSTATUS_NETWORKSENDRATE	(1LL << 13L)
#define MASK_TSERVERSTATUS_NETWORKRECVRATE	(1LL << 14L)
#define MASK_TSERVERSTATUS_DEVICEINFO		(1LL << 15L)
#define MASK_TSERVERSTATUS_SVRTYPE			(1LL << 16L)


//����״̬���
struct tDiskStatus {
	TCHAR SvrID[ MAX_GUID_LEN ];			//������ID
	uint32 Partition;						//�����̷�
	TCHAR SvrName[ MAX_NAME_LEN ];			//����������
	ulong Type;								//��������
	ulonglong Capacity;						//����������
	ulonglong UsedSize;						//��Ϸ��С
	ulonglong FreeSize;						//ʣ��ռ�
	size_t	DeadCounter;					//��������
	uint32 ReadDataRate;					//ƽ����ȡ�����ٶ�,KB/s

	tDiskStatus(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tDiskStatus>	TDiskStatusPtr;

#define MASK_TDISKSTATUS_SVRID				(1LL << 1L)
#define MASK_TDISKSTATUS_PARTITION			(1LL << 2L)
#define MASK_TDISKSTATUS_SVRNAME			(1LL << 3L)
#define MASK_TDISKSTATUS_TYPE				(1LL << 4L)
#define MASK_TDISKSTATUS_CAPACITY			(1LL << 5L)
#define MASK_TDISKSTATUS_USEDSIZE			(1LL << 6L)
#define MASK_TDISKSTATUS_FREESIZE			(1LL << 7L)
#define MASK_TDISKSTATUS_DEADCOUNTER		(1LL << 8L)
#define MASK_TDISKSTATUS_READDATARATE		(1LL << 9L)


//��������״̬���
struct tTaskStatus {
	uint32 GID;					//��ϷID
	int	   State;				//����״̬
	int    TaskType;			//��������
	ushort Connect;				//������
	ulong  DownloadState;		//������״̬
	ulong  TransferRate;		//�����ٶ�
	ulong  TimeLeft;			//ʣ��ʱ��
	ulong  TimeElapsed;			//����ʱ��
	ulong  Progress;			//����
	uint64 BytesTotal;			//��������
	uint64 UpdateSize;			//������
	uint64  BytesTransferred;	//������

	tTaskStatus(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tTaskStatus>	TTaskStatusPtr;


#define MASK_TTASKSTATUS_GID				(1LL << 1L)
#define MASK_TTASKSTATUS_STATE				(1LL << 2L)
#define MASK_TTASKSTATUS_TASKTYPE			(1LL << 3L)
#define MASK_TTASKSTATUS_CONNECT			(1LL << 4L)
#define MASK_TTASKSTATUS_DOWNLOADSTATE		(1LL << 5L)
#define MASK_TTASKSTATUS_BYTESTRANSFERRED	(1LL << 6L)
#define MASK_TTASKSTATUS_PROGRESS			(1LL << 7L)
#define MASK_TTASKSTATUS_TIMEELAPSED		(1LL << 8L)
#define MASK_TTASKSTATUS_TIMELEFT			(1LL << 9L)
#define MASK_TTASKSTATUS_TRANSFERRATE		(1LL << 10L)
#define MASK_TTASKSTATUS_BYTESTOTAL			(1LL << 11L)
#define MASK_TTASKSTATUS_UPDATESIZE			(1LL << 12L)


//ͬ������״̬���
struct tUpdateGameStatus {
	ulong  ClientIP;				// ����IP
	TCHAR  ClientName[MAX_NAME_LEN];// ��������
	uint32 GID;						// ��ϷID
	TCHAR  GameName[MAX_NAME_LEN];	// ��Ϸ����
	TCHAR  TID[ MAX_GUID_LEN ];		// ������������Ϸ���Ͷ�Ӧ��GID����ͬ�������е�SID
	int	   Type	;					// 0����Ϸ���ͣ�1��ͬ������2����������
	int    UpdateState;				// ͬ��״̬
	uint64 SizeLeft;				// ʣ����
	ulong TransferRate;				// �����ٶ�
	uint64 UpdateSize;				// ������
	TCHAR  SvrDir[MAX_PATH];		// �����·��
	TCHAR  NodeDir[MAX_PATH];		// �ͻ���·��


	tUpdateGameStatus(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tUpdateGameStatus>	TUpdateGameStatusPtr;


#define MASK_TUPDATEGAMESTATUS_CLIENTIP				(1LL << 1L)
#define MASK_TUPDATEGAMESTATUS_CLIENTNAME			(1LL << 2L)
#define MASK_TUPDATEGAMESTATUS_GID					(1LL << 3L)
#define MASK_TUPDATEGAMESTATUS_GAMENAME				(1LL << 4L)
#define MASK_TUPDATEGAMESTATUS_TID					(1LL << 5L)
#define MASK_TUPDATEGAMESTATUS_TYPE					(1LL << 6L)
#define MASK_TUPDATEGAMESTATUS_UPDATESTATE			(1LL << 7L)
#define MASK_TUPDATEGAMESTATUS_SIZELEFT				(1LL << 8L)
#define MASK_TUPDATEGAMESTATUS_TRANSFERRATE			(1LL << 9L)
#define MASK_TUPDATEGAMESTATUS_UPDATESIZE			(1LL << 10L)
#define MASK_TUPDATEGAMESTATUS_SVRDIR				(1LL << 11L)
#define MASK_TUPDATEGAMESTATUS_NODEDIR				(1LL << 12L)



//ͬ������״̬���
struct tSyncTaskStatus {
	TCHAR  SID[ MAX_GUID_LEN ];		// ͬ�������е�SID
	uint32 GID;						// ��ϷID
	TCHAR  NameID[ MAX_GUID_LEN ];	// ͬ�������е�NameID
	TCHAR  GameName[MAX_NAME_LEN];	// ��Ϸ����
	TCHAR  SvrDir[MAX_PATH];		// ��������Ŀ¼
	TCHAR  NodeDir[MAX_PATH];		// �ڵ��Ŀ¼
	int    UpdateState;				// ͬ��״̬
	ulong  TransferRate;			// �����ٶ�
	uint64 BytesTotal;				// ��������
	uint64 UpdateSize;				// ������
	uint64 BytesTransferred;		// ������
	TCHAR  Error[ MAX_NAME_LEN ];	// ͬ�������еĴ�����Ϣ

	tSyncTaskStatus(){ memset(this,0,sizeof(*this)); }
};
typedef std::tr1::shared_ptr<tSyncTaskStatus>	TSyncTaskStatusPtr;

#define MASK_TSYNCTASKSTATUS_SID					(1LL << 1L)
#define MASK_TSYNCTASKSTATUS_GID					(1LL << 2L)
#define MASK_TSYNCTASKSTATUS_NAMEID					(1LL << 3L)
#define MASK_TSYNCTASKSTATUS_GAMENAME				(1LL << 4L)
#define MASK_TSYNCTASKSTATUS_SVRDIR					(1LL << 5L)
#define MASK_TSYNCTASKSTATUS_NODEDIR				(1LL << 6L)
#define MASK_TSYNCTASKSTATUS_UPDATESTATE			(1LL << 7L)
#define MASK_TSYNCTASKSTATUS_TRANSFERRATE			(1LL << 8L)
#define MASK_TSYNCTASKSTATUS_BYTESTOTAL				(1LL << 9L)
#define MASK_TSYNCTASKSTATUS_UPDATESIZE				(1LL << 10L)
#define MASK_TSYNCTASKSTATUS_BYTESTRANSFERRED		(1LL << 11L)
#define MASK_TSYNCTASKSTATUS_ERROR					(1LL << 12L)

struct tPlugTool
{
	//Attribuild
	ulong	PID;							// ����ID
	TCHAR	CID[ MAX_GUID_LEN ];			// ������� 
	ulong	IdcVer;							// ���İ汾��
	ulong   SvrVer;							// ���ذ汾��
	ulong	Priority;						// ���ȼ�		
	//Base Elenment
	TCHAR	Name[ MAX_NAME_LEN ];			// ��������
	TCHAR	Comment[ MAX_TEXT_LEN ];		// ��ע
	TCHAR	ToolSource[ MAX_TEXT_LEN ];	// ������Դ(�ṩ��)
	ulong	Size;							// ���ߴ�С	
	ulong	IdcClick;						// ���Ŷ�
	ulong	DownloadType;					// ��������	enum{
											//1����ʾServer Element;
											//2����ʾClient Element;
											//4����ʾConfig Element;}
	ulong  DownloadStatus;					// 0:δ���أ�1��������
	ulong	Status;							// 0��δ����;1�������ã�
	//Server Element
	TCHAR	SvrName[ MAX_NAME_LEN ];
	TCHAR	SvrExe[ MAX_PATH ];
	TCHAR	SvrParam[ MAX_PARAM_LEN ];
	TCHAR	SvrPath[ MAX_PATH ];
	ulong	SvrRunType;						// �ѷ���ʽ����������exe��ʽ���� 			
	//Client Element
	TCHAR   CliName[ MAX_NAME_LEN ];
	TCHAR	CliExe[ MAX_PATH ];
	TCHAR	CliParam[ MAX_PARAM_LEN ];
	TCHAR	CliPath[ MAX_PATH ];
	ulong	CliRunType;
	//Config Element
	TCHAR   ConfigName[ MAX_NAME_LEN ];
	TCHAR	ConfigExe[ MAX_PATH ];
	TCHAR	ConfigParam[ MAX_PARAM_LEN ];
	TCHAR	ConfigPath[ MAX_PATH ];
	ulong	ConfigRunType;
//	unsigned char	Icon[1024 * 15/*0*/];


	tPlugTool(){memset(this,0 ,sizeof(*this));}
};
typedef std::tr1::shared_ptr<tPlugTool> TPlugToolPtr;

#define MASK_TPLUGTOOL_PID				(1LL << 1L)
#define MASK_TPLUGTOOL_CID				(1LL << 2L)
#define MASK_TPLUGTOOL_IDCVER			(1LL << 3L)
#define MASK_TPLUGTOOL_SVRVER			(1LL << 4L)
#define MASK_TPLUGTOOL_PRIORITY			(1LL << 5L)
#define MASK_TPLUGTOOL_NAME				(1LL << 6L)
#define MASK_TPLUGTOOL_COMMENT			(1LL << 7L)
#define MASK_TPLUGTOOL_TOOLSOURCE		(1LL << 8L)
#define MASK_TPLUGTOOL_SIZE				(1LL << 9L)
#define MASK_TPLUGTOOL_IDCCLICK			(1LL << 10L)
#define MASK_TPLUGTOOL_DOWNLOADTYPE		(1LL << 11L)
#define MASK_TPLUGTOOL_DOWNLOADSTATUS	(1LL << 12L)
#define MASK_TPLUGTOOL_STATUS			(1LL << 13L)
#define MASK_TPLUGTOOL_SVRNAME			(1LL << 14L)
#define MASK_TPLUGTOOL_SVREXE			(1LL << 15L)
#define MASK_TPLUGTOOL_SVRPARAM			(1LL << 16L)
#define MASK_TPLUGTOOL_SVRPATH			(1LL << 17L)
#define MASK_TPLUGTOOL_SVRRUNTYPE		(1LL << 18L)
#define MASK_TPLUGTOOL_CLINAME			(1LL << 19L)
#define MASK_TPLUGTOOL_CLIEXE			(1LL << 20L)
#define MASK_TPLUGTOOL_CLIPARAM			(1LL << 21L)
#define MASK_TPLUGTOOL_CLIPATH			(1LL << 22L)
#define MASK_TPLUGTOOL_CLIRUNTYPE		(1LL << 23L)
#define MASK_TPLUGTOOL_CONFIGNAME		(1LL << 24L)
#define MASK_TPLUGTOOL_CONFIGEXE		(1LL << 25L)
#define MASK_TPLUGTOOL_CONFIGPARAM		(1LL << 26L)
#define MASK_TPLUGTOOL_CONFIGPATH		(1LL << 27L)
#define MASK_TPLUGTOOL_CONFIGRUNTYPE	(1LL << 28L)


struct tPlugToolStatus
{
	long	PID;							// ����ID
	TCHAR	CID[ MAX_GUID_LEN ];			// ������� 
	uint64	Size;							// �����С
	uint64	ReadSize;						// �Ѷ�ȡ��С
	uint64  TransferRate;					// �����ٶ�
	uint64	AvgTransferRate;				// ƽ�������ٶ�	
	ulong	TotalTime;						// �ܹ���ʱ
	ulong	TimeLeft;						// ʣ��ʱ��
	
	tPlugToolStatus(){memset(this,0 ,sizeof(*this));}
};
typedef std::tr1::shared_ptr<tPlugToolStatus> TPlugToolStatusPtr;

#define MASK_TPLUGTOOLSTATUS_PID				(1LL << 1L)
#define MASK_TPLUGTOOLSTATUS_CID				(1LL << 2L)
#define MASK_TPLUGTOOLSTATUS_SIZE				(1LL << 3L)
#define MASK_TPLUGTOOLSTATUS_TRANSFERRATE		(1LL << 4L)
#define MASK_TPLUGTOOLSTATUS_AVGTRANSFERRATE	(1LL << 5L)
#define MASK_TPLUGTOOLSTATUS_TOTALTIME			(1LL << 6L)
#define MASK_TPLUGTOOLSTATUS_TIMELEFT			(1LL << 7L)


struct tGameExVersion
{
	long	GID;							// ��ϷID
	ulong	GameExVer;						// ��Ϸ��չ�汾
	ulong	CommentVer;						// ��Ϸ���۰汾

	tGameExVersion(){memset(this,0 ,sizeof(*this));}
};
typedef std::tr1::shared_ptr<tGameExVersion> TGameExVersionPtr;

#define MASK_TGAMEEXVERSION_GID						(1LL << 1L)
#define MASK_TGAMEEXVERSION_GAMEEXVER				(1LL << 2L)
#define MASK_TGAMEEXVERSION_COMMENTVER				(1LL << 3L)
////////////////////////////////////////////////////////////////////////
// RECORD OR FIELD OPERATE HELPER MACRO
//
#define CLEAR_CHAR_ARRAY(str) str[0] = 0
#define CLEAR_STRING(str) str[0] = 0
#define STRING_ISEMPTY(str) (str[0] == 0)
#define LAST_CHAR(str) str[_tcslen(str) - 1]

inline bool VALUE_FIELD_COMP(const uint64 &lhs, const uint64 &rhs)
{
	 return lhs != rhs;
}

template<typename T>
bool VALUE_FIELD_COMP(const T &lhs, const T &rhs)
{
	return lhs != rhs;
}


inline bool VALUE_FIELD_COMP(const TCHAR *lhs, const TCHAR *rhs)
{
	return _tcscmp(lhs, rhs) != 0;
}


template<typename T>
void VALUE_FIELD_COPY(T &lhs, const T &rhs)
{
	lhs = rhs;
}

template<typename CharT, size_t N>
void VALUE_FIELD_COPY(CharT (&lhs)[N], const CharT (&rhs)[N])
{
	_tcscpy_s(lhs, _countof(lhs), rhs);
}

#define BUFFER_FIELD_COMP(f1, f2) (memcmp(f1, f2, sizeof(f1)) != 0)
#define BUFFER_FIELD_COPY(des, src) memcpy(des, src, sizeof(des))

#define STRING_FIELD_VALID(field) (field[0] != 0)
#define STRING_FIELD_CUMULATE(des, src) _tcsnicmp(des, src, _countof(des))

#define VALUE_FIELD_VALID(field) (field != 0)
#define VALUE_FIELD_CUMULATE(des, src) des += src

#define SQL_COND_MODE_EQUAL 2
#define SQL_COND_MODE_KEY 1
#define SQL_COND_MODE_NEQUAL 3

#pragma pack(pop)
} //namespace db
} //namespace i8desk



#endif //I8TYPE_H