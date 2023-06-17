#pragma once

#include "SDL.h"
#include <string>

using namespace std;

struct Image {
    SDL_Texture* texture;
    SDL_Rect rect;
};

namespace Rendering{
    void drawBoard(SDL_Color white, SDL_Color black, string playingAs, SDL_Renderer *renderer);
    Image renderImage(string path, int x, int y, SDL_Renderer *renderer);
};