# Mini Compiler Frontend

An educational compiler frontend project using C++ for the compiler logic and HTML, CSS, and JavaScript for the future web interface.

## Project Structure

```text
backend/
  include/
    token.h      Token types and token structure
    lexer.h      Lexer interface and lexical errors
    ast.h        Abstract syntax tree structures
  src/
    main.cpp     Backend entry point
    token.cpp    Token type implementation
    lexer.cpp    Lexical analyzer implementation
    ast.cpp      Abstract syntax tree implementation
  tests/
    token_test.cpp
    lexer_test.cpp
    ast_test.cpp
frontend/
  index.html     Frontend entry point
  css/           Stylesheets
  js/            JavaScript files
```

## Current Phase

Phase 5 defines the abstract syntax tree and verifies its basic structure with CTest. Parsing, semantic analysis, the HTTP server, and frontend integration will be added in later phases.

## C++ Environment

The current development environment uses MinGW GCC and CMake.

## Build and Run with MinGW

From the project root in PowerShell:

```powershell
New-Item -ItemType Directory -Force build | Out-Null
g++ -std=c++17 -Wall -Wextra -pedantic backend/src/main.cpp -o build/mini_compiler.exe
./build/mini_compiler.exe
```

Expected output depends on the current backend entry point.


## CMake Build

After installing CMake:

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
./build/mini_compiler.exe
```

The `build/` directory is local generated output and is ignored by Git.

## Run Tests

```powershell
ctest --test-dir build --output-on-failure
```
