cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD 17)

project(Lii CXX)
add_subdirectory(libs/stb)
add_subdirectory(src)

#File installations

#GetThe output dir
if(DEFINED RUNTIME_OUTPUT_DIRECTORY)
	set(outputDir "${RUNTIME_OUTPUT_DIRECTORY}/src")
else()
	set(outputDir "${CMAKE_BINARY_DIR}/src")
endif()
message("Runtime directory is: ${outputDir}")

install(DIRECTORY "src/Shaders" DESTINATION "${outputDir}")
install(DIRECTORY "Resources/Textures" DESTINATION "${outputDir}")
install(FILES "libs/glew/glew32.dll" DESTINATION ${outputDir})