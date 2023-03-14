#include <iostream>
using namespace std;

class Piece {
	public:
		string currentSquare;
		string color;
		char boardChar;
		
		Piece(){
		}
		
		Piece(string currentSquare, string color){
			if(color != "white" && color != "black"){
				cout << "Incorrect color" << endl;
				//throw std::exception("Incorrect color");
			}
			
			this->currentSquare = currentSquare;
			this->color = color;
		}
		void move(string to, char board[][8]);
		void printPiece();
};

class Pawn: public Piece {
	public:
		Pawn(string currentSquare, string color) : Piece(currentSquare, color){
			if(color == "white"){
				this->boardChar = 'P';
			} else {
				this->boardChar = 'p';
			}
		}
};


class Rook: public Piece {
	public:
		Rook(string currentSquare, string color) : Piece(currentSquare, color){
			
			if(color == "white"){
				this->boardChar = 'R';
			} else {
				this->boardChar = 'r';
			}
		}
};

class Knight: public Piece {
	public:
		Knight(string currentSquare, string color) : Piece(currentSquare, color){
			
			if(color == "white"){
				this->boardChar = 'N';
			} else {
				this->boardChar = 'n';
			}
		}
};

class Bishop: public Piece {
	public:
		Bishop(string currentSquare, string color) : Piece(currentSquare, color){
			
			if(color == "white"){
				this->boardChar = 'B';
			} else {
				this->boardChar = 'b';
			}
		}
};

class Queen: public Piece {
	public:
		Queen(string currentSquare, string color) : Piece(currentSquare, color){
			
			if(color == "white"){
				this->boardChar = 'Q';
			} else {
				this->boardChar = 'q';
			}
		}
};

class King: public Piece {
	public:
		King(string currentSquare, string color) : Piece(currentSquare, color){
			
			if(color == "white"){
				this->boardChar = 'K';
			} else {
				this->boardChar = 'k';
			}
		}
};

class WhitePieces{
	public:
		Piece* whitePieces = new Piece[16];
		
		WhitePieces(){
			whitePieces[0] = Rook("a1", "white");
			whitePieces[1] = Knight("b1", "white");
			whitePieces[2] = Bishop("c1", "white");
			whitePieces[3] = Queen("d1", "white");
			whitePieces[4] = King("e1", "white");
			whitePieces[5] = Bishop("f1", "white");
			whitePieces[6] = Knight("g1", "white");
			whitePieces[7] = Rook("h1", "white");
			whitePieces[8] = Pawn("a2", "white");
			whitePieces[9] = Pawn("b2", "white");
			whitePieces[10] = Pawn("c2", "white");
			whitePieces[11] = Pawn("d2", "white");
			whitePieces[12] = Pawn("e2", "white");
			whitePieces[13] = Pawn("f2", "white");
			whitePieces[14] = Pawn("g2", "white");
			whitePieces[15] = Pawn("h2", "white");
		}
		
		void printPieces();
};

class BlackPieces{
	public:
		Piece* blackPieces = new Piece[16];
		
		BlackPieces(){
			blackPieces[0] = Rook("a8", "black");
			blackPieces[1] = Knight("b8", "black");
			blackPieces[2] = Bishop("c8", "black");
			blackPieces[3] = Queen("d8", "black");
			blackPieces[4] = King("e8", "black");
			blackPieces[5] = Bishop("f8", "black");
			blackPieces[6] = Knight("g8", "black");
			blackPieces[7] = Rook("h8", "black");
			blackPieces[8] = Pawn("a7", "black");
			blackPieces[9] = Pawn("b7", "black");
			blackPieces[10] = Pawn("c7", "black");
			blackPieces[11] = Pawn("d7", "black");
			blackPieces[12] = Pawn("e7", "black");
			blackPieces[13] = Pawn("f7", "black");
			blackPieces[14] = Pawn("g7", "black");
			blackPieces[15] = Pawn("h7", "black");
		}
		
		void printPieces();
};
