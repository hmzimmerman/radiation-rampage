#include "startScreen.h"

#include <string>

startScreen::startScreen(SDL_Renderer* renderer, int screenWidth, int screenHeight)
    : renderer(renderer), screenWidth(screenWidth), screenHeight(screenHeight), selected(0), instruct(false) {
    // Load background texture
    backgroundTexture = IMG_LoadTexture(renderer, "../resource/EmptyStartScreen.png");
    
    // Load font
    font = TTF_OpenFont("../resource/Overseer_Italic.otf", 100);
    
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
    
    TTF_SetFontSize(font, 100);
    
    // Render title
    SDL_Surface* titleSurface = TTF_RenderText_Solid(font, "Radiation Rampage", textColor);
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);

	// Calculate title position
	int titleWidth = titleSurface->w;
    int titleHeight = titleSurface->h;
    int titleX = (screenWidth - titleWidth) / 2;
    int titleY = 200;

    // Render title texture
    SDL_Rect titleRect = {titleX, titleY, titleWidth, titleHeight};
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);

    // Clean up
    SDL_DestroyTexture(titleTexture);
    SDL_FreeSurface(titleSurface);
    
    TTF_SetFontSize(font, 34);

    // Render boxes
    for (int i = 0; i < 4; i++) {
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
    
    if(instruct){
    	// Render bullet point text box
        SDL_Rect textBoxRect = {100, 300, 600, 300};

        // Render the box background
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
        SDL_RenderFillRect(renderer, &textBoxRect);

        // Render the bullet point text
        SDL_Color textColor = {0, 0, 0, 255}; // Black color
        int textX = textBoxRect.x + 20;
        int textY = textBoxRect.y + 20;
        int lineHeight = 30; 

        // Render "Instructions" text
        renderText("Instructions:", textColor, textX, textY);
        textY += lineHeight; // Move down to start rendering bullet points

        renderText("- 1", textColor, textX, textY);
        textY += lineHeight;
        renderText("- 2", textColor, textX, textY);
        textY += lineHeight;
        renderText("- 3", textColor, textX, textY);
    }

    // Present the renderer
    SDL_RenderPresent(renderer);
}

void startScreen::renderText(const std::string& text, const SDL_Color& color, int x, int y) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Calculate text position
    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};

    // Render text texture
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Clean up
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void startScreen::setSelected(int i){
	selected = i;
}

void startScreen::setInstruct(bool i){
	instruct = i;
}

// Move selection left or right
void startScreen::moveSelection(int direction) {
    for (int i = 0; i < 4; i++) {
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

const SelectableBox* startScreen::getBoxes() const {
	return boxes;
}