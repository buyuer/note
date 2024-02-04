cmake_minimum_required(VERSION 3.21)
project(note)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/run)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/arc)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

include(cmake/utils.cmake)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    if (CMAKE_C_COMPILER_ID STREQUAL GCC OR CMAKE_C_COMPILER_ID STREQUAL Clang)
        set(CMAKE_C_FLAGS "-fsanitize=address -fsanitize=leak ${CMAKE_CXX_FLAGS}")
    endif ()
    if (CMAKE_CXX_COMPILER_ID STREQUAL GCC OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)
        set(CMAKE_CXX_FLAGS "-fsanitize=address -fsanitize=leak ${CMAKE_CXX_FLAGS}")
    endif ()
endif ()

file(GLOB SUBPATHS ${CMAKE_SOURCE_DIR}/*)

foreach (SUBPATH ${SUBPATHS})
    if (IS_DIRECTORY ${SUBPATH} AND EXISTS ${SUBPATH}/CMakeLists.txt)
        message("-> subdirectory: ${SUBPATH}")
        add_subdirectory(${SUBPATH})
    endif ()
endforeach ()
