#include <iostream>
#include <string>

#include "chess_lib.h"

#include "Tests/tests.h"
#include "Tests/test_fens.h"


void printValidMoves(Piece *p, string fen){
	Board *b = new Board("white", fen);

	vector<string> ret = p->getValidMoves(b->board);

	for(int i = 0; i < ret.size(); i++){
		cout << ret.at(i) << endl;
	}
}

int main(int argc, char** argv) {
	string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	string castling_testing_fen = "r3k2r/8/8/8/8/8/8/R3K2R";
	string promoting_testing_fen = "1b6/P7/8/3k4/5K2/8/p7/1B6";
	string random_fen = "r3kb1r/1pp5/p1b2p1p/4p3/8/2N2N2/PPP2PPP/3RR1K1";

/**/
	
/** /

	vector<string> mate_fens = {
		"4k3/8/8/8/1qP5/3P4/4PP2/3BKQ2",
		"4k3/8/8/8/6Pq/5P2/3PP3/3QKB2",
		"rnb1kbnr/pppp1ppp/8/4p3/6Pq/5P2/PPPPP2P/RNBQKBNR",
		"KN5q/7k/8/8/8/8/5bb1/8",
		"3k4/8/8/2b1p3/4P3/2N2N2/PPPP1qPP/R1BQKB1R",
		"KN5r/7k/8/8/8/8/5bb1/8"
	};
/**/

	//Test::testCheck(TestFens::check_fens);
	//Test::testPins(TestFens::pin_fens, TestFens::pinned_squares);
	//Test::testCheck(TestFens::check_fens);
	//Test::testNotCheck(TestFens::should_not_be_check_fens);

	Game::start(castling_testing_fen);

	return 0;
}
