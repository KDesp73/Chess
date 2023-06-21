#include <iostream>
#include <string>

#include "chess_lib.h"
#include "../tests/tests.h"
#include "../tests/test_fens.h"
#include "../Ansi-Text-Manipulation-Library/AnsiTextLibrary/src/ansi_lib.hpp"

#define TESTS false

using namespace AnsiTextLib;
using namespace std;

static string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
static string castling_testing_fen = "r3k2r/8/8/8/8/8/8/R3K2R";
static string promoting_testing_fen = "1b6/P7/8/3k4/5K2/8/p7/1B6";
static string random_fen = "r3kb1r/1pp5/p1b2p1p/4p3/8/2N2N2/PPP2PPP/3RR1K1";
static string enpassant_fen = "k7/3p1p2/8/4P3/3p4/8/2P1P3/7K";
static string side_enpassant_fen = "k7/6p1/8/7P/p7/8/1P6/7K";
static string absurd_mate = "QQQQQQQQ/QQQQQQQQ/QQQQpppQ/QQRQpkpQ/QQQp1bbQ/QQQP2BQ/QQQRPKQQ/QQQQBQQQ"; 
static string test_mate = "4r1k1/B4p1p/2p2n2/1p3b2/8/5N2/5PPP/3r1K1R w";

static bool showMaterial = true;
static bool showMoves = true;
static string playingAs = "white";
static string prompt_type = "oneline";
static string interface = "gui";
static int window_size = 60;
static string piece_theme = "wiki";


string getUserFEN(){
	string user_fen;
	do{
		cout << "Enter FEN: ";
		getline(cin, user_fen);
		cout << endl;
	} while(!Board::isValidFEN(user_fen));

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
	string prompt_t;

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

	cout << "\nInput move in seperate lines or in one line? (s/o)" << endl;
	do{
		cout << "> ";
		getline(cin, prompt_t);
	} while(prompt_t != "s" && prompt_t != "S" && prompt_t != "o" && prompt_t != "O");


	if(perspective == "w" || perspective == "W") playingAs = Piece::WHITE;
	if(perspective == "b" || perspective == "B") playingAs = Piece::BLACK;

	if(material == "y" || material == "Y") showMaterial = true;
	if(material == "n" || material == "N") showMaterial = false;
	
	if(moves == "y" || moves == "Y") showMoves = true;
	if(moves == "n" || moves == "N") showMoves = false;

	if(prompt_t == "s" || prompt_t == "S") prompt_type = Board::SEPERATE;
	if(prompt_t == "o" || prompt_t == "O") prompt_type = Board::ONELINE;

}

void MenuHandles::handleInputOptions(int option){
	switch (option){
	case 0:
		prompt_type = Board::SEPERATE;
		break;
	case 1:
		prompt_type = Board::ONELINE;
		break;
	case 2:
		Menu::SettingsSubMenu();
	default:
		break;
	}
}

void MenuHandles::handlePerspectiveOptions(int option){
	switch (option){
	case 0: 
		playingAs = Piece::WHITE;
		break;
	case 1: 
		playingAs = Piece::BLACK;
		break;
	case 2:
		Menu::SettingsSubMenu();
	default:
		break;
	}
}

void MenuHandles::handleMovesOptions(int option){
	switch (option){
	case 0:
		showMoves = true;
		break;
	case 1:
		showMoves = false;
		break;
	case 2:
		Menu::SettingsSubMenu();
		break;
	default:
		break;
	}
}

void MenuHandles::handleMaterialOptions(int option){
	switch (option){
	case 0:
		showMaterial = true;
		break;
	case 1:
		showMaterial = false;
		break;
	case 2:
		Menu::SettingsSubMenu();
		break;
	default:
		break;
	}
}

void MenuHandles::handleInterfaceOptions(int option){
	switch (option){
	case 0:
		interface = Board::CLI;
		break;
	case 1:
		interface = Board::GUI;
		break;
	case 2:
		Menu::SettingsSubMenu();
		break;
	default:
		break;
	}
}

void MenuHandles::handleMenuOptions(int option){
	Board b;
	switch (option){
		case 0:
			b = {starting_fen, playingAs, showMaterial, showMoves, prompt_type, window_size, piece_theme};
			Game::start(&b, interface);

			exportGamePGN(b);
			cout << "\n\nPress enter to return to menu..." << endl;
			cin.get();
			break;
		case 1:
			b = {getUserFEN(), playingAs, showMaterial, showMoves, prompt_type, window_size, piece_theme};
			Game::start(&b, interface);
			
			exportGamePGN(b);
			cout << "\n\nPress enter to return to menu..." << endl;
			cin.get();
			break;
		case 2:
			Menu::SettingsSubMenu();
			break;
		case 3:
			exit(0);
		default:
			break;
	}

	Menu::ChessMenu();
}

void MenuHandles::handleSizeOptions(int option){
	switch (option){
		case 0:
			window_size = 30;
			break;
		case 1:
			window_size = 40;
			break;
		case 2:
			window_size = 50;
			break;
		case 3:
			window_size = 60;
			break;
		case 4:
			window_size = 70;
			break;
		case 5:
			window_size = 60;
			break;
		case 6:
			window_size = 70;
			break;
		case 7:
			window_size = 80;
			break;
		case 8:
			window_size = 90;
			break;
		case 9:
			window_size = 100;
			break;
		case 10:
			Menu::SettingsSubMenu();
		default:
			break;
	}
}

void MenuHandles::handleThemeOptions(int option){
	switch (option){
	case 0:
		piece_theme = Board::WIKI;
		break;
	case 1:
		piece_theme = Board::STAUNTY;
		break;
	case 2:
		piece_theme = Board::MERIDA;
		break;
	case 3:
		Menu::SettingsSubMenu();
	default:
		break;
	}
}

void MenuHandles::handleSettingsOptions(int option){
	switch (option){
	case 0:
		Menu::InterfaceTypeSettingsSubMenu();
		break;
	case 1:
		Menu::MaterialSettingsSubMenu();
		break;
	case 2:
		Menu::MovesSettingsSubMenu();
		break;
	case 3:
		Menu::PlayingAsSettingsSubMenu();
		break;
	case 4:
		Menu::PromptTypeSettingsSubMenu();
		break;
	case 5:
		Menu::WindowSizeSettingsSubMenu();
		break;
	case 6:
		Menu::PieceThemeSettingsSubMenu();
		break;
	case 7:
		Menu::ChessMenu();
		break;
	default:
		break;
	}
	Menu::SettingsSubMenu();
}



int main(int argc, char** argv) {
	if(argv[argc-1][0] == 't' &&
		argv[argc-1][1] == 'e' &&
		argv[argc-1][2] == 's' &&
		argv[argc-1][3] == 't'
	){
		Test::testCheckMate(TestFens::mate_fens);
		cin.get();
		Test::testCheck(TestFens::check_fens);
		cin.get();
		Test::testDrawDueToInsufficientMaterial(TestFens::ddtim_fens);
		cin.get();
		Test::testStaleMate(TestFens::stalemate_fens);
		cin.get();
		Test::testNotCheck(TestFens::should_not_be_check_fens);
		cin.get();

		exit(0);
	}
	
	//Test::testCheckMate(vector<string>{"8/8/8/3kQ3/5K2/8/8/1BQ5 b"});
	//cin.get();
	Menu::ChessMenu();

	
	return 0;
}
