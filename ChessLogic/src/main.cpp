#include <iostream>
#include <string>

#include "Board/board_declarations.h"
#include "Board/notation.h"
#include "Board/game_logic.h"
#include "Pieces/piece_declarations.h"

void test_importFEN(){
	while(true){
		char emptyBoard[][8] = {
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		};
		
		string fen;
		cout << "Enter fen: ";
		cin >> fen;
		
		importFEN(fen, emptyBoard);
		
		printBoard(emptyBoard);
	}
}

void test_exportFEN(){
	char emptyBoard[][8] = {
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	};

	string fen = "4k2r/6r1/8/8/8/8/3R4/R3K3";

	importFEN(fen, emptyBoard);

	printBoard(emptyBoard);

	cout << "Original: " << fen << endl << "Exported: " << exportFEN(emptyBoard) << endl;
}

int main(int argc, char** argv) {
	string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

	char board[][8] = {
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	};

	//start(starting_fen);

	Pieces* wp = new WhitePieces();
	Pieces* bp = new BlackPieces();
	string *move;

	importFEN(starting_fen, board);
	printBoard(board);

	wp->loadPieces(board);
	bp->loadPieces(board);

	wp->printPieces();
	bp->printPieces();

	cout << wp->calculateMaterial() << endl;
	cout << bp->calculateMaterial() << endl;



	return 0;
}
