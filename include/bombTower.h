#ifndef BOMB_TOWER_H
#define BOMB_TOWER_H

#include "tower.h"
#include "constants.h"

class BombTower : public Tower {
private:

public:
    BombTower(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost, int fireRate);

    void attack() override;

    void upgrade() override;

    int getUpgradeCost() const override;
};

#endif