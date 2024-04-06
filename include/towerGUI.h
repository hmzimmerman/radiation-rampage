#ifndef TOWERGUI_H
#define TOWERGUI_H

#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "tower.h"
#include "view.h"

struct TowerLocation;

class TOWERGUI {
private:
    SDL_Renderer* renderer;
    bool visible;
    TowerLocation location;
    std::vector<std::string> options;
    std::vector<std::string> updateOptions;
    std::unordered_map<std::string, SDL_Texture*> towerTextures;
    
public:
    TOWERGUI(SDL_Renderer* renderer);
    ~TOWERGUI();
    TowerLocation getLocation();
    void show(const TowerLocation& towerLocation);
    void render();
    void hide();
    void selectTowerType(int mouseX, int mouseY, View* view);
    void handleTowerAction(const std::string& action);
    //void printTowerInfo();

    //Getters
    bool isVisible() const { return visible; }
};
#endif