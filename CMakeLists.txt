cmake_minimum_required(VERSION 3.20) # For C++23 (2b) support

# Set version to C++23, enable more warnings and go for maximum optimizations.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
add_compile_options(-Wall -Wextra -pedantic -O3)
add_link_options("-fuse-ld=mold")

project(ranges VERSION 0.1.0)

add_subdirectory(fmt)

include_directories(include)

add_executable(ranges main.cpp)

target_link_libraries(ranges fmt::fmt)
