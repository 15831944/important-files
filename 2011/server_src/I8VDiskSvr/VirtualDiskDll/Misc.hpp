#ifndef __VDISK_MISC_HPP
#define __VDISK_MISC_HPP

#include <winioctl.h>
#include "../../../include/Utility/SmartHandle.hpp"


namespace utility
{
	// ��ȡӲ�̴�С
	inline LARGE_INTEGER GetDiskSize(LPCTSTR lpszFile)
	{
		utility::CAutoFile hFile = ::CreateFile(lpszFile, GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,  FILE_ATTRIBUTE_NORMAL, NULL);

		//BOOL suc = ::GetFileSizeEx(hFile, &fileSize); // ��֧�ֶԾ����
		//assert(suc);

		// get disk file size.
		PARTITION_INFORMATION PartInfo = {0};
		ULONG IoLength = sizeof(PARTITION_INFORMATION);
		OVERLAPPED ov = {0};
		ov.hEvent = ::CreateEvent(NULL, TRUE, FALSE, TEXT("Global\\VDISK_DSCSISERVERINIT"));
		if( ov.hEvent == NULL )
			throw async::iocp::Win32Exception("CreateEvent");

		BOOL suc = ::DeviceIoControl(hFile, IOCTL_DISK_GET_PARTITION_INFO, NULL, 0,
			&PartInfo, sizeof(PARTITION_INFORMATION), &IoLength, &ov);
		assert(suc);
		if( !suc )
			throw async::iocp::Win32Exception("DeviceIoControl");

		::WaitForSingleObject(ov.hEvent, INFINITE);
		::CloseHandle(ov.hEvent);

		return PartInfo.PartitionLength;
	}


	// Բ��Ϊ������С����
	template<typename U>
	inline U Round(const U &m)
	{
		return (m + 512 - 1) & ~(512 - 1);
	}

}




#endif