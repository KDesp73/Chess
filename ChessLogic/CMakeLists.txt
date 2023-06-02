cmake_minimum_required(VERSION 3.16)

project(TextBasedGame)

set(CMAKE_CXX_STANDARD 11)

# Add source files
set(SOURCES
    src/main.cpp
    src/chess_lib.h

    src/Board/board_declarations.h
    src/Board/board_functions.cpp
    src/Board/board_utils.cpp
    src/Board/board_utils.h
    src/Board/Board.cpp
    src/Board/board.h
    src/Board/chess_notation.cpp
    src/Board/special_piece_moves.cpp
    src/Board/king_checks.cpp
    src/Board/structs.h
    
    src/Game/game_logic.cpp
    src/Game/game_logic.h


    src/Pieces/Bishop.cpp
    src/Pieces/King.cpp
    src/Pieces/Knight.cpp
    src/Pieces/Pawn.cpp
    src/Pieces/piece_declarations.h
    src/Pieces/Piece.cpp
    src/Pieces/Pieces.cpp
    src/Pieces/Queen.cpp
    src/Pieces/Rook.cpp

    src/text/text.h
    src/text/text.cpp
)


add_executable(TextBasedGame ${SOURCES})