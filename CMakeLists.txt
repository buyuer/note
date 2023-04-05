cmake_minimum_required(VERSION 3.21)
project(note)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output/lib)

include(cmake/utils.cmake)

add_subdirectory(c)
add_subdirectory(cpp)
add_subdirectory(boost)
add_subdirectory(qt)
add_subdirectory(libuv)
add_subdirectory(opencv)
add_subdirectory(python)

add_subdirectory(unix)
add_subdirectory(win)
add_subdirectory(linux)
add_subdirectory(darwin)
add_subdirectory(android)
