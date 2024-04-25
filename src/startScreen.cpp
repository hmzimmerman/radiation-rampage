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

void startScreen::render() {
    // Render background
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
    
    TTF_SetFontSize(font, 125);
    textColor = {150, 0, 0}; // Red color for title  
    
    // Render title
    SDL_Surface* titleSurface = TTF_RenderText_Solid(font, "Radiation Rampage", textColor);
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);

	// Calculate title position
	int titleWidth = titleSurface->w;
    int titleHeight = titleSurface->h;
    int titleX = (screenWidth - titleWidth) / 2;
    int titleY = 140;

    // Render title texture
    SDL_Rect titleRect = {titleX, titleY, titleWidth, titleHeight};
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);

    // Clean up
    SDL_DestroyTexture(titleTexture);
    SDL_FreeSurface(titleSurface);
    
    TTF_SetFontSize(font, 34);
    textColor = {255, 255, 255};

    // Render boxes
    for (int i = 0; i < 4; i++) {
        // Render box
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
        SDL_RenderFillRect(renderer, &boxes[i].rect);

        // Render text
        SDL_Color textColor = {0, 0, 0, 255}; // Black color
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, boxes[i].text.c_str(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

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
        int boxWidth = static_cast<int>(screenWidth * 0.8);
        int boxHeight = static_cast<int>(screenHeight * 0.85);
        SDL_Rect textBoxRect = {(screenWidth - boxWidth) / 2, (screenHeight - boxHeight) / 2, boxWidth, boxHeight};

        // Render the box background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black color
        SDL_RenderFillRect(renderer, &textBoxRect);
        
        int size = 40;
        int pad = 10;
        close = {
            textBoxRect.x + textBoxRect.w - size - pad,
            textBoxRect.y + pad,
            size,
            size
        };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
        SDL_RenderFillRect(renderer, &close);

        // Render the letter "X" in white color inside the box
        SDL_Color textColor = {255, 255, 255, 255}; // White color
        renderText("X", textColor, close.x + size / 2 - 10, close.y + size / 2 - 16);

        // Render the bullet point text
        int textX = textBoxRect.x + 20;
        int textY = textBoxRect.y + 20;
        int lineHeight = 30;

        // Render "Instructions" text
        renderText("Instructions:", textColor, textX, textY);
        textY += lineHeight; // Move down to start rendering bullet points

        renderText("- Survive against endless waves to beat your high score", textColor, textX, textY);
        textY += lineHeight;
        renderText("- If you go to 0 health, you lose", textColor, textX, textY);
        textY += lineHeight;
        renderText("- Build towers to combat enemies walking along the path", textColor, textX, textY);
        textY += lineHeight;
        renderText("- Manage your money to buy, upgrade, and repair towers", textColor, textX, textY);
        textY += lineHeight;
        renderText("- Environmental effects will occur that will somehow affect the game", textColor, textX, textY);
        textY += lineHeight;
        renderText("- Enemies have strengths and weakness you must keep in mind", textColor, textX, textY);
        textY += lineHeight;
        renderText("- Towers will degrade over time so make sure to keep them repaired", textColor, textX, textY);
    }
}

void startScreen::renderText(const std::string& text, const SDL_Color& color, int x, int y) {
	SDL_Surface* textSurface;
	if(text == "X"){
		TTF_Font* XFont = TTF_OpenFont("../resource/arial.ttf", 30);
        textSurface = TTF_RenderText_Solid(XFont, text.c_str(), color);
	}else{
    	textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	}
	
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