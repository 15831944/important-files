#ifndef __i8desk_define_inc__
#define __i8desk_define_inc__

#define MIN_IDC_GID  10000

//�������в��������,�Լ�ģ����
#define LOGRPT_PLUG_NAME			TEXT("LogRpt")			//��½�ϱ������
#define LOGRPT_MODULE_NAME			TEXT("LogRpt.dll")		
#define GAMEMGR_PLUG_NAME			TEXT("GameMgr")			//�������Ϸ,�ͻ��˹�����
#define GAMEMGR_MODULE_NAME			TEXT("GameMgr.dll")		
#define GAMEUPDATE_PLUG_NAME		TEXT("UpdateGame")		//��Ϸ���������²��
#define GAMEUPDATE_MODULE_NAME		TEXT("UpdateGameSvr.dll")

#define VDISK_PLUG_NAME				TEXT("VirtualDisk")		//�����̲����
#define VDISK_MODULE_NAME			TEXT("VirtualDisk.dll")	
#define SYNC_PLUG_NAME				TEXT("SyncPlug")		//ͬ�������
#define SYNC_MODULE_NAME			TEXT("SyncDisk.dll")
#define BOOTRUN_PLUG_NAME			TEXT("BootRun")			//����������
#define BOOTRUN_MODULE_NAME			TEXT("BootRun.dll")
#define CLIMGR_PLUG_NAME			TEXT("CliMgr")			//�ͻ��˵Ŀͻ���������
#define CLIMGR_MODULE_NAME			TEXT("CliMgr.dll")
#define GAMEMENU					TEXT("BarOnline.exe")	//��Ϸ�˵�

#define RTDATASVR_PLUG_NAME			TEXT("RTDataSvr")		//���ݿ⻺�����
#define RTDATASVR_MODULE_NAME		TEXT("RTDataSvr.dll")

//�ͻ�������	//for packageheader.resv[0]
#define OBJECT_UNKOWN				0
#define OBJECT_CLIENTSVI			1
#define OBJECT_CONSOLE				2
#define OBJECT_VDISKSVI				3
#define OBJECT_BARONLINE			4
#define OBJECT_SYNCTOOL				5


//����ϵͳѡ��
//�û���½��֤��ص�ѡ��(ϵͳѡ��ͻ��˲����Ҫд��LOCAL_MACHINE\SOFTWARE\Goyoo\i8desk�µ�ֵ)
#define OPT_U_CPUID					TEXT("cpuid")			//Ӳ��id
#define OPT_U_USERNAME				TEXT("username")		//�û���
#define OPT_U_PASSWORD				TEXT("password")		//����				//��д,������ԭ��
#define OPT_U_NBNAME				TEXT("nbname")			//��������:��ʾ���������Ƶĵ�һ��
#define OPT_U_NBTITLE				TEXT("nbtitile")		//���ɱ���:��ʾ���������Ƶĵڶ��С�
#define OPT_U_NBSUBTITLE			TEXT("nbsubtitile")		//�����ӱ��⣺��ʾ���������Ƶĵ�����
#define OPT_U_NBTITLEURL			TEXT("nbtitileurl")		//������ַ�������Ϊ��������������ƺ���ʾ���棬���򵯳�ָ������ַ

#define OPT_U_PROVINCE				TEXT("nbprovince")		//��������ʡ
#define OPT_U_CITY					TEXT("nbcity")			//����������
#define OPT_U_NBADDRESS				TEXT("nbaddress")		//���ɵ�ַ����ʵ�����ɵ�ַ
#define OPT_U_NBPHONE				TEXT("nbphone")			//���ɵ绰��������
#define OPT_U_NBMOBILE				TEXT("nbmobile")		//�����ƶ��绰���ֻ���
#define OPT_U_REALITYURL			TEXT("nbrealityurl")	//����ʵ���޸���ַ

