#ifndef __i8desk_define_inc__
#define __i8desk_define_inc__

#pragma once 

#include <Windows.h>
#include <tchar.h>

#include "I8Type.hpp"


//�������в��������,�Լ�ģ��
#define PLUG_RTDATASVR_NAME			TEXT("RTDataSvr")			//���ݿ⻺�����
#define PLUG_RTDATASVR_MODULE		TEXT("RTDataSvr.dll")
#define PLUG_LOGRPT_NAME			TEXT("LogRpt")				//��½�ϱ����
#define PLUG_LOGRPT_MODULE			TEXT("LogRpt.dll")
#define PLUG_GAMEMGR_NAME			TEXT("GameMgr")				//��Ϸ���ع�����
#define PLUG_GAMEMGR_MODULE			TEXT("GameMgr.dll")
#define PLUG_PLUGTOOL_NAME			TEXT("PlugToolPlug")		// ������Ĳ��
#define PLUG_PLUGTOOL_MODULE		TEXT("PlugToolPlug.dll")
#define PLUG_BUSINESS_NAME			TEXT("Business")			// ҵ����
#define PLUG_BUSINESS_MODULE		TEXT("Business.dll")	
#define PLUG_REMOTECONTROL_NAME		TEXT("WinVNC")				// Զ�̿��Ʋ��
#define PLUG_REMOTECONTROL_MODULE	TEXT("WinVNC.dll")		



#define PLUG_UPTSVR_NAME			TEXT("UpdateGameSvr")		//�������·���˲����
#define PLUG_SYNCDISK_NAME			TEXT("SyncDisk")			//ͬ����������
#define PLUG_FORCEUPT_NAME			TEXT("ForceUpdate")			//�������Ͳ����
#define PLUG_GAMEUPDATE_MODULE		TEXT("UpdateGame.dll")		//������ͬ�����

#define PLUG_VDISK_NAME				TEXT("VirtualDisk")			//�����̲��
#define PLUG_VDISK_MODULE			TEXT("VirtualDisk.dll")
#define	PLUG_BOOTRUN_NAME			TEXT("BootRun")				//����������
#define PLUG_BOOTRUN_MODULE			TEXT("BootRun.dll")
#define PLUG_CLIMGR_NAME			TEXT("CliMgr")				//�ͻ���������
#define PLUG_CLIMGR_MODULE			TEXT("CliMgr.dll")
#define PLUG_FRAME_MODULE			TEXT("Frame.dll")			//��ܲ��
#define MODULE_I8DESKSVR			TEXT("I8DeskSvr.exe")		//I8DeskSvr.exe����
#define MODULE_I8VDISKSVR			TEXT("I8VDiskSvr.exe")		//I8VDiskSvr.exe����
#define MODULE_I8DESKCLISVR			TEXT("I8DeskCliSvr.exe")	//I8DeskCliSvr.exe����
#define MODULE_BARONLINE			TEXT("BarOnline.exe")		//BarOnline.exe�˵�
#define MODULE_NODESERVER			TEXT("NodeServer.exe")		//NodeServer.exe�ڵ�������
#define KHSTARTNAME                 TEXT("KHUpdate.exe")        //���Ͱ�ȫ���ĸ����ļ�

//�ٷ���Ϸ��С����Ϸgid.
#define MIN_IDC_GID					10000
#define MAIN_SERVER_SID				TEXT("{BDD530E3-E60F-4739-80AF-6E9D845988A4}")

//�ٷ�Ĭ�ϵķ���.
#define DEFAULT_AREA_GUID			TEXT("{2B35D26B-6E5C-4d18-B108-19F778B6AF18}")
#define DEFAULT_AREA_NAME			TEXT("Ĭ�Ϸ���")

