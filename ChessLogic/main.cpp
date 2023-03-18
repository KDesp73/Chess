#include <iostream>
#include <string>

#include "declarations.h"
#include "piece_declarations.h"



int main(int argc, char** argv) {
	//start();
	
	char emptyBoard[][8] = {
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{'P', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	};
	
	Pawn* p = new Pawn("a2", "white");
	cout << "Is valid? > " << (*p).isValidMove("a4", emptyBoard) << endl;
	
	return 0;
}
