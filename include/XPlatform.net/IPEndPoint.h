#ifndef _INC_XPLATFORM_IP_ENDPOINT_H
#define _INC_XPLATFORM_IP_ENDPOINT_H


#include <cstring>
#include <string>

#if defined(WIN32)
#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
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

struct sockaddr_in;
struct sockaddr_in6;

namespace XPlatform {
	namespace Net {
		class g_IPEndPoint {
		public:

			virtual uint16_t GetPort() const = 0;
			virtual const char* GetIP() const = 0;

		};

		class IPEndPoint : public g_IPEndPoint {

			std::string IP;
			uint16_t Port;

			sockaddr_in addr{};

		public:

			inline IPEndPoint() : IP("127.0.0.1"), Port(1) {

			}

			inline IPEndPoint(const IPEndPoint& _This) : IP(_This.IP), Port(_This.Port) {
				addr.sin_port = htons(Port);
				addr.sin_family = AF_INET;
				addr.sin_addr.s_addr = inet_addr(IP.c_str());
			}

			inline IPEndPoint(const uint16_t Port) : IP(""), Port(Port) {
				addr.sin_port = htons(Port);
				addr.sin_family = AF_INET;
				addr.sin_addr.s_addr = INADDR_ANY;
			}

			inline IPEndPoint(const std::string& IP, const uint16_t Port) : IP(IP), Port(Port) {
				addr.sin_port = htons(Port);
				addr.sin_family = AF_INET;
				addr.sin_addr.s_addr = inet_addr(IP.c_str());
			}

			inline IPEndPoint(sockaddr_in& addr) : addr(addr), IP(inet_ntoa(addr.sin_addr)), Port(htons(addr.sin_port)) {
			}

			inline IPEndPoint(struct in_addr& _addr, const uint16_t Port) : Port(Port), IP(inet_ntoa(_addr)) {
				addr.sin_port = htons(Port);
				addr.sin_family = AF_INET;
				addr.sin_addr = _addr;
			}

			inline const char* GetIP() const {
				return IP.c_str();
			}

			inline void operator=(const XPlatform::Net::IPEndPoint& _This) {
				IP = _This.IP;
				Port = _This.Port;
				addr = _This.addr;
			}

			inline uint16_t GetPort() const {
				return Port;
			}

			inline const sockaddr_in* GetAddr() const {
				return &addr;
			}

			inline ~IPEndPoint() {

			}

		};
		class IPEndPoint6 : public g_IPEndPoint {

			std::string IP;
			uint16_t Port;

			sockaddr_in6 addr{};

		public:
			inline IPEndPoint6() : IP("127.0.0.1"), Port(1) {

			}

			inline IPEndPoint6(const XPlatform::Net::IPEndPoint6& _This) : IP(_This.IP), Port(_This.Port) {
				addr.sin6_port = htons(Port);
				addr.sin6_family = AF_INET6;
				inet_pton(AF_INET6, IP.c_str(), &addr.sin6_addr);
			}

			inline IPEndPoint6(const uint16_t Port) : IP(NULL), Port(Port) {
				addr.sin6_port = htons(Port);
				addr.sin6_family = AF_INET6;
				addr.sin6_addr = in6addr_any;
			}

			inline IPEndPoint6(const std::string& IP, const uint16_t Port) : IP(IP), Port(Port) {
				addr.sin6_port = htons(Port);
				addr.sin6_family = AF_INET6;
				inet_pton(AF_INET6, IP.c_str(), &addr.sin6_addr);
			}

			inline IPEndPoint6(sockaddr_in6& addr) : addr(addr), Port(htons(addr.sin6_port)) {
				char TmpStr[INET6_ADDRSTRLEN];
                std::memset(TmpStr, 0, INET6_ADDRSTRLEN);
				inet_ntop(AF_INET6, (const void*)&addr.sin6_addr, TmpStr, INET6_ADDRSTRLEN);

				IP = TmpStr;
			}

			inline IPEndPoint6(sockaddr_in6* addr) : addr(*addr), Port(htons(addr->sin6_port)) {
				char TmpStr[INET6_ADDRSTRLEN];
                std::memset(TmpStr, 0, INET6_ADDRSTRLEN);
				inet_ntop(AF_INET6, (const void*)&addr->sin6_addr, TmpStr, INET6_ADDRSTRLEN);

				IP = TmpStr;
			}

			inline const char* GetIP() const {
				return IP.c_str();
			}

			inline uint16_t GetPort() const {
				return Port;
			}

			inline const sockaddr_in6* GetAddr() const {
				return &addr;
			}

			inline void operator=(const XPlatform::Net::IPEndPoint6& _This) {
				IP = _This.IP;
				Port = _This.Port;
				addr = _This.addr;
			}

		};
	}
}

#endif
