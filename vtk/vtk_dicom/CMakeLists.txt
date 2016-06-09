cmake_minimum_required(VERSION 2.8)
PROJECT(vtk_dicom)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
add_executable(vtk_dicom vtk_dicom.cpp)
target_link_libraries(vtk_dicom ${VTK_LIBRARIES})

