#include <iostream>
#include <fstream>
#include <sstream>
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
    enemies = createEnemies();

    // Uncomment for testing
    enemies.push_back(Enemy("Human Raider", 35, 2, 172, 0, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
    enemies.push_back(Enemy("Human Raider", 35, 2, 172, -50, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
    enemies.push_back(Enemy("Human Raider", 35, 2, 172, -100, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
    enemies.push_back(Enemy("Human Raider", 35, 2, 172, -150, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
    enemies.push_back(Enemy("Human Raider", 35, 2, 172, -200, Direction::SOUTH, 10, DamageType::NORMAL, DamageType::LASER));
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
    //return wave_manager->getActiveEnemies();
    // Uncomment for testing
    return enemies;
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

void Logic::update(double elapsedTime){
    for (int i = 0; i < enemies.size(); i ++) {
        enemies[i].move();

        // Check if enemy is dead and remove from list
        if (!enemies[i].isAlive()) {
            enemies.erase(enemies.begin() + i);
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
                tower->updateTarget(enemies);
                
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