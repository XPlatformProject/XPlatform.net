cmake_minimum_required(VERSION 3.10)

project("XPlatform.net")

add_subdirectory("ThirdParty")

add_library("XPlatform.net" SHARED 
"src/ext_main.cpp" "src/net.h"
"include/XPlatform.net/IPEndPoint.h"
"include/XPlatform.net/XP_ISocket.h"
"src/SSL/Sockets/TCPSocketv6/TCPSocketv6.h" 
"src/Sockets/TCPSocket/TCPSocket.cpp"
"src/Sockets/TCPSocketv6/TCPSocketv6.h"
"src/Sockets/TCPSocketv6/TCPSocketv6.cpp"
"include/XPlatform.net/XP_IUdpSocket.h"
"src/Sockets/UDPSocket/UDPSocket.h"
"src/Sockets/UDPSocket/UDPSocket.cpp"
"src/Sockets/UDPSocket6/UDPSocketv6.cpp"
"src/Sockets/UDPSocket6/UDPSocketv6.h"
"include/XPlatform.net/SSL/SSL.h"
"src/SSL/SSLCtx/SSLCtx.h" "src/SSL/SSLCtx/SSLCtx.cpp"
"src/SSL/Sockets/TCPSocket/TCPSocket.h" "src/SSL/Sockets/TCPSocket/TCPSocket.cpp"
"src/SSL/LLApi.cpp"
"src/SSL/Sockets/TCPSocketv6/TCPSocketv6.cpp" "src/SSL/Sockets/TCPSocketv6/TCPSocketv6.h")

add_library("XPlatform.net-headers" INTERFACE)
target_include_directories("XPlatform.net-headers" INTERFACE "include/")

if(win32)
target_link_libraries("XPlatform.net-headers" INTERFACE wsock32 ws2_32)
endif(win32)

target_include_directories("XPlatform.net" PRIVATE "include/")
target_link_libraries("XPlatform.net" PRIVATE ssl XPlatform.core XFmt)

if(UNIX)
  message("-- [xplatform]: Compiling with -fpic")
  target_compile_options("XPlatform.net" PUBLIC -fpic)
  target_compile_options(ssl PUBLIC -fpic)
  target_compile_options(crypto PUBLIC -fpic)
endif(UNIX)
