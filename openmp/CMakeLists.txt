# Date      2022.02.01
# Author    dingddding@163.com
# Bref      The CMakeLists.txt

cmake_minimum_required(VERSION 3.21)
find_package(OpenMP QUIET)

if (NOT OpenMP_FOUND)
    return()
endif ()

project(note-openmp LANGUAGES C CXX)

note_generate_target(./ openmp TARGETS)

foreach (TARGET ${TARGETS})
    target_link_libraries(${TARGET} PRIVATE OpenMP::OpenMP_CXX)
    target_compile_options(${TARGET} PRIVATE ${OpenMP_CXX_FLAGS})
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
