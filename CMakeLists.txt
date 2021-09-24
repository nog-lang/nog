# CMake
cmake_minimum_required (VERSION 3.13)

# Project
project (nog)

# Source Files
file (GLOB SOURCE_CORE_STANDARD "source/core/standard/*.cpp")
file (GLOB SOURCE_CORE          "source/core/*.cpp")
file (GLOB SOURCE_COMPILER      "source/compiler/*.cpp")

# Compiler
set (DEBUG "false")

add_compile_definitions (version_standard)

if (DEBUG STREQUAL "true")
    set (CMAKE_BUILD_TYPE "Debug")
    add_compile_definitions (debug)
    add_compile_options (-Wall)
else ()
    set (CMAKE_BUILD_TYPE "Release")
    add_compile_options (-w)
endif ()

# Include directories
include_directories (source)

# Executables
add_executable (
    nog

    ${SOURCE_CORE_STANDARD}
    ${SOURCE_COMPILER}
)