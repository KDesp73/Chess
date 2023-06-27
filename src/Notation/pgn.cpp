#include "notation.h"

#include "../Board/board.h"
#include "../Board/board_utils.h"

#include <regex>
#include <vector>
#include <iostream>

using namespace BoardUtils;

string Notation::moveToPGNMove(Move move, Board *board){
    bool addPieceChar = true;
    bool isCheck = false;
    bool isCapture = false;
    bool isMate = false;
    bool isCastles = false;
    bool isCastlesLong = false;
    bool specifyPieceRank = false;
    bool specifyPieceFile = false;

    Piece *piece = board->findPiece(move.from);
    char pieceChar = toupper(board->board[translateSquare(move.from).x][translateSquare(move.from).y]);
    char pieceToCaptureChar = board->board[translateSquare(move.to).x][translateSquare(move.to).y];

    // Make the move to check if it's check or mate
    Board *temp_board = new Board(board->exportFEN());
    Board::moveFreely(move, temp_board);


    if(piece->type == Piece::PAWN) addPieceChar = false;

    if(!dynamic_cast<King *>(temp_board->findPiece(Piece::KING, (piece->color == Piece::WHITE) ? Piece::BLACK : Piece::WHITE))->isInCheck(temp_board->board).empty()) isCheck = true;
    
    if(pieceToCaptureChar != ' ') isCapture = true;    
    if(dynamic_cast<Pawn *>(piece) != NULL && dynamic_cast<Pawn *>(piece)->canEnpassant(move.to, board->getMove1Before())) isCapture = true;
    
    if(dynamic_cast<King *>(piece) != NULL && kingWantsToCastle(move) > 0) isCastles = true;
    if(dynamic_cast<King *>(piece) != NULL && kingWantsToCastle(move) < 0) isCastlesLong = true;
    
    if(temp_board->isInCheckmate(dynamic_cast<King *>(temp_board->findPiece(Piece::KING, (piece->color == Piece::WHITE) ? Piece::BLACK : Piece::WHITE)))) isMate = true;

    
    // Reset the board before the move
    temp_board = new Board(board->exportFEN());


    // Check if there is a need to specify the piece
    if(piece->type != Piece::PAWN && piece->type != Piece::KING){
        Piece *piece1 = temp_board->findPiece(piece->type, piece->color);
        Coords firstPieceCoords;
        bool canMoveToSquare1 = false, canMoveToSquare2 = false;
        if(piece1 != NULL){
            firstPieceCoords = translateSquare(piece1->currentSquare);
            canMoveToSquare1 = BoardUtils::canMove(Move{piece1->currentSquare, move.to}, temp_board);
            Board::removePieceFreely(piece1->currentSquare, temp_board);
        }
        
        Piece *piece2 = temp_board->findPiece(piece->type, piece->color);
        Coords secondPieceCoords;
        if(piece2 != NULL){
            secondPieceCoords = translateSquare(temp_board->findPiece(piece->type, piece->color)->currentSquare);
            canMoveToSquare2 = BoardUtils::canMove(Move{piece2->currentSquare, move.to}, temp_board);
        }

        int piece1Row = firstPieceCoords.x, piece1Col = firstPieceCoords.y;
        int piece2Row = secondPieceCoords.x, piece2Col = secondPieceCoords.y;

        if(canMoveToSquare1 && canMoveToSquare2 && (piece1Col != piece2Col)) specifyPieceRank = true;
        if(canMoveToSquare1 && canMoveToSquare2 && (piece1Col == piece2Col)) specifyPieceFile = true;
    }
    
    // Build the algebraic notation 
    string algebraicNotation = "";

    if(addPieceChar) algebraicNotation += pieceChar;
    
    if(!addPieceChar && isCapture)algebraicNotation += move.from.at(0);
    
    if(isCapture) algebraicNotation += "x";
    if(specifyPieceFile) algebraicNotation += move.from.at(1);
    if(specifyPieceRank) algebraicNotation += move.from.at(0);
    
    algebraicNotation += move.to;

    char promoteTo;
    if(move.promotion == Piece::QUEEN) promoteTo = 'q'; 
    else if(move.promotion == Piece::ROOK) promoteTo = 'r'; 
    else if(move.promotion == Piece::BISHOP) promoteTo = 'b'; 
    else if(move.promotion == Piece::KNIGHT) promoteTo = 'n'; 

    if(move.promotion != "" && move.promotion != "-") algebraicNotation += "=" + string(1, toupper(promoteTo));
    if(isCheck && !isMate) algebraicNotation += "+";
    if(isMate) algebraicNotation += "#";

    if(isCastles) return "0-0";
    if(isCastlesLong && !isMate) return "0-0-0";

    return algebraicNotation;
}

