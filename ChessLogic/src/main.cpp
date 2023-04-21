#include <iostream>
#include <string>

#include "Board/board_declarations.h"
#include "Board/game_logic.h"
#include "Pieces/piece_declarations.h"


int main(int argc, char** argv) {
	string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	string castling_testing_fen = "r3k2r/8/8/8/8/8/8/R3K2R";
	string promoting_testing_fen = "8/P7/8/8/8/8/p7/8";
	
	start(starting_fen);

	return 0;
}
