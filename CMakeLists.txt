cmake_minimum_required(VERSION 3.16)
project(Tetris)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_executable(Tetris src/main.cpp src/game.hpp src/gamefield.hpp src/tetramino.hpp src/game.cpp src/gamefield.cpp src/tetramino.cpp)

target_link_libraries(Tetris sfml-graphics sfml-audio)