#pragma once

#include <iostream>
#include <vector>
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
		virtual bool isValidMove(string to, char board[][8]){return false;}
};

class Pawn: public Piece {
	public:
		Pawn(string currentSquare, string color) {
			//Piece::Piece(currentSquare, color);
			value = 1;
			this->color = color;
			this->currentSquare = currentSquare;
			if(color == "white"){
				this->boardChar = 'P';
			} else {
				this->boardChar = 'p';
			}
		}
		void move(string to, char board[][8]) override;
		bool isValidMove(string to, char board[][8]) override;
		void promote(char board[][8]);
};


class Rook: public Piece {
	public:
		Rook(string currentSquare, string color) : Piece(currentSquare, color) {
			this->color = color;
			this->currentSquare = currentSquare;
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
			this->color = color;
			this->currentSquare = currentSquare;
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
			this->color = color;
			this->currentSquare = currentSquare;
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
			this->color = color;
			this->currentSquare = currentSquare;
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
			this->color = color;
			this->currentSquare = currentSquare;
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
		vector<Piece*> pieces;
		int material;
		string color;
		
		virtual ~Pieces(){
		}
		
		Pieces(){	
		}
		
		void printPieces();
		Piece* pieceInSquare(string square, char board[][8]);
		int calculateMaterial();
		virtual void loadPieces(char board[][8]) = 0;

};

class WhitePieces : public Pieces{
	public:
		~WhitePieces(){}
		WhitePieces() : Pieces(){
			this->color = "white";
		}

		void loadPieces(char board[][8]) override;
};

class BlackPieces : public Pieces{
	public:
		~BlackPieces(){}
		BlackPieces() : Pieces(){
			this->color = "black";
		}

		void loadPieces(char board[][8]) override;
};

Piece* returnPieceFromSquare(int x, int y, char board[][8]);