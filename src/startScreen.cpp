#include "startScreen.h"

#include <string>

startScreen::startScreen(SDL_Renderer* renderer, int screenWidth, int screenHeight)
    : renderer(renderer), screenWidth(screenWidth), screenHeight(screenHeight), selected(0) {
    // Load background texture
    backgroundTexture = IMG_LoadTexture(renderer, "../resource/EmptyStartScreen.png");
    
    // Load font
    font = TTF_OpenFont("../resource/arial.ttf", 34); // Adjust the font path and size as needed
    
    // Set text color
    textColor = {255, 255, 255}; // White color
    
    // Initialize the positions and text for the selectable boxes
    int boxWidth = 400;
    int boxHeight = 75;
    int padding = 50; // Padding between boxes
    int startX = (screenWidth - 2 * boxWidth - padding) / 2; // Starting X position of the first row
    int startY = screenHeight / 2 + 100; // Starting Y position of the first row

    // First row
    boxes[0] = SelectableBox(startX, startY, boxWidth, boxHeight, "Play");
    boxes[1] = SelectableBox(startX + boxWidth + padding, startY, boxWidth, boxHeight, "Leaderboard");

    // Second row
    startY += boxHeight + padding;
    boxes[2] = SelectableBox(startX, startY, boxWidth, boxHeight, "Instructions");
    boxes[3] = SelectableBox(startX + boxWidth + padding, startY, boxWidth, boxHeight, "Exit");
    
    // Initially select the first box
    boxes[0].selected = true;
    
    // Start not at any box so the game doesn't immediately switch off the start screen
    selected = -1;
}

startScreen::~startScreen() {
}

void startScreen::render() {
    // Render background
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

    // Render boxes
    for (int i = 0; i < 4; ++i) {
        // Render box
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
        SDL_RenderFillRect(renderer, &boxes[i].rect);

        // Render text
        SDL_Color textColor = {0, 0, 0, 255}; // Black color
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, boxes[i].text.c_str(), textColor);
        if (textSurface == nullptr) {
            std::cerr << "Error rendering text surface: " << TTF_GetError() << std::endl;
            continue;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture == nullptr) {
            std::cerr << "Error creating text texture: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(textSurface);
            continue;
        }

        // Calculate text position
        SDL_Rect textRect;
        textRect.x = boxes[i].rect.x + (boxes[i].rect.w - textSurface->w) / 2;
        textRect.y = boxes[i].rect.y + (boxes[i].rect.h - textSurface->h) / 2;
        textRect.w = textSurface->w;
        textRect.h = textSurface->h;

        // Render text texture
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        // Clean up
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        // Render border for selected box
        if (boxes[i].selected) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
            SDL_RenderDrawRect(renderer, &boxes[i].rect);
        }
    }

    // Present the renderer
    SDL_RenderPresent(renderer);
}

void startScreen::setSelected(int i){
	selected = i;
}

// Move selection left or right
void startScreen::moveSelection(int direction) {
	for (int i = 0; i < 4; ++i) {
    	if (boxes[i].selected) {
        	int nextIndex = (i + direction + 4) % 4; // Wrap around
            selectBox(nextIndex);
            break;
        }
    }
}

// Select a specific box
void startScreen::selectBox(int index) {
    for (int i = 0; i < 4; ++i) {
    	boxes[i].selected = (i == index);
	}
}
    
int startScreen::getSelected() const {
	return selected;
}

const SelectableBox* startScreen::getBoxes() const {
	return boxes;
}

bool startScreen::start(int mouseX, int mouseY) {
    return (mouseX >= screenWidth/2 - 100 && mouseX <= screenWidth/2 + 300 && mouseY >= screenHeight/2 + 200 && mouseY <= screenHeight/2 + 250);
}