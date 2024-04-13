#ifndef LASERTOWER_H
#define LASERTOWER_H

#include <iostream>
#include "tower.h"
#include "view.h"
#include "constants.h"

class LaserTower : public Tower {
private:
    double fireRate;
    double timeSinceLastAttack;
    Enemy* target; // Current target enemy
    View* view;

public:
    LaserTower(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost, double fireRate, View* view);

    void update(double elapsedTime);

    void attack() override;

    bool isReadyToAttack(double elapsedTime);

    // Update the tower's target based on enemy positions
    void updateTarget(std::vector<Enemy>& enemies) override;

    int getUpgradeCost() const override;

    // Getters
    int getDamage() const override { return tower::laserDamage; }
    double getFireRate() const { return fireRate; }
};

#endif