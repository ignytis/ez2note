cmake_minimum_required(VERSION 3.16)

project(ez2note VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "build")

# Helps with debugging
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

find_package(wxWidgets COMPONENTS stc core base REQUIRED)

include(${wxWidgets_USE_FILE})

add_executable(ez2note
    src/app.cpp
    src/config.cpp
    src/gui/windows/about/aboutwindow.cpp
    src/gui/windows/findreplace/findreplacedialog.cpp
    src/gui/windows/main/mainwindow.cpp
    src/gui/windows/main/menubar.cpp
    src/main.cpp
)

if(WIN32)
    target_sources(ez2note PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/resource.rc)
endif()

target_include_directories(ez2note PRIVATE src)
target_link_libraries(ez2note PRIVATE wxWidgets::wxWidgets nlohmann_json::nlohmann_json)

set_target_properties(ez2note PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

