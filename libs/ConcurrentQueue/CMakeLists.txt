cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
project(ConcurrentQueue CXX)
set(ALL_FILES
        blockingconcurrentqueue.h
        concurrentqueue.h
        lightweightsemaphore.h
)

add_library(${PROJECT_NAME} INTERFACE ${ALL_FILES})
target_include_directories(${PROJECT_NAME} INTERFACE ${ALL_FILES})