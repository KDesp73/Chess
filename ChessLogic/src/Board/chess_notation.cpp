#include <string>
#include <iostream>
#include<ctype.h>

#include "board_declarations.h"
#include "board.h"

using namespace std;

/*================{ Utils }================*/

void addSpaces(int row, int starting, int numberOfSpaces, char board[][8]); // not used

string addSpaces(int index, int num, string fen); 

string replaceSpaces(string fen);

/*================{ /Utils }================*/


void Board::importFEN(string fen){
	//cout << fen << endl << endl;
	
	string rows[8];
	
	int count = 0;
	string temp = "";
	for(int i=0; i < fen.length(); i++){
		if(fen[i] != '/'){
			if(isdigit(fen[i])){
				int num = fen[i] - 48;
				fen = addSpaces(i, num, fen);
			}
			
			temp = temp + fen[i];
		} else {
			rows[count++] = temp;
			temp = "";
		}
	}
	rows[count++] = temp;
	
	for(int i=0; i<8; i++){
		for(int j=0; j<rows[i].length(); j++){
			this->board[7-i][j] = rows[i][j];
		}
	}
}

string Board::exportFEN(){
	string temp_fen = "";

	for(int i=0; i < 8; i++){
		
		if(i != 0) temp_fen += '/';
		
		for(int j=0; j < 8; j++){
			temp_fen += this->board[7-i][j];
		}
	}
	
	string fen = replaceSpaces(temp_fen);

	return fen;
}

string exportFEN(char board[][8]){
	string temp_fen = "";

	for(int i=0; i < 8; i++){
		
		if(i != 0) temp_fen += '/';
		
		for(int j=0; j < 8; j++){
			temp_fen += board[7-i][j];
		}
	}
	
	string fen = replaceSpaces(temp_fen);

	return fen;
}


string addSpaces(int index, int num, string fen){
	fen[index] = ' ';
	
	string firstHalf = fen.substr(0, index);
	string secondHalf = fen.substr(index+1, fen.length()-1);
	
	string spaces = "";
	for(int i=0; i<num; i++){
		spaces += ' ';
	}
	
	return firstHalf + spaces + secondHalf;
}

//Not used
void addSpaces(int row, int starting, int numberOfSpaces, char board[][8]){
	for(int i=starting; i< starting + numberOfSpaces; i++){
		board[row][i] = ' ';
	}
}


string replaceSpaces(string fen){
	for(int i = 0; i < fen.length(); i++){
		if(fen[i] == ' '){
			
			int count = 0;
			do{
				count++;
			}
			while (fen[i+count] == ' ');
			
			fen.replace(i, count, to_string(count));

			i++;
		}
	}
	return fen;
}
