cmake_minimum_required(VERSION 3.27)
project (rot_img)
set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(rot_img rot_img.cpp)
target_link_libraries(rot_img ${OpenCV_LIBS})
