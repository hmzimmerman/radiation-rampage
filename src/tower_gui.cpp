#include "tower_gui.h"
#include <iostream>

GUI::GUI(SDL_Renderer* renderer) : renderer(renderer), visible(false), location(0, 0) {
    options = { "Barracks", "Bomb", "Laser" };
}

GUI::~GUI() {
    for (auto& pair : towerTextures) {
        SDL_DestroyTexture(pair.second);
    }
}

void GUI::show(const TowerLocation& towerLocation) {
    visible = true;
    location = towerLocation;
}

void GUI::render() {
    if (!visible) return;

    int adjustedY = location.y - 30; // Render GUI above tower
    int rectHeight = 25;
    int rectWidth = 195;
    int centerX = location.x - rectWidth / 2; // Center GUI above tower

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
        int textWidth, textHeight;
        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
        SDL_Rect textRect = { optionRect.x + (optionWidth - textWidth) / 2, optionRect.y + (rectHeight - textHeight) / 2, textWidth, textHeight };
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        TTF_CloseFont(font);
    }
}

void GUI::hide() {
    visible = false;
}

void GUI::selectTowerType(int mouseX, int mouseY) {
    // Check if mouse is within bounds of any option
    for (int i = 0; i < options.size(); ++i) {
        int rectWidth = 195;
        int optionX = location.x - rectWidth / 2 + i * (rectWidth / options.size());
        int optionY = location.y - 30;
        int optionWidth = rectWidth / options.size();
        int optionHeight = 25;

        if (mouseX >= optionX && mouseX <= optionX + optionWidth &&
            mouseY >= optionY && mouseY <= optionY + optionHeight) {
            // Create tower and store it in that location
            Tower* tower = Tower::createTower(options[i], location.x, location.y);
            location.occupied = true;
            location.towerType = options[i];
            if (tower) {
                towerLocations.push_back(location);
                towerLocations.back().occupied = true;
            }
            //std::cout << "Tower type selected: " << options[i] << std::endl;
            return;
        }
    }
}

void GUI::addTowerTexture(SDL_Texture* texture, const std::string& name) {
    towerTextures.insert({ name, texture });
}