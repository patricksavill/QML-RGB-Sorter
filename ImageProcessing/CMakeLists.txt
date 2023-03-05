cmake_minimum_required(VERSION 3.5)

project(ImageProcessing LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Core Gui REQUIRED)

add_library(ImageProcessing STATIC
    imageenums.h
    imageprocessing.cpp
    imageprocessing.h
)

target_link_libraries(ImageProcessing PRIVATE Qt5::Core Qt5::Gui pthread)
