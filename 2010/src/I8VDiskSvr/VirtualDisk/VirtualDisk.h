#ifndef _virtual_disk_inc_
#define _virtual_disk_inc_

#include "../../../include/plug.h"

namespace i8desk
{
	//�����̲��sendmessage�ļ�������
	//(0x01--0x04��������ǰ���������api)

	typedef struct tagVDInfo
	{
		DWORD dwIp;
		WORD  nPort;
		TCHAR szSvrDrv;
		TCHAR szCliDrv;
		DWORD dwConnect;
		DWORD dwVersion;//(time_t);
		TCHAR szTempDir[MAX_PATH];
	}tagVDInfo;

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

	IPlug* WINAPI CreatePlug   (void);

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
}

#endif
