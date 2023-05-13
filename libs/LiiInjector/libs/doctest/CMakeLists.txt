cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
project(doctest CXX)
set(ALL_FILES
        doctest.h
)
add_library(${PROJECT_NAME} INTERFACE ${ALL_FILES})
target_include_directories(${PROJECT_NAME} INTERFACE .)