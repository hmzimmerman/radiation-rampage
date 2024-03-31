#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include "enemy.h"

#include <iostream>
#include <stdio.h>
#include <vector>

class WaveManager {
    private:
        //list of enemies actively on the battlefield
        std::vector<Enemy> active_enemies;
        
        //list of list of enemies in each wave
        std::vector<std::vector<Enemy>> enemy_waves;

        //list of every enemy type
        std::vector<Enemy> enemies;

        //how many miliseconds between waves
        const int time_between_waves = 60000;
        int time_til_next_wave;

        // Assist in parsing text to enums
		Direction stringToDirection(const std::string& str);
		DamageType stringToDamageType(const std::string& str);

    public:
        //constructor, create the first 10 waves and add them to the enemy waves, and set time bwtween waves
        WaveManager();

        //gives list of enemies on the field
        std::vector<Enemy> getActiveEnemies();

        //update called in logic
        //moves time until next wave down and sends enemy out if it hits 0
        void update();

        //algorithm for generating waves past wave 10
        void waveAlgorithm();

        // Create vector of all enemy types
		std::vector<Enemy> createEnemies();




};


#endif