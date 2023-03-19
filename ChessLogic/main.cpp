#include <iostream>
#include <string>

#include "declarations.h"
#include "piece_declarations.h"



int main(int argc, char** argv) {
	//start();
	
	char emptyBoard[][8] = {
		{'R', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{'b', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	};
	
	Rook* r = new Rook("a1", "white");
	cout << "Is valid? > " << r->isValidMove("a6", emptyBoard) << endl;
	
	return 0;
}
