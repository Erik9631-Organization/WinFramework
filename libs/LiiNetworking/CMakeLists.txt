cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 17)
project(LiiNetworking)
set(platform win32)

add_subdirectory(src)
target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)