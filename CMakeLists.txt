# WymonOrion project make file generation.
# This CMakeLists file generates a make file, which compiles all files inside
# of this repository, thus builds the libs and also the application.
# In order to activate the file, remove the ".all" at the end.
cmake_minimum_required(VERSION 2.6)
project(WymonOrion)

# Set directories for include and source.
set(WO_INCL_DIR ${CMAKE_CURRENT_LIST_DIR}/Include)
set(WO_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/Source)
set(WO_GRAPHICS_INCL_DIR ${WO_INCL_DIR}/Graphics)
set(WO_GRAPHICS_SRC_DIR ${WO_SRC_DIR}/Graphics)
set(WO_UTILS_INCL_DIR ${WO_INCL_DIR}/Utilities)
set(WO_UTILS_SRC_DIR ${WO_SRC_DIR}/Utilities)

# Enable debug symbols by default.
if(CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line; -D CMAKE_BUILD_TYPE=Release)

# Set compiler flags.
set(GCC_COMPILER_FLAGS "-std=c++11 -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILER_FLAGS}")

# Set include directories.
include_directories(${WO_INCL_DIR})
include_directories(${WO_GRAPHICS_INCL_DIR})
include_directories(${WO_UTILS_INCL_DIR})

# Create lib for all items related to graphics.
set(WO_GRAPHICS_LIB "wo_graphics")
add_library(${WO_GRAPHICS_LIB}
	    ${WO_GRAPHICS_SRC_DIR}/Animation.cpp 
		${WO_GRAPHICS_SRC_DIR}/FrameRepository.cpp
	    ${WO_GRAPHICS_SRC_DIR}/Sprite.cpp
	    ${WO_GRAPHICS_SRC_DIR}/Text.cpp
	    ${WO_GRAPHICS_SRC_DIR}/Texturable.cpp
		${WO_GRAPHICS_SRC_DIR}/TextureRepository.cpp
		${WO_GRAPHICS_SRC_DIR}/TextureManager.cpp)

# Create lib for all items related to general utilities.
set(WO_UTILS_LIB "wo_utils")
add_library(${WO_UTILS_LIB}
	    ${WO_UTILS_SRC_DIR}/Unicode.cpp 
	    ${WO_UTILS_SRC_DIR}/TimeString.cpp)

# Detect and add SFML
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})
# Find any version 2.X of SFML.
# See the FindSFML.cmake file for additional details and instructions.
find_package(SFML 2 REQUIRED system window graphics)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${WO_GRAPHICS_LIB} ${SFML_LIBRARIES})
endif()

# Create the executable, wymon_orion.
set(WO_EXEC "${PROJECT_NAME}")
add_executable(${WO_EXEC}
${WO_SRC_DIR}/main.cpp
${WO_SRC_DIR}/Orion.cpp
${WO_SRC_DIR}/Textfield.cpp)

target_link_libraries(${WO_EXEC} ${WO_GRAPHICS_LIB} ${WO_UTILS_LIB})
