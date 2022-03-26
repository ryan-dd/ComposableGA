cmake_minimum_required(VERSION 3.1)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS NO_OUTPUT_DIRS)

add_executable(GA_ECS main.cpp)

target_link_libraries(GA_ECS PUBLIC CONAN_PKG::entt)
target_include_directories(GA_ECS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
