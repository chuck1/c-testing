CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

FIND_PACKAGE(CMakeHelper)

FIND_PACKAGE(Boost 1.55 COMPONENTS program_options)
SET(libs ${libs} ${Boost_LIBRARIES})


link_exe()


