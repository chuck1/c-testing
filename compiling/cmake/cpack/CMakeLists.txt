cmake_minimum_required(VERSION 2.6)
 
PROJECT(DistanceBetweenPoints)
 
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})
 
ADD_EXECUTABLE(DistanceBetweenPoints DistanceBetweenPoints.cxx)
INSTALL(TARGETS DistanceBetweenPoints DESTINATION distance)
 
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "David Doria") #required
 
INCLUDE(CPack)
