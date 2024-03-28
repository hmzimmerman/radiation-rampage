#include "laserTower.h"

LaserTower::LaserTower(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int fireRate, int buildCost)
    : Tower(name, health, damage, range, damageType, location, buildCost), fireRate(fireRate), target(nullptr) {
}

void LaserTower::attack() {
    if (target) {
        std::cout << "Laser Tower attacking enemy: " << target->getName() << std::endl;

        // TODO: Implement laser attack

        // Reset target after attacking
        target = nullptr;
    }
}

void LaserTower::updateTarget(const std::vector<Enemy>& enemies) {
    if (target) {
        // Check if the target is still in range and alive
        if (isInRange(target->getX(), target->getY()) && target->isAlive()) {
            return; // Keep the current target
        } else {
            target = nullptr; // Reset target if it's no longer in range or alive
        }
    }

    // Find the first (furthest along the path) enemy in range
    for (const auto& enemy : enemies) {
        if (isInRange(enemy.getX(), enemy.getY()) && enemy.isAlive()) {
            target = const_cast<Enemy*>(&enemy);
            return;
        }
    }
}