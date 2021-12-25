#ifndef _SRC_XPLATFORM_NET_TCP_SOCKET_V6_H
#define _SRC_XPLATFORM_NET_TCP_SOCKET_V6_H

#include<XPlatform.net/XP_ISocket.h>

namespace XPlatform {
	namespace Net {
		class TCPSocketv6 : public XPlatform::Net::XP_ISocket {
			uint32_t m_sock;
			XPlatform::Net::IPEndPoint6 m_EndPoint;
			sockaddr_in6 m_addr;
			
			static int addr_len;
		public:

			TCPSocketv6();

			TCPSocketv6(uint32_t sock, const XPlatform::Net::IPEndPoint6& EndPoint);

			XPlatform::Api::XPResult Listen
			(const XPlatform::Net::g_IPEndPoint& EndPoint) override;

			XPlatform::Api::XPResult Connect
			(const XPlatform::Net::g_IPEndPoint& EndPoint) override;

			void Close();

			uint32_t Select(uint32_t msecs);

			XPlatform::Net::XP_ISocket* Accept();

			uint32_t Send(const char* Buf, int Len);
			uint32_t Recv(char* Buf, int Len);

			const XPlatform::Net::g_IPEndPoint& GetEndPoint() const;

			void Release() override;

			~TCPSocketv6();

		};
	}
}

#endif