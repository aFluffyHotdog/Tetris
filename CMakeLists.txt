cmake_minimum_required(VERSION 3.15)
project(Tetris)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS -pthread)
# set(raylib_DIR "/home/arcade2/Tetris/raylib")
find_package(Threads REQUIRED)
find_package(raylib 3.0 REQUIRED)  # comment this out on RPI
# Dependencies
#include(FetchContent)
#FetchContent_Declare(
#    raylib
#   DOWNLOAD_EXTRACT_TIMESTAMP OFF
#    URL "https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz"
#    BUILD_COMMAND "make PLATFORM=PLATFORM_DESKTOP GRAPHICS=GRAPHICS_API_OPENGL_21" FORCE
#)
#FetchContent_MakeAvailable(raylib)



add_executable(${PROJECT_NAME}
        Arcade/main.cpp
        Arcade/Game.cpp
        Arcade/Board.cpp
        Arcade/Tetromino.cpp
        Arcade/Board.h
        Arcade/Game.h
        Arcade/Tetromino.h
        Arcade/main.cpp
        Arcade/Button.cpp
        Arcade/Button.h
)

#target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
#target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} raylib)  # uncoment this on PC

# Uncomment for RPI
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
#find_library(RAYLIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/libraylib.a)
#target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/lib/libraylib.a dl)


# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
