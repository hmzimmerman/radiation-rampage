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

        //how many seconds between waves
        int time_between_waves;

    public:
        //constructor, create the first 10 waves and add them to the enemy waves, and set time bwtween waves
        WaveManager();

        //update called in logic
        //moves time until next wave down and sends enemy out if it hits 0
        void update();

        //algorithm for generating waves past wave 10
        void waveAlgorithm();




};


#endif