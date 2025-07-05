#include "tile_manager.h"
#include "tile.h"

#include "pulse_manager.h"
#include "pulse.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

tile_manager::tile_manager(SDL_Renderer* renderer) : renderer(renderer){
    this->pulse_man = new pulse_manager();
    instantiateTiles();
}

tile_manager::~tile_manager(){
    //free(this);
}

void tile_manager::setLevel(const int level){
    this->pulse_man->instantiateLevel(level);
    switch (level){
        case 1:
            /*
            this->level_deco_state = {
                
                {WDB1, WDB1, WDB1, WDO2, WDO1, WDB1, WDB1},
                {WDO1, GOAL, WDB1, NDCO, NDCO, NDCO, WDB1},
                {WDB1, NDCO, WDB1, NDCO, WDO2, NDCO, WDB1},
                {WDO1, NDCO, NDCO, NDCO, WDB1, NDCO, WDB1},
                {WDO2, WDB1, WDO1, WDB1, WDB1, NDCO, WDB1},
                {WDB1, PNDC, NDCO, NDCO, NDCO, NDCO, WDB1},
                {WDB1, WDO1, WDB1, WDB1, WDO1, WDB1, WDB1}
            };
            this->level_attr_state = {
                {WATT, WATT, WATT, WATT, WATT, WATT, WATT},
                {WATT, PEND, WATT, NATT, NATT, NATT, WATT},
                {WATT, NATT, WATT, NATT, WATT, NATT, WATT},
                {WATT, NATT, NATT, NATT, WATT, NATT, WATT},
                {WATT, WATT, WATT, WATT, WATT, NATT, WATT},
                {WATT, PSTR, NATT, NATT, NATT, NATT, WATT},
                {WATT, WATT, WATT, WATT, WATT, WATT, WATT}
            };
            */

            this->level_deco_state = {
                {L1FN, B1BY, L2FN, B1BY, B2BY, L2FN, L1FN, B1BY, B1BY},
                {L1FN, GOAL, NDCO, NDCO, NDCO, NDCO, NDCO, NDCO, L1FN},
                {B2BY, L1FN, B1BY, B2BY, L1FN, L1FN, NDCO, L2FN, L1FN},
                {B1BY, NDCO, NDCO, B1BY, NDCO, B2BY, NDCO, B1BY, B2BY},
                {L2FN, NDCO, NDCO, NDCO, NDCO, B1BY, NDCO, L1FN, B1BY},
                {B1BY, NDCO, NDCO, NDCO, NDCO, L1FN, NDCO, L1FN, B1BY},
                {B1BY, STRT, NDCO, NDCO, NDCO, NDCO, NDCO, NDCO, B1BY},
                {L1FN, L2FN, B1BY, B2BY, B1BY, B1BY, NDCO, NDCO, L1FN},
                {B2BY, B1BY, L1FN, L2FN, L3FN, B1BY, B1BY, L1FN, B2BY}
            };
            this->level_attr_state = {
                {WATT, WATT, WATT, WATT, WATT, WATT, WATT, WATT, WATT},
                {WATT, NATT, NATT, NATT, NATT, NATT, NATT, NATT, WATT},
                {WATT, WATT, WATT, WATT, WATT, WATT, NATT, WATT, WATT},
                {WATT, NATT, NATT, WATT, NATT, WATT, NATT, WATT, WATT},
                {WATT, NATT, NATT, NATT, NATT, WATT, NATT, WATT, WATT},
                {WATT, NATT, NATT, NATT, NATT, WATT, NATT, WATT, WATT},
                {WATT, NATT, NATT, NATT, NATT, NATT, NATT, NATT, WATT},
                {WATT, WATT, WATT, WATT, WATT, WATT, NATT, NATT, WATT},                
                {WATT, WATT, WATT, WATT, WATT, WATT, WATT, WATT, WATT}
            };

            // Indicate the players starting position
            player_start_row = 5;
            player_start_col = 1;
            player_end_row = 1;
            player_end_col = 1;

            // Indicate the tile_manager dimensions
            level_rows = static_cast<int>(level_deco_state.size());
            level_cols = static_cast<int>(level_deco_state[0].size());

            break;
        case 2:
            this->level_deco_state = {
                {L1FN, B1BY, L2FN, B1BY, B2BY, L2FN, L1FN, B1BY, B1BY},
                {L1FN, GOAL, NDCO, NDCO, NDCO, NDCO, NDCO, NDCO, L1FN},
                {B2BY, L1FN, B1BY, B2BY, L1FN, L1FN, NDCO, L2FN, L1FN},
                {B1BY, NDCO, NDCO, B1BY, NDCO, B2BY, NDCO, B1BY, B2BY},
                {L2FN, NDCO, NDCO, NDCO, NDCO, B1BY, NDCO, L1FN, B1BY},
                {B1BY, NDCO, NDCO, NDCO, NDCO, L1FN, NDCO, L1FN, B1BY},
                {B1BY, STRT, STRT, NDCO, NDCO, NDCO, NDCO, NDCO, B1BY},
                {L1FN, L2FN, B1BY, B2BY, B1BY, B1BY, NDCO, NDCO, L1FN},
                {B2BY, B1BY, L1FN, L2FN, L3FN, B1BY, B1BY, L1FN, B2BY}
            };
            this->level_attr_state = {
                {WATT, WATT, WATT, WATT, WATT, WATT, WATT, WATT, WATT},
                {WATT, NATT, NATT, NATT, NATT, NATT, NATT, NATT, WATT},
                {WATT, WATT, WATT, WATT, WATT, WATT, NATT, WATT, WATT},
                {WATT, NATT, NATT, WATT, NATT, WATT, NATT, WATT, WATT},
                {WATT, NATT, NATT, NATT, NATT, WATT, NATT, WATT, WATT},
                {WATT, NATT, NATT, NATT, NATT, WATT, NATT, WATT, WATT},
                {WATT, NATT, NATT, NATT, NATT, NATT, NATT, NATT, WATT},
                {WATT, WATT, WATT, WATT, WATT, WATT, NATT, NATT, WATT},                
                {WATT, WATT, WATT, WATT, WATT, WATT, WATT, WATT, WATT}
            };

            // Indicate the players starting position
            player_start_row = 5;
            player_start_col = 1;
            player_end_row = 1;
            player_end_col = 1;

            // Indicate the tile_manager dimensions
            level_rows = static_cast<int>(level_deco_state.size());
            level_cols = static_cast<int>(level_deco_state[0].size());
            break;

        default:
            perror("Level number does not exist.\n");
            break;
    }
}

