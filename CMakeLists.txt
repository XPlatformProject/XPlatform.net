cmake_minimum_required(VERSION 3.10)

project("XPlatform.net")

add_subdirectory("ThirdParty")

add_library("XPlatform.net" SHARED 
"src/ext_main.cpp" "src/net.h"
"include/XPlatform.net/IPEndPoint.h"
"include/XPlatform.net/XP_ISocket.h"
"src/Sockets/TCPSocket/TCPSocket.h" 
"src/Sockets/TCPSocket/TCPSocket.cpp"
"src/Sockets/TCPSocketv6/TCPSocketv6.h"
"src/Sockets/TCPSocketv6/TCPSocketv6.cpp"
"include/XPlatform.net/XP_IUdpSocket.h"
"src/Sockets/UDPSocket/UDPSocket.h"
"src/Sockets/UDPSocket/UDPSocket.cpp"
"src/Sockets/UDPSocket6/UDPSocketv6.cpp"
"src/Sockets/UDPSocket6/UDPSocket6.h" )

add_library("XPlatform.net-headers" INTERFACE)
target_include_directories("XPlatform.net-headers" INTERFACE "include/")

if(win32)
target_link_libraries("XPlatform.net-headers" INTERFACE wsock32 ws2_32)
endif(win32)

target_include_directories("XPlatform.net" PRIVATE "include/")
target_link_libraries("XPlatform.net" PRIVATE ssl XPlatform.core XFmt)

