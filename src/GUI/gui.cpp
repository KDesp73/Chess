#include "gui.h"

#include "../chess_lib.h"

#include <string>

using namespace std;

int GUI::size = 0;
string GUI::pieceTheme = "wiki";

std::string GUI::getBoardCoordinates(int x, int y, string playingAs) {
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

Coords GUI::getBoardCoordinates(string square, string playingAs){
    Coords coords = BoardUtils::translateSquare(square);

    if(playingAs == "white"){
        return Coords{coords.y * GUI::size, (7-coords.x) * GUI::size};
    } else {
        return Coords{(7-coords.y) * GUI::size, coords.x * GUI::size};
    }
}

void GUI::init(int size, string pieceTheme, Board* board) {
    GUI::size = size;
    GUI::pieceTheme = pieceTheme;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Color white = {236, 202, 165};
    SDL_Color black = {196, 106, 52};
    SDL_Color red_w = {207, 53, 46};
    SDL_Color red_b = {191, 46, 38};

    SDL_Window* window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, GUI::size * 8,
                                          GUI::size * 8, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_RenderClear(renderer);
    Rendering::drawBoard(white, black, renderer);
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
                            // cout << "From square: " << fromSquare << endl;

                            if(board->findPiece(fromSquare) == NULL){
                                SDL_RenderClear(renderer);
                                Rendering::drawBoard(white, black, renderer);
                                loadPosition(board, renderer);
                                SDL_RenderPresent(renderer);
                                isPieceSelected = false;
                            }

                            if(Board::getValidMoves(board->findPiece(fromSquare), board).empty()){
                                SDL_RenderClear(renderer);
                                Rendering::drawBoard(white, black, renderer);
                                loadPosition(board, renderer);
                                SDL_RenderPresent(renderer);
                                isPieceSelected = false;
                            }
                            
                            if((board->findPiece(fromSquare) != NULL)
                            && (!Board::getValidMoves(board->findPiece(fromSquare), board).empty())
                            && playing == board->findPiece(fromSquare)->color) {
                                isPieceSelected = true;
                                SDL_RenderClear(renderer);
                                Rendering::drawBoard(white, black, renderer);
                                Rendering::colorSquares(Board::getValidMoves(board->findPiece(fromSquare), board), board->playingAs, red_w, red_b, renderer);
                                loadPosition(board, renderer);
                                SDL_RenderPresent(renderer);
                            }
                            
                            
                        } else {
                            // Release the piece and make the move
                            // cout << "To square: " << clickedSquare << endl;

                            if(board->findPiece(clickedSquare) == NULL){
                                SDL_RenderClear(renderer);
                                Rendering::drawBoard(white, black, renderer);
                                loadPosition(board, renderer);
                                SDL_RenderPresent(renderer);
                                isPieceSelected = false;
                            }

                            if(Board::getValidMoves(board->findPiece(clickedSquare), board).empty()){
                                SDL_RenderClear(renderer);
                                Rendering::drawBoard(white, black, renderer);
                                loadPosition(board, renderer);
                                SDL_RenderPresent(renderer);
                                isPieceSelected = false;
                            }

                            if(board->findPiece(clickedSquare) != NULL && board->findPiece(clickedSquare)->color == playing) {
                                fromSquare = clickedSquare;
                                
                                if((board->findPiece(fromSquare) != NULL)
                                && (!Board::getValidMoves(board->findPiece(fromSquare), board).empty())
                                && playing == board->findPiece(fromSquare)->color) {
                                    isPieceSelected = true;
                                    SDL_RenderClear(renderer);
                                    Rendering::drawBoard(white, black, renderer);
                                    Rendering::colorSquares(Board::getValidMoves(board->findPiece(fromSquare), board), board->playingAs, red_w, red_b, renderer);
                                    loadPosition(board, renderer);
                                    SDL_RenderPresent(renderer);
                                }
                            } else if(board->findPiece(clickedSquare) == NULL || board->findPiece(clickedSquare)->color != playing){
                                Move move = {fromSquare, clickedSquare};
                                // cout << "From: " << move.from << " to " << move.to << endl;

                                if (Board::movePiece(move, board)) {
                                    SDL_RenderClear(renderer);
                                    Rendering::drawBoard(white, black, renderer);
                                    loadPosition(board, renderer);
                                    SDL_RenderPresent(renderer);
                                    (board->moveFor == "white")
                                        ? board->moveFor = "black"
                                        : board->moveFor = "white";
                                } 
                                isPieceSelected = false;
                            }
                        }
                    }
                } else{
                    quit = true;
                }

                if (previousFEN == Board::exportFEN(board)) continue;
                SDL_RenderClear(renderer);
                Rendering::drawBoard(white, black, renderer);
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


void GUI::runPGN(string pgn, Board *board, int size){
    GUI::size = size;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Color white = {236, 202, 165};
    SDL_Color black = {196, 106, 52};

    SDL_Window* window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GUI::size * 8, GUI::size * 8, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_RenderClear(renderer);
    Rendering::drawBoard(white, black, renderer);
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
                Move moveMade = GameUtils::turn(board->getPieces(Piece::WHITE), board);
                if(moveMade.from != "" && moveMade.to != ""){
                    playing = "black";
                }
            } else {
                Move moveMade = GameUtils::turn(board->getPieces(Piece::BLACK), board);
                if(moveMade.from != "" && moveMade.to != ""){
                    playing = "white";
                }
            }
            board->moveFor = playing;
        } else {
            return;
        }

        if(previousFEN == Board::exportFEN(board)) continue;
        Rendering::drawBoard(white, black, renderer);
        GUI::loadPosition(board, renderer);
        SDL_RenderPresent(renderer);
    }


    // Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}