#ifndef TOWER_GUI_H
#define TOWER_GUI_H

#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "tower.h"

struct TowerLocation;

class GUI {
private:
    SDL_Renderer* renderer;
    bool visible;
    TowerLocation location;
    std::vector<std::string> options;
    std::unordered_map<std::string, SDL_Texture*> towerTextures;
public:
    GUI(SDL_Renderer* renderer);
    ~GUI();
    void show(const TowerLocation& towerLocation);
    void render();
    void hide();
    void selectTowerType(int mouseX, int mouseY);
    void addTowerTexture(SDL_Texture* texture, const std::string& name);
};
#endif