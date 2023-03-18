#pragma once

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
		bool isValidMove(string to, char board[][8]);
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
		void move(string to, char board[][8]);
		bool isValidMove(string to, char board[][8]);
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
		void move(string to, char board[][8]);
		bool isValidMove(string to, char board[][8]);
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
		void move(string to, char board[][8]);
		bool isValidMove(string to, char board[][8]);
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
		void move(string to, char board[][8]);
		bool isValidMove(string to, char board[][8]);
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
		void move(string to, char board[][8]);
		bool isValidMove(string to, char board[][8]);
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
		void move(string to, char board[][8]);
		bool isValidMove(string to, char board[][8]);
};

class Pieces{	
	public:
		Piece* pieces = new Piece[16];
		string color;
		
		Pieces(){	
		}
		
		void printPieces();
		int pieceToInt(char piece);
		Piece* pieceInSquare(string square, char board[][8]);
};

class WhitePieces: public Pieces{
	public:
		WhitePieces() : Pieces(){
			this->color = "white";
			
			pieces[0] = Rook("a1", "white");
			pieces[1] = Knight("b1", "white");
			pieces[2] = Bishop("c1", "white");
			pieces[3] = Queen("d1", "white");
			pieces[4] = King("e1", "white");
			pieces[5] = Bishop("f1", "white");
			pieces[6] = Knight("g1", "white");
			pieces[7] = Rook("h1", "white");
			pieces[8] = Pawn("a2", "white");
			pieces[9] = Pawn("b2", "white");
			pieces[10] = Pawn("c2", "white");
			pieces[11] = Pawn("d2", "white");
			pieces[12] = Pawn("e2", "white");
			pieces[13] = Pawn("f2", "white");
			pieces[14] = Pawn("g2", "white");
			pieces[15] = Pawn("h2", "white");
		}
};

class BlackPieces: public Pieces{
	public:
		BlackPieces() : Pieces(){
			this->color = "black";
			
			pieces[0] = Rook("a8", "black");
			pieces[1] = Knight("b8", "black");
			pieces[2] = Bishop("c8", "black");
			pieces[3] = Queen("d8", "black");
			pieces[4] = King("e8", "black");
			pieces[5] = Bishop("f8", "black");
			pieces[6] = Knight("g8", "black");
			pieces[7] = Rook("h8", "black");
			pieces[8] = Pawn("a7", "black");
			pieces[9] = Pawn("b7", "black");
			pieces[10] = Pawn("c7", "black");
			pieces[11] = Pawn("d7", "black");
			pieces[12] = Pawn("e7", "black");
			pieces[13] = Pawn("f7", "black");
			pieces[14] = Pawn("g7", "black");
			pieces[15] = Pawn("h7", "black");
		}
};
