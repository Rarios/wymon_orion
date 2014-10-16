# WymonOrion project make file generation.
cmake_minimum_required(VERSION 2.6)
project(wymon_orion)

# Set directories for include and source.
set(WO_INCL_DIR "${CMAKE_CURRENT_LIST_DIR}/incl")
set(WO_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(WO_GRAPHICS_INCL_DIR "${WO_INCL_DIR}/graphics")
set(WO_UTILS_INCL_DIR "${WO_INCL_DIR}/utils")

# Enable debug symbols by default.
if(CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line; -D CMAKE_BUILD_TYPE=Release)

# Set compiler flags.
set(GCC_COMPILER_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILER_FLAGS}")

# Set include directories.
include_directories(${WO_INCL_DIR})
include_directories(${WO_GRAPHICS_INCL_DIR})
include_directories(${WO_UTILS_INCL_DIR})

# Create lib for all items related to graphics.
set(GAPHICS_LIB_NAME wo_graphics_lib)
add_library("${GRAPHICS_LIB_NAME}" 
		"${WO_GRAPHICS_INCL_DIR}/animation.cpp" 
		"${WO_GRAPHICS_INCL_DIR}/frame_repos.cpp"
		"${WO_GRAPHICS_INCL_DIR}/sprite.cpp"
		"${WO_GRAPHICS_INCL_DIR}/text.cpp"
		"${WO_GRAPHICS_INCL_DIR}/texturable.cpp"
		"${WO_GRAPHICS_INCL_DIR}/texture_repos.cpp")

# Create lib for all items related to general utilities.
set(UTILS_LIB_NAME wo_utils_lib)
add_library("${UTILS_LIB_NAME}"
		"${WO_UTILS_INCL_DIR}/Unicode.cpp"
		"${WO_UTILS_INCL_DIR}/Time_str.cpp")


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_mod" ${CMAKE_MODULE_PATH})
# Find any version 2.X of SFML.
# See the FindSFML.cmake file for additional details and instructions.
find_package(SFML 2 REQUIRED system window graphics)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${ANIM_LIB_NAME} ${SFML_LIBRARIES})
endif()

# Create excecutable.
set(EXECUTABLE_NAME "${PROJECT_NAME}")
add_executable(${EXECUTABLE_NAME} "${ANIM_SRC_DIR}/main.cpp") 
target_link_libraries(${EXECUTABLE_NAME} ${GRAPHICS_LIB_NAME} ${UTILS_LIB_NAME})
