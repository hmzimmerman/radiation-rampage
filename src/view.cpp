#include "view.h"
#include "logic.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>

using namespace std;
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

bool View::update(Logic logic){

    // running is returned to update and is updated when player hits x or quits 
    // at the end return running 
    SDL_Event event; 
    bool running = true;
    while (SDL_PollEvent(&event)!=0){
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_q) {
                running = false;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            handleTowerPlacement(event);
        }
        // if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
        //     logic.setPaused();
        // } else if (event.window.event == SDL_WINDOWEVENT_RESTORED) {
        //     logic.setUnpaused();
        // }
    }

    SDL_RenderClear(renderer);
    SDL_Texture* texture = IMG_LoadTexture(renderer, "../resource/Map.png");
    SDL_Rect destination;
    destination.x = 0;
    destination.y = 0;
    destination.w = SCREEN_WIDTH;
    destination.h = SCREEN_HEIGHT;

    SDL_RenderCopy(renderer, texture, NULL, &destination);
    renderTowerLocations();
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
    return running;
}

void View::renderTowerLocations() {
    for (const auto& location : towerLocations) {
        if (location.occupied) {
            // Draw a green square if the location is occupied by a tower
            boxRGBA(renderer, location.x, location.y,
                    location.x + location.size, location.y + location.size,
                    0, 255, 0, 255);
        } else {
            // Draw an empty square if the location is not occupied
            rectangleRGBA(renderer, location.x, location.y,
                          location.x + location.size, location.y + location.size,
                          0, 255, 0, 255);
        }
    }
}


void View::handleTowerPlacement(SDL_Event event) {
    for (auto& location : towerLocations) {
        if (!location.occupied &&
            event.button.x >= location.x && event.button.x <= location.x + location.size &&
            event.button.y >= location.y && event.button.y <= location.y + location.size) {
            location.occupied = true;
            // TODO Add tower placement logic
            break;
        }
    }
}


View::~View(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}