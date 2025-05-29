# Mini Compiler Project

A simple compiler that can parse and evaluate mathematical expressions.

## Prerequisites

1. Install Visual Studio Code
   - Download from: https://code.visualstudio.com/

2. Install Required VS Code Extensions
   - C/C++ Extension (ms-vscode.cpptools)
   - CMake Tools (ms-vscode.cmake-tools)

3. Install Required Tools
   - MinGW-w64 (C++ Compiler)
     - Download from: https://www.mingw-w64.org/
     - Add MinGW's bin directory to your system PATH (typically `C:\mingw64\bin`)
   - CMake
     - Download from: https://cmake.org/download/
     - Add CMake to your system PATH during installation

## Project Setup in VS Code

1. Open the project folder in VS Code
   ```bash
   code .
   ```

2. Configure CMake:
   - Press `Ctrl+Shift+P`
   - Type "CMake: Configure"
   - Select "MinGW Makefiles" as the kit

3. Build the Project:
   - Press `Ctrl+Shift+P`
   - Type "CMake: Build"
   - Or click the "Build" button in the status bar

4. Run the Project:
   - Press `Ctrl+Shift+P`
   - Type "CMake: Run Without Debugging"
   - Or click the "Run" button in the status bar

## Project Structure

```
.
├── CMakeLists.txt          # CMake configuration file
├── include/                # Header files
│   ├── ast.hpp            # Abstract Syntax Tree definitions
│   ├── token.hpp          # Token definitions
│   ├── lexer/             # Lexical analyzer
│   ├── parser/            # Parser
│   └── codegen/           # Code generator
└── src/                   # Source files
    ├── main.cpp           # Main program
    ├── token.cpp          # Token implementation
    ├── lexer/             # Lexer implementation
    ├── parser/            # Parser implementation
    └── codegen/           # Code generator implementation
```

## Usage

The compiler currently supports:
- Basic arithmetic operations (+, -, *, /)
- Parentheses for grouping
- Integer and decimal numbers

Example expression: `2 + 3 * 4`

## Build Commands

```bash
# Create build directory
mkdir build
cd build

# Configure CMake
cmake .. -G "MinGW Makefiles"

# Build the project
cmake --build .

# Run the compiler
./minicompiler.exe
``` # pblcd
# pblcd
# pblcd
# pblcd
