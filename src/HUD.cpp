#include "HUD.h"
#include <iostream>

HUD::HUD(SDL_Renderer* renderer, int screenWidth, int screenHeight) 
    : renderer(renderer), screenWidth(screenWidth), screenHeight(screenHeight),
      coinCount(0), playerHealth(100), currentWave(1) {

    // Initialize background rectangle
	backgroundRect.x = (screenWidth - backgroundRect.w) / 2; // Center horizontally
    backgroundRect.y = screenHeight - 100; // 100 pixels from the bottom
    backgroundRect.w = 400; // Width of the rectangle
    backgroundRect.h = 50;  // Height of the rectangle

    // Set text color
    textColor = { 255, 255, 255, 255 }; // White color

    // Load font
    if (TTF_Init() == -1) {
        std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
    }
    font = TTF_OpenFont("../resource/arial.ttf", 24); // Replace "path/to/your/font.ttf" with the actual path to your font file
    if (font == NULL) {
        std::cerr << "Error loading font: " << TTF_GetError() << std::endl;
    }
}

void HUD::update(int coins, int health, int wave) {
    coinCount = coins;
    playerHealth = health;
    currentWave = wave;
}

void HUD::render() {
    // Render background rectangle
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black color
    SDL_RenderFillRect(renderer, &backgroundRect);

    // Render text
    std::string text = "Coins: " + std::to_string(coinCount) +
                       "   Health: " + std::to_string(playerHealth) +
                       "   Wave: " + std::to_string(currentWave);
    renderText(text, 10, screenHeight - 40); // 40 pixels from the bottom

    // Update screen
    SDL_RenderPresent(renderer);
}

void HUD::renderText(const std::string& text, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), textColor);
    if (surface == NULL) {
        std::cerr << "Error rendering text: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        std::cerr << "Error creating texture from surface: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }
    SDL_Rect textRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
