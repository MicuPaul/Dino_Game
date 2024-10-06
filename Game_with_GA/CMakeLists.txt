cmake_minimum_required(VERSION 3.28)
project(Game_with_GA)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 17)

set(GAME_SOURCE Source_Files/Game_files)
set(GAME_HEADER Header_Files/Game_files)
set(OTHER_SOURCE Source_Files/Other_files)
set(OTHER_HEADER Header_Files/Other_files)
set(IMPORTANT_FILES Spritesheet/.)

include_directories(${GAME_SOURCE})
include_directories(${IMPORTANT_FILES})
include_directories(${GAME_HEADER})
include_directories(${OTHER_SOURCE})
include_directories(${OTHER_HEADER})

set(
        SOURCE_FILES
        ${GAME_SOURCE}/main.cpp

        #Game headers
        ${GAME_HEADER}/Dino.h
        ${GAME_HEADER}/GameGlobals.h
        ${GAME_HEADER}/Game.h
        ${GAME_HEADER}/Tile.h
        ${GAME_HEADER}/Floor.h
        ${GAME_HEADER}/Clouds.h
        ${GAME_HEADER}/Obstacles.h
        ${GAME_HEADER}/Collision.h
        ${GAME_HEADER}/Score.h
        ${GAME_HEADER}/stdafx.h

        #Other headers
        ${OTHER_HEADER}/NLayer.h
        ${OTHER_HEADER}/NeuralNet.h
        ${OTHER_HEADER}/NN_Renderer.h
        ${OTHER_HEADER}/Genetic_Algorithm.h
        ${OTHER_HEADER}/Genome.h


        #Game sources
        ${GAME_SOURCE}/Dino.cpp
        ${GAME_SOURCE}/Game.cpp
        ${GAME_SOURCE}/Tile.cpp
        ${GAME_SOURCE}/Floor.cpp
        ${GAME_SOURCE}/Clouds.cpp
        ${GAME_SOURCE}/Obstacles.cpp
        ${GAME_SOURCE}/Collision.cpp
        ${GAME_SOURCE}/Score.cpp
        ${GAME_SOURCE}/stdafx.cpp

        #Other sources
        ${OTHER_SOURCE}/NLayer.cpp
        ${OTHER_SOURCE}/NeuralNet.cpp
        ${OTHER_SOURCE}/NN_Renderer.cpp
        ${OTHER_SOURCE}/Genetic_Algorithm.cpp
)




add_executable(Game_with_GA ${SOURCE_FILES})


target_link_libraries(Game_with_GA sfml-graphics)
target_link_libraries(Game_with_GA sfml-audio)
target_link_libraries(Game_with_GA sfml-system)
target_link_libraries(Game_with_GA sfml-window)
target_link_libraries(Game_with_GA sfml-network)