//�ٷ��������Ϸ���
#define CLASS_WL_GUID				TEXT("{E88DD848-DA99-46b0-97D6-23D0658B718A}")	//������Ϸ
#define CLASS_DJ_GUID				TEXT("{30CF0706-E9AE-4804-9D57-B39885B672E4}")	//������Ϸ
#define CLASS_XX_GUID				TEXT("{C185F5B5-FA0C-466e-BDDF-6E7EDA5A3F3E}")	//������Ϸ
#define CLASS_WY_GUID				TEXT("{17F2FFB5-B4DC-42ce-B424-E17CFF1279B5}")  //��ҳ��Ϸ
#define CLASS_DZ_GUID				TEXT("{FD844C21-BD62-4369-B146-DC06A5D4CE1E}")	//��ս��Ϸ
#define CLASS_QP_GUID				TEXT("{E7CDB5F3-D6C7-4607-8B71-3FC087E4B896}")	//������Ϸ
#define CLASS_PL_GUID				TEXT("{C8DDDA32-EFD6-43af-B94B-FBADF3196977}")	//��Ϸ���
#define CLASS_LT_GUID				TEXT("{CF59BC68-973B-461a-97AF-29E183EB3645}")	//���칤��
#define CLASS_CY_GUID				TEXT("{58D87CC9-5BB1-43e0-A919-C7ED3D7CE46A}")	//���ù���
#define CLASS_YY_GUID				TEXT("{E1DDCC22-9AAF-4020-A65B-F022DBFABC47}")	//Ӱ������
#define CLASS_GP_GUID				TEXT("{B59A5F1F-9431-461f-A5BD-C88949E29709}")	//��Ʊ֤ȯ

#define CLASS_TJ_NAME	            TEXT("�Ƽ���Ϸ")
#define CLASS_WL_NAME				TEXT("������Ϸ")
#define CLASS_DJ_NAME				TEXT("������Ϸ")
#define CLASS_XX_NAME				TEXT("������Ϸ")
#define CLASS_WY_NAME				TEXT("��ҳ��Ϸ")
#define CLASS_DZ_NAME				TEXT("��ս��Ϸ")
#define CLASS_QP_NAME				TEXT("������Ϸ")
#define CLASS_PL_NAME				TEXT("��Ϸ���")
#define CLASS_LT_NAME				TEXT("���칤��")
#define CLASS_CY_NAME				TEXT("���ù���")
#define CLASS_YY_NAME				TEXT("Ӱ������")
#define CLASS_GP_NAME				TEXT("��Ʊ֤ȯ")


//�����̼���������˿ڵĻ���
#define VDISK_PORT_BASE				17918			// (17918 + 'Driver' - 'A')


//ˢ�������̵��¼�����
#define VDISK_EVENT_NAME	TEXT("__i8desk_vdisk_refresh_event_")

#define    DEFAULT_SKIN_NAME          TEXT("Ĭ��.png")                                     //Ĭ��Ƥ��
#define    PATH_ROOT               	  TEXT("%root%")			                           //��ʾӦ�ó���װĿ¼
#define    PATH_SYSTEM		          TEXT("%system%")			                           //��ʾϵͳĿ¼
#define    PATH_PROGRAM	              TEXT("%program%")			                           //��ʾC:\program file\\Ŀ¼


//����ϵͳѡ��
//�û���½��֤��ص�ѡ��(ϵͳѡ��ͻ��˲����Ҫд��LOCAL_MACHINE\SOFTWARE\Goyoo\i8desk�µ�ֵ)
#define OPT_U_CPUID					TEXT("cpuid")			//Ӳ��id
#define OPT_U_USERNAME				TEXT("username")		//�û���
#define OPT_U_PASSWORD				TEXT("password")		//����				//��д,������ԭ��
#define OPT_U_OAU1					TEXT("oau1")			// OAU1
#define OPT_U_OAU2					TEXT("oau2")			// OAU2
#define OPT_U_NBNAME				TEXT("nbname")			//��������:��ʾ���������Ƶĵ�һ��
#define OPT_U_NBTITLE				TEXT("nbtitile")		//���ɱ���:��ʾ���������Ƶĵڶ��С�
#define OPT_U_NBSUBTITLE			TEXT("nbsubtitile")		//�����ӱ��⣺��ʾ���������Ƶĵ�����
#define OPT_U_NBTITLEURL			TEXT("nbtitileurl")		//������ַ�������Ϊ��������������ƺ���ʾ���棬���򵯳�ָ������ַ

