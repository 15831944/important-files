#pragma once

#ifndef __VDISK_MEMORY_MANAGER_HPP__
#define __VDISK_MEMORY_MAMAGER_HPP__


#include "../../../include/MemoryPool/FixedMemoryPool.hpp"
#include "../../../include/MemoryPool/SGIMemoryPool.hpp"
#include "../../../include/Allocator/ContainerAllocator.hpp"

#include "../../../include/Cache/Cache.hpp"

#include "NetLayerHdr.h"


namespace i8desk
{	

	// �ڴ�ع�����
	struct VDiskMemoryMgr
	{
		static const size_t MaxDiskDataSize	= 0x10000;
		static const size_t PackageBufSize	= PACKAGE_BUFFER_SIZE;

		// DiskDataʹ��
		typedef async::memory::SGIMemoryPool<true, MaxDiskDataSize>					DiskDataPoolType;

		// ר���ڴ�أ��ṩ��Packageʹ��
		typedef async::memory::FixedMemoryPool<false, PACKAGE_BUFFER_SIZE>			PackagePoolType;

		// Packageר�÷�����
		typedef async::allocator::ContainerAllocator<char, PackagePoolType>			PackageAllocType;

		// Disk���ݷ�����
		typedef async::allocator::ContainerAllocator<char, DiskDataPoolType>		DiskDataAllocType;
	};

}



#endif