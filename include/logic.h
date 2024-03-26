#ifndef LOGIC_H
#define LOGIC_H

#include "waveManager.h"
#include "enemy.h"

#include <iostream>
#include <stdio.h>
#include <vector>

class Logic {
    private:
        int score;
        int health;
        double time;
        bool game_over; //tells view if the game is over
        bool paused;	//tells other views if the game is paused

        WaveManager *wave_manager;
		std::vector<Enemy> enemies;

    public:
        //constructor, create the wave manager and set game_over and paused to false
        Logic();

        int getScore();

        //set if game is paused
        void setPaused();
        void setUnpaused();
        
        //get if game is paused
        bool isPaused();

        //returns vector of enemies currently on the filed
        std::vector<Enemy> getEnemiesOnField();

        //update method
        void update(double inTime);

        //reset the game for new session
        void reset();

		//create a vector of all enemy types
		std::vector<Enemy> createEnemies();
		
		//assist in parsing text to enums
		Direction stringToDirection(const std::string& str);
		DamageType stringToDamageType(const std::string& str);
};

#endif