#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "view.h"
#include "logic.h"
#include "tower_gui.h"

using namespace std;
View::View(){
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        cout << "Error. SDL could not initialize" << endl;
    };

    window = SDL_CreateWindow("Radiation Rampage",
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

    if (TTF_Init() < 0) {
    std::cerr << "Error. Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
    }

    logic = new Logic();
    tower_gui = new TOWER_GUI(renderer);
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
            handleTowerClick(event);
            handleTowerTypeSelection(event);
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
    renderGUI();
    renderTowerLocations();
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
    return running;
}

// Show GUI for tower if mouse click occurs within tower region
void View::handleTowerClick(SDL_Event event) {
    for (auto& location : towerLocations) {
        if (!location.occupied &&
            event.button.x >= location.x && event.button.x <= location.x + location.size &&
            event.button.y >= location.y && event.button.y <= location.y + location.size) {
            tower_gui->show(location);
            return;
        }
    }
}

// Pass mouse coordinates to GUI for option selection
void View::handleTowerTypeSelection(SDL_Event event) {
    tower_gui->selectTowerType(event.button.x, event.button.y);
}

// Render respective tower images
void View::renderTowerLocations() {
    for (const auto& location : towerLocations) {
        if (location.occupied) {
            SDL_Texture* towerTexture = nullptr;
            std::string textureName;
            if (location.towerType.compare("Barracks") == 0) {
                towerTexture = IMG_LoadTexture(renderer, "../resource/barrackstower.png");
                textureName = "Barracks";
            } else if (location.towerType.compare("Bomb") == 0) {
                towerTexture = IMG_LoadTexture(renderer, "../resource/bombtower.png");
                textureName = "Bomb";
            } else if (location.towerType.compare("Laser") == 0) {
                towerTexture = IMG_LoadTexture(renderer, "../resource/lasertower.png");
                textureName = "Laser";
            }

            tower_gui->addTowerTexture(towerTexture, textureName);
            SDL_Rect towerRect = { location.x, location.y, location.size, location.size };
            SDL_RenderCopy(renderer, towerTexture, nullptr, &towerRect);
        }
    }
}

void View::renderGUI() {
    tower_gui->render();
}

View::~View(){
    delete logic;
    delete tower_gui; 
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}