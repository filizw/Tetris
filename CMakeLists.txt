cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME Tetris)
project(${PROJECT_NAME} LANGUAGES CXX)

#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

set(FONT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/font)
set(FONT_FILE ${FONT_DIR}/Arial.ttf)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/font)
configure_file(${FONT_FILE} ${CMAKE_BINARY_DIR}/font/ COPYONLY)

# Fetch SFML library
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(include)

file(GLOB SOURCES "./src/*.cpp" "./include/*.h")
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
