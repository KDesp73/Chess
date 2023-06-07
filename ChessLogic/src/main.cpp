#include <iostream>
#include <string>

#include "chess_lib.h"

#include "Tests/tests.h"
#include "Tests/test_fens.h"
#include "../Ansi-Text-Manipulation-Library/AnsiTextLibrary/src/ansi_lib.hpp"
using namespace AnsiTextLib;

static string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
static string castling_testing_fen = "r3k2r/8/8/8/8/8/8/R3K2R";
static string promoting_testing_fen = "1b6/P7/8/3k4/5K2/8/p7/1B6";
static string random_fen = "r3kb1r/1pp5/p1b2p1p/4p3/8/2N2N2/PPP2PPP/3RR1K1";

void ChessMenu();

void handleOptions(int option){
	switch (option){
	case 0:
		Game::start(starting_fen);
		break;
	case 1:
		Test::testCheckMate(TestFens::mate_fens);
		cout << "Press enter to return to menu..." << endl;
		cin.get();
		ChessMenu();
	case 2:
		Test::testCheck(TestFens::check_fens);
		cout << "Press enter to return to menu..." << endl;
		cin.get();
		ChessMenu();
	case 3:
		Test::testPins(TestFens::pin_fens, TestFens::pinned_squares);
		cout << "Press enter to return to menu..." << endl;
		cin.get();
		ChessMenu();
	case 4:
		cout << "Press enter to exit..." << endl;
		cin.get();
		exit(0);
	default:
		break;
	}
}

void ChessMenu(){
	menu(4, vector<string>{"Play Chess", "Test Mate", "Test Check", "Test Pins", "Exit"}, &handleOptions);
}

int main(int argc, char** argv) {


	ChessMenu();
	

	return 0;
}
