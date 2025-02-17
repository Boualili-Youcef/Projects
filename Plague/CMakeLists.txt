cmake_minimum_required(VERSION 3.10)

project(Plague LANGUAGES C CXX)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Collect source files from the src directory
file(GLOB_RECURSE SOURCE_FILES  src/main.cpp src/city/BaseCity.cpp)

# Define the executable (adjust target name and sources as needed)
add_executable(plague ${SOURCE_FILES})

# ...additional configuration if needed...
