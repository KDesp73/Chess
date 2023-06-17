#include "./board.h"

#include "../../chess_lib.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

string getPath(char pieceChar){
    switch (pieceChar){
    case ' ':
        return "";
    case 'p':
        return "pawn_b.png";
    case 'r':
        return "rook_b.png";
    case 'n':
        return "knight_b.png";
    case 'b':
        return "bishop_b.png";
    case 'q':
        return "queen_b.png";
    case 'P':
        return "pawn_w.png";
    case 'k':
        return "king_b.png";
    case 'R':
        return "rook_w.png";
    case 'N':
        return "knight_w.png";
    case 'B':
        return "bishop_w.png";
    case 'Q':
        return "queen_w.png";
    case 'K':
        return "king_w.png";
    default:
        break;
    }
    return "";
}

void loadPosition(string fen, int size, string playingAs, SDL_Renderer *renderer){
    if(!Board::isValidFEN(fen)){
        cerr << "Invalid FEN" << endl;
        return;
    }

    Board board = {fen};

    for (size_t i = 0; i < 8; i++){
        for (size_t j = 0; j < 8; j++){
            string path = getPath(board.board[i][j]);
            if(path == "") continue;
            cout << path << endl;


            if(playingAs == "white") Rendering::renderImage("../assets/" + path, j * size, (7-i) * size, size, renderer);   
            else if(playingAs == "black") Rendering::renderImage("../assets/" + path, j * size, i * size, size, renderer);   
            else return;
        }
    }
    SDL_RenderPresent(renderer);
    IMG_Quit();
}