#ifndef __update_game_inc__
#define __update_game_inc__

#include "public.h"

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

typedef struct tagUpdateStatus
{
	DWORD   cbSize;						//�ṹ���С�����ڰ汾����
	DWORD	Status;						//����״̬
	__int64	m_qNeedsUpdateBytes;		//��Ҫ���µ��ֽ���
	__int64	m_qUpdatedBytes;			//�������µ��ֽ���
	DWORD	m_dwLeftTime;				//����ʣ��ʱ��
	DWORD	m_dwSpeed;					//�����ٶ�k/s
	wchar_t Info[1024];					//�����Ϣ���ļ������ߴ�����Ϣ
}tagUpdateStatus;

IPlug*	__stdcall CreatePlug();
IPlug*	__stdcall CreatePlug2(bool bUpdate);
HANDLE	__stdcall UG_StartUpdate(DWORD gid, LPCWSTR src, LPCWSTR dst, DWORD flag, 
	LPCWSTR sip, LPCWSTR cip = NULL, DWORD speed = 0);
void	__stdcall UG_StopUpdate(HANDLE handle);
bool	__stdcall UG_GetUpdateStatus(HANDLE handle, tagUpdateStatus* pStatus);

//////////////////////////////////////////////////////////////////////////
//������ǰ��10�汾����ĺ���
struct FastCopyStatus
{
	DWORD   Progress;			//update status.
	DWORD   StartType;			//reserved.
	DWORD	TotalUpdateFile;	//reserved.
	DWORD	UpdateFile;			//reserved.
	DWORD   CurProgress;		//reserved.
	DWORD   TotalProgress;		//progress of updating.(500��ʾ50%.)
	DWORD   AverageSpeed;		//average speed. k/s
	DWORD   UsedSecond;			//reserved.
	DWORD   LeftSecond;			//need seconds.
	__int64 TotalFileSize;		//need update total bytes.
	__int64 UpdateFizeSize;		//updated bytes.
	char 	szCurFile[260];		//info tip.
};

enum FC_STATUS
{
	FCS_FINISH					=	0x00000001,
	FCS_ERROR					=	0x00010000,
	FCS_PROGRESS				=	0x00020000,
	FCS_PROGRESS_SCAN			=	0x00020001,
	FCS_PROGRESS_UPDATE			=	0x00020002,
	FCS_PROGRESS_DELMOREFILE	=	0x00020003,
	FCS_NOROOM					=	0x00030000,
	FCS_DELGAME					=   0x00030001,
	FCS_NOIDXFILE				=	0x00030002
};

DWORD __stdcall FastCopy_Start(LPCSTR psrc, LPCSTR pdest, LPCSTR pMainSrvIP, LPCSTR pSecondSrvIp,
	DWORD GID, FC_COPY_MODE mode, bool FiOpenp2p, DWORD dwProtSize);
void __stdcall FastCopy_End(DWORD handle);
void __stdcall FastCopy_Cancel(DWORD handle);
void __stdcall FastCopy_GetSpeedEx(DWORD handle, FastCopyStatus* pStatus);
void __stdcall FastCopy_GetSpeed(DWORD handle, FastCopyStatus* pStatus);
//////////////////////////////////////////////////////////////////////////

#endif