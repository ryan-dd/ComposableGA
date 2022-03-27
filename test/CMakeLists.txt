cmake_minimum_required(VERSION 3.1)

add_executable(runTests opti_problem_test.cpp integration_test.cpp)

target_link_libraries(runTests PUBLIC CONAN_PKG::gtest)
add_test(runTests runTests) 
