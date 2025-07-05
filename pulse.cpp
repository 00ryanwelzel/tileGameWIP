#include "pulse.h"

#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

pulse::pulse(const SDL_Color start_color, const SDL_Color end_color, const int frame_total, const int rate_of_change_ID)
    : start_color(start_color), end_color(end_color), frame_total(frame_total), rate_of_change_ID(rate_of_change_ID){
    setHeight();
    setRange();
}


pulse::~pulse(){
    // something something idk yet
}

int pulse::sigmoid(int height, int range, const int frame){
    // Flip direction if range is negative
    if(range < 0) height -= range;

    // Scaled Sigmoid
    float k = 5.0f / (frame_total / 2.0f);
    float s = 1.0f / (1.0f + exp(-k * frame));
    int sig_val = static_cast<int>(floor(height + range * s));

    // Adjust value on crossing midpoint
    if(sig_val >= 0) sig_val++;

    return clamp(sig_val, 0, 255);
}

SDL_Color pulse::sigmoidColor(const int frame){
    SDL_Color out_color;

    out_color.r = sigmoid(this->height_r, this->range_r, frame);
    out_color.g = sigmoid(this->height_g, this->range_g, frame);
    out_color.b = sigmoid(this->height_b, this->range_b, frame); 
    out_color.a = 255;
    
    return out_color;
}

void pulse::setHeight(){
    this->height_r = min(start_color.r, end_color.r);
    this->height_g = min(start_color.g, end_color.g);
    this->height_b = min(start_color.b, end_color.b);
}

void pulse::setRange(){
    this->range_r = end_color.r - start_color.r;
    this->range_g = end_color.g - start_color.g;
    this->range_b = end_color.b - start_color.b;
}

