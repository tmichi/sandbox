cmake_minimum_required(VERSION 3.3)
find_package( PkgConfig )
pkg_check_modules( EIGEN3 REQUIRED eigen3 )
include_directories( ${EIGEN3_INCLUDE_DIRS} )
if(APPLE)
	INCLUDE_DIRECTORIES(include)
	set(CMAKE_MACOSX_RPATH 1)
	ADD_DEFINITIONS(-g -O3 -Wall)
endif(APPLE)

ADD_EXECUTABLE(intersect intersect_main.cpp IntersectCommand.hpp IntersectCommand.cpp)
TARGET_LINK_LIBRARIES(intersect mibase mivol)
ADD_EXECUTABLE(iso2d iso2d_main.cpp Iso2dCommand.hpp Iso2dCommand.cpp)
TARGET_LINK_LIBRARIES(iso2d mibase mivol)

ADD_EXECUTABLE(dem dem_main.cpp)
TARGET_LINK_LIBRARIES(dem mibase mivol)






