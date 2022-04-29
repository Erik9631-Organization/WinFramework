cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD 17)
project(Lii CXX)



#GetThe output dir
if(DEFINED RUNTIME_OUTPUT_DIRECTORY)
	set(outputDir "${RUNTIME_OUTPUT_DIRECTORY}/src")
else()
	set(outputDir "${CMAKE_BINARY_DIR}/src")
endif()
message("Runtime directory is: ${outputDir}")

add_subdirectory(libs/stb EXCLUDE_FROM_ALL)
add_subdirectory(libs/PhysX-4.1/physx/compiler/public EXCLUDE_FROM_ALL)
add_subdirectory(src)

#File installations

message("current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/Shaders" DESTINATION "${outputDir}")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Resources/Textures" DESTINATION "${outputDir}")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/glew32.dll" DESTINATION ${outputDir})
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/libs/PhysX-4.1/physx/bin/${CMAKE_BUILD_TYPE}/" DESTINATION ${outputDir} FILES_MATCHING PATTERN "*.dll")