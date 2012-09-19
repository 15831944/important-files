#ifndef __public_inc__
#define __public_inc__

#include "../../../include/frame.h"
#include "../../../include/Extend STL/UnicodeStl.h"
#include "../../../include/MultiThread/Lock.hpp"

#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>

#pragma comment(lib, "ws2_32.lib")
using namespace i8desk;

#define PLUG_VERSION			0x0200
#define PORT_TCP_UPDATE			5969
#define PORT_UDP_UPDATE			5969
#define PORT_UDP_UI				5970
#define UPDATE_EVENT_NAME		TEXT("_force_stop_update_")

//////////////////////////////////////////////////////////////////////////
//�������������������Ľ�������

	//ȡ��Ϸ��Ϣ:gid + dir(game root dir(include last \\))| 0 + ver + filesize(low dword)
	#define CMD_UPT_GETGMAEINFO		0x0101

	//�����ļ���:filesize(i64) + fileoffset(i64) + blksize + filename(not include root).
	//����ʱ�����ļ����ݵ����ݡ�����᷵��
	#define CMD_UPT_RECVBLOCK		0x0102

	//�ϱ����½���:ip + gid + speed + progress + needupdatebytes(i64) + leftbytes(i64) | 0.
	#define CMD_UPT_RPTPROGRESS		0x0103

	//��������ϱ�:ip + gid + version(0��ʾ�쳣���) + dir.| 0
	#define CMD_UPT_RPTFINISH		0x0104

	//���������ϱ�:gid | 0
	#define CMD_UPT_INDEXERR		0x0105

	// ��ȡ����̨IP
	#define CMD_GET_CONSOLE_IP		0x0106

	// �ϱ�ͬ���������
	#define CMD_UPT_SYNCTASK_RPTPROGRESS 0x0107

	// �ϱ�ͬ����Ϸ����
	#define CMD_UPT_SYNCGAME_ERROR		0x0108

	// ����״̬ 
	#define CMD_SYNC_GETSTATUS 0x0109

	// ȡ�ķ������б�
	#define CMD_SYNC_GETALLTASK	0x300

	//������Ϸ�汾��.   gid + ver|0
	#define CMD_SYNC_SETGMAEVER		0x0201

// ͬ�����ݽṹ
struct SyncGameInfo
{
	long gid_;
	int svrVer_;
	int maxSpeed_;
	int forceRepair_;
	long svrIP_;
	long cliIP_;
	TCHAR gameName_[MAX_NAME_LEN];
	TCHAR syncTaskName_[MAX_NAME_LEN];
	TCHAR svrPath_[MAX_PATH];
	TCHAR nodePath_[MAX_PATH];
	TCHAR sid_[MAX_GUID_LEN];
	SyncGameInfo()
	{
		memset(this, 0, sizeof(*this));
	}
};
typedef std::tr1::shared_ptr<SyncGameInfo> SyncGameInfoPtr;
typedef std::map<std::pair<long, stdex::tString>, SyncGameInfoPtr> SyncGamesInfo;


//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////


//Producer - Consumer - Module.
template<class _Ty>
struct _func_
{
	void operator()(_Ty& obj)
	{
	}
};

template<typename object, typename Func = _func_<object>, size_t poolsize = 20>
class PCMomule
{
	typedef async::thread::AutoCriticalSection	MetuxLock;
	typedef async::thread::AutoLock<MetuxLock>	AutoLock;

private:
	HANDLE	m_hExit;
	MetuxLock	m_lock;
	HANDLE	m_hPop;
	HANDLE	m_hPush;
	std::list<object>	m_list;
public:
	PCMomule(HANDLE  hExit):m_hExit(hExit)
	{
		m_hPush = CreateSemaphore(NULL, poolsize, poolsize, NULL);
		m_hPop  = CreateSemaphore(NULL, 0,		  poolsize, NULL);
	}
	~PCMomule()
	{
		CloseHandle(m_hPop);
		CloseHandle(m_hPush);

		Func f;
		AutoLock lock(m_lock);
		std::for_each(m_list.begin(), m_list.end(), f);
		m_list.clear();
	}
	size_t GetPoolSize() { return poolsize; }
	bool Push(object &obj)
	{
		HANDLE event[] = {m_hExit, m_hPush};
		DWORD dwRet = WaitForMultipleObjects(_countof(event), event, FALSE, INFINITE);
		if (dwRet != WAIT_OBJECT_0 + 1)
			return false;
		
		AutoLock lock(m_lock);
		m_list.push_back(obj);
		ReleaseSemaphore(m_hPop, 1, NULL);
		return true;
	}
	bool Pop(object& obj)
	{
		HANDLE event[] = {m_hExit, m_hPop};
		DWORD dwRet = WaitForMultipleObjects(_countof(event), event, FALSE, INFINITE);
		if (dwRet != WAIT_OBJECT_0 + 1)
			return false;

		AutoLock lock(m_lock);
		obj = m_list.front();
		m_list.pop_front();
		ReleaseSemaphore(m_hPush, 1, NULL);
		return true;
	}
};

class CEvenyOneSD
{
public:
	PVOID Build(PSECURITY_DESCRIPTOR pSD)
	{
		PSID   psidEveryone = NULL;
		PACL   pDACL   = NULL;
		BOOL   bResult = FALSE;
		PACCESS_ALLOWED_ACE pACE = NULL;
		
		try
		{
			SID_IDENTIFIER_AUTHORITY siaWorld = SECURITY_WORLD_SID_AUTHORITY;
			SECURITY_INFORMATION si = DACL_SECURITY_INFORMATION;
			
			if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION))
				throw GetLastError();

			if (!AllocateAndInitializeSid(&siaWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &psidEveryone))
				throw GetLastError();

			DWORD dwAclLength = sizeof(ACL) + sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) + GetLengthSid(psidEveryone);

			pDACL = (PACL) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwAclLength);
			if (!pDACL) 
				throw GetLastError();

			if (!InitializeAcl(pDACL, dwAclLength, ACL_REVISION))
				throw GetLastError();

			if (!AddAccessAllowedAce(pDACL, ACL_REVISION, GENERIC_ALL, psidEveryone))
				throw GetLastError();

			if (!SetSecurityDescriptorDacl(pSD, TRUE, pDACL, FALSE))
				throw GetLastError();
			bResult = TRUE;
		}
		catch (...)  { }

		if (psidEveryone)
		{
			FreeSid(psidEveryone);
			psidEveryone = NULL;
		}
		if (bResult == FALSE) 
		{
			if (pDACL) 
				HeapFree(GetProcessHeap(), 0, pDACL);
			pDACL = NULL;
		}

		return pDACL;
	}
	CEvenyOneSD()
	{
		ptr=NULL;
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = &sd;
		sa.bInheritHandle = FALSE;
		ptr = Build(&sd);
	}
	virtual ~CEvenyOneSD()
	{
		if(ptr)
		{
			HeapFree(GetProcessHeap(), 0, ptr);
		}
	}
	SECURITY_ATTRIBUTES* GetSA()
	{
		return (ptr != NULL) ? &sa : NULL;
	}
protected:
	PVOID  ptr;
	SECURITY_ATTRIBUTES sa;
	SECURITY_DESCRIPTOR sd;
};

#endif