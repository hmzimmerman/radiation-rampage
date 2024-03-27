#ifndef VIEW_H
#define VIEW_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include "logic.h"

class TOWER_GUI;
struct TowerLocation;

const int SCREEN_HEIGHT = 720;
const int SCREEN_WIDTH = 1280;

class View{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        Logic* logic;
        TOWER_GUI* tower_gui;
        TOWER_GUI* update_tower_gui;
    public:
        View();
        ~View();
        bool update(Logic logic);

        void renderGUI();
        void renderTowerLocations();
        void renderTowerRadius(const TowerLocation& location);
        void handleTowerClick(SDL_Event event);
        void handleTowerTypeSelection(SDL_Event event);
};
#endif