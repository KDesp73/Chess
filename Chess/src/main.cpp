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
static string absured_mate = "QQQQQQQQ/QQQQQQQQ/QQQQpppQ/QQRQpkpQ/QQQp1bbQ/QQQP2BQ/QQQRPKQQ/QQQQBQQQ"; 


static bool showMaterial = true;
static bool showMoves = true;
static string playingAs = "white";

void ChessMenu();

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
	string perspective;
	string material;
	string moves;

	cout << "Play from the perspective of white or black? (w/b)" << endl;
	do{
		cout << "> ";
		getline(cin, perspective);
	} while(perspective != "w" && perspective != "b" && perspective != "W" && perspective != "B");

	cout << "\nShow material advantage? (y/n)" << endl;
	do{
		cout << "> ";
		getline(cin, material);
	} while(material != "y" && material != "n" && material != "Y" && material != "N");

	cout << "\nShow moves? (y/n)" << endl;
	do{
		cout << "> ";
		getline(cin, moves);
	} while(moves != "y" && moves != "n" && moves != "Y" && moves != "N");


	if(perspective == "w" || perspective == "W") playingAs = Piece::WHITE;
	if(perspective == "b" || perspective == "B") playingAs = Piece::BLACK;

	if(material == "y" || material == "Y") showMaterial = true;
	if(material == "n" || material == "N") showMaterial = false;
	
	if(moves == "y" || moves == "Y") showMoves = true;
	if(moves == "n" || moves == "N") showMoves = false;

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
	// Test::testCheckMate(TestFens::mate_fens);
	// cin.get();
	// Test::testStaleMate(TestFens::stalemate_fens);
	// cin.get();
	// Test::testDrawDueToInsufficientMaterial(TestFens::ddtim_fens);
	// cin.get();
	// Test::testCheck(TestFens::check_fens);
	// cin.get();
	// Test::testNotCheck(TestFens::should_not_be_check_fens);
	// cin.get();

	
	//ChessMenu();

	//Board b{"r1bqk2r/1pppbppp/p1n2n2/4p3/B7/3P1N2/PPP1PPPP/RNBQK2R"};
	Board b{"2k5/8/8/R6R/8/8/8/2K5"};
	Board::movePiece(Move{"a5", "e5"}, &b);
	Board::movePiece(Move{"e5", "a5"}, &b);
	Board::movePiece(Move{"h5", "e5"}, &b);
	Board::movePiece(Move{"e5", "h5"}, &b);

/*
	b.printBigBoard();
	Board::movePiece(Move{"f3", "d2"}, &b);
	b.printBigBoard();
	Board::movePiece(Move{"d2", "f3"}, &b);
	b.printBigBoard();
	Board::movePiece(Move{"b1", "d2"}, &b);
	b.printBigBoard();
	Board::movePiece(Move{"d2", "f1"}, &b);
	b.printBigBoard();
	Board::movePiece(Move{"f3", "d2"}, &b);
	b.printBigBoard();
	Board::movePiece(Move{"d2", "f3"}, &b);
	b.printBigBoard();
	Board::movePiece(Move{"f1", "d2"}, &b);
	b.printBigBoard();
	Board::movePiece(Move{"d2", "f1"}, &b);
	b.printBigBoard();
*/

	cout << b.exportPGN() << endl;

	return 0;
}
