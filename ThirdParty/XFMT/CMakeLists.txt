cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(XFmt)

add_library(XFmt "src/XFmt.cpp" "src/Utils/Utils.cpp" "src/Utils/Utils.h" "include/XFmt/XFmt.h")

target_include_directories(XFmt PUBLIC "include/")