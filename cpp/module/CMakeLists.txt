cmake_minimum_required(VERSION 3.28)

project(cpp_module LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Test main.cpp)
target_sources(Test PUBLIC Test.cxx)
target_sources(Test PUBLIC FILE_SET all_modules TYPE CXX_MODULES FILES
        Test.ixx
        Test-First.ixx)