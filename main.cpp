#include "tile_manager.h"
#include "tile.h"

#include "pulse_manager.h"
#include "pulse.h"

#include "UIElement.h"

//#include "SDL_FontCache.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;


// Window size
const int w = 640;
const int h = 480;

// Tile characteristics
static const int tile_dim = 32;
static const int tile_border_dim = 2;

// Environment location
int player_row = 5;
int player_col = 1;

int player_x = (w / 2) - (tile_dim / 2);
int player_y = (h / 2) - (tile_dim / 2);

int global_x = player_x - (player_col * tile_dim); 
int global_y = player_y - (player_row * tile_dim);

bool is_moving = false;
int step = 16; // 4 pixels per frame when moving
int movement_x = 0;
int movement_y = 0;
int move_progress = 0;
int move_distance = 0;
int target_row = 0;
int target_col = 0;

void setRenderColor(SDL_Renderer* renderer, SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

// ----------------------------- // 
// REAL SHIT
// ----------------------------- //

int main() {
    // Set up enviromnemt
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    // after errors

    // title, random bs, width, height, visible
    SDL_Window* window = SDL_CreateWindow(
        "Fortnite 2 Electic Boogaloo: Directed by Michael Bay",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w, h,
        SDL_WINDOW_SHOWN
    );

    // whatever the fuck renderer does
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    tile_manager* test = new tile_manager(renderer);
    test->setLevel(2);
    player_row = test->getPlayerStartRow();
    player_col = test->getPlayerStartCol();
    
    target_row = player_row;
    target_col = player_col;

    bool running = true;
    SDL_Event event;

    int real_frame = 0;
    int fake_frame = 0;

    while (running) {
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
            
            
            if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
                if(!is_moving){
                    switch (event.key.keysym.sym){
                        case SDLK_LEFT:
                            while(test->isInBounds(target_row, target_col - 1) &&
                            !test->getSolid(target_row, target_col - 1)){
                                //global_x += tile_dim;
                                move_distance += tile_dim;
                                target_col--;
                            }
                            if(target_col != player_col){
                                movement_x = 1;
                                movement_y = 0;
                                is_moving = true;
                            }
                            break;

                        case SDLK_RIGHT:
                            while(test->isInBounds(target_row, target_col + 1) &&
                            !test->getSolid(target_row, target_col + 1)){
                                //global_x -= tile_dim;
                                move_distance += tile_dim;
                                target_col++;
                            }
                            if(target_col != player_col){
                                movement_x = -1;
                                movement_y = 0;
                                is_moving = true;
                            }
                            break;

                        case SDLK_UP:
                            while(test->isInBounds(target_row - 1, target_col) &&
                            !test->getSolid(target_row - 1, target_col)){
                                //global_y += tile_dim;
                                move_distance += tile_dim;
                                target_row--;
                            }
                            if(target_row != player_row){
                                movement_x = 0;
                                movement_y = 1;
                                is_moving = true;
                            }
                            break;

                        case SDLK_DOWN:
                            while(test->isInBounds(target_row + 1, target_col) &&
                            !test->getSolid(target_row + 1, target_col)){
                                //global_y -= tile_dim;
                                move_distance += tile_dim;
                                target_row++;
                            }
                            if(target_row != player_row){
                                movement_x = 0;
                                movement_y = -1;
                                is_moving = true;
                            }
                            break;

                        default: break;
                    }
                }
            }    
            
        }
        
        if(is_moving){
            global_x += movement_x * step;
            global_y += movement_y * step;
            move_progress += step;

            if(move_progress >= move_distance){
                is_moving = false;
                movement_x = 0;
                movement_y = 0;
                move_progress = 0;
                move_distance = 0;
                player_row = target_row;
                player_col = target_col;
            }

        }
        // Clear screen
        setRenderColor(renderer, SDL_Color{0, 0, 0, 0});
        SDL_RenderClear(renderer);

        /*
        tile* test_tile;
        tile* test_tile2;
        pulse_manager* test_pm;

        test_tile = new tile(renderer, 2, 32, 2);
        test_tile2 = new tile(renderer, 2, 32, 2);
        test_pm = new pulse_manager(renderer);

        test_pm->makeLevel(1);
        test_pm->instantitePulsePackages();

        SDL_Color pulse_col = test_pm->getCurrentColor(0, frame);
        SDL_Color pulse_col2 = test_pm->getCurrentColor(1, frame % 64);

        test_tile->setColorFromColor(pulse_col);
        test_tile2->setColorFromColor(pulse_col2);

        test_tile->draw(1, 1, 0, 0);
        test_tile2->draw(3, 3, 0, 0);
        */


        
        // adjust and redraw the level
        test->setOffsetX(global_x);
        test->setOffsetY(global_y);
        test->drawLevel(real_frame);

        if(player_row == test->getPlayerEndRow() && player_col == test->getPlayerEndCol()){
            cout << "victory royale!" << endl;
        }

        
        SDL_Rect* player = new SDL_Rect{
            player_x,
            player_y,
            tile_dim,
            tile_dim
        };

        setRenderColor(renderer, SDL_Color{255, 255, 255, 255});
        SDL_RenderFillRect(renderer, player);

        delete player;
        

        //UIElement* testelement = new UIElement(1, 1, SDL_Color{255, 255, 255, 255}, SDL_Color{0, 0, 0, 255});
        //testelement->draw(renderer, 16, 32, 2, w, h);


        

        /*
        test_tile->draw(1, 1, 0, 0);
        test_tile2->draw(3, 3, 0, 0);

        if(test_pulse->getIsPulsing()){
            test_pulse->stepColor();
            test_pulse->adjustColor();

            test_tile->setColorFromColor(test_pulse->getColor());

            // ----------------- //

            test_pulse2->stepColor();
            test_pulse2->adjustColor();

            test_tile2->setColorFromColor(test_pulse2->getColor());

        } else {
            test_pulse = new pulse(renderer, test_start, test_end, 128, 1);
            test_pulse2 = new pulse(renderer, test_end, test_start, 128, 1);
        }
        */

        

        // Render text
        /*
        FC_Font* font = FC_CreateFont();
        FC_LoadFont(
            font, 
            renderer, 
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 
            24, 
            FC_MakeColor(255, 255, 255, 255), 
            TTF_STYLE_NORMAL
        );

        FC_Draw(font, renderer, 0, 0, "Fortnite");
        */

        
        real_frame = real_frame + 1;
        real_frame = real_frame % 256;
        //cout << frame << endl;

        SDL_RenderPresent(renderer);

        // Destroy obj
        //FC_FreeFont(font);
        
    }

    // Cleanup

    //delete button;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}