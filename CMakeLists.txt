cmake_minimum_required(VERSION 3.21)
project(tuner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia)

add_executable(tuner
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    devicechooser.cpp
    devicechooser.h
    devicechooser.ui
    audioprocessor.h
    audioprocessor.cpp
)

target_link_libraries(tuner
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Multimedia
)
