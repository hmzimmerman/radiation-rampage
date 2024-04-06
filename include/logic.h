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
        bool game_over; // Tells view if the game is over
        bool paused;	// Tells other views if the game is paused

        WaveManager *wave_manager;
		std::vector<Enemy> enemies;

    public:
        // Constructor, create the wave manager and set game_over and paused to false
        Logic();

        int getScore();
        int getHealth();

        // Set if game is paused
        void setPaused();
        void setUnpaused();
        
        void takeDamage(int d);
        
        // Get if game is paused
        bool isPaused();

        // Return vector of enemies currently on the filed
        std::vector<Enemy> getEnemiesOnField();

        // Update method
        void update(double inTime);

        // Reset the game for new session
        void reset();

		// Create vector of all enemy types
		std::vector<Enemy> createEnemies();
		
		// Assist in parsing text to enums
		Direction stringToDirection(const std::string& str);
		DamageType stringToDamageType(const std::string& str);
		
		// Get method for enemies
		std::vector<Enemy> getEnemies();
};

#endif