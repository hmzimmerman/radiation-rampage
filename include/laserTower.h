#ifndef LASERTOWER_H
#define LASERTOWER_H

#include <iostream>
#include "tower.h"

class LaserTower : public Tower {
private:
    int fireRate;
    Enemy* target; // Pointer to the current target enemy

public:
    LaserTower(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int fireRate, int buildCost);

    void attack() override;

    // Update the tower's target based on enemy positions
    void updateTarget(const std::vector<Enemy>& enemies);
};

#endif