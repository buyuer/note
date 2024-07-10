# Date      2022.02.01
# Author    dingddding@163.com
# Bref      The CMakeLists.txt

cmake_minimum_required(VERSION 3.21)
project(note-algo LANGUAGES C CXX)

note_generate_target(./ algo TARGETS)

foreach (TARGET ${TARGETS})
    set_target_properties(
            ${TARGET}
            PROPERTIES
            C_STANDARD 23
            C_EXTENSIONS OFF
            C_STANDARD_REQUIRED ON
    )
endforeach ()