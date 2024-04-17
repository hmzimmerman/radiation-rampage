#include "laserTower.h"

LaserTower::LaserTower(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost, double fireRate, View* view)
    : Tower(name, health, damage, range, damageType, location, buildCost), fireRate(fireRate), target(nullptr), view(view), timeSinceLastAttack(0.0) {
}

void LaserTower::attack() {
    // Check if the tower has a target and the target is alive
    if (target && target->isAlive()) {
        target->takeDamage(getDamage());

        // Render laser beam
        const TowerLocation& towerLocation = getLocation();
        int centerX = towerLocation.x + towerLocation.size / 2;
        int centerY = towerLocation.y + towerLocation.size / 2;
        view->triggerLaserAttackAnimation(centerX, centerY, target->getX(), target->getY());

        timeSinceLastAttack = 0.0;
    }
}

// Update target enemy to the first enemy within range
void LaserTower::updateTarget(std::vector<Enemy>& enemies) {
    // Find the enemy in range with the most distance traveled
    int maxDistance = -1;
    for (auto& enemy : enemies) {
        if (isInRange(enemy.getX(), enemy.getY()) && enemy.isAlive()) {
            int distance = enemy.getDistanceTraveled();
            if (distance > maxDistance) {
                target = &enemy;
                maxDistance = distance;
            }
        }
    }

    // If no enemy is found in range, set target to none
    if (maxDistance == -1) {
        target = nullptr;
    } else {
        return;
    }
}

bool LaserTower::isReadyToAttack(double elapsedTime) {
    // Increment the time since the last attack
    timeSinceLastAttack += elapsedTime;

    // Check if enough time has elapsed to perform another attack
    if (timeSinceLastAttack >= 1.0 / fireRate) {
        timeSinceLastAttack = 0.0;
        return true;
    }

    return false;
}

int LaserTower::getUpgradeCost() const {
    using namespace tower;
    return tower::laserUpgradeCost;
}

void LaserTower::upgrade() {
    setUpgraded(true);
}

void LaserTower::update(double elapsedTime) {
    if (isReadyToAttack(elapsedTime)) {
        attack();
    }
}