#define OPT_U_SMAC					TEXT("smac")			//�����MAC��ַ
#define OPT_U_SVER					TEXT("sver")			//����˰汾��
#define OPT_U_CMAC					TEXT("cmac")			//�ͻ���MAC��ַ
#define OPT_U_CVER					TEXT("cver")			//�ͻ��˰汾��
#define OPT_U_NID					TEXT("nid")				//����id
#define OPT_U_SID					TEXT("sid")				//������id
#define OPT_U_RID					TEXT("rid")				//����id
#define OPT_U_AID					TEXT("aid")				//�̳�aid.
#define OPT_U_REGDATE				TEXT("regdate")			//�û�ע������		//��д.��ʽtime32_t
#define OPT_U_DATEEND				TEXT("dateend")			//��������			//��д
#define OPT_U_USERTYPE				TEXT("usertype")		//�û�����
#define OPT_U_OEMID					TEXT("bindoemid")		//����id
#define OPT_U_OEMNAME				TEXT("oemname")			//��������
#define OPT_U_TASKINFO				TEXT("taskinfo")		//������Ϣ			//��д
#define OPT_U_PLUGINFO				TEXT("pluginfo")		//�����Ϣ			//��д
#define OPT_U_MESSAGE				TEXT("message")			//���Ĺ�����Ϣ		//��д
#define OPT_U_CTLPWD				TEXT("ctrlpassword")	//����̨����		//��д,������ԭ��
#define OPT_U_ERRINFO				TEXT("ErrInfo")			//���ڿ���̨��ʾ��½�Ĵ�����Ϣ��//��д.
#define OPT_U_REGDATE				TEXT("regdate")			//�û�ע������

#define OPT_U_CONSHOWDIALOG			TEXT("conpopdialog")	//�����·�������̨����Ϣ:�Ƿ񵯳��Ի���(1|0)
#define OPT_U_CONSHOWCANCEL			TEXT("conshowcancel")	//�����·�������̨����Ϣ:�Ƿ���ʾȡ����ť
#define OPT_U_CONMESSAGE			TEXT("conmessage")		//�����·�������̨����Ϣ:��Ϣ����
#define OPT_U_CONOKURL				TEXT("conokurl")		//�����·�������̨����Ϣ:��ȷ���󵯳�����ַ




#define OPT_S_BACKUPDIR				TEXT("sbackupdir")		//����˱���Ŀ¼.
#define OPT_S_BACKUPNUM				TEXT("sbackupnum")		//���������ļ��ĸ���.
#define OPT_S_BACKUPDATE			TEXT("sbackupdate")		//��ʼ���ݵ�ʱ��.
#define OPT_S_FLUSH_DB_INTERVAL     TEXT("sflushdbinterval")//ˢ�»��浽���ݿ�ļ��ʱ��
#define OPT_S_FLUSH_DB_OPNUMBER     TEXT("sflushdbopnumber")//ˢ�»��浽���ݿ���ۻ���������

//���������ѡ��
#define OPT_D_INITDIR				TEXT("dinitdir")		//������Ϸ���ص�Ĭ��Ŀ¼
#define OPT_D_TEMPDIR				TEXT("dtempdir")		//������Ϸ������ʱĿ¼
#define OPT_D_LINETYPE				TEXT("dlinetype")		//������·���� (0��ʾ����,1��ʾ��ͨ)
#define OPT_D_JOINTYPE				TEXT("djointype")		//���������� (0��ʾADSL,1��ʾ����)
#define OPT_D_TASKNUM				TEXT("dtasknum")		//ͬʱ���ص���������� (n)
#define OPT_D_CONNNUM				TEXT("dconnnum")		//��������� (n)
#define OPT_D_ADSLSPEED				TEXT("dADSLpeed")		//ADSL�������ص��ٶ�����(n)(k/s)
#define OPT_D_SPEED					TEXT("dpeed")			//�������ص��ٶ�����(n)(k/s)
#define OPT_D_TIMEUPT				TEXT("dtimeupt")		//���ð�ʱ�θ���(0,1)
#define OPT_D_TIMEUPTVALUE			TEXT("dtimeuptvalue")	//ʱ�θ��µ�ֵ.HH:MM,HH:MM|HH:MM,HH:MM
#define OPT_D_AREADEFRUNTYPE		TEXT("dareadefruntype")	//����Ĭ�����з�ʽ.aid(guid),value(0,1,vid)|aid(guid),value(0,1,vid)