#define OPT_U_PROVINCE				TEXT("nbprovince")		//��������ʡ
#define OPT_U_CITY					TEXT("nbcity")			//����������
#define OPT_U_PROVINCEID			TEXT("nbprovinceid")	//��������ʡID
#define OPT_U_CITYID				TEXT("nbcityid")		//����������ID

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
#define OPT_M_SHOWGONGGAOTYPE		TEXT("mshowgonggaotype")//�ͻ�����ʾ����ķ�ʽ��0��ͼƬ���棻1���������� 2:��������֣�
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
#define OPT_M_MENUPAGE				TEXT("mmenupage")		//�˵�Ĭ����ҳp1$n(1|0��ʾ����),p2$n(
#define OPT_M_WHICHONESC            TEXT("mwhichonesc")     //������һ����ȫ����
#define OPT_M_USERDATADIR			TEXT("muserdatadir")	//���˴��̵��Զ��屣��Ŀ¼
#define OPT_M_CLASSSHUT             TEXT("ClassShortcuts")  //Ŀ¼��ݷ�ʽ
#define OPT_M_NETBARJPG             TEXT("netbarjpgdir")	//�ͻ�����ʾ�������ͼƬ
#define OPT_M_GGPICDIR				TEXT("mggpicdir")		//�ͻ��˹���ͼƬ��Ϣ·��
#define OPT_M_CPU_TEMPRATURE		TEXT("cputmprature")	// CPU����¶�
#define OPT_M_FIRSTTIME				TEXT("firstTime")		// �״ΰ�װʱ��

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

#define OPT_M_LASTTJTIME			TEXT("LastTJTime")		//�ϴ����ʱ��
#define OPT_M_LASTJKZS				TEXT("LastJKZS")		//�ϴν���ָ��
#define OPT_M_GAMEVERSION			TEXT("GameVersion")		// ������Ϸ��Ȩ��ʾ

#define OPT_M_LOCALPLUG				TEXT("localplug")		//�Ƿ����ñ��ز��(0|1)
#define OPT_M_CREATEDAY				TEXT("nbCreateday")		// ���ɴ���������
#define OPT_M_DISKTYPE				TEXT("disktype")		// �������� 1:���� 2:���� 3:���
#define OPT_M_DISKPRODUCTNAME		TEXT("diskproductname")	// ���̲�Ʒ����
#define OPT_M_FEEPRODUCTNAME		TEXT("feeproductname")	// �շѲ�Ʒ����
#define OPT_M_CULTURALNAME			TEXT("culturalcontrolproductname") // ��ȫ����������
#define OPT_M_BROADBANDTYPE			TEXT("broadbandtype")	// ����״��1:���� 2:ADSL 3:����
#define OPT_M_REALITY				TEXT("reality")			// �Ƿ���ͨ��ʵ�� 1:�� 0:��
#define OPT_D_SELSYNCTASKALL		TEXT("isSelSyncTaskAll")// �Ƿ�Ĭ��ѡ������ͬ������  1:�� 0:��

//����ͨ������
#define PRO_VERSION					0x0303		//��ʾͨѶЭ��汾��packageheader.version.
#define CMD_RET_SUCCESS				1			//����Ӧ��ɹ�
#define CMD_RET_FAIL				0			//����Ӧ��ʧ��

#define I8DESK_INVALID_CMD			0x0000		//�����������
#define CMD_CON_HEART_BEAT			0x0001		//����̨��������
#define CMD_RELOAD_CACHE_FILE		0x0002		//���¼��ػ����ļ�

