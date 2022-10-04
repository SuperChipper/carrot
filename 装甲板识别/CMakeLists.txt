cmake_minimum_required(VERSION 3.10)

project(cv_test)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(cv_test main.cpp src/Detect.cpp)

target_include_directories(cv_test PUBLIC ${OpenCV_INCLUDE_DIRS} include)

target_link_libraries(cv_test ${OpenCV_LIBS})
