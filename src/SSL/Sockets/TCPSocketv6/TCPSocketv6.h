#ifndef _SRC_XPLATFORM_NET_SSL_TCP_SOCKET_V6_H
#define _SRC_XPLATFORM_NET_SSL_TCP_SOCKET_V6_H

#include<XPlatform.net/XP_ISocket.h>

#include "..//..//SSLCtx/SSLCtx.h"
#include "..//..//..//Sockets/TCPSocketv6/TCPSocketv6.h"

#include <openssl/ssl.h>

namespace XPlatform{
	namespace Net {
		namespace SSL {
			class TCPSocketv6 : public XPlatform::Net::TCPSocketv6 {

				XPlatform::Net::SSL::Context* m_pSSLCtx;
				::SSL* m_pSSL = NULL;

			public:
				TCPSocketv6(uint32_t sock, const XPlatform::Net::IPEndPoint6& EndPoint, XPlatform::Net::SSL::Context* pSSLCtx, ::SSL* pSSL);
				TCPSocketv6(XPlatform::Net::SSL::Context* pSSLCtx);

				XPlatform::Net::XP_ISocket* Accept() override;

				XPlatform::Net::XPlatformNetResult Connect
				(const XPlatform::Net::g_IPEndPoint& g_EndPoint) override;

				uint32_t Send(const char* Buf, int Len) override;
				uint32_t Recv(char* Buf, int Len) override;

				void Close() override;

				void Release() override;

				~TCPSocketv6();
			};
		}
	}
}

#endif