#include <iostream>
#include <stdio.h>
#include <vector>
#include "waveManager.h"
#include "enemy.h"
#include "tower.h"
#include "laserTower.h"
#include "barracks.h"
#include "constants.h"

// Constructor
Logic::Logic() {
    score = 0;
    health = 20;
    game_over = false;
    paused = false;
    wave_manager = new WaveManager();
    moneyManager = new MoneyManager();
}

int Logic::getScore() {
    return score;
}

int Logic::getHealth() {
    return health;
}

int Logic::getMoney(){
    return moneyManager->getMoney();
}

bool Logic::isPaused() {
    return paused;
}

void Logic::setPaused() {
    paused = true;
}

void Logic::setUnpaused() {
    paused = false;
}

void Logic::takeDamage(int d){
	health -= d;
}

std::vector<Enemy> Logic::getEnemiesOnField() {
    return wave_manager->getActiveEnemies();
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
    if(isPaused() == false){
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
	    for (const TowerLocation& location : towerLocations) {
	        if (location.occupied) {
	            Tower* tower = location.tower;
	            if (tower) {
	                tower->updateTarget(wave_manager->getActiveEnemies());
	                
	                // Check if the tower is a LaserTower and if it's ready to attack
	                if (LaserTower* laserTower = dynamic_cast<LaserTower*>(tower)) {
	                    if (laserTower->isReadyToAttack(elapsedTime)) {
	                        laserTower->attack();
	                    }
	                } else if (Barracks* barracksTower = dynamic_cast<Barracks*>(tower)) {
	                    if (barracksTower->isReadyToAttack(elapsedTime)) {
	                        barracksTower->attack();
	                    }
                        barracksTower->update(elapsedTime); 
	                } else {
	                    // Other tower attacks
	                    //tower->attack();
	                }
	            }
	        }
	    }
	}
}
