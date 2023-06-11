#include "board.h"
#include "board_utils.h"

using namespace BoardUtils;

string Board::moveToPGNMove(Move move, Board *board, char promoteTo){
    bool addPieceChar = true;
    bool isCheck = false;
    bool isCapture = false;
    bool isMate = false;
    bool isCastles = false;
    bool isCastlesLong = false;
    bool specifyKnightRank = false;
    bool specifyKnightFile = false;

    Board *temp_board = new Board(Board::exportFEN(board));
    Board::moveFreely(move, temp_board, promoteTo);

    Piece *piece = board->findPiece(move.from);
    char pieceChar = board->board[translateSquare(move.from).x][translateSquare(move.from).y];
    pieceChar = toupper(pieceChar);
    char pieceToCaptureChar = board->board[translateSquare(move.to).x][translateSquare(move.to).y];

    if(piece->type == Piece::PAWN) addPieceChar = false;
    if(!dynamic_cast<King *>(temp_board->findPiece(Piece::KING, (piece->color == Piece::WHITE) ? Piece::BLACK : Piece::WHITE))->isInCheck(temp_board->board).empty()) isCheck = true;
    if(pieceToCaptureChar != ' ') isCapture = true;
    if(dynamic_cast<Pawn *>(piece) != NULL && dynamic_cast<Pawn *>(piece)->canEnpassant(move.to, *board->move_1_before)) isCapture = true;
    if(dynamic_cast<King *>(piece) != NULL && kingWantsToCastle(move) < 0) isCastles = true;
    if(dynamic_cast<King *>(piece) != NULL && kingWantsToCastle(move) > 0) isCastlesLong = true;
    if(temp_board->isInCheckmate(dynamic_cast<King *>(temp_board->findPiece(Piece::KING, (piece->color == Piece::WHITE) ? Piece::BLACK : Piece::WHITE)))) isMate = true;

    temp_board = new Board(Board::exportFEN(board));

    // Check if there is a need to specify the knight
    Piece *knight1 = temp_board->findPiece(Piece::KNIGHT, piece->color);
    Coords firstKnightCoords;
    bool canMoveToSquare1 = false, canMoveToSquare2 = false;
    if(knight1 != NULL){
        firstKnightCoords = translateSquare(knight1->currentSquare);
        canMoveToSquare1 = BoardUtils::canMove(knight1, Move{knight1->currentSquare, move.to}, temp_board);
        Board::removePieceFreely(knight1->currentSquare, temp_board);
    }
    
    Piece *knight2 = temp_board->findPiece(Piece::KNIGHT, piece->color);
    Coords secondKnightCoords;
    if(knight2 != NULL){
        secondKnightCoords = translateSquare(temp_board->findPiece(Piece::KNIGHT, piece->color)->currentSquare);
        canMoveToSquare2 = BoardUtils::canMove(temp_board->findPiece(Piece::KNIGHT, piece->color), Move{knight2->currentSquare, move.to}, temp_board);
    }

    int knight1Row = firstKnightCoords.x, knight1Col = firstKnightCoords.y;
    int knight2Row = secondKnightCoords.x, knight2Col = secondKnightCoords.y;

    if(canMoveToSquare1 && canMoveToSquare2 && (knight1Col != knight2Col)) specifyKnightRank = true;
    if(canMoveToSquare1 && canMoveToSquare2 && (knight1Col == knight2Col)) specifyKnightFile = true;

    string algebraicNotation = "";

    if(addPieceChar) algebraicNotation += pieceChar;
    
    if(!addPieceChar && isCapture)algebraicNotation += move.from.at(0);
    
    if(isCapture) algebraicNotation += "x";
    if(specifyKnightFile) algebraicNotation += move.from.at(1);
    if(specifyKnightRank) algebraicNotation += move.from.at(0);
    
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

Move Board::pgnMoveToMove(string algebraicNotation, Board *board){
    cerr << "Not yet implemented" << endl;
    return Move{};
}

void importPGN(string pgn){
    cerr << "Not yet implemented" << endl;
}