#ifndef _XPLATFORM_NET_H
#define _XPLATFORM_NET_H

#define XPLATFORM_NET_EXT_NAME "XPLATFORM_EXT_NET"

#include <XPlatform.core/api.h>
#include <string>

namespace XPlatform {
	namespace Net {
		enum class XPlatformNetResult : XPlatform::Api::u8 {
			XPLATFORM_NET_RESULT_SELECT_SUCCESS,
			XPLATFORM_NET_RESULT_SUCCESS,
			XPLATFORM_NET_RESULT_FAILED,
			XPLATFORM_NET_RESULT_SELECT_FAILED,
			XPLATFORM_NET_RESULT_FAILED_TO_BIND_SOCKET_TO_ADDRESS,
			XPLATFORM_NET_RESULT_FAILED_TO_CONNECT_TO_ADDRESS,
			XPLATFORM_NET_RESULT_FAILED_TO_LISTEN_SOCKET			
		};

		constexpr char* XPlatformNetResolveHostnameToIP = "xplatform_resolve_hostname_to_ip";
		typedef const std::string&(*pfn_XPlatformNetResolveHostnameToIP)(const std::string& host);
	}
}

#endif