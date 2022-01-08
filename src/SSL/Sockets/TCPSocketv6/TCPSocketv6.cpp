#include "TCPSocketv6.h"

#include <openssl/ssl.h>
#include <cassert>

XPlatform::Net::SSL::TCPSocketv6::TCPSocketv6(uint32_t sock, const XPlatform::Net::IPEndPoint6& EndPoint, XPlatform::Net::SSL::Context* pSSLCtx, ::SSL* pSSL)
	: XPlatform::Net::TCPSocketv6(sock, EndPoint), m_pSSLCtx(pSSLCtx), m_pSSL(pSSL) {



}

XPlatform::Net::SSL::TCPSocketv6::TCPSocketv6(XPlatform::Net::SSL::Context* pSSLCtx) :m_pSSLCtx(pSSLCtx) {
	
}

XPlatform::Net::XP_ISocket* XPlatform::Net::SSL::TCPSocketv6::Accept() {
	uint32_t tmp_sock = 0;

#ifdef WIN32
	tmp_sock = accept(m_sock,
		reinterpret_cast<struct sockaddr*>(&m_addr),
		reinterpret_cast<int*>(&XPlatform::Net::TCPSocketv6::addr_len));
#else
	tmp_sock = accept(m_sock,
		reinterpret_cast<struct sockaddr*>(&m_addr),
		reinterpret_cast<socklen_t*>(&XPlatform::Net::TCPSocketv6::addr_len));
#endif

	if (tmp_sock < 0) return NULL;

	::SSL* pSSL = SSL_new(m_pSSLCtx->GetRawHandle());
	assert(pSSL != NULL);
	
	SSL_set_fd(pSSL, tmp_sock);

	if (SSL_accept(pSSL) <= 0) {
		SSL_free(pSSL);
		return NULL;
	}

	return reinterpret_cast<XPlatform::Net::XP_ISocket*>(
		new XPlatform::Net::SSL::TCPSocketv6(tmp_sock, XPlatform::Net::IPEndPoint6(m_addr), m_pSSLCtx, pSSL)
	);
}

uint32_t XPlatform::Net::SSL::TCPSocketv6::Send(const char* Buf, int Len) {
	return SSL_write(m_pSSL, Buf, Len);
}

uint32_t XPlatform::Net::SSL::TCPSocketv6::Recv(char* Buf, int Len) {
	return SSL_read(m_pSSL, Buf, Len);
}

XPlatform::Net::XPlatformNetResult XPlatform::Net::SSL::TCPSocketv6::Connect
(const XPlatform::Net::g_IPEndPoint& EndPoint) {
	m_EndPoint = reinterpret_cast<const XPlatform::Net::IPEndPoint6&>(EndPoint);
	m_addr = *m_EndPoint.GetAddr();

	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sock < 0) {
		return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_FAILED;
	}

	if (connect(m_sock, (struct sockaddr*)&m_addr, sizeof(m_addr)) < 0) {
		return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_FAILED_TO_CONNECT_TO_ADDRESS;
	}

	m_pSSL = SSL_new(m_pSSLCtx->GetRawHandle());
	SSL_set_fd(m_pSSL, m_sock);

	int res = SSL_connect(m_pSSL);
	if (res <= 0) {
		int err = SSL_get_error(m_pSSL, res);
		return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_FAILED;
	}

	return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_SELECT_SUCCESS;
}

void XPlatform::Net::SSL::TCPSocketv6::Close() {
	if (m_pSSL != NULL) {
		SSL_shutdown(m_pSSL);
		SSL_free(m_pSSL);
	}
#ifdef WIN32
#define close closesocket
#endif
	close(m_sock);
}


void XPlatform::Net::SSL::TCPSocketv6::Release() {
	delete this;
}

XPlatform::Net::SSL::TCPSocketv6::~TCPSocketv6() {
}
