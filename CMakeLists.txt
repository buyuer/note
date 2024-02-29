cmake_minimum_required(VERSION 3.21)
project(note)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/run)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/arc)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(utils)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    if (CMAKE_C_COMPILER_ID STREQUAL GCC OR CMAKE_C_COMPILER_ID STREQUAL Clang)
        set(CMAKE_C_FLAGS "-fsanitize=address -fsanitize=leak ${CMAKE_C_FLAGS}")
    endif ()
    if (CMAKE_CXX_COMPILER_ID STREQUAL GCC OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)
        set(CMAKE_CXX_FLAGS "-fsanitize=address -fsanitize=leak ${CMAKE_CXX_FLAGS}")
    endif ()
endif ()

if (CMAKE_C_COMPILER_ID STREQUAL GCC OR CMAKE_C_COMPILER_ID STREQUAL Clang)
    add_compile_options(-Werror)
elseif (MSVC)
    add_compile_options(/WX)
endif ()

get_build_info(NOTE_BUILD_INFO)
message("-> build info: ${NOTE_BUILD_INFO}")
add_compile_definitions(BUILD_INFO=\"${NOTE_BUILD_INFO}\")

get_subdir(SUBPATHS ${CMAKE_SOURCE_DIR})
foreach (SUBPATH ${SUBPATHS})
    message("-> subdirectory: ${SUBPATH}")
    add_subdirectory(${SUBPATH})
endforeach ()
