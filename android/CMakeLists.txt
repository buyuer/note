# Date      2022.02.01
# Author    dingddding@163.com
# Bref      The CMakeLists.txt

cmake_minimum_required(VERSION 3.21)
if (NOT ANDROID)
    return()
endif ()

project(note-android LANGUAGES C CXX)

add_library(note SHARED)

target_sources(note PRIVATE note.cpp)

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
