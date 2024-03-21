#ifndef VIEW_H
#define VIEW_H

#include <SDL.h>
#include <stdio.h>
#include <sdl_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include "logic.h"
#include "tower.h"


const int SCREEN_HEIGHT = 720;
const int SCREEN_WIDTH = 1280;

class View{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
    public:
        View();
        ~View();
        bool update(Logic logic);

        void renderTowerLocations();
        void handleTowerPlacement(SDL_Event event);
};
#endif
