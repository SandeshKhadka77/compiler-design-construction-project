cmake_minimum_required(VERSION 3.15)

project(mini_compiler_frontend VERSION 0.1.0 LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(mini_compiler
    backend/src/ast.cpp
    backend/src/lexer.cpp
    backend/src/main.cpp
    backend/src/parser.cpp
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

add_executable(lexer_test
    backend/tests/lexer_test.cpp
    backend/src/lexer.cpp
    backend/src/token.cpp
)

target_include_directories(lexer_test PRIVATE
    backend/include
)

if(MSVC)
    target_compile_options(lexer_test PRIVATE /W4)
else()
    target_compile_options(lexer_test PRIVATE -Wall -Wextra -pedantic)
endif()

add_test(NAME lexer_test COMMAND lexer_test)

add_executable(ast_test
    backend/tests/ast_test.cpp
    backend/src/ast.cpp
)

target_include_directories(ast_test PRIVATE
    backend/include
)

if(MSVC)
    target_compile_options(ast_test PRIVATE /W4)
else()
    target_compile_options(ast_test PRIVATE -Wall -Wextra -pedantic)
endif()

add_test(NAME ast_test COMMAND ast_test)

add_executable(parser_test
    backend/tests/parser_test.cpp
    backend/src/ast.cpp
    backend/src/lexer.cpp
    backend/src/parser.cpp
    backend/src/token.cpp
)

target_include_directories(parser_test PRIVATE
    backend/include
)

if(MSVC)
    target_compile_options(parser_test PRIVATE /W4)
else()
    target_compile_options(parser_test PRIVATE -Wall -Wextra -pedantic)
endif()

add_test(NAME parser_test COMMAND parser_test)
