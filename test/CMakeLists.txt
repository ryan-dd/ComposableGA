cmake_minimum_required(VERSION 3.1)

add_executable(runTests opti_problem_test.cpp integration_test.cpp)

target_include_directories(runTests PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(runTests PUBLIC gtest gtest_main pthread)

target_include_directories(runTests PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(runTests PUBLIC EvoAlgo)

add_test(runTests runTests) 
