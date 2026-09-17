cmake_minimum_required(VERSION 3.15)

project(mini_compiler_frontend VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(mini_compiler
    backend/src/main.cpp
)

target_include_directories(mini_compiler PRIVATE
    backend/include
)
