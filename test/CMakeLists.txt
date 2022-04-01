cmake_minimum_required(VERSION 3.1)

add_executable(runTests integration_test.cpp)

target_link_libraries(runTests PUBLIC CONAN_PKG::gtest)
add_test(runTests runTests) 
