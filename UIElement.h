#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#pragma once

using namespace std;

class UIElement{
    private:
        SDL_Color primary;
        SDL_Color secondary;

        SDL_Rect bounds;

        int style;
        int function;

        bool boundsSet;

    public:
        // Constructor
        UIElement(const int style, const int function, const SDL_Color primary, const SDL_Color secondary);
        ~UIElement();

        // Check if a point is inside the bounds
        bool containsPoint(const SDL_Rect& bounds, const int mouseX, const int mouseY) const;

        void draw(SDL_Renderer* renderer, const int x, const int y, const int pixel_buf, const int windowW, const int windowH);

        // Getters
        inline int getFunction() const { return function; }

        // Setters
        void setBounds(const SDL_Rect rect);
        void setRendererColor(SDL_Renderer* renderer, const SDL_Color color);

        void setPrimary(SDL_Color color);
        void setSecondary(SDL_Color color);

        void setPosition(int x, int y);
        void setSize(int w, int h);
};

#endif