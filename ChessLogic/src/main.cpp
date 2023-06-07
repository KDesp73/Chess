#include <iostream>
#include <string>

#include "chess_lib.h"

#include "Tests/tests.h"
#include "Tests/test_fens.h"


int main(int argc, char** argv) {
	string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	string castling_testing_fen = "r3k2r/8/8/8/8/8/8/R3K2R";
	string promoting_testing_fen = "1b6/P7/8/3k4/5K2/8/p7/1B6";
	string random_fen = "r3kb1r/1pp5/p1b2p1p/4p3/8/2N2N2/PPP2PPP/3RR1K1";


	//Test::testCheck(TestFens::check_fens);
	//Test::testPins(TestFens::pin_fens, TestFens::pinned_squares);
	//Test::testCheck(TestFens::check_fens);
	//Test::testNotCheck(TestFens::should_not_be_check_fens);
	// Test::testCheckMate(TestFens::mate_fens);
	// Test::testCheckMate("3k4/8/8/2b1p3/4P3/2N2N2/PPPP1qPP/R1BQKB1R");

	Game::start(castling_testing_fen);

	return 0;
}
