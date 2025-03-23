cmake_minimum_required(VERSION 3.30)
project(SystemyOperacyjne)

set(CMAKE_CXX_STANDARD 20)

add_executable(SystemyOperacyjne main.cpp
        Philosopher.cpp
        Philosopher.h)

target_compile_options(SystemyOperacyjne PRIVATE -fmodules-ts)