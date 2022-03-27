cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 20)

project(ComposableGA)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS NO_OUTPUT_DIRS)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
add_subdirectory(src)

enable_testing()
add_subdirectory(test)

