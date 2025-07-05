#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H

#include "tile.h"

#include "pulse_manager.h"
#include "pulse.h"

#include <vector>
#include <SDL2/SDL.h>

#pragma once

class tile_manager{
    private:
        // Container for tile decoration information
        struct tile_deco{
            tile* tile_ptr;
            int pulse_chain;
            int deco_ID;

            tile_deco() 
                : tile_ptr(nullptr), pulse_chain(-1), deco_ID(-1) {}

            tile_deco(tile* tile_ptr_, int pulse_chain_, int deco_ID_) 
                : tile_ptr(tile_ptr_), pulse_chain(pulse_chain_), deco_ID(deco_ID_) {}
        };

        // Container for tile attribute information
        struct tile_attr{
            bool solid;
            bool slide;
            bool deadly;
            bool activatable;
            int attribute_ID;

            tile_attr() 
                : solid(-1), slide(-1), deadly(-1), activatable(-1), attribute_ID(-1) {} 

            tile_attr(bool solid_, bool slide_, bool deadly_, bool activatable_, int attribute_ID_) 
                : solid(solid_), slide(slide_), deadly(deadly_), activatable(activatable_), attribute_ID(attribute_ID_) {} 
        };

        // Other stuff
        SDL_Renderer* renderer;
        pulse_manager* pulse_man;
        int level;
        int level_rows;
        int level_cols;

        int player_start_row;
        int player_start_col;
        int player_end_row;
        int player_end_col;

        int offset_x;
        int offset_y;

        const int tile_size = 32;
        const int tile_subsize = 2;

        std::vector<std::vector<tile_deco>> level_deco_state;
        std::vector<std::vector<tile_attr>> level_attr_state;

        // ----------------------------------- //
        // Reused tile decoration configurations
        // ----------------------------------- //

        // These might be useful at some point, just wanted to reserve them
        tile_deco NDCO;
        tile_deco STRT;
        tile_deco GOAL;

        // Layered decoration, layer count X
        tile_deco L1FN;
        tile_deco L2FN;
        tile_deco L3FN;

        // Brick decoration, brick count X
        tile_deco B1BY;
        tile_deco B2BY;
        tile_deco B3BY;
        
        // Standard tile attributes
        tile_attr NATT; 
        tile_attr PSTR;
        tile_attr PEND;
        tile_attr WATT; 
        
    public:
        // Constructor
        tile_manager(SDL_Renderer* renderer);
        ~tile_manager();

        // Main functions
        void setLevel(const int level);
        void drawLevel(const int frame);
        
        bool isInBounds(const int row, const int col);
        bool isSameDeco(const tile_deco a, const tile_deco b);
        bool isSameAttr(const tile_attr a, const tile_attr b);

        void instantiateTiles();

        // Getters setters
        void setOffsetX(const int offset_x);
        void setOffsetY(const int offset_y);

        inline int getPlayerStartRow() const { return player_start_row; }
        inline int getPlayerStartCol() const { return player_start_col; }
        inline int getPlayerEndRow() const { return player_end_row; }
        inline int getPlayerEndCol() const { return player_end_col; }

        bool getSolid(const int row, const int col);
};

#endif