//�ͻ���ѡ����
#define OPT_M_WINMODE				TEXT("mwinmode")		//�˵�����ģʽ		(0|1)
#define OPT_M_BROWSEDIR				TEXT("mbrowsedir")		//�����Ҽ����Ŀ¼	(0|1)
#define OPT_M_RUNSHELL				TEXT("mrunshell")		//�����ͻ���shell����(0|1)
#define OPT_M_RUNMENU				TEXT("mrunmenu")		//�����ͻ��˲˵�����(0|1)
#define OPT_M_CLISKIN				TEXT("mclientskin")		//�ͻ���Ƥ��skinname|skinfilename
#define OPT_M_CLIPWD				TEXT("mclipwd")			//�ͻ��˸߼���������(�����CRC32�ַ���)
#define OPT_M_MENUACT				TEXT("mmenuact")		//������Ϸ��˵�ִ�еĶ���(��:��ʾ�޶�������ʾ��С��������ʾ�ر�)
#define OPT_M_HOTCOUNT				TEXT("mhotcount")		//��ʾ������Ϸ�ĸ���n
#define OPT_M_ONLYONE				TEXT("monlyone")		//��������ȡһ������0|1
#define OPT_M_AUTOUPT				TEXT("mautoupdate")		//�˵��Ƿ��Զ�����
#define OPT_M_VDDIR					TEXT("mvddir")			//��������ʱ·��
#define OPT_M_IEURL					TEXT("mieurl")			//�ͻ��ˣɣ���ҳ
#define OPT_M_SHOWGONGGAO			TEXT("mshowgonggao")	//�ͻ����Ƿ���ʾ����
#define OPT_M_GGMSG					TEXT("mggmsg")			//�ͻ��˹�����Ϣ
#define OPT_M_GGFONT				TEXT("mggfont")			//�˵��������� (������|��С|��ɫ|��־(bit0:���壬bit1:б��,bit2:�»���,bit3:ɾ����))
#define OPT_M_TSSPEED				TEXT("mtsspeed")		//�����ٶ�
#define OPT_M_SYNTIME				TEXT("msyntime")		//ͬ��ʱ��ѡ��
#define OPT_M_SAFECENTER			TEXT("msafecenter")		//�Ƿ����ð�ȫ����(0|1)
#define OPT_M_WHICHONE_SC			TEXT("mwhichonesc")		//�����ĸ���ȫ����(1��i8,2:����)
#define OPT_M_IEHISTORY				TEXT("miehistory")		//�Ƿ�����IE��ʷ��¼(0|1)
#define OPT_M_USEUDISK				TEXT("museudisk")		//�Ƿ�����U��(0|1)
#define OPT_M_MUSIC					TEXT("mmusic")			//ǿ�Ƶ�������վ (����|URL)
#define OPT_M_VIDEO					TEXT("mvideo")			//ǿ�Ƶĵ�Ӱ��վ (����|URL)
#define OPT_M_GGONOFF				TEXT("madonoff")		//���ƹ�����ʾ���(p1$n(1,��ʾǿ����ʾ��0��ʾǿ�Ʋ���ʾ��-1���������õ�����ʾ.),p2$n(����)).
#define OPT_M_RPOPONOFF				TEXT("mrpoponoff")		//�˵����½ǵ���������(p1$n(1,��ʾ�򿪣�0��ʾ�ر�),p2$n(n��ʾ��ʾ�Ļ���)).
#define OPT_M_BOTLAYER				TEXT("mbotlayer")		//�˵��ײ��������p1$n(1,��ʾ��,0��ʾ�ر�),p2$n(����)
#define OPT_M_MEMUPAGE				TEXT("mmenupage")		//�˵�Ĭ����ҳp1$n(1|0��ʾ����),p2$n(



/*
1001  ��Ϸ����-������Ϸ
1002  ��Ϸ����-������Ϸ
1003  ��Ϸ����-������Ϸ
1004  ��Ϸ����-������Ϸ
1005  ��Ϸ����-��ս��Ϸ
1006  ��Ϸ����-������Ϸ
2001  ����/���-���칤��
3001  ��ҳ���-��ַ����
*/
#define OPT_M_DOTCARD				TEXT("mdotcard")		//���Ŀ��Ƶĵ㿨�̳ǵ�ַ��
#define OPT_M_URLNAV				TEXT("murlnav")			//���Ŀ��Ƶ���ַ�����б�
#define OPT_M_VDMUS					TEXT("mvdmus")			//���Ŀ��Ƶ�Ӱ�������б�
#define OPT_M_PERSONURL				TEXT("mpersonurl")		//���Ŀ��Ƶĸ����û�������ַ
#define OPT_M_GAMEROOMURL			TEXT("mgameroomurl")	//��Ϸ����������ַ�б�


