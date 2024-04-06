#include <iostream>
#include <stdio.h>
#include <vector>
#include "waveManager.h"
#include "enemy.h"
#include "tower.h"
#include "laserTower.h"
#include "barracks.h"

// Constructor
Logic::Logic() {
    score = 0;
    health = 20;
    game_over = false;
    paused = false;
    wave_manager = new WaveManager();

    // Uncomment for testing
    //enemies.push_back(Enemy("Human Raider", 35, 2, 172, 0, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
    //enemies.push_back(Enemy("Human Raider", 35, 2, 172, -50, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
    //enemies.push_back(Enemy("Human Raider", 35, 2, 172, -100, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
    //enemies.push_back(Enemy("Human Raider", 35, 2, 172, -150, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
    //enemies.push_back(Enemy("Human Raider", 35, 2, 172, -200, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
}

int Logic::getScore() {
    return score;
}

int Logic::getHealth() {
    return health;
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
<<<<<<< src/logic.cpp
    return wave_manager->getActiveEnemies();
}

void Logic::update(double elapsedTime){
    if(isPaused() == false){
    for (int i = 0; i < wave_manager->getActiveEnemies().size(); i ++){
        wave_manager->getActiveEnemies()[i].move();
    }

    if(wave_manager->getActiveEnemies()[i].getX() >= SCREEN_WIDTH){
	        	takeDamage(wave_manager->getActiveEnemies()[i].getDamage());
	        	wave_manager->getActiveEnemies()[i].takeDamage(wave_manager->getActiveEnemies()[i].getHealth());
	        }

    wave_manager->update();
    // Check if enemy is dead and remove from list
	        if (!wave_manager->getActiveEnemies()[i].isAlive()) {
	            wave_manager->getActiveEnemies().erase(wave_manager->getActiveEnemies().begin() + i);
	            i--;
	            //score += enemy.getScore(); // Increment score for killing enemy
	            continue;
	        }
        }


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
	                    barracksTower->attack();
	                } else {
	                    // Other tower attacks
	                    //tower->attack();
	                }
	            }
	        }
	    }
	}
}
