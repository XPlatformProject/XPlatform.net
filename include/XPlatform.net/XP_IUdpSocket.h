#ifndef _INC_XPLATFORM_UDP_SOCKET_H
#define _INC_XPLATFORM_UDP_SOCKET_H

#include<XPlatform.net/IPEndPoint.h>
#include<XPlatform.core/api.h>
#include<XPlatform.core/XP_IObject.h>

#define XPLATFORM_EXT_NET_CLASS_ID_UDP_SOCKET 0x0003
#define XPLATFORM_EXT_NET_CLASS_ID_UDP_SOCKETv6 0x0004

namespace XPlatform {
	namespace Net {
		class XP_IUdpSocket : public XPlatform::core::XPlatformCrossModuleObject {
		public:
			
			virtual XPlatform::Api::XPResult Bind
			(const XPlatform::Net::g_IPEndPoint& IPEndPoint) = 0;

			virtual XPlatform::Api::XPResult CreateSocket() = 0;

			virtual uint32_t SendTo(
				const char* buf,
				int len,
				const XPlatform::Net::g_IPEndPoint& IPEndPoint
				) = 0;

			virtual uint32_t RecvFrom(
				char* buf,
				int len,
				XPlatform::Net::g_IPEndPoint& IPEndPoint
			) = 0;

			virtual void Close() = 0;

			virtual uint32_t Select(uint32_t msecs) = 0;

			virtual void Release() = 0;
		};
	}
}

#endif