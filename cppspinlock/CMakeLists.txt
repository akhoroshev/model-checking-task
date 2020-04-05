cmake_minimum_required(VERSION 3.10)
project(cppspinlock)

set(CMAKE_CXX_STANDARD 17)

add_library(cppspinlock spinlock.cpp)

enable_testing()
add_executable(tests tests.cpp)
target_link_libraries(tests cppspinlock pthread)

add_test(NAME tests COMMAND tests)