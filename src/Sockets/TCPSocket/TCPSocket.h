#ifndef _SRC_XPLATFORM_NET_TCP_SOCKET_H
#define _SRC_XPLATFORM_NET_TCP_SOCKET_H

#include<XPlatform.net/XP_ISocket.h>

namespace XPlatform {
	namespace Net {
		class TCPSocket : public XPlatform::Net::XP_ISocket {
		protected:
			uint32_t m_sock;
			XPlatform::Net::IPEndPoint m_EndPoint;
			sockaddr_in m_addr;
			
			static int addr_len;
			
			TCPSocket(uint32_t sock, const XPlatform::Net::IPEndPoint& EndPoint);
		private:

		public:

			TCPSocket();

			virtual XPlatform::Net::XPlatformNetResult Listen
			(const XPlatform::Net::g_IPEndPoint& EndPoint) override;

			virtual XPlatform::Net::XPlatformNetResult Connect
			(const XPlatform::Net::g_IPEndPoint& EndPoint) override;

			virtual void Close();

			XPlatform::Net::XPlatformNetResult Select(uint32_t msecs);

			virtual XPlatform::Net::XP_ISocket* Accept();

			virtual uint32_t Send(const char* Buf, int Len);
			virtual uint32_t Recv(char* Buf, int Len);

			const XPlatform::Net::g_IPEndPoint& GetEndPoint() const;

			virtual void Release() override;

			~TCPSocket();

		};
	}
}

#endif