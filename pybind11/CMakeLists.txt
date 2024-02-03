# Date      2022.02.01
# Author    dingddding@163.com
# Bref      The CMakeLists.txt

cmake_minimum_required(VERSION 3.21)
find_package(pybind11 QUIET)
if (NOT pybind11_FOUND)
    return()
endif ()

project(note-pybind11 LANGUAGES C CXX)
