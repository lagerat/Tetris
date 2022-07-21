cmake_minimum_required(VERSION 3.15)
project(Tetris)

set(CMAKE_CXX_STANDARD 14)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()
if(LINUX)
    set(SFML_DIR SFML-2.5.1/lib/cmake/SFML-linux)
else()
    set(SFML_DIR SFML-2.5.1/lib/cmake/SFML-windows)
endif()

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

add_executable(Tetris src/main.cpp src/game.hpp src/gamefield.hpp src/tetramino.hpp src/game.cpp src/gamefield.cpp src/tetramino.cpp)

target_include_directories(Tetris PRIVATE SFML-2.5.1/include/) 

target_link_libraries(Tetris sfml-graphics)


if(WIN32)

    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1/bin/ DESTINATION ${PROJECT_BINARY_DIR}/)

endif()
