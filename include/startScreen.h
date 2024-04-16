#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <SDL.h>

class startScreen {
public:
    startScreen(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~startScreen();
    
    void render();
    bool handleInput(const SDL_Event& event);
    
    bool start(int mouseX, int mouseY);

private:
    SDL_Renderer* renderer;
    int screenWidth;
    int screenHeight;
};

#endif