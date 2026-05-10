cmake_minimum_required(VERSION 3.0)
project(chessgame)
set(CMAKE_CXX_STANDARD 17)
add_executable(chessgame Main.cc Board/Board.cc Piece/Piece.cc Types/Types.h)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
target_link_libraries(chessgame PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)