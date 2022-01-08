#include "net.h"
#include<XPlatform.core/engine.h>
#include<XPlatform.net/Net.h>

#include<XFmt/XFmt.h>

#include<cassert>

#if defined(WIN32)
#include<winsock2.h>
#include<WS2tcpip.h>
#else
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#endif

#include<openssl/ssl.h>

#include "Sockets/TCPSocket/TCPSocket.h"
#include "Sockets/TCPSocketv6/TCPSocketv6.h"
#include "Sockets/UDPSocket/UDPSocket.h"
#include "Sockets/UDPSocket6/UDPSocketv6.h"

XPlatform::core::XPlatformExtensionInfo _NetExtInf{};

int _SO_REUSE_ADDR = 0;

XP_NET_API XPlatform::Api::XPResult xplatform_extension_init(){
	XPlatform::Api::XPResult res =
	XPlatform::core::Engine::GetInstance()->GetExtensionInfo
	(XPLATFORM_NET_EXT_NAME, &_NetExtInf);
	if (res != XPlatform::Api::XPResult::XPLATFORM_RESULT_SUCCESS) {
		XPlatform::core::Engine::GetInstance()->GetMsgCallback()
		(
			XFmt::Fmt("[XPlatform][Net]:Failed to find extension: '%s'!",
			XPLATFORM_NET_EXT_NAME
		).c_str(),
			XPlatform::Api::XPResult::XPLATFORM_RESULT_FAILED,
		0);

		return XPlatform::Api::XPResult::XPLATFORM_RESULT_FAILED;
	}

#ifdef WIN32
	WSAData WsData{};
	int Res = WSAStartup(MAKEWORD(2, 1), &WsData);
	assert(Res == 0);
	if (Res != 0) {
		XPlatform::core::Engine::GetInstance()->GetMsgCallback()
		(
			"Failed to initialize WinSock 2.0",
			XPlatform::Api::XPResult::XPLATFORM_RESULT_FAILED,
			0);

		return XPlatform::Api::XPResult::XPLATFORM_RESULT_FAILED;
	}

#endif

	if(SSL_load_error_strings() == 0) return XPlatform::Api::XPResult::XPLATFORM_RESULT_FAILED;
	if(SSL_library_init() == 0) return XPlatform::Api::XPResult::XPLATFORM_RESULT_FAILED;
	if (OpenSSL_add_all_algorithms() == 0)return XPlatform::Api::XPResult::XPLATFORM_RESULT_FAILED;

	return XPlatform::Api::XPResult::XPLATFORM_RESULT_SUCCESS;
}

XP_NET_API void* xplatform_ext_create_class(uint32_t Id) {
	switch (Id){
	case XPLATFORM_EXT_NET_CLASS_ID_TCP_SOCKET:
		return reinterpret_cast<void*>(new XPlatform::Net::TCPSocket);
	case XPLATFORM_EXT_NET_CLASS_ID_TCP_SOCKETv6:
		return reinterpret_cast<void*>(new XPlatform::Net::TCPSocketv6);
	case XPLATFORM_EXT_NET_CLASS_ID_UDP_SOCKET:
		return reinterpret_cast<void*>(new XPlatform::Net::UDPSocket);
	case XPLATFORM_EXT_NET_CLASS_ID_UDP_SOCKETv6:
		return reinterpret_cast<void*>(new XPlatform::Net::UDPSocketv6);
	}

	return NULL;
}

template<class t_class>
void delete_class(void* obj) {
	delete reinterpret_cast<t_class*>(obj);
}

XP_NET_API void xplatform_ext_delete_class(uint32_t Id, void* ptr) {
	assert(ptr != NULL);
	switch (Id){
	case XPLATFORM_EXT_NET_CLASS_ID_TCP_SOCKET:
		delete_class<XPlatform::Net::TCPSocket>(ptr);
		break;
	case XPLATFORM_EXT_NET_CLASS_ID_TCP_SOCKETv6:
		delete_class<XPlatform::Net::TCPSocketv6>(ptr);
		break;
	case XPLATFORM_EXT_NET_CLASS_ID_UDP_SOCKET:
		delete_class<XPlatform::Net::UDPSocket>(ptr);
		break;
	case XPLATFORM_EXT_NET_CLASS_ID_UDP_SOCKETv6:
		delete_class<XPlatform::Net::TCPSocketv6>(ptr);
		break;
	default:
		assert(Id != Id && "required delete class id dont found!");
		break;
	}
}

XP_NET_API const std::string& xplatform_resolve_hostname_to_ip(const std::string& host) {
	hostent* hostname = gethostbyname(host.c_str());
	if (hostname)
		return std::string(inet_ntoa(**(in_addr**)hostname->h_addr_list));
	return {};
}

XP_NET_API void xplatform_extension_shutdown() {
#ifdef WIN32
	WSACleanup();
#endif
}