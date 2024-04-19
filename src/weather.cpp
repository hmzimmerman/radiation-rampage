#include <iostream>
#include <stdio.h>

#include "weather.h"


Weather::Weather(){
    towerHpMod = 0;
    towerRangeMod = 0;
    enemyHpMod = 0;
    enemySpeedMod = 0;
}

void Weather::weatherSetAcidRain(){
    towerHpMod = 2;
    towerRangeMod = 0;
    enemyHpMod = 0;
    enemySpeedMod = 0;
}

void Weather::weatherSetSandstorm(){
    towerHpMod = 0;
    towerRangeMod = 2;
    enemyHpMod = 0;
    enemySpeedMod = 0;
}

void Weather::weatherSetRadiation(){
    towerHpMod = 0;
    towerRangeMod = 0;
    enemyHpMod = 2;
    enemySpeedMod = 0;
}

void Weather::weatherSetEarthquake(){
    towerHpMod = 3;
    towerRangeMod = 0;
    enemyHpMod = 0;
    enemySpeedMod = 2;
}

void Weather::weatherSetWind(){

}



float Weather::getTowerHpMod(){
    return towerHpMod;
}

float Weather::getTowerRangeMod(){
    return towerRangeMod;
}

float Weather::getenemyHpMod(){
    return enemyHpMod;
}

float Weather::getenemySpeedMod(){
    return enemySpeedMod;
}