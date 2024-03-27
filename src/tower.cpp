#include <vector>
#include "tower.h"
#include "tower_gui.h"
#include "constant.h"

Tower::Tower(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost)
    : name(name), health(health), damage(damage), range(range), damageType(damageType), location(location), buildCost(buildCost) {}

Tower::~Tower() {}

LaserTower::LaserTower(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int fireRate, int buildCost)
    : Tower(name, health, damage, range, damageType, location, buildCost), fireRate(fireRate) {
}

void LaserTower::attack() {
    // TODO
}

BombTower::BombTower(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int fireRate, int buildCost)
    : Tower(name, health, damage, range, damageType, location, buildCost), fireRate(fireRate) {
}

void BombTower::attack() {
    // TODO
}

Barracks::Barracks(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost)
    : Tower(name, health, damage, range, damageType, location, buildCost) {
}

void Barracks::attack() {
    // TODO
}

Tower* Tower::createTower(const std::string& type, const TowerLocation& location) {
    using namespace tower;
    if (type == "Barracks") {
        return new Barracks("Barracks", tower::barracksHealth, tower::barracksDamage, 
                            tower::barracksRange, tower::barracksAreaOfEffect, 
                            tower::barracksDamageType, location, tower::barracksBuildCost);
    } else if (type == "Bomb") {
        return new BombTower("BombTower", tower::bombHealth, tower::bombDamage, tower::bombRange, 
                            tower::bombAreaOfEffect, tower::bombDamageType, location, 
                            tower::bombBuildCost, tower::bombFireRate);
    } else if (type == "Laser") {
        return new LaserTower("LaserTower", tower::laserHealth, tower::laserDamage, 
                            tower::laserRange, tower::laserAreaOfEffect, tower::laserDamageType, location, 
                            tower::laserBuildCost, tower::laserFireRate);
    }
    return nullptr;
}

std::vector<TowerLocation> towerLocations = {
    TowerLocation(275, 71),
    TowerLocation(275, 405),
    TowerLocation(613, 405),
    TowerLocation(917, 254),
    TowerLocation(1067, 390),
};