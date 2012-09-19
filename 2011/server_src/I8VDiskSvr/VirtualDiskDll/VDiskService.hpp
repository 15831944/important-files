#ifndef __VDISK_SERVICE_HPP
#define __VDISK_SERVICE_HPP



#include "../../../include/MultiThread/Tls.hpp"
#include "../../../include/AsyncIO/IOCP/Dispatcher.hpp"
#include "../../../include/AsyncIO/Timer/Timer.hpp"

#include "MemoryManager.h"
#include "MemoryCache.hpp"


namespace i8desk
{

	// forward declare
	class VDiskAcceptor;

	// ----------------------------------------------------
	// class VDiskService

	class VDiskService
	{

	private:
		// ˢ��������ʹ�õ�socket
		SOCKET refreshSock_;	

		// �汾��
		DWORD version_;

		// ��Ҫ��ȡ�ļ�·��
		stdex::tString filePath_;

		// IO Service
		async::iocp::IODispatcher io_;

		// Acceptor
		std::auto_ptr<VDiskAcceptor> acceptor_;

		// Timer
		async::timer::Timer time_;

		// DiskCache
		MemoryCacheMgr cache_;

	public:
		VDiskService();

	private:
		VDiskService(const VDiskService &);
		VDiskService &operator=(const VDiskService &);


	public:
		// ����
		DWORD Start(LPCTSTR ip, WORD port, LPCTSTR filePath);
		// ����
		void Stop();

		// ��ȡ������Ϣ
		void  GetVDiskInfo(PDWORD pdwConnect, PDWORD pdwVersion);
		// ˢ��
		void  RefreshBufferEx();

	public:
		inline async::iocp::IODispatcher &GetService() { return io_;		}
		inline SOCKET GetSocket() const				{ return refreshSock_;	}
		inline const stdex::tString &GetFilePath() const	{ return filePath_;		}
		
		inline void SetSocket(SOCKET sock)			{ refreshSock_ = sock;	}

		inline MemoryCacheMgr &GetDiskCache()		{ return cache_; }

	private:
		void _Total();
	};
}






#endif