
cmake_minimum_required(VERSION 3.27)

project(Clippy
        VERSION 0.1.0
        DESCRIPTION "A local assistant."
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

# Create target "ChatUpServer"
add_executable(Clippy main.cpp)
