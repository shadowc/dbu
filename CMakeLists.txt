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

    set(EXTRA_INCLUDES_PATH)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(__LINUX TRUE)

    set(EXTRA_INCLUDES_PATH
        "/usr/include"
        "/usr/local/include"
    )

    message(NOTICE "...")
    message(NOTICE "Make sure you have ncurses-devel package installed")
    message(NOTICE "sudo apt-get install libncurses-dev")
    message(NOTICE "...")

    target_link_libraries(DBU "libncurses")
endif()

configure_file(platform.h.in platform.h)

set(
    PROJECT_SRC
    "src/DBU.cpp" 
    "src/event/KeyboardTools.cpp"
    "src/event/EventQueue.cpp"
    "src/console/Console.cpp"  
    "src/console/Color.cpp"  
    "src/console/ForegroundColors.cpp" 
    "src/console/BackgroundColors.cpp" 
    "src/console/Attributes.cpp" 
    "src/console/ColorSchemeManager.cpp"
    "src/console/ConsoleTools.cpp"
    "src/widget/AbstractWidget.cpp"
    "src/widget/Screen.cpp"
)

# Add source to this project's executable.
add_executable (DBU ${PROJECT_SRC})

target_include_directories(DBU PUBLIC
    "include"
    "${EXTRA_INCLUDES_PATH}"
    "${PROJECT_BINARY_DIR}"
)
