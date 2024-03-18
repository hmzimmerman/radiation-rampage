#ifndef LOGIC_H
#define LOGIC_H

#include "waveManager.h"
#include "enemy.h"

#include <iostream>
#include <stdio.h>
#include <vector>
#include <vector>

class Logic {
    private:
        int score;
        bool lost;//tells view if the game is over
        double time;
        bool game_over; //tells view if the game is over
        bool paused;//tells other views if the game is paused

        WaveManager wave_manger;

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

}


#endif