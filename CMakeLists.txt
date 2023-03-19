# CMakeList.txt : CMake project for DBU, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.10)

project(DBU VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(__DEBUGLINUX TRUE)
endif()

message(NOTICE "Building for ${CMAKE_SYSTEM_NAME} ${CMAKE_BUILD_TYPE}")

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(__WIN32 TRUE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(__LINUX TRUE)
endif()

configure_file(platform.h.in platform.h)

set(
    PROJECT_SRC
    "DBU.cpp" 
    "console/Console.cpp"  
    "console/Color.cpp"  
    "console/ForegroundColors.cpp" 
    "console/BackgroundColors.cpp" 
    "console/Attributes.cpp" 
    "console/ColorSchemeManager.cpp"
    "console/ConsoleTools.cpp"
    "widget/AbstractWidget.cpp"
)

# Add source to this project's executable.
add_executable (DBU ${PROJECT_SRC})

target_include_directories(DBU PUBLIC
    "include"
    "${PROJECT_BINARY_DIR}"
)
