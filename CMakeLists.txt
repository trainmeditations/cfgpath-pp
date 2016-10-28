cmake_minimum_required(VERSION 3.5.2 FATAL_ERROR)
project(cfgpath-pp)

add_executable(cfgpath-test test.cpp cfgpath.hpp cfgpath.cpp)