void tile_manager::drawLevel(const int frame){
    for (size_t i = 0; i < level_deco_state.size(); i++) {
        for (size_t j = 0; j < level_deco_state[i].size(); j++) {
            tile_deco& temp = level_deco_state[i][j];

            if (isSameDeco(temp, NDCO) || isSameDeco(temp, STRT) || isSameDeco(temp, GOAL))
                continue;

            const int chain = temp.pulse_chain;
            const int chain_len = pulse_man->getChainLength(chain);
            const SDL_Color color = pulse_man->getCurrentColor(chain, frame % chain_len);

            temp.tile_ptr->setColorFromColor(color);
            temp.tile_ptr->draw(renderer, static_cast<int>(i), static_cast<int>(j), offset_x, offset_y);
        }
    }
}

void tile_manager::instantiateTiles(){
    // ----------------------------------- //
    // Reused tile decoration configurations
    // ----------------------------------- //

    // These might be useful at some point, just wanted to reserve them
    NDCO = {nullptr, -1, -1}; // No decoration 
    STRT = {nullptr, -1, -1}; // Player starts at this position
    GOAL = {nullptr, -1, -1}; // Player ends at this position

    // Layered decoration, layer count X
    L1FN = {new tile(4, tile_size, tile_subsize), 0, 1}; // Layers? 1, Filled? No
    L2FN = {new tile(5, tile_size, tile_subsize), 0, 2}; // Layers? 2, Filled? No
    L3FN = {new tile(6, tile_size, tile_subsize), 1, 3}; // Layers? 3, Filled? No

    // Brick decoration, brick count X
    B1BY = {new tile(7, tile_size, tile_subsize), 1, 4}; // Bricks? 1, Border? Yes
    B2BY = {new tile(8, tile_size, tile_subsize), 2, 5}; // Bricks? 2, Border? Yes
    B3BY = {new tile(9, tile_size, tile_subsize), 2, 6}; // Bricks? 3, Border? Yes
    
    // Standard tile attributes
    NATT = {false, false, false, false, 1}; // No attributes
    PSTR = {false, false, false, false, 2}; // Player starts at this postion
    PEND = {false, false, false, true, 3}; // Player ends at this position
    WATT = {true, false, false, false, 4}; // Wall attributes
    
}

bool tile_manager::isSameDeco(const tile_deco a, const tile_deco b){
    return a.deco_ID == b.deco_ID;
}

bool tile_manager::isInBounds(const int row, const int col){
    return row >= 0 && col >= 0 && row < level_rows && col < level_cols;
}

void tile_manager::setOffsetX(const int offset_x){
    this->offset_x = offset_x;
}

void tile_manager::setOffsetY(const int offset_y){
    this->offset_y = offset_y;
}

bool tile_manager::getSolid(const int row, const int col){
    return level_attr_state[row][col].solid;
}