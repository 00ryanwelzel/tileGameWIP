#include "pulse_manager.h"
#include "pulse.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

pulse_manager::pulse_manager(){
}

pulse_manager::~pulse_manager(){
    for(vector<pulse*>& row : pulse_chains){
        for(pulse* p : row){
            delete p;
            p = nullptr;
        }
    }
}

void pulse_manager::instantiateLevel(const int level){
    instantiatePulseChains(level);

    switch (level){
        case 1:
            this->pulse_chains = {
                {MTCF, CTMF},
                {CTMS, MTCS},
                {RTGF, GTBF, BTRF}
            };
            break;

        case 2:
            this->pulse_chains = {
                {OYSS, YOSS},
                {CBSS, BCSS},
                {CMSF, MCSF}
            };
            break;

        default: 
            break;
    }

    instantiatePulseChainLengths();
    instantiateMaxFrame();
}

void pulse_manager::instantiatePulseChains(const int level){
    // Pulse definition:
    // SDL_Color start_color, SDL_Color end_color, int frame_total, int rate_of_change_ID
    // Naming Scheme:
    // Start color, end color, easing function, "speed"

    XXXX = new pulse({0, 0, 0, 0}, {0, 0, 0, 0}, -1, -1);

    switch (level){
        case 1:
            MTCF = new pulse({255, 0, 255, 255}, {0, 255, 255, 255}, 128, 1);
            MTCS = new pulse({255, 0, 255, 255}, {0, 255, 255, 255}, 32, 1);

            CTMF = new pulse({0, 255, 255, 255}, {255, 0, 255, 255}, 128, 1);
            CTMS = new pulse({0, 255, 255, 255}, {255, 0, 255, 255}, 32, 1);

            RTGF = new pulse({255, 0, 0, 255}, {0, 255, 0, 255}, 16, 1);
            GTBF = new pulse({0, 255, 0, 255}, {0, 0, 255, 255}, 16, 1);
            BTRF = new pulse({0, 0, 255, 255}, {255, 0, 0, 255}, 16, 1);

            break;
            
        case 2:
            OYSS = new pulse({255, 0, 0, 255}, {255, 255, 0, 255}, 64, 1);
            YOSS = new pulse({255, 255, 0, 255}, {255, 0, 0, 255}, 64, 1);

            BCSS = new pulse({0, 0, 255, 255}, {0, 255, 255, 255}, 64, 1);
            CBSS = new pulse({0, 255, 255, 255}, {0, 0, 255, 255}, 64, 1);

            CMSF = new pulse({0, 255, 255, 255}, {255, 0, 255, 255}, 4, 1);
            MCSF = new pulse({255, 0, 255, 255}, {0, 255, 255, 255}, 4, 1);

            break;
    
        default:
            break;
    }
}

void pulse_manager::instantiatePulseChainLengths(){
    pulse_chain_lengths.clear();
    for(const auto& row : pulse_chains){
        int total = 0;
        for(const auto& pulse : row){
            total += pulse->getFrameTotal();
        }
        pulse_chain_lengths.push_back(total);
    }
    cout << "Done" << endl;
}

void pulse_manager::instantiateMaxFrame(){
    int result = 1;
    for(const int i : pulse_chain_lengths){
        result = lcm(result, i);
    }
    this->maxFrame = result;
}


SDL_Color pulse_manager::getCurrentColor(const int row, int current_frame){
    for (pulse* temp : pulse_chains[row]) {
        int frame_total = temp->getFrameTotal();

        if (current_frame < frame_total) {
            int centered_frame = current_frame - (frame_total / 2);
            return temp->sigmoidColor(centered_frame);
        }

        current_frame -= frame_total;
    }

    return SDL_Color{ 0, 0, 0, 255 };
}

bool pulse_manager::isSamePulse(const pulse* a, const pulse* b){
    // Unfinished
    return a->getFrameTotal() == b->getFrameTotal();
}

// Tool Functions ------------------------- //
// ---------------------------------------- //

int pulse_manager::lcmVector(const std::vector<int>& vector) const {
    int result = 1;
    for (int num : vector) {
        result = lcm(result, num);
    }
    return result;
}

int pulse_manager::lcm2dVector(const std::vector<std::vector<int>>& vector) const {
    int result = 1;
    for (const auto& row : vector) {
        result = lcm(result, lcmVector(row));
    }
    return result; 
}