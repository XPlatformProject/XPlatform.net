#include "UDPSocket.h"

int XPlatform::Net::UDPSocket::addr_len = sizeof(sockaddr_in);

XPlatform::Net::XPlatformNetResult XPlatform::Net::UDPSocket::Bind(const XPlatform::Net::g_IPEndPoint& IPEndPoint){
	m_EndPoint = reinterpret_cast<const XPlatform::Net::IPEndPoint&>(IPEndPoint);
	m_addr = *m_EndPoint.GetAddr();

	if (m_sock == NULL) {
		m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (m_sock < 0) {
			return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_FAILED;
		}
	}

	if (bind(m_sock, reinterpret_cast<const sockaddr*>(&m_addr), sizeof(m_addr)) < 0) {
		return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_FAILED_TO_BIND_SOCKET_TO_ADDRESS;
	}

	return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_SUCCESS;
}

XPlatform::Net::XPlatformNetResult XPlatform::Net::UDPSocket::CreateSocket(){
	m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_sock < 0) return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_FAILED;

	return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_SUCCESS;
}

uint32_t XPlatform::Net::UDPSocket::SendTo(const char* buf, int len, const XPlatform::Net::g_IPEndPoint& IPEndPoint){
#ifdef WIN32
	return sendto(m_sock,buf, len, NULL, reinterpret_cast<const sockaddr*>(reinterpret_cast<const XPlatform::Net::IPEndPoint&>(IPEndPoint).GetAddr()), sizeof(sockaddr_in));
#else 
	return sendto(m_sock, buf, len, NULL, reinterpret_cast<const sockaddr*>(reinterpret_cast<const XPlatform::Net::IPEndPoint&>(IPEndPoint).GetAddr()), sizeof(sockaddr_in));
#endif
}

uint32_t XPlatform::Net::UDPSocket::RecvFrom(char* buf, int len, XPlatform::Net::g_IPEndPoint& IPEndPoint){
	sockaddr_in FromAddr{};

	uint32_t bytes = 0;

#ifdef WIN32
	bytes = recvfrom(m_sock, buf, len, NULL, reinterpret_cast<sockaddr*>(&FromAddr),reinterpret_cast<int*>(&XPlatform::Net::UDPSocket::addr_len));
#else
	bytes = recvfrom(m_sock, buf, len, NULL, reinterpret_cast<sockaddr*>(&FromAddr), reinterpret_cast<socklen_t*>(&XPlatform::Net::UDPSocket::addr_len));
#endif

	IPEndPoint = XPlatform::Net::IPEndPoint(FromAddr);

	return bytes;
}

XPlatform::Net::XPlatformNetResult XPlatform::Net::UDPSocket::Select(uint32_t msecs) {
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

	res = select(m_sock + 1, &rset, nullptr, nullptr, tvalptr);

	if (res <= 0)
		return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_SELECT_FAILED;

	if (!FD_ISSET(m_sock, &rset))
		return XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_SELECT_FAILED;

	return  XPlatform::Net::XPlatformNetResult::XPLATFORM_NET_RESULT_SELECT_SUCCESS;

}

void XPlatform::Net::UDPSocket::Close() {
#ifdef WIN32
#define close closesocket
#endif
	close(m_sock);
}

void XPlatform::Net::UDPSocket::Release(){
	delete this;
}
