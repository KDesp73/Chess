#include "gui.h"
#include "../chess_lib.h"

using namespace std;

int GUI::size = 0;

void GUI::init(int size, Board *board){
    GUI::size = size;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Color white = {236, 202, 165};
    SDL_Color black = {196, 106, 52};

    SDL_Window* window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GUI::size * 8, GUI::size * 8, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_RenderClear(renderer);
    Rendering::drawBoard(white, black, board->playingAs, renderer);
    loadPosition(board, renderer);
    SDL_RenderPresent(renderer);

    bool quit = false;
    SDL_Event event;
    string previousFEN;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        
            previousFEN = Board::exportFEN(board);
            string playing = board->moveFor;
        
            if(!GameUtils::isMate(board) && !GameUtils::isDraw(board)){
                Board *prev_board = new Board(Board::exportFEN(board));
                Move moveMade;
                if(playing == "white"){
                    int mouseX, mouseY;

                    Coords fromCoords, toCoords;

                    if(event.type == SDL_MOUSEBUTTONDOWN){
                        if(event.button.button == SDL_BUTTON_LEFT){
                            cout << "Mouse clicked" << endl;
                            mouseX = event.button.x;
                            mouseY = event.button.y;
                        
                            if(sizeof(fromCoords) == 0){
                                fromCoords = {mouseX / GUI::size, mouseY / GUI::size};
                                BoardUtils::printCoords(fromCoords);
                            } else {
                                toCoords = {mouseX / GUI::size, mouseY / GUI::size};
                                BoardUtils::printCoords(toCoords);
                            }
                            
                        
                            if(board->findPiece(BoardUtils::translateSquare(fromCoords))->color == "white"){
                                Move move = {BoardUtils::translateSquare(fromCoords), BoardUtils::translateSquare(toCoords)};
                                if(Board::movePiece(move, board)){
                                    moveMade = move;
                                } else toCoords = {};
                            } else fromCoords = {};
                        }
                    }

                    if(moveMade.from != "" && moveMade.to != ""){
                        playing = "black";
                    }
                } else {
                    int mouseX, mouseY;

                    Coords fromCoords, toCoords;

                    if(event.type == SDL_MOUSEBUTTONDOWN){
                        if(event.button.button == SDL_BUTTON_LEFT){
                            cout << "Mouse clicked" << endl;
                            mouseX = event.button.x;
                            mouseY = event.button.y;
                        
                            if(sizeof(fromCoords) == 0){
                                fromCoords = {mouseX / GUI::size, mouseY / GUI::size};
                            } else {
                                toCoords = {mouseX / GUI::size, mouseY / GUI::size};
                            }
                            
                        
                            if(board->findPiece(BoardUtils::translateSquare(fromCoords))->color == "black"){
                                Move move = {BoardUtils::translateSquare(fromCoords), BoardUtils::translateSquare(toCoords)};
                                if(Board::movePiece(move, board)){
                                    moveMade = move;
                                } else toCoords = {};
                            } else fromCoords = {};
                        }
                    }

                    if(moveMade.from != "" && moveMade.to != ""){
                        playing = "white";
                    }
                }
                board->moveFor = playing;
            }
        }

        

        if(previousFEN == Board::exportFEN(board)) continue;
        Rendering::drawBoard(white, black, board->playingAs, renderer);
        GUI::loadPosition(board, renderer);
        SDL_RenderPresent(renderer);
    }


    

    // Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Move GUI::turn(){
    SDL_Event event;
    int mouseXFROM, mouseYFROM;
    int mouseXTO, mouseYTO;
    int time = 0;
    bool clicked = false;

    while (!clicked && time != 2){

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if(time == 0){
                            mouseXFROM = event.button.x;
                            mouseYFROM = event.button.y;
                            time++;
                            clicked = true;
                            break;
                        } else if(time == 1){
                            mouseXTO = event.button.x;
                            mouseYTO = event.button.y;
                            time++;
                            break;
                        }
                    }
                    break;
            }
        }
    }

    Coords from = {mouseXFROM / GUI::size, mouseYFROM / GUI::size};
    Coords to = {mouseXTO / GUI::size, mouseYTO / GUI::size};
    Move move = {BoardUtils::translateSquare(from), BoardUtils::translateSquare(from)};

    return move;
}