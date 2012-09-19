#pragma once

enum FC_STATUS
{
		FCS_FINISH				=	0x00000001,
		FCS_ERROR				=	0x00010000,
		FCS_PROGRESS				=	0x00020000,
		FCS_PROGRESS_SCAN			=	0x00020001,
		FCS_PROGRESS_UPDATE			=	0x00020002,
		FCS_PROGRESS_DELMOREFILE	=	0x00020003,
		FCS_NOROOM				=	0x00030000,
		FCS_DELGAME				=   0x00030001
};

enum FC_COPY_MODE
{
	FC_COPY_COMPARE		= 0,
	FC_COPY_QUICK		= 1,
	FC_COPY_FORE		= 2,
	FC_COPY_VERSION		= 3
};
enum FC_FLAG
{
	FC_FLAG_DELETEMOREFILE = 0x01
};
enum FC_STARTTYPE
{
		FC_START_VDISK		= 0x00,			//�������.
		FC_START_LDISK		= 0x01			//���ش���
};

struct FastCopyStatus
{
	DWORD   Progress;					//���µĽ׶Ρ�
	DWORD   StartType;					//���ɹ����º󣬲˵��Ǵ����������������Ǵӱ���������
	
	DWORD	TotalUpdateFile;			//�ܹ���Ҫ�����ļ�����
	DWORD	UpdateFile;					//�������µ��ļ�����
	
	DWORD   CurProgress;				//��ǰ�ļ��Ľ���.
	DWORD   TotalProgress;				//������ȡ�
	
	DWORD   AverageSpeed;				//ƽ���ٶ�
	DWORD   UsedSecond;					//���¼������˶����롣
	
	DWORD   LeftSecond;					//����Ҫ�����롣

	__int64 TotalFileSize;				//�ܹ���Ҫ���µ��ֽ�����//���ռ䲻��ʱ�����ֵ�Ǹ��߲˵���Ҫɾ�����ֽ�������Ӧ���Ǵ��ڵ�������Ҫ���µ��ֽ�����
	__int64 UpdateFizeSize;				//�������ֽ�����
	
	char 	szCurFile[260];		//��ǰ���ڲ������ļ�.����д������Ǵ�����Ϣ.
};



////////////////�ӿڶ���/////////////////////////////
//DWORD WINAPI FastCopy_Start(LPCSTR psrc,			//��Ϸ�ڷ������ϵ�Ŀ¼
//							LPCSTR pdest,			//��Ϸ���µ���Ŀ��Ŀ¼
//							LPCSTR pMainSrvIP,		//��������ip
//							LPCSTR pSecondSrvIp,	//�ӷ�����ip
//							DWORD GID,				//��Ϸgid
//							FC_COPY_MODE mode,		//����ģʽ
//							bool FiOpenp2p,			//�Ƿ�p2p
//							DWORD dwProtSize );		//dwProtSize ��ʾ��ʣ����ռ䡣
//
//void WINAPI FastCopy_End(DWORD handle);
//
//void WINAPI FastCopy_GetSpeedEx(DWORD handle, FastCopyStatus* status);
//
//void WINAPI FastCopy_Cancel(DWORD handle);

//��̬���ض���
typedef DWORD (WINAPI *FASTCOPY_START)(LPCSTR psrc,			//��Ϸ�ڷ������ϵ�Ŀ¼
							LPCSTR pdest,			//��Ϸ���µ���Ŀ��Ŀ¼
							LPCSTR pMainSrvIP,		//��������ip
							LPCSTR pSecondSrvIp,	//�ӷ�����ip
							DWORD GID,				//��Ϸgid
							FC_COPY_MODE mode,		//����ģʽ
							bool FiOpenp2p,			//�Ƿ�p2p
							DWORD dwProtSize );		//dwProtSize ��ʾ��ʣ����ռ䡣

typedef void (WINAPI *FASTCOPY_END)(DWORD handle);

typedef void (WINAPI *FASTCOPY_GETSPEEDEX)(DWORD handle, FastCopyStatus* status);