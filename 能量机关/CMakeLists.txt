cmake_minimum_required(VERSION 3.1)

project(windmill-detect)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
add_executable(windmill_detect main.cpp)
add_library(detect OBJECT src/WindmillDetect.cpp src/Kalmanfilter.cpp)
target_include_directories(detect PUBLIC include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(windmill_detect ${OpenCV_LIBS} detect)
