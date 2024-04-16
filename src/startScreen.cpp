#include "startScreen.h"

#include <string>

startScreen::startScreen(SDL_Renderer* renderer, int screenWidth, int screenHeight) : renderer(renderer) {
    // Load background texture
    backgroundTexture = IMG_LoadTexture(renderer, "../resource/EmptyStartScreen.png");
    if (backgroundTexture == nullptr) {
        std::cerr << "Error loading StartScreen.png: " << IMG_GetError() << std::endl;
    }

    // Load font
    font = TTF_OpenFont("../resource/arial.ttf", 24);
    if (font == nullptr) {
        std::cerr << "Error loading font: " << TTF_GetError() << std::endl;
    }

    // Define positions and sizes of four boxes
    int boxWidth = 200;
    int boxHeight = 50;
    int margin = 20;
    int startY = (screenHeight - 4 * (boxHeight + margin)) / 2;

    std::string boxTexts[4] = {"Play", "Instructions", "Leaderboard", "Exit"};
    for (int i = 0; i < 4; ++i) {
        int startX = (screenWidth - boxWidth) / 2;
        int startY = (screenHeight - 4 * (boxHeight + margin)) / 2 + i * (boxHeight + margin);
        boxes[i] = SelectableBox(startX, startY, boxWidth, boxHeight, boxTexts[i]);
    }

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

    // Handle input events
    void startScreen::handleInput(const SDL_Event& event) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    moveSelection(-1);
                    break;
                case SDLK_RIGHT:
                    moveSelection(1);
                    break;
                // Handle other keys if needed
            }
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            // Handle clicking to select a box
                int mouseX, mouseY;
    			SDL_GetMouseState(&mouseX, &mouseY);
            for (int i = 0; i < 4; i++){
            	SDL_Point mousePosition = {mouseX, mouseY};
                if (SDL_PointInRect(&mousePosition, &boxes[i].rect)) {
                    selectBox(i);
                    selected = i;
                    break;
                }
            }
        }
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

bool startScreen::start(int mouseX, int mouseY) {
    return (mouseX >= screenWidth/2 - 100 && mouseX <= screenWidth/2 + 300 && mouseY >= screenHeight/2 + 200 && mouseY <= screenHeight/2 + 250);
}