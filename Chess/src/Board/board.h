#pragma once

#include <cstring>
#include <string>
#include <unordered_map>
#include "../Pieces/Pieces.h"

using namespace std;

class Board{
    public:
        string playingAs;
        bool showMaterial;
        bool showMoves;
        string moveFor;
        string prompt_type;

        char board[8][8] = {
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
        };
        
        bool isInCheckmate(King *king);
		bool isInStalemate(King *king);
        bool isThreeFoldRepetition();
        bool isDrawDueToInsufficientMaterial();
        bool isFiftyMoveRule();
        bool isProtected(Piece *piece);
        bool isPinned(string to, Piece *piece);

        void resetMovesSinceCapture();
        Pieces* getPieces(string color);
        void setOutcome(string outcome);
        void setKingsCastlingRights(King *king);
        void increaceMovesSinceCapture();
        void setMove1Before(Move move);
        Move getMove1Before();

        void importFEN(string fen);
        void importPGN(string pgn);
        string exportPGN();
        
        void printBoard();
        void printBigBoard();
        void scanBoard(vector<Piece*> whitePieces, vector<Piece*> blackPieces);

        Piece *findPiece(string type, string color);
        int findPiece(Piece *piece);
        Piece* findPiece(Coords coords);
        Piece*findPiece(string square);
        
        void pushBoardState(string fen);
        void pushMove(string move);
        int quantityOfPiece(string type, string color);
        
        static string moveToPGNMove(Move m, Board *board, char promoteTo = '-');
        static Move pgnMoveToMove(string algebraicNotation, Board *board);
        static void copyBoard(char src[8][8], char dest[8][8]);
        static void copyMove(Move *src, Move *dest);
        static vector<string> getValidMoves(Piece *piece, Board *board);
        static bool movePiece(Move move, Board *board);
        static void moveFreely(Move move, Board *board, char promoteTo = '-');
        static bool removePiece(string square, Board *board);
        static bool removePieceFreely(string square, Board *board);

        static bool promotePawn(string square, Pawn *pawn, Board *board, char promoteTo = '-');
        static char promoteTo();
        static bool enpassantPawn(string square, Pawn *pawn, Board *board);
        static bool castleKing(string square, King *king, Board *board);
        
        static bool isValidFEN(string fen);
        static string exportFEN(Board *board);
        static string exportFEN(char board[][8]);


        ~Board(){}
        Board(){};
        Board(string fen, string playingAs = Piece::WHITE, bool showMaterial = true, bool showMoves = true, string prompt_type = Board::SEPERATE){
            this->playingAs = playingAs;
            this->showMaterial = showMaterial;
            this->showMoves = showMoves;
            this->prompt_type = prompt_type;

            importFEN(fen);
            wp->loadPieces(board);
            bp->loadPieces(board);

            setKingsCastlingRights(dynamic_cast<King *>(findPiece(Piece::KING, Piece::WHITE)));
            setKingsCastlingRights(dynamic_cast<King *>(findPiece(Piece::KING, Piece::BLACK)));

            past_board_states.insert({fen, 1});
        }

        Board(char board[8][8], string playingAs = Piece::WHITE, bool showMaterial = true, bool showMoves = true, string prompt_type = Board::SEPERATE){
            Board(Board::exportFEN(board), playingAs, showMaterial, showMoves, prompt_type);
        }


    private:
        Pieces *wp = new WhitePieces();
        Pieces *bp = new BlackPieces();
        Move move_1_before{"a1", "a1"};
        unordered_map<string, int> past_board_states;
        string outcome = "";
        int moves_since_capture = 0;
        string castling_rights;
        string pgn = "";
        vector<string> pgn_moves;

    public:
        static const string ONELINE;
        static const string SEPERATE;
};
