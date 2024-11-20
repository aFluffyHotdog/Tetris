cmake_minimum_required(VERSION 3.15)
project(Tetris)

find_package(raylib 3.0 REQUIRED) # Requires at least version 5.0

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
        Arcade/main.cpp
        Arcade/Game.cpp
        Arcade/Board.cpp
        Arcade/Tetromino.cpp
        Arcade/Board.h
        Arcade/Game.h
        Arcade/Tetromino.h
        Arcade/main.cpp
        Arcade/NetworkHandler.cpp
        Arcade/NetworkHandler.h
)

target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()