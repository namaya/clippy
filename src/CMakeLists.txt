
cmake_minimum_required(VERSION 3.27)

project(Clippy
        VERSION 0.1.0
        DESCRIPTION "A local assistant."
        LANGUAGES CXX
)

# Install dependencies
include(FetchContent)

FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
    GIT_TAG v3.0
)

FetchContent_MakeAvailable(argparse)


include_directories(../.cvenv/include)
link_directories(../.cvenv/lib)

# Build main executable
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_executable(
    Clippy
    main.cpp
    pdfparser.cpp
    ocrtask.cpp
)

target_link_libraries(Clippy argparse poppler-cpp tesseract leptonica.6)
