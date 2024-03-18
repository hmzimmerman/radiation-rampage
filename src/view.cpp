#include "view.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>

View::View(){
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        cout << "Error. SDL could not initialize" << endl;
    };

    window = SDL_CreateWindow("player",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Delay(100);
    if (window == NULL){
        cout << "Error. Could not create window" << endl;
    };

    renderer =  SDL_CreateRenderer(window,
                       -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        cout << "Error creating renderer" << endl;
    };
}

void View::update(){
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

View::~View(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}