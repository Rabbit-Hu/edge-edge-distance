cmake_minimum_required(VERSION 3.10)
project(eed VERSION 1.0)

# Specify C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the library directory
include_directories(${PROJECT_SOURCE_DIR}/lib)

# Add subdirectories
add_subdirectory(lib)
add_subdirectory(example)
add_subdirectory(tests)