#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include<ctype.h>

#include "board.h"
#include "board_utils.h"

using namespace std;

/*================{ Utils }================*/

void addSpaces(int row, int starting, int numberOfSpaces, char board[][8]); // not used

string addSpaces(int index, int num, string fen); 

string replaceSpaces(string fen);

std::vector<std::string> splitString(const std::string& input, char delimiter);

int findMove(Move move, vector<Move> moves);

int characterQuantity(char c, string str);

/*================{ /Utils }================*/


void Board::importFEN(string fen){
	vector<string> fields = splitString(fen, ' ');
	
	string move_for = "w";
	string castling_rights = "KQkq";
	string enpassant_square = "-";

	fen = fields.at(0);

	if(fields.size() > 1)
		move_for = fields.at(1);
	if(fields.size() > 2)
		castling_rights = fields.at(2);
	if(fields.size() > 3)
		enpassant_square = fields.at(3);
	

	this->moveFor = (move_for == "w") ? Piece::WHITE : Piece::BLACK;
	this->castling_rights = castling_rights;	

	if(enpassant_square != "-"){
		if(BoardUtils::isValidSquare(enpassant_square)){
			char file = enpassant_square.at(0);
			int rank = int(enpassant_square.at(1)) - 48;
			int direction = (rank == 3) ? 1 : -1;

			this->move_1_before = new Move{string(1, file) + to_string(rank - 1 * direction), string(1, file) + to_string(rank + 1 * direction)};
		} else enpassant_square = "-";
	}

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

string Board::exportFEN(Board *board){
	string temp_fen = "";

	for(int i=0; i < 8; i++){
		
		if(i != 0) temp_fen += '/';
		
		for(int j=0; j < 8; j++){
			temp_fen += board->board[7-i][j];
		}
	}
	
	string fen = replaceSpaces(temp_fen);

	string move_for = (board->moveFor == Piece::WHITE) ? "w" : "b";
	string castling_rights;
	string enpassant_square = "-";

	if(!dynamic_cast<King * >(board->findPiece(Piece::KING, Piece::WHITE))->h_rook_moved) castling_rights += "K";
	if(!dynamic_cast<King * >(board->findPiece(Piece::KING, Piece::WHITE))->a_rook_moved) castling_rights += "Q";
	if(!dynamic_cast<King * >(board->findPiece(Piece::KING, Piece::BLACK))->h_rook_moved) castling_rights += "k";
	if(!dynamic_cast<King * >(board->findPiece(Piece::KING, Piece::BLACK))->a_rook_moved) castling_rights += "q";

	vector<Move> enpassant_moves = {
		{"a2", "a4"},	
		{"b2", "b4"},	
		{"c2", "c4"},	
		{"d2", "d4"},	
		{"e2", "e4"},	
		{"f2", "f4"},	
		{"g2", "g4"},	
		{"h2", "h4"},
		{"a7", "a5"},	
		{"b7", "b5"},	
		{"c7", "c5"},	
		{"d7", "d5"},	
		{"e7", "e5"},	
		{"f7", "f5"},	
		{"g7", "g5"},	
		{"h7", "h5"}	
	};

	if(findMove(*board->move_1_before, enpassant_moves) > 0){
		char file = board->move_1_before->from.at(0);
		int rank = int(board->move_1_before->from.at(1)) - 48;

		int direction = (rank == 2) ? 1 : -1;

		enpassant_square = string(1, file) + to_string(rank + direction);
	}

	fen += " " + move_for;
	fen += " " + castling_rights;
	fen += " " + enpassant_square;

	return fen;
}



string Board::exportFEN(char board[][8]){
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




bool Board::isValidFEN(string fen_string){
	string accepted_fen_characters = "rnbkqpRNBKQP/12345678";
	string accepted_castling_characters = "KkQq";

	vector<string> fields = splitString(fen_string, ' ');
	
	string fen = fen_string;
	string move_for = "w";
	string castling_rights = "KQkq";
	string enpassant_square = "-";

	fen = fields.at(0);
	if(fields.size() > 1)
		move_for = fields.at(1);
	if(fields.size() > 2)
		castling_rights = fields.at(2);
	if(fields.size() > 3)
		enpassant_square = fields.at(3);

	
	for (size_t i = 0; i < fen.size(); i++){
		if(characterQuantity(fen.at(i), accepted_fen_characters) == 0) return false;
	}
	

	if(characterQuantity('/', fen) != 7) return false;
	if(characterQuantity('K', fen) != 1) return false;
	if(characterQuantity('k', fen) != 1) return false;

	if(move_for != "w" && move_for != "b") return false;

	for (size_t i = 0; i < castling_rights.size(); i++){
		if(characterQuantity(castling_rights.at(i), accepted_castling_characters) == 0) return false;
	}

	if(enpassant_square.size() != 2 && enpassant_square != "-") return false;


	string active_color = (move_for == "w") ? Piece::WHITE : Piece::BLACK;

	Board board{fen_string};
	if(!dynamic_cast<King *>(board.findPiece(Piece::KING, active_color))->isInCheck(board.board).empty()) return false;

	return true;
}




int characterQuantity(char c, string str){
	int count = 0;
	for (size_t i = 0; i < str.size(); i++){
		if(str.at(i) == c) count++;
	}
	return count;
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

std::vector<std::string> splitString(const std::string& input, char delimiter) {
    std::vector<std::string> result;
    std::size_t startPos = 0;
    std::size_t foundPos = input.find(delimiter);

    while (foundPos != std::string::npos) {
        std::string token = input.substr(startPos, foundPos - startPos);
        result.push_back(token);
        startPos = foundPos + 1;
        foundPos = input.find(delimiter, startPos);
    }

    // Adding the remaining part of the string after the last delimiter
    std::string lastToken = input.substr(startPos);
    result.push_back(lastToken);

    return result;
}

int findMove(Move move, vector<Move> moves){
	for (size_t i = 0; i < moves.size(); i++){
		if(move.from == moves.at(i).from && move.to == moves.at(i).to) return i;
	}
	return -1;
}