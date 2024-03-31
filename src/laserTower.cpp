#include "laserTower.h"

LaserTower::LaserTower(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost, double fireRate, View* view)
    : Tower(name, health, damage, range, damageType, location, buildCost), fireRate(fireRate), target(nullptr), view(view) {
}

void LaserTower::attack() {
    // Check if the tower is ready to attack
    if (target && target->isAlive()) {
        std::cout << "Laser Tower attacking enemy: " << target->getName() << std::endl;
        std::cout << "Damage: " << getDamage() << std::endl;
        target->takeDamage(getDamage());

        // Render laser beam
        const TowerLocation& towerLocation = getLocation();
        view->triggerLaserAttackAnimation(towerLocation.x, towerLocation.y, target->getX(), target->getY());

        timeSinceLastAttack = 0.0;
    }
}

void LaserTower::updateTarget(const std::vector<Enemy>& enemies) {
    // Find the first (furthest along the path) enemy in range
    for (const auto& enemy : enemies) {
        if (isInRange(enemy.getX(), enemy.getY()) && enemy.isAlive()) {
            target = const_cast<Enemy*>(&enemy);
            return;
        }
    }
    // If no enemy is found in range, set target to none
    target = nullptr;
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