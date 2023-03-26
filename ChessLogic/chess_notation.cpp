#include <string>
#include <iostream>
#include<ctype.h>

using namespace std;

/*================{ Utils }================*/

void addSpaces(int row, int starting, int numberOfSpaces, char board[][8]); // not used

string addSpaces(int index, int num, string fen); 

/*================{ /Utils }================*/


void importFEN(string fen, char board[][8]){
	cout << fen << endl << endl;
	
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
			board[7-i][j] = rows[i][j];
		}
	}
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

void addSpaces(int row, int starting, int numberOfSpaces, char board[][8]){
	for(int i=starting; i< starting + numberOfSpaces; i++){
		board[row][i] = ' ';
	}
}

string exportFEN(char board[][8]){
	string fen = "";

	for(int i=0; i < 8; i++){
		
		if(i != 0) fen += '/';
		
		for(int j=0; j < 8; j++){
			fen += board[7-i][j];
		}
		cout << fen << endl;
	}
	
	cout << fen << endl;
	return fen;
}

 
