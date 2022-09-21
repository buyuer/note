cmake_minimum_required(VERSION 3.17)
project(note)

add_subdirectory(c)
add_subdirectory(cpp)
add_subdirectory(libuv)

if (UNIX)
    add_subdirectory(unix)
endif ()

if (WIN32)
    add_subdirectory(win)
endif ()

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_subdirectory(linux)
endif ()

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    add_subdirectory(darwin)
endif ()

add_executable(note main.cpp)
