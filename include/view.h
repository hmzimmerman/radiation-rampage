#include <SDL.h>
#include <stdio.h>
#include <sdl_ttf.h>
#include <SDL2_gfxPrimitives.h>


const int SCREEN_HEIGHT = 720;
const int SCREEN_WIDTH = 1280;

class View{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        View();
        ~View();
        //TODO pass in game logic here 
        void update();

};