#define OPT_M_USERALLOC				TEXT("museralloc")		//���������û�(0|1)
#define OPT_M_USERUPFILE			TEXT("muserupfile")		//�����û��ϴ�����(0|1)
#define OPT_M_DEFAULTSIZE			TEXT("musersize")		//Ĭ���û��ռ��С(n=50M)��λΪM
#define OPT_M_USERDATADIR			TEXT("muserdatadir")	//���˴��̵��Զ��屣��Ŀ¼

#define OPT_M_GAMEDRV				TEXT("mgamedrv")		//Ĭ�ϱ�����Ϸ��ŵ��̷�.('E')
#define OPT_M_P2P					TEXT("mp2p")			//���ظ����Ƿ�����p2p.(1|0)
#define OPT_M_INPROTTYPE			TEXT("minprottype")		//���ظ��´�͸��ԭ�ķ�ʽ.�����0��ʾ������͸.�����Ǵ�͸���ٶ�

#define OPT_M_SAFECENTER			TEXT("msafecenter")		//�Ƿ����ð�ȫ����(0|1)
#define OPT_M_WHICHONE_SC			TEXT("mwhichonesc")		//�����ĸ���ȫ����(1��i8,2:����)
#define OPT_M_IEHISTORY				TEXT("miehistory")		//�Ƿ�����IE��ʷ��¼(0|1)

#define OPT_M_EXCLUDEDIR			TEXT("mexcludedir")		//��������ʱҪ�ų���Ŀ¼(��|�ָ�)
#define OPT_M_USEUDISK				TEXT("museudisk")		//�Ƿ�����U��(0|1)

#define OPT_M_CMDMASK				TEXT("gamemgrcmdmask")	//��Ϸ��������������ѡ��

#define OPT_M_PENETATEFILE			TEXT("PenetateFile")	//������͸��Ŀ¼��(��|�ָ�)

#define OPT_M_LASTTJTIME			TEXT("LastTJTime")	//�ϴ����ʱ��
#define OPT_M_LASTJKZS				TEXT("LastJKZS")	//�ϴν���ָ��



//����ͨ������
#define PRO_VERSION					0x0200					//��ʾͨѶЭ��汾��packageheader.version.
#define CMD_RET_SUCCESS				1						//����Ӧ��ɹ�
#define CMD_RET_FAIL				0						//����Ӧ��ʧ��

#define I8DESK_INVALID_CMD       0x0000		//�����������
#define CMD_CON_HEART_BEAT       0x0001		//����̨��������
#define CMD_RELOAD_CACHE_FILE    0x0002		//���¼��ػ����ļ�

#define CMD_GAME_GETLIST         0x0101		//�õ���Ϸ�б� 2009�汾ʹ��
#define CMD_GAME_GETICONLIST	 0x0102		//�õ���Ϸͼ��ѹ����
#define CMD_GAME_REPCLICK	     0x0103		//�ϱ���Ϸ�����,�˵�����һ��
#define CMD_GAME_CLIEXESQL	     0x0104		//�ͻ���ִ��SQL
#define CMD_GAME_ICONREFRESH     0x0105		//ͼ�껺��ʧЧ
#define CMD_GAME_CONGETSTAUTS    0x0106	    //����̨ȡ״̬��Ϣ
#define CMD_GAME_CONTOCLIENT	 0x0107		//���ת������̨�����ݸ��ͻ���
#define CMD_GAME_CLIENTTOCON     0x0108		//�ͻ��˷������ݸ�����̨
#define CMD_GAME_ICON			 0x0109		//ͼ�����
#define CMD_TASK_OPERATION		 0x010A		//�������
#define CMD_TASK_STATE_CHANGED   0x010B		//��������״̬ 
#define CMD_VALIDATE             0x010C		//֪ͨ��������ȥ������֤

