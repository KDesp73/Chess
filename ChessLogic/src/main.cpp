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

int main(int argc, char** argv) {
	string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	string castling_testing_fen = "r3k2r/8/8/8/8/8/8/R3K2R";
	string promoting_testing_fen = "8/P7/8/8/8/8/p7/8";
	string random_fen = "r3kb1r/1pp5/p1b2p1p/4p3/8/2N2N2/PPP2PPP/3RR1K1";
	string checkmate_fen = "rnb1kbnr/pppp1ppp/8/4p3/6Pq/5P2/PPPPP2P/RNBQKBNR";

	//start(starting_fen);

	string temp_fen = "r1bqkb1r/pppp1Qpp/2n2n2/4p3/2B1P3/8/PPPP1PPP/RNB1K1NR";
	Board b{"white", temp_fen};
	b.printBigBoard();

	King k{"e8", "black"};

	printValidMoves(&k, temp_fen);

	cout << "Is in check? " << k.isInCheck(b.board) << endl;
	cout << "Is in checkmate? " << k.isInCheckmate(b.board) << endl;

	return 0;
}
