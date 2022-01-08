#include"TCPSocketv6.h"

#include"..//..//net.h"

int XPlatform::Net::TCPSocketv6::addr_len = sizeof(sockaddr_in6);

XPlatform::Net::TCPSocketv6::TCPSocketv6(){

}

XPlatform::Net::TCPSocketv6::TCPSocketv6(uint32_t sock, const XPlatform::Net::IPEndPoint6& EndPoint)
	:m_sock(sock), m_EndPoint(EndPoint)
{

}

XPlatform::Net::XPlatformNetResult XPlatform::Net::TCPSocketv6::Listen(const XPlatform::Net::g_IPEndPoint& EndPoint){
	m_EndPoint = reinterpret_cast<const XPlatform::Net::IPEndPoint6&>(EndPoint);
	m_addr = *m_EndPoint.GetAddr();

	m_sock = socket(AF_INET6, SOCK_STREAM, IPPROTO::IPPROTO_TCP);
	if (m_sock < 0) {
		return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_FAILED;
	}

#ifdef WIN32

	setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, 
		reinterpret_cast<const char*>(_SO_REUSE_ADDR), sizeof(int));

#else 

	setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR,
		reinterpret_cast<const void*>(_SO_REUSE_ADDR), sizeof(int));

#endif

	if (bind(m_sock, reinterpret_cast<const sockaddr*>(&m_addr), sizeof(m_addr)) < 0) {
		return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_FAILED_TO_BIND_SOCKET_TO_ADDRESS;
	}

	if (listen(m_sock, SOMAXCONN) < 0) {
		return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_FAILED_TO_LISTEN_SOCKET;
	}

	return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_SUCCESS;
}

XPlatform::Net::XPlatformNetResult XPlatform::Net::TCPSocketv6::Connect
(const XPlatform::Net::g_IPEndPoint& EndPoint){
	m_EndPoint = reinterpret_cast<const XPlatform::Net::IPEndPoint6&>(EndPoint);
	m_addr = *m_EndPoint.GetAddr();

	m_sock = socket(AF_INET6, SOCK_STREAM, IPPROTO::IPPROTO_TCP);
	if (m_sock < 0) {
		return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_FAILED;
	}
	
	if (connect(m_sock, (struct sockaddr*)&m_addr, sizeof(m_addr)) < 0) {
		return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_FAILED_TO_CONNECT_TO_ADDRESS;
	}

	return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_SUCCESS;
}

void XPlatform::Net::TCPSocketv6::Close(){
#ifdef WIN32
#define close closesocket
#endif
	close(m_sock);
}

XPlatform::Net::XPlatformNetResult XPlatform::Net::TCPSocketv6::Select(uint32_t msecs){
	struct timeval tval;
	struct timeval* tvalptr = nullptr;
	fd_set rset;
	int res;

	if (msecs > 0) {
		tval.tv_sec = msecs / 1000;
		tval.tv_usec = (msecs % 1000) * 1000;
		tvalptr = &tval;
	}

	FD_ZERO(&rset);
	FD_SET(m_sock, &rset);

	res = select(m_sock + 3, &rset, nullptr, nullptr, tvalptr);

	if (res <= 0)
		return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_SELECT_FAILED;

	if (!FD_ISSET(m_sock, &rset))
		return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_SELECT_FAILED;

	return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_SELECT_SUCCESS;

}

XPlatform::Net::XP_ISocket* XPlatform::Net::TCPSocketv6::Accept(){
	uint32_t tmp_sock = 0;

#ifdef WIN32
	tmp_sock = accept(m_sock,
		reinterpret_cast<struct sockaddr*>(&m_addr),
		reinterpret_cast<int*>(&XPlatform::Net::TCPSocketv6::addr_len));
#else
	tmp_sock = accept(m_sock,
		reinterpret_cast<struct sockaddr*>(&m_addr),
		reinterpret_cast<socklen_t*>(&XPlatform::Net::TCPSocket::addr_len));
#endif
	
	if (tmp_sock < 0) return NULL;

	return reinterpret_cast<XPlatform::Net::XP_ISocket*>(
		new XPlatform::Net::TCPSocketv6(tmp_sock, XPlatform::Net::IPEndPoint6(m_addr))
	);
}

uint32_t XPlatform::Net::TCPSocketv6::Send(const char* Buf, int Len){
	return send(m_sock, Buf, Len, NULL);
}

uint32_t XPlatform::Net::TCPSocketv6::Recv(char* Buf, int Len){
	return recv(m_sock, Buf, Len, NULL);
}

const XPlatform::Net::g_IPEndPoint& XPlatform::Net::TCPSocketv6::GetEndPoint() const{
	return reinterpret_cast<const XPlatform::Net::g_IPEndPoint&>(m_EndPoint);
}

void XPlatform::Net::TCPSocketv6::Release(){
	delete this;
}

XPlatform::Net::TCPSocketv6::~TCPSocketv6(){

}
