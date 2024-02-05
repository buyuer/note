# Date      2022.02.01
# Author    dingddding@163.com
# Bref      The CMakeLists.txt

cmake_minimum_required(VERSION 3.21)
find_package(Qt6 COMPONENTS Core Gui QUIET)

if (NOT Qt6_FOUND)
    return()
endif ()

project(note-qt LANGUAGES CXX)

note_generate_target(./ qt TARGETS)

foreach (TARGET ${TARGETS})
    target_link_libraries(${TARGET} PRIVATE Qt6::Core)
    set_target_properties(
            ${TARGET}
            PROPERTIES
            C_STANDARD 11
            C_EXTENSIONS OFF
            C_STANDARD_REQUIRED ON
            CXX_STANDARD 23
            CXX_EXTENSIONS OFF
            CXX_STANDARD_REQUIRED OFF
    )
endforeach ()
