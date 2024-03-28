#ifndef BARRACKS_H
#define BARRACKS_H

#include "tower.h"

class Barracks : public Tower {
public:
    Barracks(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost);

    void attack() override;
};

#endif