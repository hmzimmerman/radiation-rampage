#include "waveManager.h"
#include "enemy.h"
#include "logic.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>

//constructor
Logic::Logic() {
    score = 0;
    health = 20;
    game_over = false;
    paused = false;
    wave_manager = new WaveManager();
    enemies = createEnemies();
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

Direction Logic::stringToDirection(const std::string& str) {
    if (str == "NORTH") return Direction::NORTH;
    if (str == "SOUTH") return Direction::SOUTH;
    if (str == "EAST") return Direction::EAST;
    if (str == "WEST") return Direction::WEST;

    return Direction::SOUTH; // Default value
}

DamageType Logic::stringToDamageType(const std::string& str) {
    if (str == "LASER") return DamageType::LASER;
    if (str == "BOMB") return DamageType::BOMB;
    if (str == "NORMAL") return DamageType::NORMAL;

    return DamageType::NORMAL; // Default value
}

std::vector<Enemy> Logic::createEnemies(){
    std::ifstream inputFile("stats.txt");
    if (!inputFile) {
        std::cerr << "Failed to open file." << std::endl;
    }

    std::vector<Enemy> enemies;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string name;
        int health, speed, x, y, damage;
        std::string direct_str, weakness_str, strength_str; // Read as strings

        if (!(iss >> name >> health >> speed >> x >> y >> direct_str >> damage >> weakness_str >> strength_str)) {
            std::cerr << "Error reading line from file." << std::endl;
            continue;
        }

        // Convert strings to enums
        Direction direct = stringToDirection(direct_str);
        DamageType weakness = stringToDamageType(weakness_str);
        DamageType strength = stringToDamageType(strength_str);

        enemies.emplace_back(name, health, speed, x, y, direct, damage, weakness, strength);
    }
    
    return enemies;
}

std::vector<Enemy> Logic::getEnemies(){
	return enemies;
}