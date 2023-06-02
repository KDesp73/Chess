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
	string promoting_testing_fen = "1b6/P7/8/3k4/5K2/8/p7/1B6";
	string random_fen = "r3kb1r/1pp5/p1b2p1p/4p3/8/2N2N2/PPP2PPP/3RR1K1";
	string checkmate_fen = "rnb1kbnr/pppp1ppp/8/4p3/6Pq/5P2/PPPPP2P/RNBQKBNR";

/**/ //Checkmate
	string temp_fen = "q5K1/8/6k1/8/8/8/8/8";
	Board b{"white", temp_fen};
	b.printBigBoard();

	Piece *p = b.findPiece("King", "white");
	King *king = dynamic_cast<King *>(p);
	//printValidMoves(king, temp_fen);

	cout << "Is in check? " << !king->isInCheck(b.board).empty() << endl;
	cout << "Is in checkmate? " << b.isInCheckmate(king) << endl;
/**/

	//Game::start(castling_testing_fen);

	return 0;
}
