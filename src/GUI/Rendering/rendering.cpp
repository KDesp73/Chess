#include "rendering.h"
#include <iostream>

#include <SDL2/SDL.h>
#include "SDL_image.h"

using namespace std;

void Rendering::drawBoard(int squareSize, SDL_Color white, SDL_Color black, string playingAs, SDL_Renderer *renderer){
    int rows = 8;
    int columns = 8;
    SDL_Color color;

    SDL_RenderClear(renderer);

     for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int x = j * squareSize;
            int y = i * squareSize;

            // Set the color based on the position
            if(playingAs == "white") color = (i + j) % 2 == 0 ? white : black;
            else if(playingAs == "black") color = (i + j) % 2 != 0 ? white : black;
            else return;

            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

            SDL_Rect square = {x, y, squareSize, squareSize};
            SDL_RenderFillRect(renderer, &square);
        }
    }

    SDL_RenderPresent(renderer);
}

void Rendering::renderImage(string path, int x, int y, int size, SDL_Renderer* renderer) {
    SDL_Surface* imageSurface = IMG_Load(path.c_str());
    if (!imageSurface) {
        printf("Failed to load image: %s\n", IMG_GetError());
        return;
    }

    // Create a new surface with the desired dimensions for the resized image
    SDL_Surface* resizedSurface = SDL_CreateRGBSurface(0, size, size, imageSurface->format->BitsPerPixel,
                                                       imageSurface->format->Rmask, imageSurface->format->Gmask,
                                                       imageSurface->format->Bmask, imageSurface->format->Amask);
    if (!resizedSurface) {
        printf("Failed to create resized surface: %s\n", SDL_GetError());
        SDL_FreeSurface(imageSurface);
        return;
    }

    // Resize the original image onto the new surface
    if (SDL_BlitScaled(imageSurface, NULL, resizedSurface, NULL) != 0) {
        printf("Failed to resize image: %s\n", SDL_GetError());
        SDL_FreeSurface(imageSurface);
        SDL_FreeSurface(resizedSurface);
        return;
    }

    // Create the texture from the resized surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, resizedSurface);
    if (!texture) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(imageSurface);
        SDL_FreeSurface(resizedSurface);
        return;
    }

    // Get the dimensions of the image
    int imageWidth = resizedSurface->w;
    int imageHeight = resizedSurface->h;

    // Clean up and free resources
    SDL_FreeSurface(imageSurface);
    SDL_FreeSurface(resizedSurface);

    SDL_Rect imageRect;
    imageRect.x = x;                // X coordinate of the top-left corner
    imageRect.y = y;                // Y coordinate of the top-left corner
    imageRect.w = imageWidth;       // Width of the image
    imageRect.h = imageHeight;      // Height
    
    // Render the texture onto the renderer
    SDL_RenderCopy(renderer, texture, nullptr, &imageRect);

    // Destroy the texture to avoid memory leaks
    SDL_DestroyTexture(texture);
}