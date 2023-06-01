#pragma once

#include <iostream>
#include <vector>
#include "../Board/structs.h"

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
			}
			
			this->currentSquare = currentSquare;
			this->color = color;
		}
		virtual void printPiece();
		virtual bool isValidMove(string to, char board[][8]){return false;}
		virtual vector<string> getValidMoves(char board[][8]){vector<string> ret; return ret;}
		bool capturesOwnPiece(Coords toCoords, char board[][8]);
};

class Pawn: public Piece {
	public:
		Pawn(string currentSquare, string color) : Piece(currentSquare, color){
			value = 1;
			this->type = "Pawn";
			if(color == "white"){
				this->boardChar = 'P';
			} else {
				this->boardChar = 'p';
			}
		}
		bool isValidMove(string to, char board[][8]) override;
		vector<string> getValidMoves(char board[][8]) override;
		bool isValidCapture(string to, char board[][8]);
		bool canPromote(string to, char board[][8]);
};


class Rook: public Piece {
	public:
		bool hasMoved = false;
		Rook(string currentSquare, string color) : Piece(currentSquare, color) {
			this->type = "Rook";
			value = 5;
			if(color == "white"){
				this->boardChar = 'R';
			} else {
				this->boardChar = 'r';
			}
		}
		bool isValidMove(string to, char board[][8]) override;
		vector<string> getValidMoves(char board[][8]) override;
};

class Knight: public Piece {
	public:
		Knight(string currentSquare, string color) : Piece(currentSquare, color){
			value = 3;
			this->type = "Knight";
			if(color == "white"){
				this->boardChar = 'N';
			} else {
				this->boardChar = 'n';
			}
		}
		bool isValidMove(string to, char board[][8]) override;
		vector<string> getValidMoves(char board[][8]) override;
};

class Bishop: public Piece {
	public:
		Bishop(string currentSquare, string color) : Piece(currentSquare, color){
			value = 3;
			this->type = "Bishop";
			if(color == "white"){
				this->boardChar = 'B';
			} else {
				this->boardChar = 'b';
			}
		}
		vector<string> getValidMoves(char board[][8]) override;
		bool isValidMove(string to, char board[][8]) override;
};

class Queen: public Piece {
	public:
		Queen(string currentSquare, string color) : Piece(currentSquare, color){
			value = 9;
			this->type = "Queen";
			if(color == "white"){
				this->boardChar = 'Q';
			} else {
				this->boardChar = 'q';
			}
		}
		bool isValidMove(string to, char board[][8]) override;
		vector<string> getValidMoves(char board[][8]) override;
};

class King: public Piece {
	public:
		bool hasMoved = false;
		King(string currentSquare, string color) : Piece(currentSquare, color){
			value = 10000;
			this->type = "King";
			if(color == "white"){
				this->boardChar = 'K';
			} else {
				this->boardChar = 'k';
			}
		}
		bool isValidMove(string to, char board[][8]) override;
		vector<string> getValidMoves(char board[][8]) override;
		bool canCastle(string to, char board[][8]);
		bool castle(string to, char board[][8]);
		bool isInCheck(char board[][8]);
		bool isInCheck(string to, char board[][8]);
		bool isInCheckmate(char board[][8]);
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