string Notation::exportPGN(Board *board){
    string pgn;
    vector<string> pgn_moves = board->getPGNMoves();

    if(pgn_moves.size() == 1) 
        pgn +=  to_string(1) + ". " + pgn_moves[0] + " ";
    else{
        for (int i = 0; i < pgn_moves.size(); i += 2){
            pgn +=  to_string(i / 2 + 1) + ". " + pgn_moves[i] + " " + ((i+1 < pgn_moves.size()) ? pgn_moves[i + 1] : "") + " ";
        }
    }
    
    
    pgn += board->getOutcome();

    board->setPGN(pgn);

    return pgn;
}



string findChessCoords(std::string algebraicNotation){
    std::regex coordRegex("[a-h][1-8]");
    
    auto words_begin = std::sregex_iterator(algebraicNotation.begin(), algebraicNotation.end(), coordRegex);
    auto words_end = std::sregex_iterator();
    
    return (*words_begin).str();
}

char pieceFromMove(string algebraicNotation){
    string pieces = "NBRQK";
    for (size_t i = 0; i < algebraicNotation.size(); i++){
        for (size_t j = 0; j < pieces.size(); j++){
            if(algebraicNotation.at(i) == pieces.at(j)) return algebraicNotation[i];
        }
    }
    return ' ';
}

Move Notation::algebraicNotationToMove(string algebraicNotation, int index, Board board){
    string color = (index % 2 == 0) ? Piece::WHITE : Piece::BLACK;

    if(color == Piece::WHITE && algebraicNotation == "O-O") return Move{"e1", "g1"};
    if(color == Piece::WHITE && algebraicNotation == "O-O-O") return Move{"e1", "c1"};
    if(color == Piece::BLACK && algebraicNotation == "O-O") return Move{"e8", "g8"};
    if(color == Piece::BLACK && algebraicNotation == "O-O-O") return Move{"e8", "c8"};
    
    string piece_type;
    string to_square = findChessCoords(algebraicNotation);

    
    switch (pieceFromMove(algebraicNotation)){
        case 'N':
            piece_type = Piece::KNIGHT;
            break;
        case 'B':
            piece_type = Piece::BISHOP;
            break;
        case 'R':
            piece_type = Piece::ROOK;
            break;
        case 'Q':
            piece_type = Piece::QUEEN;
            break;
        case 'K':
            piece_type = Piece::KING;
            break;
        case ' ':
            piece_type = Piece::PAWN;
            break;
        default:
            break;
    }


    Board temp_board{board.exportFEN()};

    Piece *piece = temp_board.findPiece(piece_type, color);

    if(piece == NULL || piece == 0x0 || piece == nullptr){
        cerr << "Invalid move" << endl;
        return {};
    }

    while(!BoardUtils::canMove(Move{piece->currentSquare, to_square}, &temp_board)){
        //Remove the piece
        temp_board.getPieces(color)->pieces.erase(std::remove(temp_board.getPieces(color)->pieces.begin(), temp_board.getPieces(color)->pieces.end(), piece), temp_board.getPieces(color)->pieces.end());
        piece = temp_board.findPiece(piece_type, color);
    }

    return Move{piece->currentSquare, to_square};
}

std::vector<Move> Notation::pgnToMoves(std::string pgn, Board *board){
    vector<string> pgn_moves = parsePGN(pgn);
    vector<Move> moves;

    for (size_t i = 0; i < pgn_moves.size(); i++){
        moves.push_back(algebraicNotationToMove(pgn_moves.at(i), i, *board));
    }
    
    return moves;
}

vector<string> Notation::parsePGN(string pgn){
    vector<string> moves;

    std::regex pattern{R"((\d+)\.\s+([^\s]+)\s+([^\s]+)(:?\s+|$))"};
    std::smatch matches{};
    while (std::regex_search(pgn, matches, pattern)){
        moves.push_back(matches[2]);
        moves.push_back(matches[3]);
        pgn = matches.suffix();
    }

    for (size_t i = 0; i < moves.size(); i++){
        if(moves.at(i) == "1-0" || moves.at(i) == "0-1" || moves.at(i) == "1/2-1/2"){
            moves.erase(moves.begin() + i);
            i--;
        }
    }
    

    return moves;
}



void Board::importPGN(string pgn){
    cerr << "Not yet implemented" << endl;
}
