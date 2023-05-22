cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)
project(Lii CXX)
#Options
option(windows "Use windows platform" OFF)
option(linux "Use windows platform" OFF)
message("Windows option: ${windows}")

#Compile definitions
IF(windows)
	add_compile_definitions(windows)
endif()
add_definitions(-DNOMINMAX)




#GetThe output dir
if(DEFINED RUNTIME_OUTPUT_DIRECTORY)
	set(outputDir "${RUNTIME_OUTPUT_DIRECTORY}/src")
else()
	set(outputDir "${CMAKE_BINARY_DIR}/src")
endif()
message("Runtime directory is: ${outputDir}")

#Global libs that need to be compiled / included
add_subdirectory(libs/stb EXCLUDE_FROM_ALL)
add_subdirectory(libs/ConcurrentQueue)
add_subdirectory(libs/LiiInjector)
add_subdirectory(libs/MemoryManager)
add_subdirectory(libs/catch2)
add_subdirectory(src)
add_subdirectory(libs/Tracy)
add_subdirectory(libs/agc)
target_include_directories(antigrain PUBLIC libs/agc/include)
target_link_libraries(${PROJECT_NAME}
		stb
		opengl32
		catch2Lib
		"${CMAKE_SOURCE_DIR}/libs/glew/glew32.lib"
		"${CMAKE_SOURCE_DIR}/libs/glew/glew32s.lib"
		MemoryManagerLib
		ConcurrentQueue
		LiiInjector
		TracyClient
		antigrain
		)


#File installations
message("current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/Shaders" DESTINATION "${outputDir}")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Resources/Textures" DESTINATION "${outputDir}")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/glew32.dll" DESTINATION ${outputDir})