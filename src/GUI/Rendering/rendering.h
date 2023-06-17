#include "SDL.h"
#include <string>

using namespace std;

namespace Rendering{
    void drawBoard(int squareSize, SDL_Color white, SDL_Color black, SDL_Renderer *renderer);
    void renderImage(string path, int x, int y, int size, SDL_Renderer *renderer);
};