#ifndef TOWER_GUI_H
#define TOWER_GUI_H

#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "tower.h"

struct TowerLocation;

class TOWER_GUI {
private:
    SDL_Renderer* renderer;
    bool visible;
    TowerLocation location;
    std::vector<std::string> options;
    std::vector<std::string> updateOptions;
    std::unordered_map<std::string, SDL_Texture*> towerTextures;
public:
    TOWER_GUI(SDL_Renderer* renderer);
    ~TOWER_GUI();
    TowerLocation getLocation();
    void show(const TowerLocation& towerLocation, Tower* tower);
    void render();
    void hide();
    void selectTowerType(int mouseX, int mouseY);
    void addTowerTexture(SDL_Texture* texture, const std::string& name);
    void handleTowerAction(const std::string& action);
    //void printTowerInfo();

    //Getters
    bool isVisible() const { return visible; }
};
#endif