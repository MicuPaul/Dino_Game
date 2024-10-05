cmake_minimum_required(VERSION 3.28)
project(Dino_Game)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory("${PROJECT_SOURCE_DIR}/Finished_Game_for_single_player" "${PROJECT_SOURCE_DIR}/Finished_Game_for_single_player/CMake_files")
add_subdirectory("${PROJECT_SOURCE_DIR}/Game_with_GA" "${PROJECT_SOURCE_DIR}/Game_with_GA/CMake_files")