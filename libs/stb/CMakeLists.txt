cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME stb)


project(${PROJECT_NAME} CXX)
set(stb_image
    stb_image.cpp
    stb_image.h
    stb_image_resize.h
    stb_image_resize.cpp
        )




source_group(stb_image FILES ${stb_image})
add_library(${PROJECT_NAME} STATIC ${stb_image})