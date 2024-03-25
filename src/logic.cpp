#include "waveManager.h"
#include "enemy.h"
#include "logic.h"

#include <iostream>
#include <stdio.h>
#include <vector>

//constructor
Logic::Logic() {
    score = 0;
    health = 20;
    game_over = false;
    paused = false;
    //TODO UNCOMMENT. CHANGES JUST FOR TESTING
    // wave_manager = new WaveManager();

    enemies.push_back(Enemy("Human Raider", 100, 3, 125, -99, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
    enemies.push_back(Enemy("Human Raider", 100, 3, 135, -99, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
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
    //TODO CHANGE BACK
    // return wave_manager->getActiveEnemies();

    return enemies;
}

void Logic::update(double inTime){
    for (int i = 0; i < enemies.size(); i ++){
        enemies[i].move();
    }
}