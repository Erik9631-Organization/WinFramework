cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
project(MemoryManagerLib CXX)

add_library(MemoryManagerLib INTERFACE)
target_include_directories(MemoryManagerLib INTERFACE
        Api
        MemoryManager
        )