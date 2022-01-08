#ifndef _SRC_XPLATFORM_NET_SSL_TCP_SOCKET_H
#define _SRC_XPLATFORM_NET_SSL_TCP_SOCKET_H

#include<XPlatform.net/XP_ISocket.h>

#include "..//..//SSLCtx/SSLCtx.h"
#include "..//..//..//Sockets/TCPSocket/TCPSocket.h"

#include <openssl/ssl.h>

namespace XPlatform{
	namespace Net {
		namespace SSL {
			class TCPSocket : public XPlatform::Net::TCPSocket {

				XPlatform::Net::SSL::Context* m_pSSLCtx;
				::SSL* m_pSSL = NULL;

			public:
				TCPSocket(uint32_t sock, const XPlatform::Net::IPEndPoint& EndPoint, XPlatform::Net::SSL::Context* pSSLCtx, ::SSL* pSSL);
				TCPSocket(XPlatform::Net::SSL::Context* pSSLCtx);

				XPlatform::Net::XP_ISocket* Accept() override;

				XPlatform::Net::XPlatformNetResult Connect
				(const XPlatform::Net::g_IPEndPoint& g_EndPoint) override;

				uint32_t Send(const char* Buf, int Len) override;
				uint32_t Recv(char* Buf, int Len) override;

				void Close() override;

				void Release() override;

				~TCPSocket();
			};
		}
	}
}

#endif