# include "tests.h"

#include "../chess_lib.h"
#include "../Board/board_utils.h"
#include "../../Ansi-Text-Manipulation-Library/AnsiTextLibrary/src/ansi_lib.hpp"

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace BoardUtils;
using namespace AnsiTextLib;

bool Test::testCheckMate(vector<string> mate_fens){
	int passed_count = 0, failed_count = 0;
	Text::clearScreen();
	cout << Text::b_cyan + "Testing Mate...\n" + Text::normal << endl;
	bool passed = true;
	for (int i = 0; i < mate_fens.size(); i++){
		Board b{"white", mate_fens.at(i)};
		//b.printBigBoard();

		Piece *p = b.findPiece("King", "white");
		King *king = dynamic_cast<King *>(p);

		if(b.isInCheckmate(king)) {
			passed_count++;
			cout << Text::green + "Passed\n" + Text::normal;
			
		}else{
			passed = false;
			failed_count++;
			cout << Text::red + "Failed" + Text::normal +" at: " + mate_fens.at(i) + "\n";
		}
	}

	cout << endl << endl << Text::green + "Passed: " + to_string(passed_count) + Text::normal << endl;
	cout << Text::red + "Failed: " + to_string(failed_count) + Text::normal << endl;

	return passed;
}

bool Test::testCheckMate(string mate_fen){
	return Test::testCheckMate(vector<string>{mate_fen});
}

bool Test::testPins(vector<string> pin_fens, vector<string> squaresToCheck){
    int passed_count = 0, failed_count = 0;
    Text::clearScreen();

    cout << Text::b_cyan + "Testing Pins...\n" + Text::normal << endl;
	bool passed = true;
	for (int i = 0; i < pin_fens.size(); i++){
		Board b{"white", pin_fens.at(i)};
		//b.printBigBoard();

		Piece *p = b.findPiece(squaresToCheck.at(i));

		if(Board::isPinned(p, &b)){
            cout << Text::green + "Passed" + Text::normal << endl;
            passed_count++;
        } else{
            passed = false;
            cout << Text::red + "Failed" + Text::normal << " at: " + pin_fens.at(i) + " - " + squaresToCheck.at(i) << endl;
            failed_count++;
        }
	}

	cout << endl << endl << Text::green + "Passed: " + to_string(passed_count) + Text::normal << endl;
	cout << Text::red + "Failed: " + to_string(failed_count) + Text::normal << endl;

	return passed;
}

bool Test::testPins(string pin_fen, string square){
	return Test::testPins(vector<string>{pin_fen}, vector<string>{square});
}



bool Test::testCheck(vector<string> check_fens){
	int passed_count = 0, failed_count = 0;
	Text::clearScreen();
	cout << Text::b_cyan + "Testing Checks...\n" + Text::normal << endl;
	bool passed = true;
	for (int i = 0; i < check_fens.size(); i++){
		Board b{"white", check_fens.at(i)};
		//b.printBigBoard();

		Piece *p = b.findPiece("King", "white");
		King *king = dynamic_cast<King *>(p);
		//printValidMoves(king, temp_fen);

		(!king->isInCheck(b.board).empty()) ? cout << Text::green + "Passed\n" + Text::normal : cout << Text::red + "Failed" + Text::normal +" at: " + check_fens.at(i) + "\n";
	
		if(king->isInCheck(b.board).empty()) {
			passed = false;
			failed_count++;
		}else{
			passed_count++;
		}
	}

	cout << endl << endl << Text::green + "Passed: " + to_string(passed_count) + Text::normal << endl;
	cout << Text::red + "Failed: " + to_string(failed_count) + Text::normal << endl;

	return passed;
}

bool Test::testCheck(string check_fen){
	return Test::testCheck(vector<string>{check_fen});
}


bool Test::testNotCheck(vector<string> should_not_be_check_fens){
	int passed_count = 0, failed_count = 0;
	Text::clearScreen();
	cout << Text::b_cyan + "Testing Not in Check...\n" + Text::normal << endl;
	bool passed = true;
	for (int i = 0; i < should_not_be_check_fens.size(); i++){
		Board b{"white", should_not_be_check_fens.at(i)};
		//b.printBigBoard();

		Piece *p = b.findPiece("King", "white");
		King *king = dynamic_cast<King *>(p);
		//printValidMoves(king, temp_fen);

		(king->isInCheck(b.board).empty()) ? cout << Text::green + "Passed\n" + Text::normal : cout << Text::red + "Failed" + Text::normal +" at: " + should_not_be_check_fens.at(i) + "\n";
	
		if(!king->isInCheck(b.board).empty()) {
			passed = false;
			failed_count++;
		}else{
			passed_count++;
		}
	}

	cout << endl << endl << Text::green + "Passed: " + to_string(passed_count) + Text::normal << endl;
	cout << Text::red + "Failed: " + to_string(failed_count) + Text::normal << endl;

	return passed;
}

bool Test::testNotCheck(string should_not_be_check_fen){
	return Test::testNotCheck(vector<string>{should_not_be_check_fen});
}