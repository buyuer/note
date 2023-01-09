cmake_minimum_required(VERSION 3.21)
project(note)

include(cmake/utils.cmake)

add_subdirectory(c)
add_subdirectory(cpp)
add_subdirectory(boost)
add_subdirectory(qt)
add_subdirectory(libuv)
add_subdirectory(opencv)

add_subdirectory(unix)
add_subdirectory(win)
add_subdirectory(linux)
add_subdirectory(darwin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
