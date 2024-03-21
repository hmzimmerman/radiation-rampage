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
    wave_manager = new WaveManager();
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