cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD 17)
project(Lii CXX)
#Options
option(windows "Use windows platform" OFF)
option(linux "Use windows platform" OFF)
message("Windows option: ${windows}")

#Compile definitions
IF(windows)
	add_compile_definitions(windows)
endif()


#GetThe output dir
if(DEFINED RUNTIME_OUTPUT_DIRECTORY)
	set(outputDir "${RUNTIME_OUTPUT_DIRECTORY}/src")
else()
	set(outputDir "${CMAKE_BINARY_DIR}/src")
endif()
message("Runtime directory is: ${outputDir}")

#Global libs that need to be compiled / included
add_subdirectory(libs/stb EXCLUDE_FROM_ALL)
add_subdirectory(libs/PhysX-4.1/physx/compiler/public EXCLUDE_FROM_ALL)
add_subdirectory(libs/ConcurrentQueue)
include_directories(libs/ConcurrentQueue)
add_subdirectory(libs/MemoryManager)
add_subdirectory(libs/catch2)
include_directories(libs/catch2)
add_subdirectory(src)


#File installations
message("current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/Shaders" DESTINATION "${outputDir}")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Resources/Textures" DESTINATION "${outputDir}")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/glew32.dll" DESTINATION ${outputDir})
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/libs/PhysX-4.1/physx/bin/${CMAKE_BUILD_TYPE}/" DESTINATION ${outputDir} FILES_MATCHING PATTERN "*.dll")