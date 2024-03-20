#include "enemy.h"

#include <iostream>
#include <stdio.h>
#include <vector>

//constructor
WaveManager::WaveManager() {
    //setting timing
    time_til_next_wave = time_between_waves;

    //create first 10 waves of enemies
    std::vector<enemy> wave1;
        //wave1.push_back(human raider);
    std::vector<enemy> wave2;
    std::vector<enemy> wave3;
    std::vector<enemy> wave4;
    std::vector<enemy> wave5;
    std::vector<enemy> wave6;
    std::vector<enemy> wave7;
    std::vector<enemy> wave8;
    std::vector<enemy> wave9;
    std::vector<enemy> wave10;

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

std::vector<Enemy> WaveManager::getActiveEnemies() {
    return active_enemies;
}

void WaveManager::update() {
    //right now this is working on a per tick level, ideally we would want it to work in seconds (or we could just crank up the time
    //between rounds)
    //I am going to leave this for now but hopefully I will remember to bring this up at our 
    //next meeting
    time_til_next_wave -= 1
    if (time_between_waves < 1) {

        // Pop the last element from enemy waves
        std::vector<Enemy> wave_to_add = enemy_waves.back();
        enemy_waves.pop_back();

        //add the popped waves to active enemies
        // Iterate through wave_to_add and add elements to active_enemies with some delay
        for (const auto& elem : wave_to_add) {
            active_enemies.push_back(elem);
            
            // TODO Add a delay of 1 second between each addition
            //not sure how to do this
        }
        //reset clock
        time_til_next_wave = time_bewteen_waves;
    }

}