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
		string type;
		
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
		virtual bool move(string to, char board[][8]);
		virtual void printPiece();
		virtual bool isValidMove(string to, char board[][8]){return false;}
};

class Pawn: public Piece {
	public:
		Pawn(string currentSquare, string color) {
			//Piece::Piece(currentSquare, color);
			value = 1;
			this->type = "Pawn";
			this->color = color;
			this->currentSquare = currentSquare;
			if(color == "white"){
				this->boardChar = 'P';
			} else {
				this->boardChar = 'p';
			}
		}
		bool move(string to, char board[][8]) override;
		bool isValidMove(string to, char board[][8]) override;
		bool isValidCapture(string to, char board[][8]);
		void promote(char board[][8]);
};


class Rook: public Piece {
	public:
		bool hasMoved = false;
		Rook(string currentSquare, string color) : Piece(currentSquare, color) {
			this->type = "Rook";
			this->color = color;
			this->currentSquare = currentSquare;
			value = 5;
			if(color == "white"){
				this->boardChar = 'R';
			} else {
				this->boardChar = 'r';
			}
		}
		bool move(string to, char board[][8]) override;
		bool isValidMove(string to, char board[][8]) override;
};

class Knight: public Piece {
	public:
		Knight(string currentSquare, string color) : Piece(currentSquare, color){
			value = 3;
			this->type = "Knight";
			this->color = color;
			this->currentSquare = currentSquare;
			if(color == "white"){
				this->boardChar = 'N';
			} else {
				this->boardChar = 'n';
			}
		}
		bool move(string to, char board[][8]) override;
		bool isValidMove(string to, char board[][8]) override;
};

class Bishop: public Piece {
	public:
		Bishop(string currentSquare, string color) : Piece(currentSquare, color){
			value = 3;
			this->type = "Bishop";
			this->color = color;
			this->currentSquare = currentSquare;
			if(color == "white"){
				this->boardChar = 'B';
			} else {
				this->boardChar = 'b';
			}
		}
		bool move(string to, char board[][8]) override;
		bool isValidMove(string to, char board[][8]) override;
};

class Queen: public Piece {
	public:
		Queen(string currentSquare, string color) : Piece(currentSquare, color){
			value = 9;
			this->type = "Queen";
			this->color = color;
			this->currentSquare = currentSquare;
			if(color == "white"){
				this->boardChar = 'Q';
			} else {
				this->boardChar = 'q';
			}
		}
		bool move(string to, char board[][8]) override;
		bool isValidMove(string to, char board[][8]) override;
};

class King: public Piece {
	public:
		bool hasMoved = false;
		bool inCheck = false;
		King(string currentSquare, string color) : Piece(currentSquare, color){
			value = 10000;
			this->type = "King";
			this->color = color;
			this->currentSquare = currentSquare;
			if(color == "white"){
				this->boardChar = 'K';
			} else {
				this->boardChar = 'k';
			}
		}
		bool move(string to, char board[][8]) override;
		bool isValidMove(string to, char board[][8]) override;
		bool canCastle(string to, char board[][8]);
		bool castle(string to, char board[][8]);
		bool isInCheck();
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

Piece* pieceFromChar(int x, int y, char board[][8]);