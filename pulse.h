#ifndef PULSE_H
#define PULSE_H

#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#pragma once

constexpr int clamp(int x, int min, int max){
    return (x < min) ? min : ((x > max) ? max : x);
}

constexpr int min(int a, int b){
    return (a < b) ? a : b;
}

class pulse{
    private:
        // Color states
        SDL_Color start_color;
        SDL_Color end_color;

        // Pulse metadata
        unsigned int frame_total;
        unsigned int rate_of_change_ID;

        // Derived values for each color channel
        unsigned int height_r, height_g, height_b;
        int range_r, range_g, range_b;

    public:
        // Constructor Destructor ------------------------ //

        pulse(const SDL_Color start_color, const SDL_Color end_color, const int frame_total, const int rate_of_change_ID);
        ~pulse();

        // Main functions -------------------------------- //

        // Easing functions
        int sigmoid(int height, int range, const int frame);
        int linear(int height, int range, const int frame);
        int easing(int height, int range, const int frame);

        // Collectors for easing functions
        SDL_Color sigmoidColor(const int frame);
        SDL_Color linearColor(const int frame);
        SDL_Color easingColor(const int frame);

        // Getters --------------------------------------- //

        inline int getFrameTotal() const { return frame_total; }

        // Setters --------------------------------------- //

        void setHeight();
        void setRange();

        // Debugging ------------------------------------- //

        void printRange();
};

#endif