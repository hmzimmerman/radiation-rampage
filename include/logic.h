#ifndef LOGIC_H
#define LOGIC_H

#include "waveManager.h"
#include "enemy.h"
#include "moneyManager.h"


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
        MoneyManager *moneyManager;


    public:
        // Constructor, create the wave manager and set game_over and paused to false
        Logic();

        int getScore();
        int getHealth();
        int getMoney();

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
		
		// Get method for enemies
		std::vector<Enemy> getEnemies();
		
		// Get method for Wave Manager
		WaveManager* getManager() const { return wave_manager; }

        // Update money manager based on tower action. Returns true if transaction went through, false if it didn't
        bool updateMoneyTowerAction(const std::string& action, int coinAmount);

};

#endif