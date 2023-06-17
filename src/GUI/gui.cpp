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
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        string previousFEN = Board::exportFEN(board);

        string playing = board->moveFor;
	
        if(!GameUtils::isMate(board) && !GameUtils::isDraw(board)){
            Board *prev_board = new Board(Board::exportFEN(board));
            if(playing == "white"){
                cout << "White's turn" << endl;

                Move moveMade = GameUtils::turn(board->getPieces(Piece::WHITE), board);
                if(moveMade.from != "" && moveMade.to != ""){
                    playing = "black";
                }
            } else {
                cout << "Black's turn" << endl;
                Move moveMade = GameUtils::turn(board->getPieces(Piece::BLACK), board);
                if(moveMade.from != "" && moveMade.to != ""){
                    playing = "white";
                }
            }
            board->moveFor = playing;
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