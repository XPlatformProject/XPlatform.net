#ifndef _INC_XPLATFORM_SSL_H
#define _INC_XPLATFORM_SSL_H

#include <XPlatform.net/SSL/SSLCtx.h>

namespace XPlatform {
	namespace Net {
		namespace SSL{
			constexpr char* m_pXPlatformCreateContextFunctionName = "xplatform_openssl_create_ssl_context";
			typedef XPlatform::Net::SSL::Ctx* (*pfn_XPlatformCreateContextFunction)(bool IsClient);
		
			constexpr char* m_pXPlatformCreateSSLTCPSocketFunctionName = "xplatform_openssl_create_tcp_ssl_socket";
			constexpr char* m_pXPlatformCreateSSLTCPSocketV6FunctionName = "xplatform_openssl_create_tcp_ssl_socket_v6";
			typedef XPlatform::Net::XP_ISocket* (*pfn_XPlatformCreateSSLTCPSocketFunction)(XPlatform::Net::SSL::Ctx* m_pCtx);
		}
	}
}

#endif