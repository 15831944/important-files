#ifndef _DEFINE_H_
#define _DEFINE_H_


#include "string"
#include "NetLayer.h"
using namespace i8desk;
using namespace std;

#define PORT  17791

#define NET_CMD_POSTBLOCKFILE   0x0100
#define NET_CMD_REGISTCLIENT	0x0101
#define NET_CMD_LOGSERVER		0x0102	
#define NET_CMD_GETFILE			0x0103
#define NET_CMD_LOG				0x0104
#define NET_CMD_GETUDISKINFO	0x0105
#define NET_CMD_GETCOMMENTRES	0x0106

#define MET_CMD_GETBLCOKFILE	0x0107
#define NET_CMD_DELETEFILE		0x0108
#define NET_CMD_GETCONFIGINFO	0x0109
#define NET_CMD_RESETPASSWORD	0x010A

#define NET_CMD_SAVEGAMERECORD	0x0110
#define NET_CMD_GETSAVEGAMELST	0x0111

#define NET_CMD_DELETEGAMERECORD 0x0112

#define NET_CMD_GETGAMERECORD	0x0113

#define NET_CMD_FAIL			0x0600
#define NET_CMD_SUCESS			0x0601




#define BLOCK			64*1024
#define USERNAMELEN		64
#define FILENAMELEN		64

struct FileHeader
{
	
	char filename[FILENAMELEN];//�ļ���
	char FilePath[USERNAMELEN];//��ŵ��ļ�·��
	DWORD Num;//�ֿ����
	DWORD DataSize;//���ݴ�С
	DWORD64 FileSize;//�ļ���С
	bool bEnd;//�Ƿ����ļ������һ�죬�ǵĻ���Ҫ�ر��ļ���
	bool IsPersion;
};

struct FileInfo
{
	std::string filename;
	DWORD filesize;
	DWORD dwTime;
};

typedef struct tagSrvConfigInfo
{
	string			sztitle;		//��ʾ����
	string			szSavePath;		//���˴浵·��
	DWORD			dwAllocSize;	//���˷���ռ��С
	bool			bShowPersion;	//�Ƿ���ʾ���˴洢��
	string			szCustomInfo;	//�û��Զ���˵����
	bool			bAutoStart;		//�Ƿ���ϵͳ����
	bool			bRegist;		//�Ƿ����ע��
	string			szStopRigTitle;	//ֹͣע����ʾ��Ϣ
	DWORD			dwDay;			// ɾ�����첻��½�û�
	DWORD			dwSpace;			//���ÿռ�С�ںö�ֹͣע��
	string			szCommResPath;	//������Դ·��
	bool			bShowCommres;  //�Ƿ���ʾ������Դ��
	tagSrvConfigInfo():sztitle("��������"),dwAllocSize(100),bShowPersion(true)
					,szCustomInfo("�û��Զ���"),bAutoStart(true),bRegist(true),
					szStopRigTitle("���̿ռ䲻��"),dwDay(50),dwSpace(500),bShowCommres(true)
	{
		
	}
}SrvConfigInfo;

#endif