#ifndef _virtual_disk_inc_
#define _virtual_disk_inc_

#include "../../../include/frame.h"

namespace i8desk
{
	//�����̲��sendmessage�ļ�������
	//(0x01--0x04��������ǰ���������api)

	struct tagVDInfo
	{
		TCHAR  ID[MAX_GUID_LEN];
		TCHAR  svrMode[MAX_NAME_LEN];

		DWORD dwIp;
		DWORD nPort;
		char szSvrDrv;
		char szCliDrv;
		DWORD dwConnect;
		DWORD dwVersion;//(time_t);
		
		ulong cacheSize;
		int ssdDrv;
		TCHAR szTempDir[MAX_PATH];
	};
	typedef std::tr1::shared_ptr<tagVDInfo> VDInfoPtr;


	struct VDiskClientStatus
	{
		tagVDInfo	*vDiskInfo;					// ��������Ϣ

		TCHAR		VID[MAX_GUID_LEN];			// ������ID
		ulong		VIP;						// ������IP
		ulong		ClientIP;					//�ͻ���IP
		ulonglong	ReadCount;					//��ȡ������				
		ulong		ReadSpeed;					//��ȡ�ٶ�
		ulong		ReadMax;					//��ȡ��ֵ
		ulong		ConnectTime;				//����ʱ��
		ulong		CacheShooting;				//����������
	};
	typedef std::tr1::shared_ptr<VDiskClientStatus> VDiskClientStatusPtr;


	#define VDISK_CMD_START		0x01 
	/*����˵��
		[in]param1:tagVDInfo* pVDisk.
		param2:��������0
		return value:����һ��,��ʾ������ʵ������ľ��(��ʶ)��
	*/

	#define VDISK_CMD_STOP		0x02
	/*����˵��
		[in]param1:DWORD handle.Ҫֹͣ�����̶���ľ��.
		param2:������(0);
		return value:0.
	*/

	#define VDISK_CMD_REFRESH	0x03
	/*����˵��:
		[in]param1:DWORD handle.Ҫˢ�������̶���ľ��.
		param2:������(0);
		return value:0.
	*/

	#define VDISK_CMD_GETINFO	0x04
	/*����˵��:
		[in]param1:DWORD handle.Ҫ�����������̶�����.
		[in, out]param2:tagVDInfo* pVDInfo.�����̵�״̬
		return value:0
	*/

	ISvrPlug* WINAPI CreateSvrPlug(DWORD);

// 	DWORD  WINAPI StartServer  (PHANDLE handle, LPCSTR lpszSvrIP, char szDriver, WORD wPort);
// 	void   WINAPI GetVdiskInfo (HANDLE handle, PDWORD pdwConnect, PDWORD pdwVersion);
// 	void   WINAPI StopServer   (HANDLE handle);
// 	void   WINAPI RefreshBuffer(HANDLE handle);

	#define VDISK_CMD_GETALLINFO 0x05
	/*����˵��:
		[in,out]param1:tagVDInfo* pVDInfo.
		[in]param2:DWORD dwCount.��ʾ����1���Է���������̸���
		return value:д��״̬�������̸���.

		eg.
		DWORD dwCount = 10;//��Ҫȡ״̬�������̸�����
		tagVDInfo VDInfo[dwCount] = {0};
		DWORD dwVDCount = SendMessage(VDISK_CMD_GETSTATUS2, (DWORD)VDInfo, dwConnt);
	*/

	#define VDISK_CMD_GETINFOEX 0x06
}

#endif
