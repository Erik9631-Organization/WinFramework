cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
project(catch2Lib CXX)
set(ALL_FILES
        catch_amalgamated.hpp
        catch_amalgamated.cpp
)
ADD_DEFINITIONS(-DCATCH_AMALGAMATED_CUSTOM_MAIN)

add_library(catch2Lib ${ALL_FILES})
target_include_directories(catch2Lib PUBLIC .)