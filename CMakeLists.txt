cmake_minimum_required(VERSION 3.17)
project(note)

add_subdirectory(c)
add_subdirectory(cpp)
add_subdirectory(boost)
add_subdirectory(qt)
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

set_target_properties(
        note
        PROPERTIES
        C_STANDARD 11
        C_EXTENSIONS OFF
        C_STANDARD_REQUIRED ON
        CXX_STANDARD 23
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED OFF
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
