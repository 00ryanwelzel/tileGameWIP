#ifndef PULSE_MANAGER_H
#define PULSE_MANAGER_H

#include "pulse.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#pragma once

using namespace std;

constexpr int lcm(int a, int b){
    return (a / std::gcd(a, b)) * b;
}

class pulse_manager{
    private:
        int maxFrame;

        pulse* XXXX;

        // Level 1
        pulse* MTCS;
        pulse* MTCF;

        pulse* CTMS;
        pulse* CTMF;

        pulse* RTGF;
        pulse* GTBF;
        pulse* BTRF;
        
        // Level 2
        pulse* OYSS;
        pulse* YOSS;

        pulse* BCSS;
        pulse* CBSS;

        pulse* MCSF;
        pulse* CMSF;

        // Data on pulse chains
        std::vector<std::vector<pulse* >> pulse_chains;
        std::vector<int> pulse_chain_lengths;

    public:
        // Constructor Destructor
        
        pulse_manager();
        ~pulse_manager();

        // Main Functions

        void instantiateLevel(const int level);
        void instantiatePulseChains(const int level);
        void instantiatePulseChainLengths();
        void instantiateMaxFrame();

        SDL_Color getCurrentColor(int row, int current_frame);

        bool isSamePulse(const pulse* a, const pulse* b);

        // Used for frame iteration data
        int lcmVector(const std::vector<int>& vector) const;
        int lcm2dVector(const std::vector<std::vector<int>>& vector) const;

        // Getters Setters

        inline int getChainLength(const int row) const { return pulse_chain_lengths[row]; }
        inline int getMaxFrame() const { return maxFrame; }

};

#endif