#define CMD_CON_OFFLINE_NOTIFY   0x010D		//����̨����֪ͨ 
#define CMD_CON_GETINFO_FROM_GAMEUPDATESVR  0x010E	//�鿴��Ϸ��Ϣ
#define CMD_CON_NOTIFY_REFRESH_PL	0x010F	//����̨֪ͨ�����������ȥˢ��pl

//��־ʱ��(dword)+��־����(dword)+��־����(string)+�����(string)
#define CMD_PLUGIN_LOG_REPORT		0x0110	//�������������־

#define CMD_GAME_REQ_ICONS_IDX		0x0121	//������Ϸͼ������
#define CMD_GAME_RSP_ICONS_IDX		0x0122	//������Ϸͼ������
#define CMD_GAME_REQ_ICONS_DATA		0x0123	//������Ϸͼ������
#define CMD_GAME_RSP_ICONS_DATA		0x0124	//������Ϸͼ������
#define CMD_GAME_CONEXESQL	        0x0125	//����ִ̨��SQL

#define CMD_GAME_GETIDXS	        0x0130	//ȡ��Ϸ�������б�
#define CMD_GAME_GETSOME	        0x0131	//ȡָ������Ϸ�б���Ϣ 2010�汾ʹ��


#define CMD_VDISK_GETLIST		 0x0201		//�õ��������б�
#define CMD_SYSOPT_GETLIST	     0x0301		//�õ�ϵͳѡ��
#define CMD_SYSOPT_SYNTIME	     0x0302     //�õ�����˵�ͬ��ʱ��
#define CMD_FAVORITE_GETLIST	 0x0401		//�õ��ղؼ��б�
#define CMD_BOOT_GETLIST		 0x0501		//�õ����������б�
#define CMD_BOOT_DELLIST         0x0502     //ɾ�����������б�
#define CMD_GET_BARSKINS         0x0503     //����˵�Ƥ���б�
#define CMD_REP_BARSKINS		 0x0504     //���ز˵�Ƥ���б�

#define CMD_GET_SERVER_CONFIG	 0x0505     //��ȡ�����������
#define CMD_GET_VDISK_CONFIG	 0x0506     //��ȡ�������������������

#define CMD_CLIRPT_CLIENTINFO	 0x0601		//service����ʱ�ϱ��ͻ�����ϸ��Ϣ 
#define CMD_CLIRPT_HARDWARE      0x0602		//�ϱ��ͻ���Ӳ����Ϣ 
#define CMD_SVRRPT_SERVERINFO	 0x0603		//�ϱ���������Ϣ���ɵ����
#define CMD_SVRRPT_SERVERINFO_EX 0x0604		//�ϱ���������Ϣ��չ

#define CMD_USER_REGISTER		 0x0701		//�û�ע��
#define CMD_USER_LOGIN		     0x0702		//�û���½
#define CMD_USER_MODPWD		     0x0703		//�޸�����

#define CMD_USER_UPLOAD		     0x0704		//�����ϴ�	�ϴ������ػ�ֿ�
#define CMD_USER_DOWNLOAD	     0x0705		//��������
#define CMD_USER_DELETE		     0x0706		//ɾ���ļ�
#define CMD_USER_STATE_CHANGE    0x0707
#define CMD_USER_DOWNLOAD_START  0x0708		//���������ļ�


#define CMD_CLIUPT_GETLIST       0x0901		//�õ��ܰ汾��.
#define CMD_CLIUPT_DOWNFILE	     0x0902		//�����ļ�����������һ�������ļ�
#define CMD_CLIUPT_UPLOAD        0x0903		//�ϴ�
#define CMD_CLIUPT_GET_FILELIST	 0x0904		//�õ��̷���Ŀ¼�����ļ��б�

#define CMD_CLIUPT_DELETE        0x0905
#define CMD_CLIUPT_UPDATE        0x0906		//֪ͨ�ͻ��˸��µİ汾��.
#define CMD_CLIUPT_DOWNFILEINFO  0x0907		//�����ļ�ǰ��ȡ���ļ���CRC
#define CMD_CLIUPT_DOWNFILE_START 0x0908	//���������ļ�
#define CMD_DOWNFILE_NEXT		 0x0909		//�����ļ���������

