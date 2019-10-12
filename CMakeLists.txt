cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(cpp_examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Werror -pedantic -O2")

enable_testing()
find_package(GTest REQUIRED)

add_subdirectory(Function)
add_subdirectory(Matrix)
