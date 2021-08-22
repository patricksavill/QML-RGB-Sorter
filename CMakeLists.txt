cmake_minimum_required(VERSION 3.5)

project(QML-RGB-Sorter LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Core Quick Gui REQUIRED)

# Add the front and back end directories
add_subdirectory(FrontEnd)
add_subdirectory(ImageProcessing)

