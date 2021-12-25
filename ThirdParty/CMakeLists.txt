cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("ThirdParty")

set(WITH_APPS OFF)
add_subdirectory(openssl)
add_subdirectory(XFMT)