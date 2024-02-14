
cmake_minimum_required(VERSION 3.27)

project(Clippy
        VERSION 0.1.0
        DESCRIPTION "A local assistant."
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
    GIT_TAG v3.0
)

FetchContent_MakeAvailable(argparse)

add_executable(Clippy main.cpp)

target_link_libraries(Clippy argparse)
