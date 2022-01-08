#ifndef _SRC_XPLATFORM_NET_TCP_SOCKET_V6_H
#define _SRC_XPLATFORM_NET_TCP_SOCKET_V6_H

#include<XPlatform.net/XP_ISocket.h>

namespace XPlatform {
	namespace Net {
		class TCPSocketv6 : public XPlatform::Net::XP_ISocket {
		protected:
			static int addr_len;

			uint32_t m_sock;
			XPlatform::Net::IPEndPoint6 m_EndPoint;
			sockaddr_in6 m_addr;
			
			TCPSocketv6(uint32_t sock, const XPlatform::Net::IPEndPoint6& EndPoint);
		public:

			TCPSocketv6();


			XPlatform::Net::XPlatformNetResult Listen
			(const XPlatform::Net::g_IPEndPoint& EndPoint) override;

			virtual XPlatform::Net::XPlatformNetResult Connect
			(const XPlatform::Net::g_IPEndPoint& EndPoint) override;

			virtual void Close() override;

			XPlatform::Net::XPlatformNetResult Select(uint32_t msecs)override;

			virtual XPlatform::Net::XP_ISocket* Accept()override;

			uint32_t Send(const char* Buf, int Len);
			uint32_t Recv(char* Buf, int Len);

			const XPlatform::Net::g_IPEndPoint& GetEndPoint() const;

			virtual void Release() override;

			~TCPSocketv6();

		};
	}
}

#endif