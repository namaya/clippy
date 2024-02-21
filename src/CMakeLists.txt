
cmake_minimum_required(VERSION 3.27)

project(Clippy
        VERSION 0.1.0
        DESCRIPTION "A local assistant."
        LANGUAGES CXX
)

#
#   Link pre-installed third-party dependencies
#

# Link pre-installed dependencies (if dependency supports CMake packages)
set(CMAKE_PREFIX_PATH ../.cvenv)

find_package(OpenCV CONFIG REQUIRED)
find_package(argparse CONFIG REQUIRED)

# otherwise directly link and include dependency header and library files
include_directories(../.cvenv/include)
link_directories(../.cvenv/lib)

# Build main executable
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_executable(
    Clippy
    main.cpp
    pdfextract.cpp
    ocrtask.cpp
)

target_link_libraries(
    Clippy
    PRIVATE
    argparse::argparse
    fswatch.13
    poppler-cpp
    tesseract
    leptonica.6
    ${OpenCV_LIBS}
)
