#include "startScreen.h"
#include <SDL_image.h>

startScreen::startScreen(SDL_Renderer* renderer, int screenWidth, int screenHeight)
	: renderer(renderer), screenWidth(screenWidth), screenHeight(screenHeight) {
}

startScreen::~startScreen() {
}

void startScreen::render() {
    SDL_RenderClear(renderer);

    SDL_Texture* screenTexture = IMG_LoadTexture(renderer, "../resource/StartScreen.png");

    SDL_Rect bgRect = {0, 0, screenWidth, screenHeight};
    SDL_RenderCopy(renderer, screenTexture, nullptr, &bgRect);

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Cleanup
    SDL_DestroyTexture(screenTexture);
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