 #include "enemy.h"
#include "waveManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <SDL.h>

//constructor
WaveManager::WaveManager() {
    //setting timing
    time_til_next_wave = 1;

    //create list of enemies
    enemies = createEnemies();

    SDL_Init( SDL_INIT_TIMER );

    //create first 10 waves of enemies
    std::vector<Enemy> wave1;
        wave1.push_back(enemies[0]);
        wave1.push_back(enemies[0]);
        wave1.push_back(enemies[0]);
        wave1.push_back(enemies[0]);
        wave1.push_back(enemies[0]);
    std::vector<Enemy> wave2;
        wave2.push_back(enemies[0]);
        wave2.push_back(enemies[0]);
        wave2.push_back(enemies[1]);
        wave2.push_back(enemies[0]);
        wave2.push_back(enemies[0]);
        wave2.push_back(enemies[0]);
        wave2.push_back(enemies[1]);
    std::vector<Enemy> wave3;
        wave3.push_back(enemies[2]);
        wave3.push_back(enemies[2]);
        wave3.push_back(enemies[1]);
        wave3.push_back(enemies[2]);
        wave3.push_back(enemies[2]);
        wave3.push_back(enemies[2]);
        wave3.push_back(enemies[1]);
    std::vector<Enemy> wave4;
        wave4.push_back(enemies[4]);
        wave4.push_back(enemies[4]);
        wave4.push_back(enemies[1]);
        wave4.push_back(enemies[0]);
        wave4.push_back(enemies[0]);
        wave4.push_back(enemies[4]);
        wave4.push_back(enemies[5]);
    std::vector<Enemy> wave5;
        wave5.push_back(enemies[6]);
        wave5.push_back(enemies[6]);
        wave5.push_back(enemies[1]);
        wave5.push_back(enemies[6]);
        wave5.push_back(enemies[6]);
        wave5.push_back(enemies[6]);
        wave5.push_back(enemies[1]);
    std::vector<Enemy> wave6;
        wave6.push_back(enemies[3]);
        wave6.push_back(enemies[3]);
        wave6.push_back(enemies[3]);
        wave6.push_back(enemies[3]);
        wave6.push_back(enemies[3]);
        wave6.push_back(enemies[0]);
        wave6.push_back(enemies[0]);
        wave6.push_back(enemies[0]);
    std::vector<Enemy> wave7;
        wave7.push_back(enemies[1]);
        wave7.push_back(enemies[0]);
        wave7.push_back(enemies[0]);
        wave7.push_back(enemies[0]);
        wave7.push_back(enemies[0]);
        wave7.push_back(enemies[0]);
        wave7.push_back(enemies[0]);
        wave7.push_back(enemies[0]);
        wave7.push_back(enemies[0]);
        wave7.push_back(enemies[0]);
        wave7.push_back(enemies[0]);
    std::vector<Enemy> wave8;
        wave8.push_back(enemies[3]);
        wave8.push_back(enemies[3]);
        wave8.push_back(enemies[3]);
        wave8.push_back(enemies[3]);
        wave8.push_back(enemies[3]);
        wave8.push_back(enemies[7]);
        wave8.push_back(enemies[7]);
        wave8.push_back(enemies[7]);
        wave8.push_back(enemies[7]);
        wave8.push_back(enemies[7]);
    std::vector<Enemy> wave9;
        wave9.push_back(enemies[7]);
        wave9.push_back(enemies[1]);
        wave9.push_back(enemies[7]);
        wave9.push_back(enemies[7]);
        wave9.push_back(enemies[7]);
        wave9.push_back(enemies[1]);
        wave9.push_back(enemies[1]);
        wave9.push_back(enemies[7]);
        wave9.push_back(enemies[1]);
    std::vector<Enemy> wave10;
        wave10.push_back(enemies[5]);
        wave10.push_back(enemies[5]);
        wave10.push_back(enemies[5]);
        wave10.push_back(enemies[5]);
        wave10.push_back(enemies[5]);
        wave10.push_back(enemies[5]);
        wave10.push_back(enemies[5]);
        wave10.push_back(enemies[5]);
        wave10.push_back(enemies[5]);

    //push back waves in reverse order so they can easily be poped off
    enemy_waves.push_back(wave10);
    enemy_waves.push_back(wave9);
    enemy_waves.push_back(wave8);
    enemy_waves.push_back(wave7);
    enemy_waves.push_back(wave6);
    enemy_waves.push_back(wave5);
    enemy_waves.push_back(wave4);
    enemy_waves.push_back(wave3);
    enemy_waves.push_back(wave2);
    enemy_waves.push_back(wave1);
}

std::vector<Enemy>& WaveManager::getActiveEnemies() {
    return active_enemies;
}

Direction WaveManager::stringToDirection(const std::string& str) {
    if (str == "NORTH") return Direction::NORTH;
    if (str == "SOUTH") return Direction::SOUTH;
    if (str == "EAST") return Direction::EAST;
    if (str == "WEST") return Direction::WEST;

    return Direction::SOUTH; // Default value
}

DamageType WaveManager::stringToDamageType(const std::string& str) {
    if (str == "LASER") return DamageType::LASER;
    if (str == "BOMB") return DamageType::BOMB;
    if (str == "NORMAL") return DamageType::NORMAL;

    return DamageType::NORMAL; // Default value
}

std::vector<Enemy> WaveManager::createEnemies(){
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

// Callback function to be called by the timer
Uint32 WaveManager::TimerCallback(Uint32 interval, void* wave) {
    //case void* back to enemy
    WaveManager* manager = static_cast<WaveManager*>(wave);
    manager->active_enemies.push_back(manager->enemies_to_add.back());
    manager->enemies_to_add.pop_back();
    
    // Return 0 to stop the timer from repeating
    return 0;
}

void WaveManager::update() {
    //right now this is working on a per tick level, ideally we would want it to work in seconds (or we could just crank up the time
    //between rounds)
    //I am going to leave this for now but hopefully I will remember to bring this up at our 
    //next meeting
    time_til_next_wave -= 1;
    if (time_til_next_wave < 1) {
        // Pop the last element from enemy waves
        if (!enemy_waves.empty()) {
        enemies_to_add = enemy_waves.back();
        enemy_waves.pop_back();

        //add the popped waves to active enemies
        // Iterate through wave_to_add and add elements to active_enemies with some delay
        Uint32 delay = 1000;
        for (Enemy& elem : enemies_to_add) {
            // Set the timer to trigger after 1000 milliseconds (1 seconds) per enemeny
            SDL_AddTimer(delay, TimerCallback, this);
            delay += 1000;
            
        }
        }
        //reset clock
        time_til_next_wave = time_between_waves;
    }

}