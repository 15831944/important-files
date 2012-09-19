#ifndef __UPDATE_GAME_HPP
#define __UPDATE_GAME_HPP


#define UPDATE_FLAG_FORCE_UPDATE		0x01		//ǿ�Ƹ���
#define UPDATE_FLAG_QUICK_COMPARE		0x02		//���ٸ���	//��ǿ�Ƹ���ֻ�ܶ�ѡһ��
#define UPDATE_FLAG_DELETE_MOREFILE		0x04		//ִ��ɾ�������ļ�
#define UPDATE_FLAG_DELETE_GAME			0x08		//�ռ䲻��ʱ��ִ��ɾ������ʵ͵���Ϸ��

#define UPDATE_STATUS_FINISH			0x01		//���³ɹ����
#define UPDATE_STAUTS_COMPARE			0x02		//�Ա��ļ�
#define UPDATE_STATUS_UPDATE			0x04		//�����ļ���
#define UPDATE_STATUS_DELETE_MOREFILE	0x08		//ɾ�������ļ�
#define UPDATE_STATUS_DELETE_GAME		0x010		//ɾ����Ϸ
#define UPDATE_STATUS_ERROR				0xffffffff	//���³���

enum
{
	// ֪ͨ����ǿ���޸�ĳ����Ϸ
	CMD_UPT_SM_NOFIGY3UPFORCE	= 666,

	// ȡ�����߿ͻ����б�
	CMD_UPT_SM_CLIENTONLINE		= 0x01
};


// ���ͨ��
enum
{
	CMD_UPT_SM_GETUPDATGAME	= 0x01,		// ȡ�����ڽ����������µ���Ϸ״̬
	CMD_UPT_SM_GETSYNCGAME	= 0x02,		// ȡ������ͬ������Ϸ��״̬
	CMD_UPT_SM_IPHAVEGAME	= 0x03,		// ȡ��ĳ���ͻ�������Щ��Ϸ(param1:ip).
	CMD_UPT_SM_GAMEINIP		= 0x04,		// ȡ��ĳ����Ϸ����Щ��������С�(param1:gid).
	CMD_UPT_SM_NOTIFYSYNC	= 0x05,		// ֪ͨͬ����Ϸ:nofity second server sync game(param2=gid, param2=1(forceupdate))
	CMD_UPT_SM_NOTIFYDELETE	= 0x06,		// ֪ͨɾ����Ϸ:notify second server delete game.(param1=gid).
	CMD_UPT_SM_OPERATE		= 0x07,		// ���ͬ��������в���
};	

enum SyncOperateState
{
	StartTask,					// ��ʼ����ͬ��
	StopTask,					// ֹͣ����ͬ��
	AddGame,					// ���ͬ����Ϸ
	DeleteGame,					// ɾ��ͬ����Ϸ
	SuspendTask,				// ��ͣͬ����Ϸ
	ResumeTask,					// �ָ�ͬ����Ϸ
	PutTopGame,					// �ö�ͬ����Ϸ
	PutBottonGame,				// �õ�ͬ����Ϸ
	NotifySync,					// ֪ͨͬ��
};

enum UpdateErrorCode //���´������
{
    UPT_ERR_NONE,        //����
    UPT_ERR_DIRNOTOK,    //Ŀ¼������ȷ
    UPT_ERR_CREATEDIR,   //����Ŀ¼ʧ��
    UPT_ERR_INNERERR,    //�ڲ�����
    UPT_ERR_LOADDEVICE,  //���������豸����
    UPT_ERR_GETGAMEINFO, //ȡ��Ϸ��Ϣʧ��
    UPT_ERR_DWNIDX,      //��������ʧ��
    UPT_ERR_DISKNOROOM,  //���̿ռ䲻��
    UPT_ERR_PARSEIDX,    //��������ʧ��
    UPT_ERR_CONNFAIL,    //���ӷ�����ʧ��
    UPT_ERR_DWNFAIL,     //�������ݿ�ʧ��
    UPT_ERR_CRCERR,      //���ݿ�crc��ͬ
    UPT_ERR_FILEOPEN,    //���ļ�ʧ��
    UPT_ERR_FILEWRITE,   //д�ļ�ʧ��
    UPT_ERR_FILEPOPDATA, //��������ʧ��
    UPT_ERR_FILECLOSE    //�ر��ļ�ʧ��
};

typedef struct tagUpdateStatus
{
	DWORD           cbSize;					//�ṹ���С�����ڰ汾����
	DWORD           dwStatus;				//����״̬
	__int64         qNeedsUpdateBytes;		//��Ҫ���µ��ֽ���
	__int64         qUpdatedBytes;			//�������µ��ֽ���
	DWORD           dwLeftTime;				//����ʣ��ʱ��
	DWORD           dwSpeed;				//�����ٶ�k/s
    UpdateErrorCode enErrCode;              //�������
	wchar_t         awInfo[1024];			//�����Ϣ���ļ������ߴ�����Ϣ
}tagUpdateStatus;

typedef void (__stdcall *OnConnect_pfn)(void* pParam, DWORD dwIP);

i8desk::ISvrPlug*	__stdcall CreateSvrPlug(DWORD Reserved);
i8desk::ICliPlug*	__stdcall CreateClientPlug(DWORD Reserved);


/*
0��ʾ���ͣ�1��ʾͬ����2��ʾ��������.
*/

enum 
{
	Push = 0,
	Sync,
	Update
};
HANDLE	__stdcall UG_StartUpdate(DWORD gid, LPCWSTR tid, LPCWSTR src, LPCWSTR dst, DWORD flag, 
								 LPCWSTR sip, LPCWSTR cip = NULL, DWORD speed = 0, DWORD type = 0);
void	__stdcall UG_StopUpdate(HANDLE handle);
void	__stdcall UG_PauseUpdate(HANDLE handle);
void	__stdcall UG_ResumeUpdate(HANDLE handle);
bool	__stdcall UG_GetUpdateStatus(HANDLE handle, tagUpdateStatus* pStatus);
bool    __stdcall UG_SetConnectCallBack(HANDLE handle, OnConnect_pfn pfnCallBack, void* pCallBackParam);

#endif