#include <iostream>
#include <stdio.h>
#include <vector>

#include "waveManager.h"
#include "enemy.h"
#include "tower.h"
#include "laserTower.h"
#include "barracks.h"
#include "bombTower.h"
#include "constants.h"

// Constructor
Logic::Logic() {
    score = 0;
    health = 20;
    game_over = false;
    paused = false;
    start = true;
    wave_manager = std::make_shared<WaveManager>();
    moneyManager = std::make_shared<MoneyManager>();
}

bool Logic::updateMoneyTowerAction(const std::string& action, int coinAmount){
    if (action == "Buy" || 
        action == "Upgrade" ||
        action == "Repair" ){
        bool res = moneyManager->spendMoney(coinAmount);
        return res;
    }else if(action == "Sell"){
        moneyManager->gainMoney(coinAmount);
        return true;
    }
    // Should never reach here 
    return false;
}

void Logic::update(double elapsedTime){
    using namespace window;
    if(isPaused() == false && onStart() == false){
        // Player slowly gains money every update 
        if (moneyManager->isReadyToSlowGain(elapsedTime)){
            moneyManager->slowGain();
        }

        for (int i = 0; i < wave_manager->getActiveEnemies().size(); i ++){
            wave_manager->getActiveEnemies()[i].move();

            if(wave_manager->getActiveEnemies()[i].getX() >= window::screenWidth){
                    takeDamage(wave_manager->getActiveEnemies()[i].getDamage());
                    wave_manager->getActiveEnemies()[i].takeDamage(wave_manager->getActiveEnemies()[i].getHealth());
            }

            // Check if enemy is dead and remove from list
            if (!wave_manager->getActiveEnemies()[i].isAlive()) {
                wave_manager->getActiveEnemies().erase(wave_manager->getActiveEnemies().begin() + i);
                i--;
                continue;
            }
        }
        
        wave_manager->update();

        // Iterate through towers to update their targets and attack
	    for (const TowerLocation& location : TowerLocationManager::getTowerLocations()) {
	        if (location.occupied) {
	            std::shared_ptr<Tower> tower = location.tower;
	            if (tower) {
	                if (std::shared_ptr<LaserTower> laserTower = std::dynamic_pointer_cast<LaserTower>(tower)) {
                        laserTower->updateTarget(wave_manager->getActiveEnemies());
	                    laserTower->update(elapsedTime);
	                } else if (std::shared_ptr<Barracks> barracksTower = std::dynamic_pointer_cast<Barracks>(tower)) {
                        barracksTower->updateTarget(wave_manager->getActiveEnemies());
                        barracksTower->update(elapsedTime);
	                } else if (std::shared_ptr<BombTower> bombTower = std::dynamic_pointer_cast<BombTower>(tower)){
                        if (bombTower->isReadyToAttack(elapsedTime)){
                            bombTower->updateTarget(wave_manager->getActiveEnemies());
                        }
	                }
	            }
	        }
	
	}
}
}

void Logic::switchStart(bool s){
	start = s;
}