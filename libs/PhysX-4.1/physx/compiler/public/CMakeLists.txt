##
## Redistribution and use in source and binary forms, with or without
## modification, are permitted provided that the following conditions
## are met:
##  * Redistributions of source code must retain the above copyright
##    notice, this list of conditions and the following disclaimer.
##  * Redistributions in binary form must reproduce the above copyright
##    notice, this list of conditions and the following disclaimer in the
##    documentation and/or other materials provided with the distribution.
##  * Neither the name of NVIDIA CORPORATION nor the names of its
##    contributors may be used to endorse or promote products derived
##    from this software without specific prior written permission.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
## EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
## IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
## PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
## CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
## EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
## PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
## PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
## OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
## (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
## OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##
## Copyright (c) 2008-2021 NVIDIA Corporation. All rights reserved.

IF(TARGET_BUILD_PLATFORM STREQUAL "mac" OR TARGET_BUILD_PLATFORM STREQUAL "ios")
	cmake_minimum_required(VERSION 3.12)
ELSE()
	cmake_minimum_required(VERSION 3.11)
ENDIF()

project(PhysXSDK C CXX)

SET(PHYSX_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(CMAKE_CONFIGURATION_TYPES "debug") #enum configTypes {debug checked profile release}
set(TARGET_BUILD_PLATFORM "windows") # has to match the TARGET_BUILD_PLATFORM in $ENV{PHYSX_PATH}/physix/buildtools/cmake_generate_projects.py
set(PX_BUILDSNIPPETS OFF CACHE BOOL "Generate the snippets")
set(PX_BUILDPUBLICSAMPLES OFF CACHE BOOL "Generate the samples projects")
set(PX_GENERATE_STATIC_LIBRARIES OFF CACHE BOOL "Generate static libraries")
set(PX_FLOAT_POINT_PRECISE_MATH OFF CACHE BOOL "Float point precise math")
set(NV_USE_STATIC_WINCRT ON CACHE BOOL "Use the statically linked windows CRT")
set(NV_USE_DEBUG_WINCRT ON CACHE BOOL "Use the debug version of the CRT")
set(PXSHARED_PATH ${PHYSX_ROOT_DIR}/../pxshared)
set(PXSHARED_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CMAKEMODULES_VERSION "1.27")
set(CMAKEMODULES_PATH ${PHYSX_ROOT_DIR}/../externals/cmakemodules)
set(PX_OUTPUT_LIB_DIR ${PHYSX_ROOT_DIR}/bin/)
set(PX_OUTPUT_BIN_DIR ${PHYSX_ROOT_DIR}/bin/)

set( PHYSX_LIBRARIES
		PhysXExtensions
		PhysX
		PhysXPvdSDK
		PhysXVehicle
		PhysXCharacterKinematic
		PhysXCooking
		PhysXCommon
		PhysXFoundation
		)
add_library(PhysXSDK INTERFACE)
target_link_libraries(PhysXSDK INTERFACE ${PHYSX_LIBRARIES})

OPTION(PX_BUILDSNIPPETS "Generate the snippets" OFF)
OPTION(PX_BUILDPUBLICSAMPLES "Generate the samples" OFF)
OPTION(PX_CMAKE_SUPPRESS_REGENERATION "Disable zero_check projects" OFF)


IF(NOT DEFINED CMAKEMODULES_VERSION)
	SET(CMAKEMODULES_PATH $ENV{PM_CMakeModules_PATH} CACHE INTERNAL "Path to CMakeModules")
	SET(CMAKEMODULES_NAME "CMakeModules" CACHE INTERNAL "CMakeModules name")
	SET(CMAKEMODULES_VERSION "1.27" CACHE INTERNAL "CMakeModules version from generation batch")
ENDIF()

SET(CMAKE_MODULE_PATH ${CMAKEMODULES_PATH})


IF(PX_CMAKE_SUPPRESS_REGENERATION)
	SET(CMAKE_SUPPRESS_REGENERATION true)
ENDIF()

# This is required to be defined by external callers!
IF(NOT DEFINED PHYSX_ROOT_DIR)
	MESSAGE(FATAL_ERROR "PHYSX_ROOT_DIR variable wasn't set.")
ENDIF()

IF(NOT EXISTS ${PHYSX_ROOT_DIR})
	MESSAGE(FATAL_ERROR "PHYSX_ROOT_DIR variable was invalid.")
ENDIF()

SET(PUBLIC_RELEASE 1)

# Enable folder properties
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# Disable zero_check projects. The default for Switch and XboxOne is ON.
IF(PX_CMAKE_SUPPRESS_REGENERATION)
	SET(CMAKE_SUPPRESS_REGENERATION true)
ENDIF()

# Add PhysX SDK Source code to solution
ADD_SUBDIRECTORY(${PHYSX_ROOT_DIR}/source/compiler/cmake ${CMAKE_CURRENT_BINARY_DIR}/sdk_source_bin)

MESSAGE("Added PhysX")

IF(PX_BUILDSNIPPETS)
	# Add Snippets projects into the solution
	ADD_SUBDIRECTORY(${PHYSX_ROOT_DIR}/snippets/compiler/cmake ${CMAKE_CURRENT_BINARY_DIR}/sdk_snippets_bin)

	MESSAGE("Added Snippets")
ENDIF()

IF(PX_BUILDPUBLICSAMPLES)
	IF(TARGET_BUILD_PLATFORM STREQUAL "windows" OR TARGET_BUILD_PLATFORM STREQUAL "linux")
		# Add samples projects into the solution
		ADD_SUBDIRECTORY(${PHYSX_ROOT_DIR}/samples/compiler/cmake ${CMAKE_CURRENT_BINARY_DIR}/sdk_samples_bin)

		MESSAGE("Added Samples")
	ENDIF()
ENDIF()

IF(TARGET_BUILD_PLATFORM STREQUAL "switch")
	FILE(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/ALL_BUILD.vcxproj.user" INPUT  "${CMAKE_MODULE_PATH}/switch/Microsoft.Cpp.${NX_TARGET_DEVKIT}.user.props" CONDITION  1)
	FILE(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/INSTALL.vcxproj.user" INPUT  "${CMAKE_MODULE_PATH}/switch/Microsoft.Cpp.${NX_TARGET_DEVKIT}.user.props" CONDITION  1)
ENDIF()
