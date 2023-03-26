#include "piece_declarations.h"
#include "board_declarations.h"
#include <cstdlib>


void Rook::move(string to, char board[][8]){
	if(!isValidMove(to, board)) return;
	
	Piece::move(to, board);

}

bool Rook::isValidMove(string to, char board[][8]) {
	char file = currentSquare.at(0);
	int rank = currentSquare.at(1) - 48;
	
	cout << file << " " << rank << endl;
	
	char toFile = to.at(0);
	int toRank = to.at(1) - 48;
	
	cout << toFile << " " << toRank << endl;
	
	int* toCoords = translateSquare(to);
	
	if((file != toFile) && (rank != toRank)) return false; // No diagonal movement
	if(currentSquare == to) return false; // No move to currentSquare
	//if(board[*toCoords][*(toCoords+1)] != ' ') return false; //
	
	if(file == toFile){
		for(int i=1; i < abs(file-toFile); i++){
			if(board[*toCoords - i][*(toCoords+1)] != ' ') return false;
		}
	}
	
	if(rank == toRank){
		for(int i=1; i < abs(rank-toRank); i++){
			if(board[*toCoords][*(toCoords+1) - i] != ' ') return false;
		}
	}
	
	return true;
}
