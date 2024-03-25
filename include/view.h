#ifndef VIEW_H
#define VIEW_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include "logic.h"

class TOWER_GUI;

const int SCREEN_HEIGHT = 720;
const int SCREEN_WIDTH = 1280;

class View{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        Logic* logic;
        TOWER_GUI* tower_gui;
    public:
        View();
        ~View();
        bool update(Logic logic);

        void renderTowerLocations();
        void handleTowerClick(SDL_Event event);
        void renderGUI();
        void handleTowerTypeSelection(SDL_Event event);
};
#endif