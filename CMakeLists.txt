cmake_minimum_required(VERSION 3.15)

project(mini_compiler_frontend VERSION 0.1.0 LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(mini_compiler
    backend/src/main.cpp
    backend/src/token.cpp
)

target_include_directories(mini_compiler PRIVATE
    backend/include
)

if(MSVC)
    target_compile_options(mini_compiler PRIVATE /W4)
else()
    target_compile_options(mini_compiler PRIVATE -Wall -Wextra -pedantic)
endif()

add_executable(token_test
    backend/tests/token_test.cpp
    backend/src/token.cpp
)

target_include_directories(token_test PRIVATE
    backend/include
)

if(MSVC)
    target_compile_options(token_test PRIVATE /W4)
else()
    target_compile_options(token_test PRIVATE -Wall -Wextra -pedantic)
endif()

add_test(NAME token_system_test COMMAND token_test)
