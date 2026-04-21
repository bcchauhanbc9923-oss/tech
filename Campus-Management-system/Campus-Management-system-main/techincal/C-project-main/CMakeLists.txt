cmake_minimum_required(VERSION 3.10)
project(CampusNavigationSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/Building.cpp
    src/CampusGraph.cpp
    src/NavigationServer.cpp
    src/main.cpp
)

# Create executable
add_executable(navigate ${SOURCES})

# Compiler flags
if(MSVC)
    target_compile_options(navigate PRIVATE /W4)
else()
    target_compile_options(navigate PRIVATE -Wall -Wextra -Wpedantic)
endif()
