cmake_minimum_required(VERSION 3.10)

project(Morpheus)

set(CMAKE_CXX_STANDARD 17)

if(UNIX)
    add_compile_options(-Wall -Wextra -ggdb)
endif()

add_executable(MorpheusApp main.cpp)