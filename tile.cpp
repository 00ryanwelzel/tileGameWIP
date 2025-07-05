#include "tile.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

// Hold all the attributes of a specific tile
tile::tile(const int deco, const int tile_size, const int tile_subsize)
    : deco(deco), tile_size(tile_size), tile_subsize(tile_subsize) {}

tile::~tile(){
    //free(this);
}

void tile::draw(SDL_Renderer* renderer, const int row, const int col, const int offset_x, const int offset_y){
    setRenderer(renderer);

    SDL_Rect temp;

    switch (this->deco){
        // Case 1 --> 3 count up on number of borders + full interior (ie case 2 has 2 borders + interior)
        // Case 4 --> 6 count up on number of borders + black interior
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            // Outermost border
            temp = SDL_Rect{
                offset_x + (col * this->tile_size), 
                offset_y + (row * this->tile_size),
                tile_size, 
                tile_size
            };

            setRenderColor(this->color);
            SDL_RenderFillRect(renderer, &temp);

            // Fill interior
            temp = SDL_Rect{
                offset_x + (col * tile_size) + tile_subsize, 
                offset_y + (row * tile_size) + tile_subsize,
                tile_size - (2 * tile_subsize), 
                tile_size - (2 * tile_subsize),
            };
                    
            setRenderColor(this->black);
            SDL_RenderFillRect(renderer, &temp);

            // Break before interior is added on case 4
            if(this->deco == 4) break;

            // Innermost border
            temp = SDL_Rect{
                offset_x + (col * tile_size) + 2 * tile_subsize, 
                offset_y + (row * tile_size) + 2 * tile_subsize,
                tile_size - (4 * tile_subsize), 
                tile_size - (4 * tile_subsize),
            };
                    
            setRenderColor(this->color);
            SDL_RenderFillRect(renderer, &temp);

            // Break before one more border is added on case 1
            if(this->deco == 1) break;

            // Fill interior again
            temp = SDL_Rect{
                offset_x + (col * tile_size) + 3 * tile_subsize, 
                offset_y + (row * tile_size) + 3 * tile_subsize,
                tile_size - (6 * tile_subsize), 
                tile_size - (6 * tile_subsize),
            };
                    
            setRenderColor(this->black);
            SDL_RenderFillRect(renderer, &temp);

            // Break before interior is added on case 5
            if(this->deco == 5) break;

            // Color interior primary
            temp = SDL_Rect{
                offset_x + (col * tile_size) + 4 * tile_subsize, 
                offset_y + (row * tile_size) + 4 * tile_subsize,
                tile_size - (8 * tile_subsize), 
                tile_size - (8 * tile_subsize),
            };
                    
            setRenderColor(this->color);
            SDL_RenderFillRect(renderer, &temp);

            // Break before one more border is added on case 2
            if(this->deco == 2) break;

            // Fill interior again
            temp = SDL_Rect{
                offset_x + (col * tile_size) + 5 * tile_subsize, 
                offset_y + (row * tile_size) + 5 * tile_subsize,
                tile_size - (10 * tile_subsize), 
                tile_size - (10 * tile_subsize),
            };
                    
            setRenderColor(this->black);
            SDL_RenderFillRect(renderer, &temp);

            // Break before interior is added on case 6
            if(this->deco == 6) break;

            // Final interior coloring
            temp = SDL_Rect{
                offset_x + (col * tile_size) + 6 * tile_subsize, 
                offset_y + (row * tile_size) + 6 * tile_subsize,
                tile_size - (12 * tile_subsize), 
                tile_size - (12 * tile_subsize),
            };
                    
            setRenderColor(this->color);
            SDL_RenderFillRect(renderer, &temp);

            break;

        // Case 7 --> 9 count up on number of bricks + has a border
        // Case 10 --> 12 count up on number of bricks + lacks a border

        case 7:
        case 8:
        case 9:
            // Outermost border
            temp = SDL_Rect{
                offset_x + (col * this->tile_size), 
                offset_y + (row * this->tile_size),
                tile_size, 
                tile_size
            };

            setRenderColor(this->color);
            SDL_RenderFillRect(renderer, &temp);
            // Fall through

        case 10:
        case 11:
        case 12:
            // Fill interior
            temp = SDL_Rect{
                offset_x + (col * tile_size) + tile_subsize, 
                offset_y + (row * tile_size) + tile_subsize,
                tile_size - (2 * tile_subsize), 
                tile_size - (2 * tile_subsize),
            };
                    
            setRenderColor(this->black);
            SDL_RenderFillRect(renderer, &temp);

            // Large Brick
            temp = SDL_Rect{
                offset_x + (col * tile_size) + 2 * tile_subsize, 
                offset_y + (row * tile_size) + 2 * tile_subsize,
                8 * tile_subsize, 
                4 * tile_subsize,
            };
            
            setRenderColor(this->color);
            SDL_RenderFillRect(renderer, &temp);

            // Fill interior of the brick
            temp = SDL_Rect{
                offset_x + (col * tile_size) + 3 * tile_subsize, 
                offset_y + (row * tile_size) + 3 * tile_subsize,
                8 * tile_subsize, 
                4 * tile_subsize,
            };
            
            setRenderColor(this->black);
            SDL_RenderFillRect(renderer, &temp);

            // Break on one brick desired
            if((this->deco == 7) || (this->deco == 10)) break;

            // Second smaller Brick
            temp = SDL_Rect{
                offset_x + (col * tile_size) + 7 * tile_subsize, 
                offset_y + (row * tile_size) + 6 * tile_subsize,
                6 * tile_subsize, 
                3 * tile_subsize,
            };
            
            setRenderColor(this->color);
            SDL_RenderFillRect(renderer, &temp);

            // Fill interior of the brick
            temp = SDL_Rect{
                offset_x + (col * tile_size) + 8 * tile_subsize, 
                offset_y + (row * tile_size) + 7 * tile_subsize,
                6 * tile_subsize, 
                3 * tile_subsize,
            };
            
            setRenderColor(this->black);
            SDL_RenderFillRect(renderer, &temp);

            break;

        // No tile placed at location
        case 0: 
            break;

        // Error has occured
        default:
            perror("This deco id does not exist.\n");
            break;
    }

} 

void tile::setRenderColor(const SDL_Color color){
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
}

