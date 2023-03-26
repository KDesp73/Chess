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
		void move(string to, char board[][8]) override;
		bool isValidMove(string to, char board[][8]) override;
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
		void move(string to, char board[][8]) override;
		bool isValidMove(string to, char board[][8]) override;
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
		void move(string to, char board[][8]) override;
		bool isValidMove(string to, char board[][8]) override;
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
		void move(string to, char board[][8]) override;
		bool isValidMove(string to, char board[][8]) override;
};

/*==========================={ Pieces }===========================*/

class Pieces{	
	public:
		Piece* pieces[16];
		string color;
		
		virtual ~Pieces(){
		}
		
		Pieces(){	
		}
		
		void printPieces();
		//int pieceToInt(char piece){} // no clue why i put that here
		Piece* pieceInSquare(string square, char board[][8]);
};

class WhitePieces: public Pieces{
	public:
		WhitePieces(){
			this->color = "white";
			
			/*
			pieces[0] = new Rook("a1", color);
			pieces[1] = new Knight("b1", color);
			pieces[2] = new Bishop("c1", color);
			pieces[3] = new Queen("d1", color);
			pieces[4] = new King("e1", color);
			pieces[5] = new Bishop("f1", color);
			pieces[6] = new Knight("g1", color);
			pieces[7] = new Rook("h1", color);
			pieces[8] = new Pawn("a2", color);
			pieces[9] = new Pawn("b2", color);
			pieces[10] = new Pawn("c2", color);
			pieces[11] = new Pawn("d2", color);
			pieces[12] = new Pawn("e2", color);
			pieces[13] = new Pawn("f2", color);
			pieces[14] = new Pawn("g2", color);
			pieces[15] = new Pawn("h2", color);
			*/
		}
};

class BlackPieces: public Pieces{
	public:
		BlackPieces(){
			this->color = "black";
			
			/*
			pieces[0] = new Rook("a8", color);
			pieces[1] = new Knight("b8", color);
			pieces[2] = new Bishop("c8", color);
			pieces[3] = new Queen("d8", color);
			pieces[4] = new King("e8", color);
			pieces[5] = new Bishop("f8", color);
			pieces[6] = new Knight("g8", color);
			pieces[7] = new Rook("h8", color);
			pieces[8] = new Pawn("a7", color);
			pieces[9] = new Pawn("b7", color);
			pieces[10] = new Pawn("c7", color);
			pieces[11] = new Pawn("d7", color);
			pieces[12] = new Pawn("e7", color);
			pieces[13] = new Pawn("f7", color);
			pieces[14] = new Pawn("g7", color);
			pieces[15] = new Pawn("h7", color);
			*/
		}
};
