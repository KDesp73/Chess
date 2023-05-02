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

	//start(random_fen);



/*  // Pieces for random_fen 
	Pawn *p = new Pawn("e2", "white");
	Knight *n = new Knight("f3", "white");
	Rook *r = new Rook("e1", "white");
	Bishop *b = new Bishop("c6", "black");


*/
	King *k = new King("e1", "white");
	
	cout << "Valid moves: ";
	printValidMoves(k, "r1b1kbnr/ppp2p1p/8/3pp1pq/4P1P1/2Nn1P1B/PPP4P/R1BQK1NR");
	cout << endl;

	Board *b = new Board("white", "r1b1kbnr/ppp2p1p/8/3pp1pq/4P1P1/2Nn1P1B/PPP4P/R1BQK1NR");

	b->printBigBoard();

	cout << k->isInCheck(b->board) << endl;
	cout << k->isInCheckmate(b->board) << endl;

	b->~Board();
	k->~King();

	return 0;
}
