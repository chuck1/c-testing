cmake_minimum_required (VERSION 2.8.7) 

project(test)

include_directories(./ ../libtest)
link_directories(../libtest)

add_executable(test main.cpp)

target_link_libraries(test libtest)

option(__DEBUG "debugging output" ON)

configure_file("config.h.in" "config.h")

