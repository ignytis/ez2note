cmake_minimum_required(VERSION 3.16)

project(ez2note VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "build")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(ez2note
src/app.cpp
src/main.cpp
src/gui/windows/about/about.cpp
src/gui/windows/mainwindow/mainwindow.cpp
)

target_include_directories(ez2note PRIVATE src)

target_link_libraries(ez2note PRIVATE Qt6::Widgets)

set_target_properties(ez2note PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)