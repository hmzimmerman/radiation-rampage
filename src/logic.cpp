#include "waveManager.h"
#include "enemy.h"
#include "tower.h"
#include "laserTower.h"

#include <iostream>
#include <stdio.h>
#include <vector>

// Constructor
Logic::Logic() {
    score = 0;
    health = 20;
    game_over = false;
    paused = false;
    wave_manager = new WaveManager();

    // Uncomment for testing
    //enemies.push_back(Enemy("Human Raider", 35, 1, 172, 0, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
    //enemies.push_back(Enemy("Human Raider", 35, 1, 172, -50, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
    //enemies.push_back(Enemy("Human Raider", 35, 1, 172, -100, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
    //enemies.push_back(Enemy("Human Raider", 35, 1, 172, -150, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
    //enemies.push_back(Enemy("Human Raider", 35, 1, 172, -200, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
}

int Logic::getScore() {
    return score;
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

std::vector<Enemy> Logic::getEnemiesOnField() {
    return wave_manager->getActiveEnemies();
}

void Logic::update(double elapsedTime){
    for (int i = 0; i < wave_manager->getActiveEnemies().size(); i ++){
        wave_manager->getActiveEnemies()[i].move();
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
                } else {
                    // Other tower attacks
                    //tower->attack();
                }
            }
        }
    }
}