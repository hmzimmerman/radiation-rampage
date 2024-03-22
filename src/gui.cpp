#include "gui.h"
#include <iostream>

GUI::GUI(SDL_Renderer* renderer) : renderer(renderer), visible(false), location(0, 0) {
    options = { "Barracks Tower", "Bomb Tower", "Laser Tower" };
}

GUI::~GUI() {}

void GUI::show(const TowerLocation& towerLocation) {
    visible = true;
    location = towerLocation;
}

void GUI::render() {
    if (!visible) return;

    int adjustedY = location.y - 75; // Render GUI above tower

    // Render GUI background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
    SDL_Rect guiRect = { location.x, adjustedY, 200, 75 };
    SDL_RenderFillRect(renderer, &guiRect);

    // Render GUI options
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect optionRect = { location.x, adjustedY, 200, 25 };
    for (int i = 0; i < options.size(); ++i) {
        optionRect.y = adjustedY + i * 25;
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
