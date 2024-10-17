cmake_minimum_required(VERSION 3.13)
project(sd2)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add submodule directory for stable-diffusion
add_subdirectory(stable-diffusion.cpp)

# Include directories for stable-diffusion and its dependencies
include_directories(stable-diffusion.cpp src)

# Create executable from your main.cpp
add_executable(sd2 src/main.cpp)

# Link with the stable-diffusion library
target_link_libraries(sd2 stable-diffusion)
