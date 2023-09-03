cmake_minimum_required(VERSION 3.16)

project(Chess)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add SDL
# sudo apt install cmake libsdl2-dev g++
# sudo apt install cmake libsdl2-image-dev

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

include_directories(include Cli-Kit)
add_subdirectory(Cli-Kit)



# Add source files
set(SOURCES
    src/main.cpp

    src/Board/board_utils.cpp
    src/Board/Board.cpp
    src/Board/special_piece_moves.cpp
    src/Board/king_checks.cpp
    src/Board/movement.cpp
    
    src/Game/game_logic.cpp
    
    
    src/Pieces/Bishop.cpp
    src/Pieces/King.cpp
    src/Pieces/Knight.cpp
    src/Pieces/Pawn.cpp
    src/Pieces/Piece.cpp
    src/Pieces/Pieces.cpp
    src/Pieces/Queen.cpp
    src/Pieces/Rook.cpp
    
    src/GUI/gui.cpp
    src/GUI/Board/board.cpp
    src/GUI/Rendering/rendering.cpp
    
    src/Notation/fen.cpp
    src/Notation/pgn.cpp


    src/Menu/menu.cpp

)

set(INCLUDE
    src/chess_lib.h
 
    include/board_utils.h
    include/Pieces.h
    include/board.h
    include/gui.h
    include/game_logic.h
    include/structs.h
    include/rendering.h
    include/notation.h
    include/game_utils.h
    include/game_menu.h

)

set(TESTS
    tests/tests.h
    tests/test_fens.h
    tests/tests.cpp
)

add_executable(Chess ${SOURCES} ${TESTS} ${INCLUDE})

target_link_libraries(${PROJECT_NAME} CliKit)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
