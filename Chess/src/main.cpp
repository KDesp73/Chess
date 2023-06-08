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

	if(p == "y" || p == "Y") showMaterial = true;
	if(p == "n" || p == "N") showMaterial = false;

}

void handleOptions(int option){
	switch (option){
	case 0:
		Game::start(starting_fen, playingAs, showMaterial);
		break;
	case 1:
		Game::start(getUserFEN(), playingAs, showMaterial);
		break;
	case 2:
		setSettings();
		break;
	case 3:
		exit(0);
	default:
		break;
	}

	cout << "Press enter to return to menu..." << endl;
	cin.get();
	ChessMenu();
}

void ChessMenu(){
	menu(4, vector<string>{"Play", "Play from FEN", "Settings", "Exit"}, &handleOptions);
}

int main(int argc, char** argv) {

	ChessMenu();

	return 0;
}
