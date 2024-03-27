#include <vector>
#include "tower.h"
#include "tower_gui.h"

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
    //TODO MAKE TOWER COSTS AND FIRE RATE CONSTANTS + CHANGE THEM 
    if (type == "Barracks") {
        return new Barracks("Barracks", 100, 100, 0, DamageType::NORMAL, location, 50);
    } else if (type == "Bomb") {
        return new BombTower("BombTower", 100, 100, 200, DamageType::BOMB, location, 10, 50);
    } else if (type == "Laser") {
        return new LaserTower("LaserTower", 100, 100, 300, DamageType::LASER, location, 10, 50);
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