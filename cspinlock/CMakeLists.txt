cmake_minimum_required(VERSION 3.10)
project(cspinlock C)

set(CMAKE_C_STANDARD 11)

add_executable(main main.c)
target_link_libraries(main pthread)
