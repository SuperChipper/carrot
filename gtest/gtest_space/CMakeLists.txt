cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
find_package(OpenCV REQUIRED)
aux_source_directory(src TEST_SRC)
add_library(src_t ${TEST_SRC})
target_include_directories(src_t PUBLIC include)
target_link_libraries(src_t ${OpenCV_LIBS})

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
  hello_test
  hello_test.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
  src_t
)

include(GoogleTest)
gtest_discover_tests(hello_test)