#define CMD_CLIUPT_GET_ALL_CLIENTS 0x0910	// ��ȡ���еĿͻ���

#define CMD_VDSVR_GETLIST	     0x0a01		//�����̷������õ��������б�
#define CMD_VDSVR_REPSTATUS      0x0a02		//�����̱���״̬
#define CMD_VDSVR_GETUPDATE_FILEINFO 0x0a03		// ��ȡ�������̽ڵ����������Ҫ�����ļ�
#define CMD_VDSVR_GETUPDATE_FILELIST 0x0a04		// ��ȡ�������̽ڵ����������Ҫ�����ļ��б�

#define CMD_SYNCTOOL_TASKSTATE   0x0b01		//֪ͨͬ��������������״̬
#define CMD_SYNCTOOL_ADD_GAME    0x0b02		//ͬ������֪ͨ���������Ϸ

#define CMD_UPT_ICONLIST_VERSION 0x0c01		//֪ͨ�������ͼ���б�İ汾��
#define CMD_UPT_CLIENT_INDEX     0x0c02		//֪ͨ������¿ͻ������������

#define CMD_NOTIFY_SERVER_MEDICAL 0x0c03	//֪ͨ�����������
#define CMD_NOTIFY_SAVE_DATA	 0x0c04		// ֪ͨ����ѻ����������д�����ݿ�
//End of command define
///////////////////////////////////////////////////////////////////////////////////////



//ÿ������ܴ��͵���Ϸ��Ŀ
static const DWORD MAX_COUNT_GAME_PER_PACKEG = 10;

//ÿ������ܴ��͵�ͼ����Ŀ
static const DWORD MAX_COUNT_ICON_PER_PACKEG = 10;




//��������
enum TaskType
{
	tUserTask,
	tForceTask,
	tSmartForceTask		/*���Ի�ǿ��*/,
	tTimeTask			/*ʱ������*/
};

enum TaskState 
{
	tsChecking,			//���ڶԱ�
	tsQueue,			//�ȴ�����
	tsDownloading,		//��������
	tsSuspend,			//��ͣ����
	tsComplete,			//�������
	tsSelfQueue,		//�����Ŷ�
	tsWaitSeed,			//�ȴ�����
	tsHashmap,			//У������
	tsCopyfile,			//�����ļ�
	tsDeleteOldFile,	//�����ļ�
};

// �������
enum TaskOperation
{
	toAdd,		// ��������
	toDel,		// ɾ������
	toGetState,	// ��ȡ����״̬
	toSync,		// ֪ͨͬ������ͬ����Ϸ
	toSuspend,	// ��������
	toRestart,	// �ָ�����
	toAdjust,	// �����ȴ��������ȼ�
	toDelGame,	// ֪ͨͬ������ɾ����ϷĿ¼
};

enum VDStartType 
{
	vdBoot			=	0,			/*����*/
	vdStartMenu,					/*���˵�*/
	vdStartGame,					/*����Ϸ*/
};

//ͼ�����
enum IconOperation 
{
	ioAdd,
	ioDel,
	ioGetIconFromZip,
	ioGetIconFromFile
};

//�ļ�·��������
enum FPType 
{
	fpabsPath,						/*����·��*/
	fprelPath,						/*���·��*/
};

enum FType {fFile,fDir};


//�ϴ���������
enum UpLoadPacketType 
{
	uptFirst,
	uptMiddle,
	uptLast,
	upOnlyOne
};

enum TaskNotify 
{
	tnDownloadComplete,
	tnDownloadComFailed,
	tnDownloadCheckFailed,
	tnStopComplete
}; 

enum emRunType
{
	ERT_NONE = 0,	//δ����
	ERT_LOCAL,		//���ظ���
	ERT_VDISK,		//������
	ERT_DIRECT,		//ֱ�����У�������ֱ�Ӵӿͻ��������У�
};

enum emSyncType
{
	stUnknown = 0,	//δ����
	stMirror,		//���������
	stVDisk,		//��ͬ����������Դ
	stUpdate,		//��ͬ������������Դ
	stCustom,		//�Զ���ͬ��
//	stAllRes		//ͬ��������Դ
};

enum emBalanceType
{
	btUnknown = 0,
	btDynamic,
	btAreaPriority
};

