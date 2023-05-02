#include "piece_declarations.h"
#include "../Board/board_declarations.h"



bool King::move(string to, char board[][8]){
	if(!isValidMove(to, board)) return false;

    King::hasMoved = true;

    // in case of castling //
    int* fromCoords = translateSquare(currentSquare);
	int* toCoords = translateSquare(to);

	int fromRow = fromCoords[0], fromCol = fromCoords[1];
    int toRow = toCoords[0], toCol = toCoords[1];

    int colDiff = abs(fromCol - toCol);

    if(colDiff == 2) {
        return King::castle(to, board);
    }
    // // //
	
	return Piece::move(to, board);
}

bool King::isValidMove(string to, char board[][8]) {
	int* fromCoords = translateSquare(currentSquare);
	int* toCoords = translateSquare(to);

	int fromRow = fromCoords[0], fromCol = fromCoords[1], toRow = toCoords[0], toCol = toCoords[1];

	int rowDiff = abs(fromRow - toRow);
    int colDiff = abs(fromCol - toCol);

	if(this->capturesOwnPiece(toCoords, board)) return false;

    // check if king wants to castle
    if(colDiff == 2 && canCastle(to, board)) {
        cout << "The king can castle" << endl;
        return true;
    }

    // Check if the move is valid (1 square in any direction)
    if (rowDiff <= 1 && colDiff <= 1)
        return true;

    return false;
}

bool King::canCastle(string to, char board[][8]){
    int* fromCoords = translateSquare(currentSquare);
	int* toCoords = translateSquare(to);

	int fromRow = fromCoords[0], fromCol = fromCoords[1];
    int toRow = toCoords[0], toCol = toCoords[1];

    int direction = toCol - fromCol;

    if(hasMoved) return false;
    if(toRow - fromRow != 0) return false;
    if(abs(direction) != 2) return false;

    // is the space between the king and the rook empty?
    // is the king in check?
    // will the king be in check?
    // did the wanted rook move?


    return true;
}

Rook* getRookToCastle(int direction, string color, char board[][8]){
    Piece *wantedRook;
    if(direction > 0 && color == "white"){
        wantedRook = pieceFromChar(0, 7, board);
    } else if(direction < 0 && color == "white"){
        wantedRook = pieceFromChar(0, 0, board);
    } else if(direction > 0 && color == "black"){
        wantedRook = pieceFromChar(7, 7, board);
    } else if(direction < 0 && color == "black"){
        wantedRook = pieceFromChar(7, 0, board);
    }

    cout << "Wanted rook: "; 
    wantedRook->printPiece();
    cout << endl;


    return dynamic_cast<Rook*>(wantedRook);
}

bool King::castle(string to, char board[][8]){
    if(!canCastle(to, board)) return false;

    int* fromCoords = translateSquare(currentSquare);
	int* toCoords = translateSquare(to);

	int fromRow = fromCoords[0], fromCol = fromCoords[1];
    int toRow = toCoords[0], toCol = toCoords[1];

    int direction = toCol - fromCol;

    Rook* wantedRook = getRookToCastle(direction, this->color, board);

    if(wantedRook == NULL) return false;
    cout << "here" << endl;

    return move(to, board);
}

bool King::isInCheck(){
    return false;
}

vector<string> King::getValidMoves(char board[][8]){
	vector<string> ret;
	string letters = "abcdefgh";

	string moveToCheck;
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			moveToCheck = letters[i] + to_string((j+1));

			if(this->isValidMove(moveToCheck, board)){
				ret.push_back(moveToCheck);
			}

		}	
	}
	return ret;
}