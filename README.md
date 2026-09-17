# Mini Compiler Frontend

An educational compiler frontend project using C++ for the compiler logic and HTML, CSS, and JavaScript for the future web interface.

## Project Structure

```text
backend/
  include/       Header files
  src/           C++ source files
  tests/         Backend tests
frontend/
  index.html     Frontend entry point
  css/           Stylesheets
  js/            JavaScript files
```

## Current Phase

Phase 3 implements the initial token system and verifies it with a CTest test. Lexing, parsing, the HTTP server, and frontend integration will be added in later phases.

## C++ Environment

The current development environment uses MinGW GCC. CMake is the intended build-system entry point, but it must be installed separately and added to `PATH` before CMake commands can be used.

## Build and Run with MinGW

From the project root in PowerShell:

```powershell
New-Item -ItemType Directory -Force build | Out-Null
g++ -std=c++17 -Wall -Wextra -pedantic backend/src/main.cpp -o build/mini_compiler.exe
./build/mini_compiler.exe
```

Expected output:

```text
Mini Compiler Backend - Phase 2 setup complete.
```

## CMake Build

After installing CMake:

```powershell
cmake -S . -B build
cmake --build build
./build/Debug/mini_compiler.exe
```

The exact executable path can vary by generator and configuration.

## Run Tests

```powershell
ctest --test-dir build --output-on-failure
```
