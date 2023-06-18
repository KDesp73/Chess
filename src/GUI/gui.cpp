#include "gui.h"

#include "../chess_lib.h"

using namespace std;

int GUI::size = 0;

std::string getBoardCoordinates(int x, int y, string playingAs) {
    int file = x / GUI::size;
    int rank = y / GUI::size;

    string fileStr, rankStr;

    if(playingAs == "white"){
        fileStr = std::string(1, 'a' + file);
        rankStr = std::to_string(8-rank);
    } else {
        fileStr = std::string(1, 'h' - file);
        rankStr = std::to_string(rank+1);
    }
    return fileStr + rankStr;
}

void GUI::init(int size, Board* board) {
    GUI::size = size;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Color white = {236, 202, 165};
    SDL_Color black = {196, 106, 52};

    SDL_Window* window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, GUI::size * 8,
                                          GUI::size * 8, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_RenderClear(renderer);
    Rendering::drawBoard(white, black, board->playingAs, renderer);
    loadPosition(board, renderer);
    SDL_RenderPresent(renderer);

    bool quit = false;
    SDL_Event event;
    bool isPieceSelected = false;
    std::string fromSquare;
    string previousFEN;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                previousFEN = Board::exportFEN(board);
                string playing = board->moveFor;

                if (!GameUtils::isMate(board) && !GameUtils::isDraw(board)) {
                    Board* prev_board = new Board(Board::exportFEN(board));

                    int x, y;
                    SDL_GetMouseState(&x, &y);

                    // Check if a valid square is clicked
                    if (x < 8 * GUI::size && y < 8 * GUI::size) {
                        string clickedSquare = getBoardCoordinates(x, y, board->playingAs);

                        if (!isPieceSelected) {
                            // Select a piece
                            fromSquare = clickedSquare;
                            isPieceSelected = true;
                        } else {
                            // Release the piece and make the move
                            Move move = {fromSquare, clickedSquare};
                            // cout << "From: " << move.from << " to " << move.to << endl;

                            if (Board::movePiece(move, board)) {
                                SDL_RenderClear(renderer);
                                Rendering::drawBoard(
                                    white, black, board->playingAs, renderer);
                                loadPosition(board, renderer);
                                SDL_RenderPresent(renderer);
                                (board->moveFor == "white")
                                    ? board->moveFor = "black"
                                    : board->moveFor = "white";
                            } 
                            isPieceSelected = false;
                        }
                    }
                } else{
                    quit = true;
                }

                if (previousFEN == Board::exportFEN(board)) continue;
                SDL_RenderClear(renderer);
                Rendering::drawBoard(white, black, board->playingAs, renderer);
                GUI::loadPosition(board, renderer);
                SDL_RenderPresent(renderer);
            }
        }
    }

    // Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
