#include "../gui.h"
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


void GUI::loadPosition(Board *board, SDL_Renderer *renderer){
    int size = GUI::size;

    for (size_t i = 0; i < 8; i++){
        for (size_t j = 0; j < 8; j++){
            string path = getPath(board->board[i][j]);
            if(path == "") continue;

            Image image;
            int x, y;
            if(board->playingAs == "white") {
                x = j;
                y = (7-i);
            } else if(board->playingAs == "black") {
                x = j;
                y = i;
            } else return;
            string abs_path = SDL_GetBasePath();
            if(abs_path.find("build") != string::npos){
                abs_path.replace(abs_path.find("build"), 5, "assets");
            } else abs_path += "assets/";

            image = Rendering::renderImage(abs_path + path, x * size, y * size, renderer);   
            
            for(int k = 0; k < board->getPieces("white")->pieces.size(); k++){
                Coords coords = BoardUtils::translateSquare(board->getPieces("white")->pieces.at(k)->currentSquare);
                if(coords.x == x && coords.y == y){
                    board->getPieces("white")->pieces.at(k)->image = image;
                }
            }
        
            for(int k = 0; k < board->getPieces("black")->pieces.size(); k++){
                Coords coords = BoardUtils::translateSquare(board->getPieces("black")->pieces.at(k)->currentSquare);
                if(coords.x == x && coords.y == y){
                    board->getPieces("black")->pieces.at(k)->image = image;
                }
            }
        }
    }
    IMG_Quit();
}
