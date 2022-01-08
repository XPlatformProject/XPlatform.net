#ifndef _XPLATFORM_UDP_SOCKET_H
#define _XPLATFORM_UDP_SOCKET_H

#include<XPlatform.net/XP_IUdpSocket.h>

namespace XPlatform {
	namespace Net {
		class UDPSocket : public XPlatform::Net::XP_IUdpSocket {
			XPlatform::Net::IPEndPoint m_EndPoint;
			uint32_t m_sock = NULL;
			sockaddr_in m_addr;
		
			static int addr_len;

		public:
			XPlatform::Net::XPlatformNetResult Bind
			(const XPlatform::Net::g_IPEndPoint& IPEndPoint) override;

			XPlatform::Net::XPlatformNetResult CreateSocket() override;

			uint32_t SendTo(
				const char* buf,
				int len,
				const XPlatform::Net::g_IPEndPoint& IPEndPoint
			) override;

			uint32_t RecvFrom(
				char* buf,
				int len,
				XPlatform::Net::g_IPEndPoint& IPEndPoint
			);

			XPlatform::Net::XPlatformNetResult Select(uint32_t msecs) override;

			void Close();

			void Release();

		};
	}
}

#endif	