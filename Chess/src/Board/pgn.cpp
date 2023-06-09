#include "board.h"
#include "board_utils.h"

using namespace BoardUtils;

string Board::moveToPGNMove(Move move, Board *board){
    bool addPieceChar = true;
    bool isCheck = false;
    bool isCapture = false;
    bool isMate = false;
    bool isCastles = false;
    bool isCastlesLong = false;

    Board *temp_board = new Board(Board::exportFEN(board));
    Board::moveFreely(move, temp_board);

    Piece *piece = board->findPiece(move.from);
    char pieceChar = board->board[translateSquare(move.from).x][translateSquare(move.from).y];
    pieceChar = toupper(pieceChar);
    char pieceToCaptureChar = board->board[translateSquare(move.to).x][translateSquare(move.to).y];

    if(piece->type == Piece::PAWN) addPieceChar = false;
    if(!dynamic_cast<King *>(temp_board->findPiece(Piece::KING, (piece->color == Piece::WHITE) ? Piece::BLACK : Piece::WHITE))->isInCheck(temp_board->board).empty()) isCheck = true;
    if(pieceToCaptureChar != ' ') isCapture = true;
    if(dynamic_cast<Pawn *>(piece) != NULL && dynamic_cast<Pawn *>(piece)->canEnpassant(move.to, *board->move_1_before)) isCapture = true;
    if(kingWantsToCastle(move) < 0) isCastles = true;
    if(kingWantsToCastle(move) > 0) isCastlesLong = true;
    if(temp_board->isInCheckmate(dynamic_cast<King *>(temp_board->findPiece(Piece::KING, (piece->color == Piece::WHITE) ? Piece::BLACK : Piece::WHITE)))) isMate = true;

    string algebraicNotation = "";

    if(addPieceChar) algebraicNotation += pieceChar;
    
    if(!addPieceChar && isCapture)algebraicNotation += move.from.at(0);
    
    if(isCapture) algebraicNotation += "x";
    if(isCheck && !isMate) algebraicNotation += "+";
    algebraicNotation += move.to;
    if(isMate) algebraicNotation += "#";

    if(isCastles) return "0-0";
    if(isCastlesLong && !isMate) return "0-0-0";

    return algebraicNotation;
}

string Board::exportPGN(){
    for (int i = 0; i < pgn_moves.size(); i += 2){
        this->pgn +=  to_string(i / 2 + 1) + ". " + pgn_moves[i] + " " + pgn_moves[i + 1] + " ";
    }
    
    return this->pgn + outcome;
}