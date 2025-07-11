cmake_minimum_required(VERSION 3.21)
project(rznz_guitar_tool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt modules
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Find RtAudio via pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(RTAUDIO REQUIRED rtaudio)

# Define executable with consistent name
set(APP_NAME rznz-guitar-tool)
add_executable(${APP_NAME}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    devicechooser.cpp
    devicechooser.h
    devicechooser.ui
    audioprocessor.cpp
    audioprocessor.h
)

# Include RtAudio headers
target_include_directories(${APP_NAME} PRIVATE ${RTAUDIO_INCLUDE_DIRS})

# Link libraries
target_link_libraries(${APP_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    ${RTAUDIO_LIBRARIES}
)

