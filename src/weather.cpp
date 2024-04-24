#include <iostream>
#include <stdio.h>
#include <random>

#include "weather.h"

//constructor
Weather::Weather(){
    weatherSetNone();
    time_til_next_weather = time_between_weather;
}

void Weather::updateWeather(double elapsedTime){
    //subtract the elapsed time (in seconds)
    time_til_next_weather -= elapsedTime;
    if (time_til_next_weather < 1) {
        //return to default weather if weather not default
        if (name != "none") {
            weatherSetNone();
        }
        else {
            // Create a random number generator engine
            std::random_device rd;  // Obtain a random number from hardware
            std::mt19937 gen(rd()); // Seed the generator
            std::uniform_int_distribution<int> distrib(1, 6); //add a number between 1 and 8

            int randomNumber = distrib(gen); // generate the number
            switch (randomNumber) {
                case 1:
                    weatherSetAcidRain();
                    break;
                case 2:
                    weatherSetSandstorm();
                    break;
                case 3:
                    weatherSetRadiation();
                    break;
                case 4:
                    weatherSetEarthquake();
                    break;
                case 5:
                    weatherSetWindEast();
                    break;
                case 6:
                    weatherSetWindWest();
                    break;
            }
        }

        //reset clock
        time_til_next_weather = time_between_weather;
    }
}

void Weather::weatherSetNone(){
    name = "none";
    towerHpMod = 1;
    towerRangeMod = 1;
    enemyHpMod = 1;
    enemySpeedMod = 0;
}

void Weather::weatherSetAcidRain(){
    name = "Acid Rain";
    towerHpMod = 2;
    towerRangeMod = 1;
    enemyHpMod = 1;
    enemySpeedMod = 0;
}

void Weather::weatherSetSandstorm(){
    name = "Sandstorm";
    towerHpMod = 1;
    towerRangeMod = 2;
    enemyHpMod = 1;
    enemySpeedMod = 0;
}

void Weather::weatherSetRadiation(){
    name = "Radiation";
    towerHpMod = 1;
    towerRangeMod = 1;
    enemyHpMod = 2;
    enemySpeedMod = 0;
}

void Weather::weatherSetEarthquake(){
    name = "Earthquake";
    towerHpMod = 3;
    towerRangeMod = 1;
    enemyHpMod = 1;
    enemySpeedMod = -2;
}

void Weather::weatherSetWindEast(){
    name = "Wind";
    towerHpMod = 1;
    towerRangeMod = 1;
    enemyHpMod = 1;
    enemySpeedMod = 2;
}

void Weather::weatherSetWindWest(){
    name = "Wind";
    towerHpMod = 1;
    towerRangeMod = 1;
    enemyHpMod = 1;
    enemySpeedMod = -2;
}
