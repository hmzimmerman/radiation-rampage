#include "bombtower.h"

BombTower::BombTower(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost, int fireRate)
    : Tower(name, health, damage, range, damageType, location, buildCost), fireRate(fireRate) {
}

void BombTower::attack() {
    // TODO
}