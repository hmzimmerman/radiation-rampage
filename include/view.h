#ifndef VIEW_H
#define VIEW_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include "logic.h"
#include "HUD.h"

class TOWERGUI;
struct TowerLocation;
struct FailedTransMessage;


struct AttackAnimation {
    bool active;
    int startX;
    int startY;
    int endX;
    int endY;
    Uint32 startTime;
};

struct FailedTransMessage{
    // Message box displayed when a money transaction fails
    bool active;
    Uint32 startTime;
};


class View{
    private:
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;

        SDL_Window* window;
        SDL_Renderer* renderer;
        Logic* logic;
        TOWERGUI* tower_gui;
        TOWERGUI* update_tower_gui;
        HUD* hud;
        AttackAnimation attackAnimation;
        FailedTransMessage failedTransMessage;

        
        SDL_Texture* barracksTexture;
        SDL_Texture* bombTexture;
        SDL_Texture* laserTexture;
        SDL_Texture* humanRaiderTexture;
        SDL_Texture* barracksSoldierTexture;

        void loadTowerTextures();
        void loadEnemyTextures();
        void renderFailedTransMessage();

        
    public:
        View();
        ~View();
        bool update(Logic& logic);

        void renderEnemies(const std::vector<Enemy>& enemies);
        void renderGUI();
        void renderTowerLocations();
        void renderHUD(Logic& logic);
        void renderTowerRadius(const TowerLocation& location);
        void renderSoldiers();
        void renderLost(Logic& logic);
        void renderPause();
        void handleTowerClick(const SDL_Event& event);
        void handleTowerTypeSelection(const SDL_Event& event, Logic& logic);
        void triggerLaserAttackAnimation(int startX, int startY, int endX, int endY);
};
#endif