// ����ģʽ
enum FC_COPY_MODE
{
	FC_COPY_COMPARE = 0,
	FC_COPY_QUICK	= 1,  // �Ա��ļ�
	FC_COPY_FORE	= 2,  // ���Ա� ȫ������
	FC_COPY_VERSION = 3   // �Ա������汾��
};


enum BootRunTask 
{  
	brDeskTop	= 0,	/*������*/
	brShortcut,			/*�����ݷ�ʽ*/
	brIEHomePage,		/*IE��ҳ����*/
	brCltFile,			/*ִ�пͻ�����һ�Զ����EXE*/
	brSvrFile,			/*���������·ŵ������ļ�*/
	brDelFile,			/*ɾ���ļ����ļ��л�ĳһ��Ϸ*/
	brDelGames,			/*ɾ������ʵ͵���Ϸ*/
	brSalfCenterXMl,	/*����ȫ����xml*/
	brUpdateGame		/*������Ϸ*/
};


//_packageheader+crc(DWORD)+cmd(DWORD) + info.
typedef enum E_CliCtrlCmd
{
	Ctrl_InstallProt	= 0,	//��װ��ԭ��info:�����и�dword��ʾ�Ƿ񱣻����з���.Ϊ����ʾ������Ϊ����ʾ������
	Ctrl_RemoveProt		= 1,	//ɾ����ԭ��info:��
	Ctrl_ProtArea		= 2,	//������ԭ����, info:������String,��һ����ʾ�����ķ����б��ڶ�����ʾȡ�������ķ����б�
	Ctrl_ShutDown		= 3,	//������������info:��1��dword��ʾ��Ϊ1��ʾ������Ϊ0��ʾ�ػ�
	Ctrl_ExecFile		= 4,	//ִ��ָ���ļ���info:������һ��String��ʾ��Ҫ���е��ļ�.
	Ctrl_ViewSysInfo	= 5,	//��ȡϵͳ��Ϣ��info:��
	Ctrl_ViewProcInfo	= 6,	//��ȡ������Ϣ��info:��
	Ctrl_ViewSviInfo	= 7,	//��ȡ������Ϣ��info:��
	Ctrl_KillProcSvr	= 8,	//kill���̻��߷���info:һ��DWORD(0��ʾ�Ƿ���1��ʾ�ǽ���),һ��String��ʾ�Ľ��̻��߷�����
	Ctrl_Remote         = 9,	//�ͻ���Զ�̿����������رգ�info:�ø�dword��ʾ��Ϊ����ʾ������Ϊ����ʾ�ر� 
	Ctrl_Chkdsk         = 10,	//�ͻ����޸�����
	Ctrl_PushGameAtOnce = 11,	//ʵʱ������Ϸ 

	Ctrl_EnableSC       = 100,  //���ð�ȫ����
	Ctrl_EnableIEProt   = 101,  //����IE����
	Ctrl_EnableDogProt  = 102,  //���÷�������
}E_CliCtrlCmd;



#define VDISK_I8DESK	0		//��ʾI8Desk������
#define VDISK_OTHER		1		//������������

#ifndef BitN
#define BitN(x) (1<<x) 
#endif

//�ɿ���̨�ͷ����ʹ�õĳ���������̨��SQL������޸��˱������ñ���Ӧ��λ
#define FLAG_GAMEAREA_BIT                BitN(0)
#define FLAG_VDAREA_BIT					 BitN(1)
#define FLAG_AREA_BIT					 BitN(2)
#define FLAG_CLASS_BIT					 BitN(3)
#define FLAG_CLIENT_BIT					 BitN(4)
#define FLAG_CMPSTARTTASK_BIT			 BitN(5)
#define FLAG_FAVORITE_BIT				 BitN(6)
#define FLAG_GAME_BIT					 BitN(7)
#define FLAG_GAMELOG_BIT				 BitN(8)
#define FLAG_SYSOPT_BIT					 BitN(9)
#define FLAG_USER_BIT					 BitN(10)
#define FLAG_VDISK_BIT					 BitN(11)
#define FLAG_SYNCTASK_BIT				 BitN(12)
#define FLAG_SYNCGAME_BIT				 BitN(14)
#define FLAG_ICON_BIT					 BitN(15)
#define FLAG_MODULEUSAGE_BIT			 BitN(16)
#define FLAG_CLIENTSTATUS_BIT			 BitN(17)

