#include <vector>
#include "tower.h"
#include "tower_gui.h"

Tower::Tower(std::string name, int health, int damage, int range, int areaOfEffect, DamageType damageType, int x, int y)
    : name(name), health(health), damage(damage), range(range), areaOfEffect(areaOfEffect), damageType(damageType), x(x), y(y) {}

Tower::~Tower() {}

LaserTower::LaserTower(std::string name, int health, int damage, int range, int areaOfEffect, DamageType damageType, int x, int y, int fireRate)
    : Tower(name, health, damage, range, areaOfEffect, damageType, x, y), fireRate(fireRate) {
}

void LaserTower::attack() {
    // TODO
}

BombTower::BombTower(std::string name, int health, int damage, int range, int areaOfEffect, DamageType damageType, int x, int y, int rateOfFire)
    : Tower(name, health, damage, range, areaOfEffect, damageType, x, y), fireRate(rateOfFire) {
}

void BombTower::attack() {
    // TODO
}

Barracks::Barracks(std::string name, int health, int damage, int range, int areaOfEffect, DamageType damageType, int x, int y)
    : Tower(name, health, damage, range, areaOfEffect, damageType, x, y) {
}

void Barracks::attack() {
    // TODO
}

Tower* Tower::createTower(const std::string& type, int x, int y) {
    if (type == "Barracks") {
        return new Barracks("Barracks", 100, 100, 0, 0, DamageType::NORMAL, x, y);
    } else if (type == "Bomb") {
        return new BombTower("BombTower", 100, 100, 100, 100, DamageType::BOMB, x, y, 1);
    } else if (type == "Laser") {
        return new LaserTower("LaserTower", 100, 100, 100, 0, DamageType::LASER, x, y, 1);
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