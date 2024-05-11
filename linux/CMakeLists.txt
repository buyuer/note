# Date      2022.02.01
# Author    dingddding@163.com
# Bref      The CMakeLists.txt

cmake_minimum_required(VERSION 3.21)
if (NOT CMAKE_SYSTEM_NAME MATCHES "Linux")
    return()
endif ()

project(note-linux LANGUAGES C CXX)

note_generate_target(./ linux TARGETS)

find_library(LIBAIO NAMES aio libaio NO_CACHE)
find_library(LIBURING NAMES uring liburing NO_CACHE)

foreach (TARGET ${TARGETS})
    set_target_properties(
            ${TARGET}
            PROPERTIES
            C_STANDARD 11
            # C_EXTENSIONS OFF
            C_STANDARD_REQUIRED ON
            CXX_STANDARD 23
            CXX_EXTENSIONS OFF
            CXX_STANDARD_REQUIRED OFF
    )
    if (NOT LIBAIO STREQUAL "LIBAIO_NOTFOUND")
        target_link_libraries(${TARGET} PRIVATE ${LIBAIO})
    endif ()
    if (NOT LIBURING STREQUAL "LIBAIO_NOTFOUND")
        target_link_libraries(${TARGET} PRIVATE ${LIBURING})
    endif ()
endforeach ()

add_library(runso SHARED others/runso.c)
