cmake_minimum_required(VERSION 3.28)
project(Dino_Game)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 17)

set(APP_SOURCE Source_Files)
set(APP_HEADER Header_Files)

include_directories(${APP_SOURCE})
include_directories(${APP_HEADER})

set(
        SOURCE_FILES
        ${APP_SOURCE}/main.cpp
        ${APP_HEADER}/Dino.h
        ${APP_HEADER}/Game.h
        ${APP_HEADER}/Tile.h
        ${APP_HEADER}/Floor.h
        ${APP_HEADER}/Clouds.h
        ${APP_HEADER}/Obstacles.h
        ${APP_HEADER}/Collision.h
        ${APP_HEADER}/Score.h
        ${APP_HEADER}/stdafx.h
        ${APP_SOURCE}/Dino.cpp
        ${APP_SOURCE}/Game.cpp
        ${APP_SOURCE}/Tile.cpp
        ${APP_SOURCE}/Floor.cpp
        ${APP_SOURCE}/Clouds.cpp
        ${APP_SOURCE}/Obstacles.cpp
        ${APP_SOURCE}/Collision.cpp
        ${APP_SOURCE}/Score.cpp
        ${APP_SOURCE}/stdafx.cpp
)

add_executable(Dino_Game ${SOURCE_FILES})

target_link_libraries(Dino_Game sfml-graphics)
target_link_libraries(Dino_Game sfml-audio)
target_link_libraries(Dino_Game sfml-system)
target_link_libraries(Dino_Game sfml-window)
target_link_libraries(Dino_Game sfml-network)