// �ͻ������ʹ������
#define CMD_GAME_REPCLICK			0x0103		//�ϱ���Ϸ�����,�˵�����һ��
#define CMD_GAME_ICONREFRESH		0x0105		//ͼ�껺��ʧЧ
#define CMD_GAME_CLIENTTOCON		0x0108		//�ͻ��˷������ݸ�����̨
#define CMD_GAME_REQ_ICONS_IDX		0x0121		//������Ϸͼ������
#define CMD_GAME_RSP_ICONS_IDX		0x0122		//������Ϸͼ������
#define CMD_GAME_REQ_ICONS_DATA		0x0123		//������Ϸͼ������
#define CMD_GAME_RSP_ICONS_DATA		0x0124		//������Ϸͼ������
#define CMD_GAME_GETIDXS	        0x0130		//ȡ��Ϸ�������б�
#define CMD_GAME_GETSOME	        0x0131		//ȡָ������Ϸ�б���Ϣ 2010�汾ʹ��
#define CMD_SYSOPT_SYNTIME			0x0302		//�õ�����˵�ͬ��ʱ��
#define CMD_SYSOPT_GETLIST			0x0301		//�õ�ϵͳѡ��
#define CMD_VDISK_GETLIST			0x0201		//�õ��������б�
#define CMD_FAVORITE_GETLIST		0x0401		//�õ��ղؼ��б�
#define CMD_BOOT_GETLIST			0x0501		//�õ����������б�
#define CMD_BOOT_DELLIST			0x0502		//ɾ�����������б�
#define CMD_GET_SERVER_CONFIG		0x0505		//��ȡ�����������
#define CMD_SVRRPT_SERVERINFO		0x0603		//�ϱ���������Ϣ���ɵ����
#define CMD_SVRRPT_SERVERINFO_EX	0x0604		//�ϱ���������Ϣ��չ
#define CMD_CLIUPT_DOWNFILEINFO		0x0907		//�����ļ�ǰ��ȡ���ļ���CRC
#define CMD_CLIUPT_DOWNFILE_START	0x0908		//���������ļ�
#define CMD_DOWNFILE_NEXT			0x0909		//�����ļ���������
#define CMD_GETCIENTVERSION			0x0d04		//���Զ���������
#define CMD_CLIENT_REMOTECONTROLSVR	0x0d06		// �ͻ���Զ�̿�����������
#define CMD_PLUGTOOL_GETIDXS		0x0d07		// ȡ������ߵ������б�
#define CMD_PLUGTOOL_GETSOME		0x0d08		// ȡָ���Ĳ�������б���Ϣ
#define CMD_BUSINISS_GETGAMEEXVER	0x0d09		// ȡBUSINISSS�����Ϸ�汾��Ϣ
#define CMD_REPORT_SVRIP			0x0d10		// �ϱ����ӷ�����IP
#define CMD_CLIENT_GETDELGAME		0x0d11		// ����ȡ��ɾ���ͻ����ļ�
#define CMD_CLIENT_RPTDELGAMESTATUS 0x0d12		// �ϱ��ͻ���ɾ���ļ��Ƿ�ɹ�

// �˵����ͻ��˷����ٵ�����������
#define CMD_BUSINESS_INFOEX			0x0d05		// ȡ��չ��Ϣ

//����̨���������ʹ������
#define CMD_GAME_CONTOCLIENT		0x0107		//���ת������̨�����ݸ��ͻ���
#define CMD_CON_GAME_ICON			0x0109		//ͼ�����
#define CMD_VALIDATE				0x010C		//֪ͨ��������ȥ������֤
#define CMD_CON_GETINFO_FROM_GAMEUPDATESVR  0x010E	//�鿴��Ϸ��Ϣ
#define CMD_CON_NOTIFY_REFRESH_PL	0x010F		//����̨֪ͨ�����������ȥˢ��pl
#define CMD_CON_GETSVR_STATUS		0x0111		// ����̨��ȡ������������Ϣ
#define CMD_CON_SETFILE_CLASSICON	0x0112		// ����̨��д���ͼ������
#define CMD_CON_GET_VDISKCLIENT		0x0113		// ����̨�õ������̿ͻ�������
#define CMD_CON_OFFLINE_NOTIFY		0x010D		//����̨����֪ͨ 
#define CMD_GAME_CONEXESQL	        0x0125		//����ִ̨��SQL
#define CMD_CON_SAVE_HARDWARE		0x0126		// ����̨����ͻ���Ӳ����Ϣ
#define CMD_CON_SMART_CLEAN			0x0127		// ����̨���������������
#define CMD_CON_MONITOR_DISK_SIZE	0x0128		// ����̨����Ӳ�̿ռ��Ƿ��㹻
#define CMD_CON_SYNCTASK_OPERATE	0x0129		// ����̨�������ͬ������

