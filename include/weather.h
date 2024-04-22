#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
#include <stdio.h>

class Weather {
    private:
        std::string name;
        float towerHpMod;
        float towerRangeMod;
        float enemyHpMod;
        float enemySpeedMod;

        //how many seconds between weather
        const double time_between_weather = 30;
        double time_til_next_weather;


        //set the weather to diffrent types
        void weatherSetNone();
        void weatherSetAcidRain();
        void weatherSetSandstorm();
        void weatherSetRadiation();
        void weatherSetEarthquake();
        void weatherSetWind();

    public:
        //constructor
        Weather();

        //randomly sets a weather
        void updateWeather(double elapsedTime);

        //getters for the diffrent modifiers
        float  getTowerHpMod() const { return towerHpMod; }
        float getTowerRangeMod() const { return towerRangeMod; };
        float getenemyHpMod() const { return enemyHpMod; };
        float getenemySpeedMod() const { return enemySpeedMod; };
        std::string getWeatherName() const { return name; };

};


#endif