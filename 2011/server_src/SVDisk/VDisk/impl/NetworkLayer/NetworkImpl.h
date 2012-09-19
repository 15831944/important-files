#ifndef __NETWORK_IMPL_HPP
#define __NETWORK_IMPL_HPP


#include "../../async/network/Socket.hpp"
#include "../../async/MultiThread/Thread.hpp"

//#include <Comm/Allocator/ContainerAllocator.hpp>


using namespace async;
using namespace async::network;

namespace i8desk
{

	namespace networkimpl
	{
		// ------------------------------------------------
		// class NetworkImpl

		class NetworkImpl
		{
			// �ص��ӿ�
			typedef std::tr1::function<void(const SocketPtr &, const SocketBufferPtr &, const SOCKADDR_IN &)>	AcceptCallback;
			typedef std::tr1::function<void(const SocketPtr &, const SocketBufferPtr &)>						RecvCallback;
			typedef std::tr1::function<void(const SocketPtr &, const SocketBufferPtr &, size_t)>				SendCallback;

		public:
			// һ��Ͷ��Accept����
			enum { MAX_ACCEPT = 10 };

		private:
			IODispatcher &io_;
			SocketPtr acceptor_;

			// Ͷ��Accept�߳�
			async::thread::ThreadImplEx acceptThread_;

			// �ص��ӿ�
			AcceptCallback acceptCallback_;
			RecvCallback recvCallback_;
			SendCallback sendCallback_;

		public:
			explicit NetworkImpl(IODispatcher &io);
			~NetworkImpl();


		public:
			// ע��ص�
			void Register(AcceptCallback, RecvCallback, SendCallback);
			// ����
			void Start(u_short);
			// ֹͣ
			void Stop();

			// ��������
			void Send(const SocketPtr &socket, const SocketBufferPtr &buffer);


			// IOCP�ص�����
		private:
			void _OnAccept(const AsyncResultPtr &);
			void _OnRecv(const AsyncResultPtr &);
			void _OnSend(const AsyncResultPtr &);

		private:
			DWORD _ThreadAccept();

			// ����Զ������
			void _AddRemote(const SocketPtr &, const SOCKADDR_IN &);
			// �Ƴ�Զ������
			void _RemoveRemote(const SocketPtr &);

		};


	} // end of namespace - networkimpl


} // end of namespace - i8desk

#endif