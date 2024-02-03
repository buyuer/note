# Date      2022.02.01
# Author    dingddding@163.com
# Bref      The CMakeLists.txt

cmake_minimum_required(VERSION 3.21)
find_package(Qt5 COMPONENTS Core Gui QUIET)

if (NOT Qt5_FOUND)
    return()
endif ()

project(note-qt LANGUAGES CXX)
