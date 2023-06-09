#include <iostream>
#include <string>

#include "chess_lib.h"
#include "Tests/tests.h"
#include "Tests/test_fens.h"
#include "../Ansi-Text-Manipulation-Library/AnsiTextLibrary/src/ansi_lib.hpp"

using namespace AnsiTextLib;
using namespace std;

static string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
static string castling_testing_fen = "r3k2r/8/8/8/8/8/8/R3K2R";
static string promoting_testing_fen = "1b6/P7/8/3k4/5K2/8/p7/1B6";
static string random_fen = "r3kb1r/1pp5/p1b2p1p/4p3/8/2N2N2/PPP2PPP/3RR1K1";
static string enpassant_fen = "k7/3p1p2/8/4P3/3p4/8/2P1P3/7K";
static string side_enpassant_fen = "k7/6p1/8/7P/p7/8/1P6/7K";

void ChessMenu();

static bool showMaterial = true;
static string playingAs = "white";

string getUserFEN(){
	string user_fen;
	cout << "Enter FEN: ";
	getline(cin, user_fen);

	return user_fen;
}

string exportGamePGN(Board board){
	string choice;
	cout << "\nExport PGN? (y/n)" << endl;
	do{
		cout << "> ";
		getline(cin, choice);
	} while(choice != "y" && choice != "n" && choice != "Y" && choice != "N");

	if(choice == "n" || choice == "N") return "";
	
	if(choice == "y" || choice == "Y"){
		cout << endl << board.exportPGN() << endl << endl;
		return board.exportPGN();
	}

	return "";
}

void setSettings(){
	cout << Text::blue + "-Settings-" + Text::normal << endl << endl; 
	string p;
	string s;

	cout << "Play from the perspective of white or black? (w/b)" << endl;
	do{
		cout << "> ";
		getline(cin, p);
	} while(p != "w" && p != "b" && p != "W" && p != "B");

	cout << "\nShow material advantage? (y/n)" << endl;
	do{
		cout << "> ";
		getline(cin, s);
	} while(s != "y" && s != "n" && s != "Y" && s != "N");


	if(p == "w" || p == "W") playingAs = Piece::WHITE;
	if(p == "b" || p == "B") playingAs = Piece::BLACK;

	if(s == "y" || s == "Y") showMaterial = true;
	if(s == "n" || s == "N") showMaterial = false;

}

void handleOptions(int option){
	Board b;
	switch (option){
		case 0:
			b = Game::start(starting_fen, playingAs, showMaterial);
			exportGamePGN(b);
			cout << "\n\nPress enter to return to menu..." << endl;
			cin.get();
			break;
		case 1:
			b = Game::start(getUserFEN(), playingAs, showMaterial);
			exportGamePGN(b);
			cout << "\n\nPress enter to return to menu..." << endl;
			cin.get();
			break;
		case 2:
			setSettings();
			cout << "\n\nPress enter to return to menu..." << endl;
			cin.get();
			break;
		case 3:
			exit(0);
		default:
			break;
	}

	ChessMenu();
}

void ChessMenu(){
	menu(4, vector<string>{"Play", "Play from FEN", "Settings", "Exit"}, &handleOptions);
}

int main(int argc, char** argv) {

	ChessMenu();

	Board b{starting_fen};

	b.printBigBoard();
	Board::movePiece(Move{"e2", "e4"}, &b);
	b.moveFor = Piece::BLACK;
	b.printBigBoard();
	Board::movePiece(Move{"e7", "e5"}, &b);
	b.moveFor = Piece::WHITE;
	b.printBigBoard();
	Board::movePiece(Move{"d1", "h5"}, &b);
	b.moveFor = Piece::BLACK;
	b.printBigBoard();
	Board::movePiece(Move{"b8", "c6"}, &b);
	b.moveFor = Piece::WHITE;
	b.printBigBoard();
	Board::movePiece(Move{"f1", "c4"}, &b);
	b.moveFor = Piece::BLACK;
	b.printBigBoard();
	Board::movePiece(Move{"g8", "f6"}, &b);
	b.moveFor = Piece::WHITE;
	b.printBigBoard();
	Board::movePiece(Move{"h5", "f7"}, &b);
	b.moveFor = Piece::BLACK;
	b.printBigBoard();

	cout << b.exportPGN() << endl;

	return 0;
}
