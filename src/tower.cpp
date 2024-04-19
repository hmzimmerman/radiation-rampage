#include <iostream>
#include <vector>
#include "tower.h"
#include "barracks.h"
#include "bombTower.h"
#include "laserTower.h"
#include "towerGUI.h"
#include "constants.h"

Tower::Tower(const std::string& name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost, double fireRate)
    : name(name), health(health), damage(damage), range(range), damageType(damageType), location(location), buildCost(buildCost), fireRate(fireRate), timeSinceLastSlowDegrade(0.0) {}

Tower::~Tower() {}

std::shared_ptr<Tower> Tower::createTower(const std::string& type, const TowerLocation& location, View* view) {
    using namespace tower;
    if (type == "Barracks") {
        return std::make_shared<Barracks>("Barracks", tower::barracksHealth, tower::barracksDamage, tower::barracksRange, 
                            tower::barracksDamageType, location, tower::barracksBuildCost, tower::barracksFireRate, view);
    } else if (type == "Bomb") {
        return std::make_shared<BombTower>("BombTower", tower::bombHealth, tower::bombDamage, tower::bombRange, 
                            tower::bombDamageType, location, tower::bombBuildCost, tower::bombFireRate);
    } else if (type == "Laser") {
        return std::make_shared<LaserTower>("LaserTower", tower::laserHealth, tower::laserDamage, tower::laserRange,
                            tower::laserDamageType, location, tower::laserBuildCost, tower::laserFireRate, view);
    }
    return nullptr;
}

void Tower::updateTarget(std::vector<Enemy>& enemies) {}

bool Tower::isInRange(int x, int y) const {
    int towerX = location.x + location.size / 2;
    int towerY = location.y + location.size / 2;
    int distanceSquared = (x - towerX) * (x - towerX) + (y - towerY) * (y - towerY);
    int rangeSquared = range * range;
    return distanceSquared <= rangeSquared;
}

void Tower::repair() {
    using namespace tower;
    if (name == "Barracks") {
        setHealth(tower::barracksHealth);
    } else if (name == "BombTower") {
        setHealth(tower::bombHealth);
    } else if (name == "LaserTower") {
        setHealth(tower::laserHealth);
    }
}

int Tower::getRepairCost() const{
    if (health == 0) {
        return buildCost;
    }

    float healthPercent = static_cast<float>(health) / 100.0f;
    if (healthPercent >= 0.5f && healthPercent < 1.0f) {
        // Tower health 50% - 90%
        return static_cast<int>(buildCost * 0.4f);
    } else if (healthPercent > 0.0f && healthPercent < 0.5f) {
        // Tower health 1% - 49%
        return static_cast<int>(buildCost * 0.6f);
    }
    // Tower health is already 100% no need to repair
    return 0;
}

int Tower::getSellEarnings() const{
    float healthPercent = health/100;
    if (healthPercent >= 0.50 && healthPercent <= 0.99){
        // tower health 50% - 90% 
        return buildCost * 0.6;
    }else if(healthPercent >= 0.01 && healthPercent <= 0.49){
        // tower health 1% - 49%
        return buildCost * 0.4;
    }

    // tower is in perfect condition. can sell for build amount 
    return buildCost;
}

bool Tower::isReadyToSlowDegrade(double elapsedTime){
    using namespace tower;
    timeSinceLastSlowDegrade += elapsedTime;
    if (timeSinceLastSlowDegrade < tower::secondsBetweenSlowDegrade){
        return false;
    }
    // Enough time has passed. Can slow degrade now
    timeSinceLastSlowDegrade = 0.0;
    return true;
}


void Tower::slowDegrade(){
    using namespace tower;

    // Tower health cannot be negative 
    if (health - tower::slowDegradeAmount >= 0){
        health-= tower::slowDegradeAmount;
    }
}