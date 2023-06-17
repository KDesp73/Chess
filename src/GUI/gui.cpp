#include "gui.h"

using namespace std;

void GUI::init(int squareSize){
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Color white = {236, 202, 165};
    SDL_Color black = {196, 106, 52};

    SDL_Window* window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, squareSize * 8, squareSize * 8, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Rendering::drawBoard(squareSize, white, black, renderer);
    // Rendering::renderImage("../assets/rook_b.png", 0, 0, squareSize, renderer);
    // Rendering::renderImage("../assets/knight_b.png", 1 * squareSize, 0, squareSize, renderer);
    // Rendering::renderImage("../assets/bishop_b.png", 2 * squareSize, 0, squareSize, renderer);
    loadPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", squareSize, renderer);

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }


    // Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}