# Date      2022.02.01
# Author    dingddding@163.com
# Bref      The CMakeLists.txt

cmake_minimum_required(VERSION 3.21)
if (NOT WIN32)
    return()
endif ()

project(note-win LANGUAGES C CXX)

note_generate_target(./ win TARGETS)

find_package(Threads)

foreach (TARGET ${TARGETS})
    target_link_libraries(${TARGET} Threads::Threads)
    target_link_options(${TARGET} PRIVATE "/SUBSYSTEM:WINDOWS")
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
