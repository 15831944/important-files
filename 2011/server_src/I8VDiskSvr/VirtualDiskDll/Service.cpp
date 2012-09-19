#include "stdafx.h"
#include "Service.hpp"

#include <ctime>

#include "Misc.hpp"




namespace i8desk
{

	namespace detail
	{
		// һ����Ͷ�ݽ���Socket����
		enum { MAX_ACCEPT = 20 };



		// alterable IO
		void WINAPI APCFunc(ULONG_PTR pParam)
		{
			// do nothing
		}

		template < typename Tss >
		inline void ThreadInit(Tss &tss)
		{
			tss = new cache::DiskCache;
		}

		template < typename Tss >
		inline void ThreadUninit(Tss &tss)
		{
			delete tss;
		}
	}


	using namespace async::network;


	VDiskService::VDiskService()
		: io_(GetFitThreadNum(), 
			std::tr1::bind(&detail::ThreadInit<DiskCachePtr>, cachePtr_), 
			std::tr1::bind(&detail::ThreadUninit<DiskCachePtr>, cachePtr_))
		, refreshSock_(INVALID_SOCKET)
		, syncFile_(INVALID_HANDLE_VALUE)
		, version_(0)
		, acceptor_(io_)
	{
	}


	DWORD VDiskService::Start(LPCTSTR ip, WORD port, LPCTSTR filePath)
	{
		refreshSock_	= INVALID_SOCKET;
		filePath_		= filePath;

		// ͬ����ȡ��ʱ����
		syncFile_ = ::CreateFile(filePath, GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS | FILE_FLAG_NO_BUFFERING,
			NULL);
		if( syncFile_ == INVALID_HANDLE_VALUE )
			return ::GetLastError();

		// ��������
		thread_.Start();

		return ERROR_SUCCESS;
	}

	void VDiskService::Stop()
	{
		// �ر��ļ�
		if( syncFile_ != INVALID_HANDLE_VALUE )
		{
			::CloseHandle(syncFile_);
			syncFile_ = INVALID_HANDLE_VALUE;
		}

		// ����ˢ��socket
		refreshSock_ = INVALID_SOCKET;

		// ������IO���˳������߳�
		::QueueUserAPC(detail::APCFunc, thread_, NULL);
		thread_.Stop();

		// ֹͣ����
		acceptor_.Close();
	}


	void VDiskService::GetVDiskInfo(PDWORD pdwConnect, PDWORD pdwVersion)
	{
		//*pdwConnect = networkFlow_.Size();
		*pdwVersion = version_;
	}
	
	void VDiskService::RefreshBufferEx()
	{
		// ����ļ�����
		//diskCache_.clear(std::tr1::bind(&MemoryAlloc::DeallocData, std::tr1::placeholders::_1));

		// ˢ�°汾��
		version_ = _time32(NULL);
		refreshSock_ = INVALID_SOCKET;
	}


	void VDiskService::_OnAccept(u_long error, const async::network::SocketPtr &remoteSocket)
	{
		if( error != 0 )
		{
			// �������
			return;
		}

		try
		{
			VDiskClientPtr session(CreateVDiskClient(remoteSocket, *this));
			session->Start();
		}
		catch(const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	DWORD VDiskService::_Thread()
	{
		// ͨ��ʹ��WSAEventSelect���ж��Ƿ����㹻��AcceptEx�����߼���һ���������Ŀͻ�����
		HANDLE hAcceptEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
		::WSAEventSelect(acceptor_.Get()->GetHandle(), hAcceptEvent, FD_ACCEPT);

		while(!thread_.IsAborted())
		{	
			DWORD dwError = ::WaitForSingleObjectEx(hAcceptEvent, INFINITE, TRUE);
			if( dwError == WAIT_FAILED || dwError == WAIT_IO_COMPLETION )
				break;
			else if( dwError == WAIT_OBJECT_0 )
			{
				// Ͷ�ݽ�������
				for(int i = 0; i != detail::MAX_ACCEPT; ++i)
				{
					try
					{
						SocketPtr acceptSock(MakeSocket(io_, Tcp::V4().Family(), Tcp::V4().Type(), Tcp::V4().Protocol()));
						acceptor_.AsyncAccept(acceptSock, 0, 
							std::tr1::bind(&VDiskService::_OnAccept, this, 
							std::tr1::placeholders::_1, std::tr1::placeholders::_2));
					} 
					catch(const std::exception &e)
					{
						std::cerr << e.what() << std::endl;
					}
				}
			}
		}

		::CloseHandle(hAcceptEvent);
		return 0;
	}
}