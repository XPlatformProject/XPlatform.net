#ifndef _XPLATFORM_UDP_SOCKET_V6_H
#define _XPLATFORM_UDP_SOCKET_V6_H

#include<XPlatform.net/XP_IUdpSocket.h>

namespace XPlatform {
	namespace Net {
		class UDPSocketv6 : public XPlatform::Net::XP_IUdpSocket {
			XPlatform::Net::IPEndPoint6 m_EndPoint;
			uint32_t m_sock = NULL;
			sockaddr_in6 m_addr;
		
			static int addr_len;

		public:
			XPlatform::Net::XPlatformNetResult Bind
			(const XPlatform::Net::g_IPEndPoint& IPEndPoint);

			XPlatform::Net::XPlatformNetResult CreateSocket();

			uint32_t SendTo(
				const char* buf,
				int len,
				const XPlatform::Net::g_IPEndPoint& IPEndPoint
			);

			uint32_t RecvFrom(
				char* buf,
				int len,
				XPlatform::Net::g_IPEndPoint& IPEndPoint
			);

			XPlatform::Net::XPlatformNetResult Select(uint32_t msecs);

			void Close();

			void Release();

		};
	}
}

#endif	