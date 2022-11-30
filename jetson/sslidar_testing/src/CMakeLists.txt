cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall -O3")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 14)
FIND_LIBRARY(MY_LIB NAMES HPS3DSDK64_1-8-5 PATHS ./)
set(SSLIDAR_LIBRARIES "-lpthread")

project(playback)

find_package(PCL 1.12 REQUIRED COMPONENTS common io visualization)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
#list(REMOVE_ITEM PCL_LIBRARIES "vtkproj4")


add_executable (main main.cpp environment.cpp render.cpp processPointClouds.cpp)
target_link_libraries (main ${PCL_LIBRARIES} ${SSLIDAR_LIBRARIES} ${MY_LIB})
