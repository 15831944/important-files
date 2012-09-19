#include "stdafx.h"
#include "VDiskAcceptor.hpp"

#include "VDiskClient.hpp"
#include <atlbase.h>
#include <atlconv.h>

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
	}
	


	VDiskAcceptor::VDiskAcceptor(VDiskService &svr, async::iocp::IODispatcher &io)
		: io_(io)
		, svr_(svr)
		, acceptor_(io_)
	{}

	void VDiskAcceptor::Start(LPCTSTR ip, WORD port)
	{
		// ��������
		if( acceptor_.Get()->GetHandle() == INVALID_SOCKET )
			acceptor_.Open();

		acceptor_.Bind(AF_INET, port, INADDR_ANY);
		acceptor_.Listen();

		if( !thread_.IsRunning() )
		{
			thread_.RegisterFunc(std::tr1::bind(&VDiskAcceptor::_Thread, this));
			thread_.Start();
		}
	}

	void VDiskAcceptor::Stop()
	{
		// ������IO���˳������߳�
		::QueueUserAPC(detail::APCFunc, thread_, NULL);
		thread_.Stop();

		// ֹͣ����
		acceptor_.Close();
	}

	void VDiskAcceptor::_OnAccept(u_long error, const async::network::SocketPtr &remoteSocket)
	{
		if( error != 0 )
		{
			// �������
			return;
		}

		try
		{
			VDiskClientPtr session(CreateVDiskClient(remoteSocket, svr_));
			session->Start();
		}
		catch(const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	DWORD VDiskAcceptor::_Thread()
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
						using namespace std::tr1::placeholders;
						acceptor_.AsyncAccept(0, std::tr1::bind(&VDiskAcceptor::_OnAccept, this, _1, _2));
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