#define SQL_OP_NONE						 0x00
#define SQL_OP_SELECT					 0x01
#define SQL_OP_INSERT					 0x02
#define SQL_OP_UPDATE					 0x04
#define SQL_OP_DELETE					 0x08
#define SQL_OP_ENSURE					 0x10
#define SQL_OP_COMULATE					 0x20




#define DEFAULT_AREA_GUID	TEXT("{2B35D26B-6E5C-4d18-B108-19F778B6AF18}")
#define DEFAULT_AREA_NAME	TEXT("Ĭ�Ϸ���")

#define CLASS_WL_GUID	TEXT("{E88DD848-DA99-46b0-97D6-23D0658B718A}")	//������Ϸ
#define CLASS_DJ_GUID	TEXT("{30CF0706-E9AE-4804-9D57-B39885B672E4}")	//������Ϸ
#define CLASS_XX_GUID	TEXT("{C185F5B5-FA0C-466e-BDDF-6E7EDA5A3F3E}")	//������Ϸ
#define CLASS_WY_GUID	TEXT("{17F2FFB5-B4DC-42ce-B424-E17CFF1279B5}")  //��ҳ��Ϸ	 //10�汾�������
#define CLASS_DZ_GUID	TEXT("{FD844C21-BD62-4369-B146-DC06A5D4CE1E}")	//��ս��Ϸ
#define CLASS_QP_GUID	TEXT("{E7CDB5F3-D6C7-4607-8B71-3FC087E4B896}")	//������Ϸ
#define CLASS_PL_GUID	TEXT("{C8DDDA32-EFD6-43af-B94B-FBADF3196977}")	//��Ϸ���
#define CLASS_SP_GUID	TEXT("{D5443BC8-7839-4ce3-A56A-1018CE19800D}")	//��Ϸ��Ƶ	 //10�汾ȥ����������
#define CLASS_LT_GUID	TEXT("{CF59BC68-973B-461a-97AF-29E183EB3645}")	//���칤��
#define CLASS_CY_GUID	TEXT("{58D87CC9-5BB1-43e0-A919-C7ED3D7CE46A}")	//���ù���
#define CLASS_YY_GUID	TEXT("{E1DDCC22-9AAF-4020-A65B-F022DBFABC47}")	//Ӱ������
#define CLASS_GP_GUID	TEXT("{B59A5F1F-9431-461f-A5BD-C88949E29709}")	//��Ʊ֤ȯ

#define CLASS_WL_NAME	TEXT("������Ϸ")
#define CLASS_DJ_NAME	TEXT("������Ϸ")
#define CLASS_XX_NAME	TEXT("������Ϸ")
#define CLASS_WY_NAME	TEXT("��ҳ��Ϸ")	//10�汾�������
#define CLASS_DZ_NAME	TEXT("��ս��Ϸ")
#define CLASS_QP_NAME	TEXT("������Ϸ")
#define CLASS_PL_NAME	TEXT("��Ϸ���")
#define CLASS_SP_NAME	TEXT("��Ϸ��Ƶ")	//10�汾ȥ����������
#define CLASS_LT_NAME	TEXT("���칤��")
#define CLASS_CY_NAME	TEXT("���ù���")
#define CLASS_YY_NAME	TEXT("Ӱ������")
#define CLASS_GP_NAME	TEXT("��Ʊ֤ȯ")



#define VDISK_EVENT_NAME	TEXT("__i8desk_vdisk_refresh_event_")

#define MAIN_SERVER_SID TEXT("{BDD530E3-E60F-4739-80AF-6E9D845988A4}")
#define VDISK_SERVER_MODE_GROUP TEXT("Ⱥ��ģʽ")
#define VDISK_SERVER_MODE_09    TEXT("����09��ģʽ")



static const TCHAR *I8DESK_SPECIAL_DIR = _T("i8desk");
static const size_t I8DESK_SPECIAL_DIR_LEN = ::lstrlen(I8DESK_SPECIAL_DIR);

#define VDISK_PORT_BASE 17918


//#include "utility.h"
#include "i8type.h"

#endif