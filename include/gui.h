#ifndef GUI_H
#define GUI_H

#include <SDL.h>
#include <vector>
#include "tower.h"

struct TowerLocation;

class GUI {
private:
    SDL_Renderer* renderer;
    bool visible;
    TowerLocation location;
    std::vector<std::string> options;
public:
    GUI(SDL_Renderer* renderer);
    ~GUI();
    void show(const TowerLocation& towerLocation);
    void render();
    void hide();
};
#endif