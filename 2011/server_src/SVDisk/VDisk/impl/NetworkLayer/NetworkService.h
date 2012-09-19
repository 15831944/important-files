#ifndef __NETWORK_LAYER_HPP
#define __NETWORK_LAYER_HPP


#include "NetworkImpl.h"
#include "ParserImpl.h"
#include "ProtocolParser.h"


namespace i8desk
{

	namespace networkimpl
	{
		// -----------------------------------------------------
		// class NetworkLayer

		class NetworkService
		{
			// ��һ�汾Э��
			typedef ProtocolParser<ProtocolV1> ProtocolVersion1;

		private:
			IODispatcher io_;
			std::auto_ptr<NetworkImpl> impl_;

		private:
			NetworkService();
			~NetworkService();

		private:
			NetworkService(const NetworkService &);
			NetworkService &operator=(const NetworkService &);

		public:
			static NetworkService &GetInstance()
			{
				static NetworkService layer;
				return layer;
			}

		public:
			// ����Ӳ�̴�С
			void SendDiskSize(const SocketPtr &socket, const SocketBufferPtr &buffer, const LARGE_INTEGER &sz);

			// ���ض�ȡ��������
			void SendFileData(const SocketPtr &socket, const SocketBufferPtr &buffer);

			// ����д����״̬
			void SendWriteStatus(const SocketPtr &socket, const SocketBufferPtr &buffer);


		private:
			void _AcceptCallback(const SocketPtr &, const SocketBufferPtr &, const SOCKADDR_IN &);
			void _RecvCallback(const SocketPtr &, const SocketBufferPtr &);
			void _SendCallback(const SocketPtr &, const SocketBufferPtr &, size_t);

		private:
			void _SendDiskSize();
		};
	}
	
}



#endif