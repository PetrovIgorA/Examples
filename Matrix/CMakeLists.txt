cmake_minimum_required(VERSION 3.10)

project(Matrix)

include_directories(.)

add_executable(matrix_tests tests/matrix_tests.cpp)
target_link_libraries(matrix_tests ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} pthread)

gtest_add_tests(TARGET matrix_tests)
