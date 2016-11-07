cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project(cfgpath-pp)

add_executable(cfgpath-test test.cpp cfgpath.hpp cfgpath.cpp)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT cfgpath-test)
