#pragma once

#include <iostream>
using namespace std;

class Piece {
	public:
		string currentSquare;
		string color;
		char boardChar;
		int value;
		
		virtual ~Piece(){
		}
		
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
		virtual void move(string to, char board[][8]);
		virtual void printPiece();
		virtual bool isValidMove(string to, char board[][8]){
		}
};

class Pawn: public Piece {
	public:
		Pawn(string currentSquare, string color) {
			//Piece::Piece(currentSquare, color);
			value = 1;
			if(color == "white"){
				this->boardChar = 'P';
			} else {
				this->boardChar = 'p';
			}
		}
		void move(string to, char board[][8]) override;
		bool isValidMove(string to, char board[][8]) override;
};


class Rook: public Piece {
	public:
		Rook(string currentSquare, string color) : Piece(currentSquare, color) {
			
			value = 5;
			if(color == "white"){
				this->boardChar = 'R';
			} else {
				this->boardChar = 'r';
			}
		}
		void move(string to, char board[][8]) override;
		bool isValidMove(string to, char board[][8]) override;
};

class Knight: public Piece {
	public:
		Knight(string currentSquare, string color) : Piece(currentSquare, color){
			value = 3;
			if(color == "white"){
				this->boardChar = 'N';
			} else {
				this->boardChar = 'n';
			}
		}
		virtual void move(string to, char board[][8]);
		virtual bool isValidMove(string to, char board[][8]);
};

class Bishop: public Piece {
	public:
		Bishop(string currentSquare, string color) : Piece(currentSquare, color){
			value = 3;
			if(color == "white"){
				this->boardChar = 'B';
			} else {
				this->boardChar = 'b';
			}
		}
		virtual void move(string to, char board[][8]);
		virtual bool isValidMove(string to, char board[][8]);
};

class Queen: public Piece {
	public:
		Queen(string currentSquare, string color) : Piece(currentSquare, color){
			value = 9;
			if(color == "white"){
				this->boardChar = 'Q';
			} else {
				this->boardChar = 'q';
			}
		}
		virtual void move(string to, char board[][8]);
		virtual bool isValidMove(string to, char board[][8]);
};

class King: public Piece {
	public:
		King(string currentSquare, string color) : Piece(currentSquare, color){
			value = 10000;
			if(color == "white"){
				this->boardChar = 'K';
			} else {
				this->boardChar = 'k';
			}
		}
		virtual void move(string to, char board[][8]);
		virtual bool isValidMove(string to, char board[][8]);
};

class Pieces{	
	public:
		Piece* pieces [16];
		string color;
		
		Pieces(){	
		}
		
		void printPieces();
		virtual int pieceToInt(char piece);
		virtual Piece* pieceInSquare(string square, char board[][8]);
};

class WhitePieces: public Pieces{
	public:
		WhitePieces() : Pieces(){
			this->color = "white";
			
			pieces[0] = new Rook("a1", "white");
			pieces[1] = new Knight("b1", "white");
			pieces[2] = new Bishop("c1", "white");
			pieces[3] = new Queen("d1", "white");
			pieces[4] = new King("e1", "white");
			pieces[5] = new Bishop("f1", "white");
			pieces[6] = new Knight("g1", "white");
			pieces[7] = new Rook("h1", "white");
			pieces[8] = new Pawn("a2", "white");
			pieces[9] = new Pawn("b2", "white");
			pieces[10] = new Pawn("c2", "white");
			pieces[11] = new Pawn("d2", "white");
			pieces[12] = new Pawn("e2", "white");
			pieces[13] = new Pawn("f2", "white");
			pieces[14] = new Pawn("g2", "white");
			pieces[15] = new Pawn("h2", "white");
		}
};

class BlackPieces: public Pieces{
	public:
		BlackPieces() : Pieces(){
			this->color = "black";
			
			pieces[0] = new Rook("a8", "black");
			pieces[1] = new Knight("b8", "black");
			pieces[2] = new Bishop("c8", "black");
			pieces[3] = new Queen("d8", "black");
			pieces[4] = new King("e8", "black");
			pieces[5] = new Bishop("f8", "black");
			pieces[6] = new Knight("g8", "black");
			pieces[7] = new Rook("h8", "black");
			pieces[8] = new Pawn("a7", "black");
			pieces[9] = new Pawn("b7", "black");
			pieces[10] = new Pawn("c7", "black");
			pieces[11] = new Pawn("d7", "black");
			pieces[12] = new Pawn("e7", "black");
			pieces[13] = new Pawn("f7", "black");
			pieces[14] = new Pawn("g7", "black");
			pieces[15] = new Pawn("h7", "black");
		}
};
