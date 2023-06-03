#include <iostream>
#include <string>

#include "chess_lib.h"


void printValidMoves(Piece *p, string fen){
	Board *b = new Board("white", fen);

	vector<string> ret = p->getValidMoves(b->board);

	for(int i = 0; i < ret.size(); i++){
		cout << ret.at(i) << endl;
	}
}

bool testCheckMate(vector<string> mate_fens){
	bool passed = true;
	Text::clearScreen();
	for (int i = 0; i < mate_fens.size(); i++){
		Board b{"white", mate_fens.at(i)};
		//b.printBigBoard();

		Piece *p = b.findPiece("King", "white");
		King *king = dynamic_cast<King *>(p);
		//printValidMoves(king, temp_fen);

		(b.isInCheckmate(king)) ? cout << Text::green + "Passed\n" + Text::normal : cout << Text::red + "Failed" + Text::normal +" at: " + mate_fens.at(i) + "\n";
	
		if(!b.isInCheckmate(king)) passed = false;
	}
	return passed;
}

int main(int argc, char** argv) {
	string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	string castling_testing_fen = "r3k2r/8/8/8/8/8/8/R3K2R";
	string promoting_testing_fen = "1b6/P7/8/3k4/5K2/8/p7/1B6";
	string random_fen = "r3kb1r/1pp5/p1b2p1p/4p3/8/2N2N2/PPP2PPP/3RR1K1";
	string checkmate_fen = "rnb1kbnr/pppp1ppp/8/4p3/6Pq/5P2/PPPPP2P/RNBQKBNR";



	vector<string> mate_fens = {
		"rnb1kbnr/pppp1ppp/8/4p3/6Pq/5P2/PPPPP2P/RNBQKBNR",
		"8/6q1/8/8/8/8/5n1P/6NK",
		"7q/8/8/5k1K/8/8/8/8",
		"K6q/8/1k6/8/8/8/8/8",
		"8/8/8/8/8/5k2/5q2/5K2",
		"8/8/8/8/8/5k2/6q1/7K",
		"8/8/8/K1k5/8/8/8/q7",
		"r7/8/6k1/8/K7/8/8/1r6",
		"3rq3/7k/8/8/4K3/8/8/5r2",
		"8/7k/8/8/1n6/8/PPq5/2K5",
		"KN5q/7k/8/8/8/8/5bb1/8",
		"KR6/PPn4k/8/8/8/8/8/8"
	};

	testCheckMate(mate_fens);

	return 0;
}
