#ifndef VIEW_H
#define VIEW_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include <memory>

#include "logic.h"
#include "HUD.h"
#include "startScreen.h"
<<<<<<< include/view.h
#include "weather.h"
=======
#include "damage_type.h"
>>>>>>> include/view.h

class TOWERGUI;
struct TowerLocation;
struct FailedTransMessage;


struct AttackAnimation {
    DamageType type;
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

        std::shared_ptr<Logic> logic;
        std::shared_ptr<TOWERGUI> tower_gui;
        std::shared_ptr<TOWERGUI> update_tower_gui;
        std::shared_ptr<HUD> hud;
        std::shared_ptr<startScreen> start;

        AttackAnimation attackAnimation;
        FailedTransMessage failedTransMessage;

        SDL_Texture* barracksTexture;
        SDL_Texture* bombTexture;
        SDL_Texture* laserTexture;
        SDL_Texture* barracksSoldierTexture;
        SDL_Texture* barracksUpgradeTexture;
        SDL_Texture* bombUpgradeTexture;
        SDL_Texture* laserUpgradeTexture;
        SDL_Texture* bombEffectTexture;

        SDL_Texture* humanRaiderTexture;

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
        void renderHUD(const Logic& logic);
        void renderTowerRadius(const TowerLocation& location);
        void renderSoldiers();
        void renderLost(Logic& logic);
        void renderPause();
        void handleStartScreen(const SDL_Event& event);
        void renderWaveTime(const WaveManager& manager);
        void handleTowerClick(const SDL_Event& event);
        void handleTowerTypeSelection(const SDL_Event& event, Logic& logic);
        void triggerAttackAnimation(int startX, int startY, int endX, int endY, DamageType attackType);
        void renderAttackAnimation(const Weather& weather);
};
#endif
