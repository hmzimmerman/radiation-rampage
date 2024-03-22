#include "gui.h"
#include <iostream>

GUI::GUI(SDL_Renderer* renderer) : renderer(renderer), visible(false), location(0, 0) {
    options = { "Barracks", "Bomb", "Laser" };
}

GUI::~GUI() {}

void GUI::show(const TowerLocation& towerLocation) {
    visible = true;
    location = towerLocation;
}

void GUI::render() {
    if (!visible) return;

    int adjustedY = location.y - 30; // Render GUI above tower
    int rectHeight = 25;
    int rectWidth = 195;
    int centerX = location.x - 55; // Center GUI above tower

    // Render GUI background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
    SDL_Rect guiRect = { centerX, adjustedY, rectWidth, rectHeight };
    SDL_RenderFillRect(renderer, &guiRect);

    int optionWidth = rectWidth / options.size();

    // Render GUI options
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i < options.size(); ++i) {
        SDL_Rect optionRect = { centerX + i * optionWidth, adjustedY, optionWidth, rectHeight };
        SDL_RenderDrawRect(renderer, &optionRect);

        // Render option text
        SDL_Color textColor = { 0, 0, 0 };
        TTF_Font* font = TTF_OpenFont("../resource/arial.ttf", 12);
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, options[i].c_str(), textColor);
        
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = { optionRect.x + 5, optionRect.y + 5, textSurface->w, textSurface->h };
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        TTF_CloseFont(font);
    }
}

void GUI::hide() {
    visible = false;
}
