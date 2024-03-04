# Date      2022.02.01
# Author    dingddding@163.com
# Bref      The CMakeLists.txt

cmake_minimum_required(VERSION 3.21)
find_package(Qt6 QUIET
        COMPONENTS
        Core Gui Network Widgets)

if (NOT Qt6_FOUND)
    return()
endif ()

project(note-qt LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

note_generate_target(./ qt TARGETS)

foreach (TARGET ${TARGETS})
    target_link_libraries(${TARGET} PRIVATE Qt6::Core Qt6::Gui Qt6::Network)
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
