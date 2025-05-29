cmake_minimum_required(VERSION 3.10)
project(Calculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main calculator executable
add_executable(calculator src/main.cpp)

target_include_directories(minicompiler PRIVATE include) 

# Lexer test executable
add_executable(test_lexer
    src/test_lexer.cpp
    src/token.cpp
    src/lexer/lexer.cpp
)

target_include_directories(test_lexer PRIVATE include) 