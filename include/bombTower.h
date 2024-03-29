#ifndef BOMB_TOWER_H
#define BOMB_TOWER_H

#include "tower.h"

class BombTower : public Tower {
private:
    int fireRate;

public:
    BombTower(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost, int fireRate);

    void attack() override;
};

#endif