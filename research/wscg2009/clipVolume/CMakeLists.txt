cmake_minimum_required(VERSION 3.3)
find_package( PkgConfig )
pkg_check_modules( EIGEN3 REQUIRED eigen3 )
include_directories( ${EIGEN3_INCLUDE_DIRS} /usr/local/include )
if(APPLE)
	INCLUDE_DIRECTORIES(include)
	set(CMAKE_MACOSX_RPATH 1)
	ADD_DEFINITIONS(-g -O3 -Wall -std=c++11)
endif(APPLE)
ADD_EXECUTABLE(clip main.cpp)
TARGET_LINK_LIBRARIES(clip mibase mivol mivolut)






