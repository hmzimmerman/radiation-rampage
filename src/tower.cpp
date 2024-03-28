#include <vector>
#include "tower.h"
#include "barracks.h"
#include "bombTower.h"
#include "laserTower.h"
#include "tower_gui.h"
#include "constants.h"

Tower::Tower(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost)
    : name(name), health(health), damage(damage), range(range), damageType(damageType), location(location), buildCost(buildCost) {}

Tower::~Tower() {}

Tower* Tower::createTower(const std::string& type, const TowerLocation& location) {
    using namespace tower;
    if (type == "Barracks") {
        return new Barracks("Barracks", tower::barracksHealth, tower::barracksDamage, tower::barracksRange, 
                            tower::barracksDamageType, location, tower::barracksBuildCost);
    } else if (type == "Bomb") {
        return new BombTower("BombTower", tower::bombHealth, tower::bombDamage, tower::bombRange, 
                            tower::bombDamageType, location, tower::bombBuildCost, tower::bombFireRate);
    } else if (type == "Laser") {
        return new LaserTower("LaserTower", tower::laserHealth, tower::laserDamage, tower::laserRange,
                            tower::laserDamageType, location, tower::laserBuildCost, tower::laserFireRate);
    }
    return nullptr;
}

void Tower::updateTarget(const std::vector<Enemy>& enemies) {}

bool Tower::isInRange(int x, int y) const {
    int towerX = location.x + location.size / 2;
    int towerY = location.y + location.size / 2;
    int distanceSquared = (x - towerX) * (x - towerX) + (y - towerY) * (y - towerY);
    int rangeSquared = range * range;
    return distanceSquared <= rangeSquared;
}

std::vector<TowerLocation> towerLocations = {
    TowerLocation(275, 71),
    TowerLocation(275, 405),
    TowerLocation(613, 405),
    TowerLocation(917, 254),
    TowerLocation(1067, 390),
};