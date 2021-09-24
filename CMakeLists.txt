# CMake
cmake_minimum_required (VERSION 3.13)

# Project
project (nog)

# Source Files
file (GLOB SOURCE_CORE_STANDARD "source/core/standard/*.cpp")
file (GLOB SOURCE_CORE          "source/core/*.cpp")
file (GLOB SOURCE_COMPILER      "source/compiler/*.cpp")

# Compile definitions
add_compile_definitions (version_standard)

# Include directories
include_directories (source)

# Executables
add_executable (
    nog

    ${SOURCE_CORE_STANDARD}
    ${SOURCE_COMPILER}
)