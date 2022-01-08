#include<XPlatform.core/engine.h>
#include<XPlatform.net/Net.h>

#include "../net.h"

#include<cassert>

#include <openssl/ssl.h>
#include <openssl/ssl3.h>

#include "SSLCtx/SSLCtx.h"
#include "Sockets/TCPSocket/TCPSocket.h"
#include "Sockets/TCPSocketv6/TCPSocketv6.h"

XP_NET_API void xplatform_openssl_get_cipher() {
	assert(false && "dont call, function is not working!");
}

XP_NET_API XPlatform::Net::SSL::Ctx* xplatform_openssl_create_ssl_context(bool IsClient) {
	SSL_CTX* m_pSSLCtx = SSL_CTX_new(IsClient ? TLS_client_method() : TLS_server_method());

	if (m_pSSLCtx == NULL) {
		XPlatform::core::Engine::GetInstance()->GetMsgCallback()
			("Failed to create ssl context!", XPlatform::Api::XPResult::XPLATFORM_RESULT_FAILED, _NetExtInf.ExtId);
	}

	return reinterpret_cast<XPlatform::Net::SSL::Ctx*>(new XPlatform::Net::SSL::Context(m_pSSLCtx));
}

XP_NET_API XPlatform::Net::XP_ISocket* xplatform_openssl_create_tcp_ssl_socket(XPlatform::Net::SSL::Ctx* m_pSSLCtx) {
	return reinterpret_cast<XPlatform::Net::XP_ISocket*>(new XPlatform::Net::SSL::TCPSocket(reinterpret_cast<XPlatform::Net::SSL::Context*>(m_pSSLCtx)));
}

XP_NET_API XPlatform::Net::XP_ISocket* xplatform_openssl_create_tcp_ssl_socket_v6(XPlatform::Net::SSL::Ctx* m_pSSLCtx) {
	return reinterpret_cast<XPlatform::Net::XP_ISocket*>(new XPlatform::Net::SSL::TCPSocketv6(reinterpret_cast<XPlatform::Net::SSL::Context*>(m_pSSLCtx)));
}