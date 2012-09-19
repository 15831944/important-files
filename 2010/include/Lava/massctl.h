#ifdef MASSCTL_EXPORTS
#define MASSCTL_API __declspec(dllexport)
#else
#define MASSCTL_API __declspec(dllimport)
#endif

#pragma once

#include <shlobj.h>

#ifdef  __cplusplus
extern "C" {
#endif

MASSCTL_API int __stdcall msc_init(const wchar_t *ownername,const wchar_t *password);
/*
msc_init �������ȵ���һ�ν��г�ʼ����
	ownername: �����߱�ʶ
	password: �Զ��Ŀ���
	������ֵ�����ס���Ժ�ÿ�γ�ʼ������Ӧ���ֲ��䣻������ǰ���������Ͳ��ٿ��Ի�ȡ
*/

typedef int (CALLBACK *MSCPROGRESS)(UINT step,UINT code,void *presult,void *puser);
/*
�ص����أ�	1 ����
			0 build / rebuid ���ٵ��ûص����������ϲ�Ӧ�ý��ȣ�������ֹͣ����ɽ����Ȼ��ͨ���ص�������ϲ�Ӧ��
			-1 build / rebuid ��ֹͣ�������û�ȡ������
*/

struct _PROGRESS_RESULT {
	unsigned long long ull0;
	unsigned long long ull1;
	const wchar_t *wmsg;
};

#define MSCPROGRESS_START		0
// ��ʼ: MSCPROGRESS(MSCPROGRESS_START,0,0,puser)

#define MSCPROGRESS_COMPOSE		1
// ɨ��Ŀ¼/�ļ� MSCPROGRESS(MSCPROGRESS_COMPOSE,code,_PROGRESS_RESULT *pr,puser), ֻ�� build ʱ����
// code: �ֱ�Ϊ
	#define MSCPROGRESS_STEP_SCAN		0	// ɨ��·��
	#define MSCPROGRESS_STEP_COMPARE	1	// �ļ������Ƚ�
// pr: MSCPROGRESS_STEP_SCAN ʱ, ull0/ull1 �ֱ�Ϊ ��ɨ���ļ�����/��ɨ���ܳ���, wmsg Ϊ����ɨ���·��
//     MSCPROGRESS_STEP_COMPARE ʱ, ull0/ull1 ����, wmsg Ϊ���ڼ�����ļ�

#define MSCPROGRESS_HASHMAP		2
// ����/�Ƚ� hsahmap ��: MSCPROGRESS(MSCPROGRESS_HASHMAP,code,0,puser)
// code Ϊ���Ȱٷֱ�ֵ

#define MSCPROGRESS_COPYFILE	5
// �����ļ�: MSCPROGRESS(MSCPROGRESS_COPYFILE,0,wchar_t *filename,puser)
//

#define MSCPROGRESS_COMMIT		0xFF

#define MSCPROGRESS_FINISHED	0x100
// �ɹ�: MSCPROGRESS(MSCPROGRESS_FINISHED,0,_PROGRESS_RESULT *pr,puser)
// pr: �� build ����ʱ, ull0/ull1 �ֱ�Ϊ �ļ�����/�ܳ���
//	   �� rebuild ����ʱ, ull0/ull1 �ֱ�Ϊ �����س���/�ܳ���

#define MSCPROGRESS_ERROR			0x80000000
// ����ֹͣ: MSCPROGRESS(MSCPROGRESS_ERROR,errno,wchar_t *errmsg,puser)
// errno: ������
// errmsg: ������Ϣ

#define BUILD_MODE_INPLACE	0
#define BUILD_MODE_IMPORT	1
#define BUILD_MODE_PARTIAL	2
MASSCTL_API int __stdcall msc_build(const wchar_t *taskname,const wchar_t *src,UINT mode,MSCPROGRESS progressfn,void *pvoid);
/*
msc_build �����µĻ����Ŀ¼�ļ�
	taskname: ����(��Ϸ)id��Ϊ�˸��£������Ժ��ܸı䣬��ͬ�������ֵһ��������ͬ
	src: �����ļ���(����)Ŀ¼���� mode Ϊ BUILD_MODE_INPLACE��������������Ϸ���ڴ�Ŀ¼����
		mode Ϊ BUILD_MODE_IMPORT ʱ�������Ӵ�Ŀ¼���뵽����Ŀ¼�У�����������
	mode: ������ BUILD_MODE_INPLACE �� BUILD_MODE_IMPORT���ֱ��ʾ��ԭ�ظ��»��Ǵ�����
		Ŀ¼������¡����ǵ������ʱ������λ�� BUILD_MODE_PARTIAL ��������Դ�Ƿ�������Ϸ
*/

MASSCTL_API int __stdcall msc_getseed(const wchar_t *taskname,__out BSTR *seed);
/*
msc_getseed: ��ȡĿǰ�汾������
	taskname: ��Ϸid
	seed: �������ݣ����óɹ��󷵻�
*/
MASSCTL_API int __stdcall msc_getseed2(const wchar_t *seedid,__out BSTR *seed);

MASSCTL_API int __stdcall msc_getseedex(const wchar_t *taskname,__out wchar_t *version,__out BSTR *seed,int &itype);

MASSCTL_API int __stdcall msc_createseedid(const wchar_t *taskname,__out GUID &sid,__inout BSTR *ptracklist);
/*
msc_createseedid: ��ȡĿǰ�汾������id
	taskname: ��Ϸid
	sid: ����id�����óɹ��󷵻�
	ptracklist: in/out. ���� ��������ش���NULL.
						��� trackerlist, shall use SysFreeString to free.
*/


// ���Ϻ���Ϊ�����˵���

#define REBUILD_NO_TOPDIR	1	// ����������������Ŀ¼
#define REBUILD_NO_QUICKCHK	2	// ǿ�ƿ�Ƚ�
#define REBUILD_IN_TEMPDIR	4	// ���ص���ʱĿ¼����ʱ des Ϊ multi-string����һ��ΪĿ��Ŀ¼���ڶ���Ϊ��ʱĿ¼���м���0��������˫���β��
MASSCTL_API int __stdcall msc_rebuild(__inout BSTR seed,const wchar_t *des,UINT mode,__out wchar_t *taskname,MSCPROGRESS progressfn,void *pvoid);
/*
msc_rebuild: ����Ŀ¼�ļ�
	seed: Ҫ���ص�Ŀ¼�ļ�������
	des: ����Ŀ��Ŀ¼
	mode: REBUILD_NO_TOPDIR/REBUILD_NO_QUICKCHK/REBUILD_IN_TEMPDIR
	taskname: 
*/

MASSCTL_API int __stdcall msc_rebuild2(const wchar_t *taskname,const GUID& sid,LPCSTR ptracklist,const wchar_t *des,UINT mode,MSCPROGRESS progressfn,void *pvoid);
/*
msc_rebuild2: ����Ŀ¼�ļ�
	taskname: 
	sid: Ҫ���ص�Ŀ¼�ļ�������id
	ptracklist: 
	des: ����Ŀ��Ŀ¼(same as msc_rebuild)
	mode: same as msc_rebuild
����ֵ: <0 ����
		>0 ��������
		=0 ����Ŀ¼�ļ�
*/

MASSCTL_API int __stdcall msc_addfile(const wchar_t *taskname,LPCSTR ptracklist,PVOID ptorrent,const wchar_t *szdes,const wchar_t *szsrc);

MASSCTL_API int __stdcall msc_import(const wchar_t *szseedfile,const wchar_t *des,UINT mode,wchar_t *taskname,MSCPROGRESS progressfn,void *pvoid);

MASSCTL_API unsigned __int64 __stdcall msc_getownerid(void);
/*
msc_getownerid: ��ȡ�û�id��ͨ���û�id�����������Ե���dna�����ȡ�����״����
*/

MASSCTL_API int __stdcall msc_commit(const wchar_t *taskname);
/*
msc_commit: ������ɺ󣬱�����ô˺������з��
	taskname: ��Ϸid
*/

MASSCTL_API int __stdcall msc_commitex(const wchar_t *taskname,const wchar_t *des,const wchar_t *src,MSCPROGRESS progressfn,void *pvoid);
/*
msc_commitex: ���
	taskname: ��Ϸid
	des����ϷĿ¼
	src�������ļ���ʱĿ¼
*/

MASSCTL_API int __stdcall msc_verify(const wchar_t *taskname,MSCPROGRESS progressfn,void *pvoid);

MASSCTL_API int __stdcall msc_reset(const wchar_t *taskname,const wchar_t *des=NULL);


// ���Ϻ���Ϊ���ض˵���

#define MSC_JOB_STATE_QUEUED		0
#define MSC_JOB_STATE_DOWNLOADING	1
#define MSC_JOB_STATE_SUSPENDED		2
#define MSC_JOB_STATE_COMPLETE		3

#define MSC_JOB_STATE_ERROR			0x80

struct MSC_DOWNLOAD_PROGRESS
{
    unsigned __int64 BytesTotal;
    unsigned __int64 BytesTransferred;
    unsigned int TransferRate;
    unsigned int TimeLeft;
    unsigned int TimeElapsed;
    unsigned char Progress;
    unsigned char State;
    unsigned short Connections;
};

MASSCTL_API int __stdcall msc_delete(const wchar_t *taskname);
MASSCTL_API int __stdcall msc_deleteex(const wchar_t *taskname,int flag);
MASSCTL_API int __stdcall msc_stop(const wchar_t *taskname);
MASSCTL_API int __stdcall msc_stopex(const wchar_t *taskname,int flag);
/*
	msc_stopex
		taskname:	
		flag:	1 ֹͣ����
				2 ֹͣ�ϴ�
				3 ȫ��ֹͣ
*/
MASSCTL_API int __stdcall msc_restart(const wchar_t *taskname);
MASSCTL_API int __stdcall msc_gettasklist(__out BSTR *tasklist,__out UINT *cnt);
MASSCTL_API int __stdcall msc_gettaskinfo(BSTR seed,__out wchar_t *taskname,__out wchar_t *version,__out wchar_t *homedir,__out char *trackerlist);
MASSCTL_API int __stdcall msc_getprogress(const wchar_t *taskname,__out MSC_DOWNLOAD_PROGRESS *progress);
/*
����ֵ: <0 ����
		>0 ��������
		=0 ����Ŀ¼�ļ�
	progress: ���ؽ��ȼ�״��
*/
MASSCTL_API int __stdcall msc_getmaxtransferrate(__out UINT *downdloadrate,__out UINT *uploadrate);
MASSCTL_API int __stdcall msc_setmaxtransferrate(UINT downdloadrate,UINT uploadrate);

MASSCTL_API int __stdcall msc_GetTransferRate (__out unsigned int *pRecvRate,__out unsigned int *pSendRate );
MASSCTL_API int __stdcall msc_GetBytesTransferred (__out unsigned __int64 *pBytesRecvd,__out unsigned __int64 *pBytesSent );

#ifdef  __cplusplus
}
#endif
