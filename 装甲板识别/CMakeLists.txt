cmake_minimum_required(VERSION 3.10)

project(cv_test)

find_package(OpenCV REQUIRED)
aux_source_directory(src DT_LIBS)
set(CMAKE_CXX_STANDARD 14)
add_library(detect ${DT_LIBS})
target_include_directories(detect PUBLIC include)
target_link_libraries(detect ${OpenCV_LIBS})
add_executable(cv_test main.cpp)

target_include_directories(cv_test PUBLIC ${OpenCV_INCLUDE_DIRS})

target_link_libraries(cv_test ${OpenCV_LIBS} detect)
