#include "UIElement.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

UIElement::UIElement(const int style, const int function, const SDL_Color primary, const SDL_Color secondary)
     : style(style), function(function), primary(primary), secondary(secondary){
        boundsSet = false;
}

void UIElement::draw(SDL_Renderer* renderer, const int x, const int y, const int pixel_buf, const int windowW, const int windowH){
    SDL_Rect temp;

    SDL_Rect text_rect;
    SDL_Color text_color;

    TTF_Font* text_font;
    SDL_Surface* text_surface;
    SDL_Texture* text_texture;

    int text_dim = 48;

    switch (this->style){
        case 1:
            temp = SDL_Rect{
                pixel_buf + x,
                pixel_buf + y,
                windowW - (2 * pixel_buf),
                static_cast<int>((windowH / 8) - (2 * pixel_buf))
            };

            if(!boundsSet) setBounds(temp);

            setRendererColor(renderer, primary);
            SDL_RenderFillRect(renderer, &temp);

            temp = SDL_Rect{
                (2 * pixel_buf) + x,
                (2 * pixel_buf) + y,
                windowW - (4 * pixel_buf),
                static_cast<int>((windowH / 8) - (4 * pixel_buf))
            };

            setRendererColor(renderer, secondary);
            SDL_RenderFillRect(renderer, &temp);

            text_color = {255, 255, 255, 255};
            text_rect = {bounds.x + (4 * pixel_buf), bounds.y + (2 * pixel_buf), text_dim * 11, text_dim};

            text_font = TTF_OpenFont("911porschav3.ttf", 128);
            text_surface = TTF_RenderText_Blended(text_font, "SQUARE GAME", text_color);
            text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

            SDL_RenderCopy(renderer, text_texture, nullptr, &text_rect);

            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(text_texture);
            TTF_CloseFont(text_font);

            break;
            
        case 2:
            break;
        default:
            break;
    }
}

void UIElement::setBounds(const SDL_Rect rect){
    this->bounds = rect;
    this->boundsSet = true;
}

// Check if a point is inside the bounds
bool UIElement::containsPoint(const SDL_Rect& bounds, const int mouseX, const int mouseY) const {
    if(bounds.w <= 0 || bounds.h <= 0) return false;
    return (mouseX >= bounds.x &&
            mouseX <  bounds.x + bounds.w &&
            mouseY >= bounds.y &&
            mouseY <  bounds.y + bounds.h);
}

void UIElement::setRendererColor(SDL_Renderer* renderer, const SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void UIElement::setPrimary(SDL_Color color){
    this->primary = color;
}

void UIElement::setSecondary(SDL_Color color){
    this->primary = color;
}