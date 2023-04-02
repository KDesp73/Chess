cmake_minimum_required(VERSION 3.16)

project(TextBasedGame)

set(CMAKE_CXX_STANDARD 11)

# Add source files
set(SOURCES
    src/main.cpp

    src/Board/board_declarations.h
    src/Board/board_functions.cpp
    src/Board/chess_notation.cpp
    src/Board/game_logic.cpp
    src/Board/notation.h

    src/Pieces/piece_declarations.h
    src/Pieces/Piece.cpp
    src/Pieces/Bishop.cpp
    src/Pieces/King.cpp
    src/Pieces/Knight.cpp
    src/Pieces/Pawn.cpp
    src/Pieces/Queen.cpp
    src/Pieces/Rook.cpp
    src/Pieces/Pieces.cpp
    src/Pieces/BlackPieces.cpp
    src/Pieces/WhitePieces.cpp

)


add_executable(TextBasedGame ${SOURCES})