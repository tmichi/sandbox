cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(vtkusg)
set(CMAKE_MODULE_PATH /usr/local/Cellar/vtk/6.3.0/lib/cmake/vtk-6.3)
find_package(VTK 6.3 REQUIRED)

include_directories(${VTK_INCLUDE_DIRS})
link_directories(${VTK_LIBRARY_DIRS})
#add_definitions(${VTK_DEFINITIONS})
add_executable (vtkusg main.cpp)
target_link_libraries (vtkusg ${VTK_LIBRARIES})




