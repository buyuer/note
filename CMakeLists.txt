cmake_minimum_required(VERSION 3.21)
project(note)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output/lib)

include(cmake/utils.cmake)

file(GLOB SUBPATHS ${CMAKE_SOURCE_DIR}/*)

foreach (SUBPATH ${SUBPATHS})
    if (IS_DIRECTORY ${SUBPATH} AND EXISTS ${SUBPATH}/CMakeLists.txt)
        message("-> subdirectory: ${SUBPATH}")
        add_subdirectory(${SUBPATH})
    endif ()
endforeach ()
