cmake_minimum_required(VERSION 2.8)
 
PROJECT(SmartVolumeMapper)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SmartVolumeMapper MACOSX_BUNDLE main.cpp)
 
if(VTK_LIBRARIES)
  target_link_libraries(SmartVolumeMapper ${VTK_LIBRARIES})
else()
  target_link_libraries(SmartVolumeMapper vtkHybrid vtkWidgets)
endif()
