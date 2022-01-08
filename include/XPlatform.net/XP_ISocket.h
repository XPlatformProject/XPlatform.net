#ifndef _INC_XPLATFORM_SOCKET_INTERFACE_H
#define _INC_XPLATFORM_SOCKET_INTERFACE_H

#include<XPlatform.core/api.h>
#include<XPlatform.net/IPEndPoint.h>

#include<XPlatform.core/XP_IObject.h>

#include<XPlatform.net/Net.h>

#define XPLATFORM_EXT_NET_CLASS_ID_TCP_SOCKET 0x0001
#define XPLATFORM_EXT_NET_CLASS_ID_TCP_SOCKETv6 0x0002

namespace XPlatform {
	namespace Net {
		class XP_ISocket : public XPlatform::core::XPlatformCrossModuleObject {
		public:
			virtual XPlatform::Net::XPlatformNetResult Listen
			(const XPlatform::Net::g_IPEndPoint& g_EndPoint) = 0;

			virtual XPlatform::Net::XPlatformNetResult Connect
			(const XPlatform::Net::g_IPEndPoint& g_EndPoint) = 0;

			virtual XPlatform::Net::XP_ISocket* Accept() = 0;
			virtual XPlatform::Net::XPlatformNetResult Select(uint32_t msecs) = 0;
			
			virtual uint32_t Send(const char* Buf, int Len) = 0;
			virtual uint32_t Recv(char* Buf, int Len) = 0;

			virtual void Close() = 0;

			virtual const XPlatform::Net::g_IPEndPoint& GetEndPoint() const = 0;

			virtual void Release() = 0;
		};
	}
}

#endif