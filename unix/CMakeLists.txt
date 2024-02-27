# Date      2022.02.01
# Author    dingddding@163.com
# Bref      The CMakeLists.txt

cmake_minimum_required(VERSION 3.25)
if (NOT UNIX)
    return()
endif ()

project(note-unix LANGUAGES C CXX)

note_generate_target(./ unix TARGETS)

find_package(Threads)

foreach (TARGET ${TARGETS})
    if (LINUX)
        target_link_libraries(${TARGET} PRIVATE dl)
    endif ()

    target_link_libraries(${TARGET} Threads::Threads)
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
