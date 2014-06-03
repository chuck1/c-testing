CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

add_executable(test1 main.cpp)

ADD_DEFINITIONS("-DBOOST_ALL_DYN_LINK")

#SET(Boost_USE_STATIC_LIBS ON)


FIND_PACKAGE(
	Boost 1.55
	COMPONENTS log system thread
	REQUIRED)



MESSAGE(STATUS "boost: ${Boost_LIBRARIES}")

SET(libs ${libs}
	${Boost_LIBRARIES}
	pthread
	rt
	)

#SET(libs ${libs} ${Boost_PROGRAM_OPTIONS_LIBRARY})


SET(libs ${libs} ${libs})

#MESSAGE(STATUS "libs: ${libs}")
#message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
#message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-use-linker-plugin")

target_link_libraries(test1 ${libs})


