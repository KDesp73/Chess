#include "board.h"
#include "board_utils.h"

#include <regex>
#include <vector>
#include <iostream>

using namespace BoardUtils;

string Board::moveToPGNMove(Move move, Board *board, char promoteTo){
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
    Board *temp_board = new Board(Board::exportFEN(board));
    Board::moveFreely(move, temp_board, promoteTo);


    if(piece->type == Piece::PAWN) addPieceChar = false;

    if(!dynamic_cast<King *>(temp_board->findPiece(Piece::KING, (piece->color == Piece::WHITE) ? Piece::BLACK : Piece::WHITE))->isInCheck(temp_board->board).empty()) isCheck = true;
    
    if(pieceToCaptureChar != ' ') isCapture = true;    
    if(dynamic_cast<Pawn *>(piece) != NULL && dynamic_cast<Pawn *>(piece)->canEnpassant(move.to, board->getMove1Before())) isCapture = true;
    
    if(dynamic_cast<King *>(piece) != NULL && kingWantsToCastle(move) > 0) isCastles = true;
    if(dynamic_cast<King *>(piece) != NULL && kingWantsToCastle(move) < 0) isCastlesLong = true;
    
    if(temp_board->isInCheckmate(dynamic_cast<King *>(temp_board->findPiece(Piece::KING, (piece->color == Piece::WHITE) ? Piece::BLACK : Piece::WHITE)))) isMate = true;

    
    // Reset the board before the move
    temp_board = new Board(Board::exportFEN(board));


    // Check if there is a need to specify the piece
    if(piece->type != Piece::PAWN && piece->type != Piece::KING){
        Piece *piece1 = temp_board->findPiece(piece->type, piece->color);
        Coords firstPieceCoords;
        bool canMoveToSquare1 = false, canMoveToSquare2 = false;
        if(piece1 != NULL){
            firstPieceCoords = translateSquare(piece1->currentSquare);
            canMoveToSquare1 = BoardUtils::canMove(piece1, Move{piece1->currentSquare, move.to}, temp_board);
            Board::removePieceFreely(piece1->currentSquare, temp_board);
        }
        
        Piece *piece2 = temp_board->findPiece(piece->type, piece->color);
        Coords secondPieceCoords;
        if(piece2 != NULL){
            secondPieceCoords = translateSquare(temp_board->findPiece(piece->type, piece->color)->currentSquare);
            canMoveToSquare2 = BoardUtils::canMove(temp_board->findPiece(piece->type, piece->color), Move{piece2->currentSquare, move.to}, temp_board);
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

    if(promoteTo != '-') algebraicNotation += "=" + string(1, toupper(promoteTo));
    if(isCheck && !isMate) algebraicNotation += "+";
    if(isMate) algebraicNotation += "#";

    if(isCastles) return "0-0";
    if(isCastlesLong && !isMate) return "0-0-0";

    return algebraicNotation;
}

string Board::exportPGN(){
    this->pgn = "";

    if(pgn_moves.size() == 1) 
        this->pgn +=  to_string(1) + ". " + pgn_moves[0] + " ";
    else{
        for (int i = 0; i < pgn_moves.size(); i += 2){
            this->pgn +=  to_string(i / 2 + 1) + ". " + pgn_moves[i] + " " + pgn_moves[i + 1] + " ";
        }
    }
    
    
    this->pgn += outcome;

    return this->pgn;
}

std::vector<std::string> findChessCoords(const std::string& input)
{
    std::regex coordRegex("[a-h][1-8]");
    std::vector<std::string> foundCoords;
    
    auto words_begin = std::sregex_iterator(input.begin(), input.end(), coordRegex);
    auto words_end = std::sregex_iterator();
    
    for (std::sregex_iterator it = words_begin; it != words_end; ++it) {
        foundCoords.push_back((*it).str());
    }
    
    return foundCoords;
}

int findPieceCharInMove(string algebraicNotation, string pieces){
    for (size_t i = 0; i < algebraicNotation.size(); i++){
        for (size_t j = 0; j < pieces.size(); j++){
            if(algebraicNotation.at(i) == pieces.at(j)) return i;
        }
    }
    return -1;
}

Move Board::pgnMoveToMove(string algebraicNotation, int index, Board *board){
    string pieces = "NBRQK";

    string to = findChessCoords(algebraicNotation).at(0);

    string color = (index % 2 == 0) ? Piece::WHITE : Piece::BLACK;

    Piece *pieceToMove = NULL;
    switch (findPieceCharInMove(algebraicNotation, pieces)){
    case -1:
        break;
    case 0:
        pieceToMove = board->findPiece(Piece::KNIGHT, color);
        break;
    case 1:
        pieceToMove = board->findPiece(Piece::BISHOP, color);
        break;
    case 2:
        pieceToMove = board->findPiece(Piece::ROOK, color);
        break;
    case 3:
        pieceToMove = board->findPiece(Piece::QUEEN, color);
        break;
    case 4:
        pieceToMove = board->findPiece(Piece::KING, color);
        break;
    default:
        break;
    }



    return Move{};
}

std::vector<std::string> Board::pgnToMoves(std::string pgn)
{
    std::regex coordRegex("[NBRQK]*[a-h]x*[1-8][+#]*");
    std::vector<std::string> foundCoords;
    
    std::regex numberRegex("\\d+\\.");
    std::string modifiedInput = std::regex_replace(pgn, numberRegex, "");
    
    auto words_begin = std::sregex_iterator(modifiedInput.begin(), modifiedInput.end(), coordRegex);
    auto words_end = std::sregex_iterator();
    
    for (std::sregex_iterator it = words_begin; it != words_end; ++it) {
        foundCoords.push_back((*it).str());
    }
    
    return foundCoords;
}

void Board::importPGN(string pgn){
    cerr << "Not yet implemented" << endl;
}