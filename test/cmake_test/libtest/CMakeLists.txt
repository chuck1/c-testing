cmake_minimum_required (VERSION 2.6) 

project(libtest)

include_directories(./)

add_library(libtest test.cpp)

option(__DEBUG "debugging output" ON)

configure_file("config.h.in" "config.h")

