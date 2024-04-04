#include "towerGUI.h"

TOWERGUI::TOWERGUI(SDL_Renderer* renderer) : renderer(renderer), visible(false), location(0, 0) {
    options = { "Barracks", "Bomb", "Laser" };
    updateOptions = { "Upgrade", "Repair", "Sell" };
}

TOWERGUI::~TOWERGUI() {
    for (auto& pair : towerTextures) {
        SDL_DestroyTexture(pair.second);
    }
}

void TOWERGUI::show(const TowerLocation& towerLocation) {
    visible = true;
    location = towerLocation;
}

TowerLocation TOWERGUI::getLocation() {
    return location;
}

void TOWERGUI::render() {
    if (!visible) return;

    int adjustedY = location.y - 30; // Render GUI above tower
    int rectHeight = 25;
    int rectWidth = 195;
    int centerX = location.x - rectWidth / 2; // Center GUI above tower

    // Render GUI background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
    SDL_Rect guiRect = { centerX, adjustedY, rectWidth, rectHeight };
    SDL_RenderFillRect(renderer, &guiRect);

    // Determine options based on if the location is occupied
    const auto& currentOptions = (location.occupied) ? updateOptions : options;

    int optionWidth = rectWidth / currentOptions.size();

    // Render GUI options
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i < currentOptions.size(); ++i) {
        SDL_Rect optionRect = { centerX + i * optionWidth, adjustedY, optionWidth, rectHeight };
        SDL_RenderDrawRect(renderer, &optionRect);

        // Render option text
        SDL_Color textColor = { 0, 0, 0 };
        TTF_Font* font = TTF_OpenFont("../resource/arial.ttf", 12);
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, currentOptions[i].c_str(), textColor);
        
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

void TOWERGUI::hide() {
    visible = false;
}

void TOWERGUI::selectTowerType(int mouseX, int mouseY, View* view) {
    bool clickGUI = false;

    for (int i = 0; i < towerLocations.size(); ++i) {
        TowerLocation& location = towerLocations[i];

        // Check if mouse is within bounds of any option
        int rectWidth = 195;
        int optionWidth = rectWidth / options.size();
        int optionHeight = 25;

        // Determine options based on if the location is occupied
        const auto& currentOptions = (location.occupied) ? updateOptions : options;

        for (int j = 0; j < currentOptions.size(); ++j) {
            int optionX = location.x - rectWidth / 2 + j * optionWidth;
            int optionY = location.y - 30;

            if (mouseX >= optionX && mouseX <= optionX + optionWidth &&
                mouseY >= optionY && mouseY <= optionY + optionHeight) {
                
                // If the location is not occupied, create and store the tower
                if (!location.occupied) {
                    Tower* tower = Tower::createTower(currentOptions[j], location, view);
                    if (tower) {
                        location.occupied = true;
                        location.towerType = currentOptions[j];
                        location.tower = tower;
                        //printTowerInfo();
                    }
                } else {
                    // If the location is occupied, handle tower action
                    handleTowerAction(currentOptions[j]);
                }
                clickGUI = true;
                hide();
                break;
            }
        }
    }
    // Check if click occurred within tower area
    if (!clickGUI) {
        for (const auto& location : towerLocations) {
            if (mouseX >= location.x && mouseX <= location.x + location.size &&
                mouseY >= location.y && mouseY <= location.y + location.size) {
                clickGUI = true;
                break;
            }
        }
    }
    // Otherwise, hide GUI if click occured outside of it
    if (!clickGUI) {
        hide();
    }
}

void TOWERGUI::handleTowerAction(const std::string& action) {
    if (action == "Upgrade") {
        std::cout << "Upgraded" << std::endl; // TODO
    } else if (action == "Repair") {
        std::cout << "Repaired" << std::endl; // TODO
    } else if (action == "Sell") {
        std::cout << "Sold" << std::endl; // TODO
    }
}

// Uncomment for testing
/* void TOWERGUI::printTowerInfo() {
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Tower Information:" << std::endl;
    for (const auto& location : towerLocations) {
        std::cout << "Location: (" << location.x << ", " << location.y << ")" << std::endl;
        if (location.occupied) {
            std::cout << "Tower Type: " << location.towerType << std::endl;
        } else {
            std::cout << "Empty" << std::endl;
        }
    }
} */