#define CMD_CON_GET_BARSKINS		0x0503		//����˵�Ƥ���б�
#define CMD_NOTIFY_SERVER_MEDICAL	0x0c03		//֪ͨ�����������
#define CMD_NOTIFY_SAVE_DATA		0x0c04		// ֪ͨ����ѻ����������д�����ݿ�
#define CMD_CON_PLUGTOOL_ICON		0x0c05		// ����̨������Ļ�ȡ���ͼ��
#define CMD_CON_PLUGTOOL_OPERATE	0x0c06		// ����̨������Ĳ����������
#define CMD_CON_MONITOR_STATUS		0x0c07		// ����̨�����ҳͳ����Ϣ����
#define CMD_CON_STATISTIC_STATUS	0x0c08		// ����̨ͳ����Ϸ��ͻ�����Ϣ����
#define CMD_CON_MONITOR_DELETEFILE	0x0c09		// ����̨�����ҳ����ļ�����
#define CMD_CON_GETALL_GAMEICONS	0x0c10		// ����̨��ȡ������Ϸͼ��
#define CMD_CON_GETALL_CLASSICONS	0x0c11		// ����̨��ȡ�������ͼ��
#define CMD_CON_REPORT_USERINFOMODIFY 0x0c12	// ����̨�����û���Ϣ���޸�

//����̨���������ʹ������
#define CMD_TASK_OPERATION			0x010A		//�������
#define CMD_TASK_STATE_CHANGED		0x010B		//��������״̬
#define CMD_CON_NOTIFY_DELETEFILE	0x015D		//ɾ����Ϸ�ļ� 
#define CMD_PLUG_TASK_COMPLATE		0x015E		// ����������
#define CMD_ADD_NEW_SERVER			0x015F		// �����ӷ�����
#define CMD_REFRESHPL				0x0160		// ˢ��PL

// ������ͻ���Ӳ���仯�����̨����UDP֪ͨ
#define CMD_CLIENT_HARDWARECHANGE	0xd15E		// �ͻ���Ӳ�������ı�֪ͨ

//�ϱ�������������ʹ������
//��־ʱ��(dword)+��־����(dword)+��־����(string)+�����(string)
#define CMD_PLUGIN_LOG_REPORT		0x0110		//�������������־
#define CMD_CLIRPT_CLIENTINFO		0x0601		//service����ʱ�ϱ��ͻ�����ϸ��Ϣ 
#define CMD_CLIRPT_HARDWARE			0x0602		//�ϱ��ͻ���Ӳ����Ϣ 
#define CMD_CHECKUSER_NOTIFY		0x0605		// ��֤���֪ͨ

//������ĵ������ʹ������
#define CMD_PLUGTOOL_OPERATE		0x0d01		// ������Ĳ�������

//�ͻ����������̵�����ʹ������
#define CMD_GET_VDISK_CONFIG		0x0506		//��ȡ�������������������
#define CMD_VDSVR_REPSTATUS			0x0a02		//�����̱���״̬
#define CMD_VDSVR_GETUPDATE_FILEINFO	0x0a03	// ��ȡ�������̽ڵ����������Ҫ�����ļ�
#define CMD_VDSVR_GETUPDATE_FILELIST	0x0a04	// ��ȡ�������̽ڵ����������Ҫ�����ļ��б�
#define CMD_VDSVR_VDISKCLIENT			0x0a05	//�����̱���ͻ���������Ϣ

//�����ϰ汾������
#define CMD_GAME_GETLIST			0x0101		//�õ���Ϸ�б� 2009�汾ʹ��
#define CMD_GAME_GETICONLIST		0x0102		//�õ���Ϸͼ��ѹ����(10��ʹ��)
#define CMD_GAME_CONGETSTAUTS		0x0106	    //����̨ȡ״̬��Ϣ
#define CMD_REP_BARSKINS			0x0504		//���ز˵�Ƥ���б�

#define CMD_USER_REGISTER			0x0701		//�û�ע��
#define CMD_USER_LOGIN				0x0702		//�û���½
#define CMD_USER_MODPWD				0x0703		//�޸�����

#define CMD_USER_UPLOAD				0x0704		//�����ϴ�	�ϴ������ػ�ֿ�
#define CMD_USER_DOWNLOAD			0x0705		//��������
#define CMD_USER_DELETE				0x0706		//ɾ���ļ�
#define CMD_USER_STATE_CHANGE		0x0707		// �ͻ���������֪ͨ
#define CMD_USER_DOWNLOAD_START		0x0708		//���������ļ�

