cmake_minimum_required(VERSION 3.5)

project(QML-RGB-Sorter LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Core Quick REQUIRED)

include_directories(../ImageProcessing )

# Add executables
add_executable(QML-RGB-Sorter
    frontend.h
    frontend.cpp
    LiveImage.cpp
    LiveImage.h
    ImageProvider.cpp
    ImageProvider.h
    qml.qrc
)


target_compile_definitions(QML-RGB-Sorter
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(QML-RGB-Sorter PRIVATE Qt5::Core Qt5::Quick ImageProcessing)

# Copy example image for later use
configure_file(example-image.jpg ${CMAKE_BINARY_DIR}/example-image.jpg COPYONLY)
