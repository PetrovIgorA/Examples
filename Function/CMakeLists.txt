cmake_minimum_required(VERSION 3.10)

project(Function)

include_directories(.)

add_executable(func_tests tests/Function_tests.cpp)
target_link_libraries(func_tests ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} pthread)

gtest_add_tests(TARGET func_tests)
