#include "startScreen.h"
#include <iostream>

startScreen::startScreen(SDL_Renderer* renderer, int screenWidth, int screenHeight)
	: renderer(renderer), screenWidth(screenWidth), screenHeight(screenHeight) {
}

startScreen::~startScreen() {
}

void startScreen::render() {
	SDL_RenderClear(renderer);
	
	// Render the light green background
	SDL_Rect bgRect = {0, 0, screenWidth, screenHeight};
	SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); // Light green color
	SDL_RenderFillRect(renderer, &bgRect);
	
	// Render the white box
	SDL_Rect whiteBoxRect = {screenWidth/2, screenHeight/2 + 100, 200, 150};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
	SDL_RenderFillRect(renderer, &whiteBoxRect);
	
	// Present the renderer
	SDL_RenderPresent(renderer);
}

bool startScreen::handleInput(const SDL_Event& event) {
    // Handle input events
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (start(mouseX, mouseY)) {
            return true;
        }
    }
    return false;
}

bool startScreen::start(int mouseX, int mouseY) {
    return (mouseX >= screenWidth/2 - 100 && mouseX <= screenWidth/2 + 300 && mouseY >= screenHeight/2 + 200 && mouseY <= screenHeight/2 + 250);
}