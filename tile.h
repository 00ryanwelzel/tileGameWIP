#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

class tile{
    private:
        SDL_Renderer* renderer;

        SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF};
        SDL_Color black = {0x00, 0x00, 0x00, 0xFF};

        int deco;
        int tile_size;
        int tile_subsize;

    public:
        // Constructor
        tile(const int deco, const int tile_size, const int tile_subsize);
        ~tile();

        // Main functions 
        // maybe add a hue shift function
        void draw(SDL_Renderer* renderer, const int row, const int col, const int offset_x, const int offset_y); 

        // Getters setters
        void setRenderColor(const SDL_Color color);
        void setColorFromColor(const SDL_Color color){ this->color = color; }

        void setRenderer(SDL_Renderer* in){ this->renderer = in; }
};

#endif