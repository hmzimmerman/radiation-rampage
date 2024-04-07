#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
#include <stdio.h>

class Weather {
    private:
        float towerHpMod;
        float towerRangeMod;
        float enemyHpMod;
        float enemySpeedMod;

    public:
        //constructor
        Weather();

        //set the weather to diffrent types
        void weatherSetAcidRain();
        void weatherSetSandstorm();
        void weatherSetRadiation();
        void weatherSetEarthquake();
        void weatherSetWind();

        //getters for the diffrent modifiers
        float getTowerHpMod();
        float getTowerRangeMod();
        float getenemyHpMod();
        float getenemySpeedMod();

}




#endif