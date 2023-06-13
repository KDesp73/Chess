cmake_minimum_required(VERSION 3.16)

project(Chess)

include("./Ansi-Text-Manipulation-Library/AnsiTextLibrary/CMakeLists.txt")

set(CMAKE_CXX_STANDARD 11)

# Add source files
set(SOURCES
    src/main.cpp
    src/chess_lib.h

    src/Board/board_utils.cpp
    src/Board/board_utils.h
    src/Board/Board.cpp
    src/Board/board.h
    src/Board/fen.cpp
    src/Board/pgn.cpp
    src/Board/special_piece_moves.cpp
    src/Board/king_checks.cpp
    src/Board/structs.h
    
    src/Game/game_logic.cpp
    src/Game/game_logic.h


    src/Pieces/Bishop.cpp
    src/Pieces/King.cpp
    src/Pieces/Knight.cpp
    src/Pieces/Pawn.cpp
    src/Pieces/Pieces.h
    src/Pieces/Piece.cpp
    src/Pieces/Pieces.cpp
    src/Pieces/Queen.cpp
    src/Pieces/Rook.cpp
)

set(TESTS
    tests/tests.h
    tests/test_fens.h
    tests/tests.cpp
)

add_executable(Chess ${SOURCES})

target_link_libraries(Chess AnsiTextManipulationLibrary)