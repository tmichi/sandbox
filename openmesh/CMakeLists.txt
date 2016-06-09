cmake_minimum_required(VERSION 3.0)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable (omtest openmesh0.cpp)
target_link_libraries (omtest
  OpenMeshCore
  OpenMeshTools
)

