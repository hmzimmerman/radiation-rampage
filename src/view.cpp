#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "view.h"
#include "logic.h"
#include "towerGUI.h"
#include "barracks.h"

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
    tower_gui = new TOWERGUI(renderer);
    update_tower_gui = new TOWERGUI(renderer);
    hud = new HUD(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    attackAnimation.active = false;

    loadTowerTextures();
    loadEnemyTextures();
}

void View::loadTowerTextures() {
    barracksTexture = IMG_LoadTexture(renderer, "../resource/barrackstower.png");
    bombTexture = IMG_LoadTexture(renderer, "../resource/bombtower.png");
    laserTexture = IMG_LoadTexture(renderer, "../resource/lasertower.png");
}

void View::loadEnemyTextures() {
    humanRaiderTexture = IMG_LoadTexture(renderer, "../resource/HumanRaider.png");
}

bool View::update(Logic& logic){
    // Running is returned to update and is updated when player hits x or quits
    // At the end return running
    SDL_Event event; 
    bool running = true;
    while (SDL_PollEvent(&event)!=0){
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_q) {
                running = false;
            }else if (event.key.keysym.sym == SDLK_p) {
            	if(logic.isPaused()){
                	logic.setUnpaused();
            	}else{
            		logic.setPaused();
            	}
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
    renderSoldiers();
    renderHUD();

    if (attackAnimation.active) {
        thickLineRGBA(renderer, attackAnimation.startX, attackAnimation.startY,
                      attackAnimation.endX, attackAnimation.endY,
                      4, 255, 255, 0, 255); // Render a yellow line

        // Disable animation again after a short moment
        if (SDL_GetTicks() - attackAnimation.startTime >= 100) {
            attackAnimation.active = false;
        }
    }

    // Render enemies
    std::vector<Enemy> enemies = logic.getEnemiesOnField();
    for (int i = 0; i < enemies.size(); i++) {
        SDL_Rect raiderDestination;
        raiderDestination.w = 70;
        raiderDestination.h = 70;

        // Enemy coordinate is the center of the enemy
        raiderDestination.x = enemies[i].getX() - raiderDestination.w / 2;
        raiderDestination.y = enemies[i].getY() - raiderDestination.h / 2;
        SDL_RenderCopy(renderer, humanRaiderTexture, NULL, &raiderDestination);
    }

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
    return running;
}

// Show GUI for tower if mouse click occurs within tower region
void View::handleTowerClick(const SDL_Event& event) {
    for (auto& location : towerLocations) {
        if (!location.occupied && event.button.x >= location.x && event.button.x <= location.x + location.size &&
            event.button.y >= location.y && event.button.y <= location.y + location.size) {
            tower_gui->show(location);
            update_tower_gui->hide();
            return;
        } else if (location.occupied && event.button.x >= location.x && event.button.x <= location.x + location.size &&
                 event.button.y >= location.y && event.button.y <= location.y + location.size) {
            update_tower_gui->show(location);
            tower_gui->hide();
            return;
        }
    }
}

// Pass mouse coordinates to GUI for option selection
void View::handleTowerTypeSelection(const SDL_Event& event) {
    if (tower_gui->isVisible()) {
        tower_gui->selectTowerType(event.button.x, event.button.y, this);
    } else if (update_tower_gui->isVisible()) {
        update_tower_gui->selectTowerType(event.button.x, event.button.y, this);
    }
}

// Render respective tower images
void View::renderTowerLocations() {
    for (const auto& location : towerLocations) {
        if (location.occupied) {
            SDL_Texture* towerTexture = nullptr;
            if (location.towerType.compare("Barracks") == 0) {
                towerTexture = barracksTexture;
            } else if (location.towerType.compare("Bomb") == 0) {
                towerTexture = bombTexture;
            } else if (location.towerType.compare("Laser") == 0) {
                towerTexture = laserTexture;
            }

            if (towerTexture != nullptr) {
                SDL_Rect towerRect = { location.x, location.y, location.size, location.size };
                SDL_RenderCopy(renderer, towerTexture, nullptr, &towerRect);

                //Render tower range radius
                if (update_tower_gui->isVisible()) {
                    renderTowerRadius(update_tower_gui->getLocation());
                }
            }
        }
    }
}

void View::renderTowerRadius(const TowerLocation& location) {
    if (location.occupied) {
        int circleX = location.x + location.size / 2;
        int circleY = location.y + location.size / 2;
        int radius = location.tower->getRange();

        ellipseRGBA(renderer, circleX, circleY, radius, radius, 255, 0, 0, 255);
    }
}

void View::renderGUI() {
    tower_gui->render();
    update_tower_gui->render();
}


void View::renderHUD(){
	hud->render(0, logic->getHealth(), 1);
}

void View::triggerLaserAttackAnimation(int startX, int startY, int endX, int endY){
    attackAnimation.active = true;
    attackAnimation.startX = startX;
    attackAnimation.startY = startY;
    attackAnimation.endX = endX;
    attackAnimation.endY = endY;
    attackAnimation.startTime = SDL_GetTicks();
}

void View::renderSoldiers() {
    for (const auto& location : towerLocations) {
        if (location.occupied && location.towerType == "Barracks") {
            Barracks* barracksTower = dynamic_cast<Barracks*>(location.tower);
            if (barracksTower) {
                // Get the tower and soldier locations associated with this barracks tower
                const TowerLocation& towerLocation = barracksTower->getLocation();
                const std::vector<std::pair<int, int>>& soldierLocations = barracksTower->getSoldierLocations();

                // Find the index of the tower location
                int index = -1;
                for (size_t i = 0; i < towerLocations.size(); ++i) {
                    if (towerLocations[i] == towerLocation) {
                        index = static_cast<int>(i);
                        break;
                    }
                }

                // Tower locations and soldier locations have corresponding indices
                // Render the soldiers at the corresponding location
                if (index != -1 && index < static_cast<int>(soldierLocations.size())) {
                    const auto& sLocation = soldierLocations[index];
                    SDL_Texture* soldierTexture = IMG_LoadTexture(renderer, "../resource/BarracksSoldiers.png");
                    SDL_Rect soldierRect = { sLocation.first, sLocation.second, 120, 50 };
                    SDL_RenderCopy(renderer, soldierTexture, nullptr, &soldierRect);

                    SDL_DestroyTexture(soldierTexture);
                }
            }
        }
    }
}

View::~View(){
    delete logic;
    delete tower_gui;
    delete update_tower_gui;
    delete hud;
    SDL_DestroyTexture(barracksTexture);
    SDL_DestroyTexture(bombTexture);
    SDL_DestroyTexture(laserTexture);
    SDL_DestroyTexture(humanRaiderTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}