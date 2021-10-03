# CMake
cmake_minimum_required (VERSION 3.13)

# Project
project (nog)

# Source Files
file (GLOB SOURCE_CORE_STANDARD "source/core/standard/*.cpp")
file (GLOB SOURCE_CORE          "source/core/*.cpp")
file (GLOB SOURCE_COMPILER      "source/compiler/*.cpp")

# Compiler
add_compile_definitions (version_standard)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions (debug)
else ()
    set (CMAKE_BUILD_TYPE                   "Release")
    set (CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    add_compile_options (-w -flto=full)
endif ()

# Include directories
include_directories (source)

# Executables
add_executable (
    nog

    ${SOURCE_CORE_STANDARD}
    ${SOURCE_CORE}
    ${SOURCE_COMPILER}
)