#define CMD_CLIUPT_GETLIST			0x0901		//�õ��ܰ汾��.
#define CMD_CLIUPT_DOWNFILE			0x0902		//�����ļ�����������һ�������ļ�
#define CMD_CLIUPT_UPLOAD			0x0903		//�ϴ�
#define CMD_CLIUPT_GET_FILELIST		0x0904		//�õ��̷���Ŀ¼�����ļ��б�
#define CMD_CLIUPT_DELETE			0x0905
#define CMD_CLIUPT_UPDATE			0x0906		//֪ͨ�ͻ��˸��µİ汾��.
#define CMD_CLIUPT_GET_ALL_CLIENTS	0x0910		// ��ȡ���еĿͻ���

#define CMD_VDSVR_GETLIST			0x0a01		//�����̷������õ��������б�

#define CMD_SYNCTOOL_TASKSTATE		0x0b01		//֪ͨͬ��������������״̬
#define CMD_SYNCTOOL_ADD_GAME		0x0b02		//ͬ������֪ͨ���������Ϸ

#define CMD_UPT_ICONLIST_VERSION	0x0c01		//֪ͨ�������ͼ���б�İ汾��
#define CMD_UPT_CLIENT_INDEX		0x0c02		//֪ͨ������¿ͻ������������



//End of command define
///////////////////////////////////////////////////////////////////////////////////////

//ÿ������ܴ��͵���Ϸ��Ŀ
static const DWORD MAX_COUNT_GAME_PER_PACKEG = 10;

//ÿ������ܴ��͵�ͼ����Ŀ
static const DWORD MAX_COUNT_ICON_PER_PACKEG = 10;


#ifndef BitN
#define BitN(x) (1<<x) 
#endif

//�ɿ���̨�ͷ����ʹ�õĳ���������̨��SQL������޸��˱������ñ���Ӧ��λ
#define FLAG_RUNTYPE_BIT			     BitN(0)
#define FLAG_VDAREA_BIT					 BitN(1)
#define FLAG_AREA_BIT					 BitN(2)
#define FLAG_CLASS_BIT					 BitN(3)
#define FLAG_CLIENT_BIT					 BitN(4)
#define FLAG_CMPBOOTTASK_BIT			 BitN(5)
#define FLAG_FAVORITE_BIT				 BitN(6)
#define FLAG_GAME_BIT					 BitN(7)
#define FLAG_GAMELOG_BIT				 BitN(8)
#define FLAG_SYSOPT_BIT					 BitN(9)
#define FLAG_USER_BIT					 BitN(10)
#define FLAG_VDISK_BIT					 BitN(11)
#define FLAG_SYNCTASK_BIT				 BitN(12)
#define FLAG_SERVER_BIT					 BitN(13)
#define FLAG_BOOTTASKAREA_BIT			 BitN(14)
#define FLAG_ICON_BIT					 BitN(15)
#define FLAG_MODULEUSAGE_BIT			 BitN(16)
#define FLAG_CLIENTSTATUS_BIT			 BitN(17)
#define FLAG_VDISKCLIENT_BIT			 BitN(18)
#define FLAG_VDISKSTATUS_BIT			 BitN(19)
#define FLAG_SERVERSTATUS_BIT			 BitN(20)
#define FLAG_DISKSTATUS_BIT				 BitN(21)
#define FLAG_TASKSTATUS_BIT				 BitN(22)
#define FLAG_UPDATEGAMESTATUS_BIT		 BitN(23)
#define FLAG_PLUGTOOL_BIT				 BitN(24)
#define FLAG_PLUGTOOLSTATUS_BIT			 BitN(25)
#define FLAG_PUSHGAMESTATUS_BIT			 BitN(26)
#define FLAG_SYNCGAMESTATUS_BIT			 BitN(27)
#define FLAG_SYNCGAME_BIT				 BitN(28)
#define FLAG_SYNCTASKSTATUS_BIT			 BitN(29)
#define FLAG_PUSHGAMESTATIC_BIT			 BitN(30)


#define SQL_OP_NONE						 0x00
#define SQL_OP_SELECT					 0x01
#define SQL_OP_INSERT					 0x02
#define SQL_OP_UPDATE					 0x04
#define SQL_OP_DELETE					 0x08
#define SQL_OP_ENSURE					 0x10
#define SQL_OP_COMULATE					 0x20

#endif