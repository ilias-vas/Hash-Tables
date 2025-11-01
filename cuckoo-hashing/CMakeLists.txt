cmake_minimum_required(VERSION 3.10)
project(MyProjectTests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests main.cpp cuckooTable.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES} pthread)

add_test(NAME MyTests COMMAND tests)
