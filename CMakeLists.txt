cmake_minimum_required( VERSION 3.0 )
if( 1 )
  set( CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake" )
  set( OpenCV_DIR )
  if( NOT CMAKE_CL_64 )
    set( OpenCV_DIR "C:/dev/vcpkg/installed/x86-windows/share/opencv" )
  else()
    set( OpenCV_DIR "C:/dev/vcpkg/installed/x64-windows/share/opencv" )
  endif()

endif()

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(playback)

find_package(OpenCV 4.1 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

# Executable for create matrix exercise
add_executable (camera_calibration src/main.cpp)
target_link_libraries (camera_calibration ${OpenCV_LIBRARIES})