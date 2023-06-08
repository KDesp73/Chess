#pragma once

#include <cstring>
#include <string>
#include <unordered_map>
#include "../Pieces/Pieces.h"

using namespace std;

class Board{
    private:
        Pieces *wp = new WhitePieces();
        Pieces *bp = new BlackPieces();
        unordered_map<string, int> past_board_states;
        int moves_since_capture = 0;
    public:
        string playingAs;
        bool showMaterial;
        string moveFor = "white";
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
        

        Move *move_1_before = new Move(Move{"a1", "a1"});
        Move *move_2_before = new Move(Move{"a1", "a1"});


        ~Board(){
            delete wp;
            delete bp;
        }
        Board(string fen, string playingAs = Piece::WHITE, bool showMaterial = true){
            this->playingAs = playingAs;
            this->showMaterial = showMaterial;
            importFEN(fen);
            wp->loadPieces(board);
            bp->loadPieces(board);

            past_board_states.insert({fen, 1});
        }

        Board(char board[8][8], string playingAs = Piece::WHITE, bool showMaterial = true){
            this->playingAs = playingAs;
            this->showMaterial = showMaterial;
            Board::copyBoard(board, this->board);
            wp->loadPieces(board);
            bp->loadPieces(board);

            past_board_states.insert({Board::exportFEN(board), 1});
        }

        Pieces* getPieces(string color);
        void importFEN(string fen);
        static string exportFEN(Board *board);
        static string exportFEN(char board[][8]);
        void printBoard();
        void printBigBoard();
        void scanBoard(vector<Piece*> whitePieces, vector<Piece*> blackPieces);
        Piece *findPiece(string type, string color);
        int findPiece(Piece *);
        Piece* findPiece(Coords coords);
        Piece*findPiece(string square);
        Rook* getRookToCastle(int direction, string color);
        bool isInCheckmate(King *king);
		bool isInStalemate(King *king);
        bool isThreeFoldRepetition();
        bool isDrawDueToInsufficientMaterial();
        bool isFiftyMoveRule();
        void pushBoardState(string fen);
        int quantityOfPiece(string type, string color);
        void increaceMovesSinceCapture();
        void resetMovesSinceCapture();

        static void copyBoard(char src[8][8], char dest[8][8]);
        static void copyMove(Move *src, Move *dest);
        static bool isProtected(Piece *piece, Board *board);
        static bool isPinned(string to, Piece *piece, Board *board);
        static vector<string> getValidMoves(Piece *piece, Board *board);
        static bool movePiece(Move move, Board *board);
        static void moveFreely(Move move, Board *board);
        static bool removePiece(string square, Board *board);
        static bool removePieceFreely(string square, Board *board);

        static bool promotePawn(string square, Pawn *pawn, Board *board);
        static bool enpassantPawn(string square, Pawn *pawn, Board *board);
        static bool castleKing(string square, King *king, Board *board);
};