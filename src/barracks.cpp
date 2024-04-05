#include "barracks.h"

Barracks::Barracks(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost, View* view)
    : Tower(name, health, damage, range, damageType, location, buildCost), view(view), soldierLocations({
        {115, 109},
        {115, 441},
        {735, 441},
        {900, 155},
        {1060, 290}
    }) {}

void Barracks::attack() {
    // Check if the tower has a target and the target is alive
    if (target && target->isAlive()) {
        std::cout << "Halting enemy: " << target->getName() << std::endl;

        // Reset the target after attacking?
        //target = nullptr;
    }
    view->renderSoldiers();
}

void Barracks::updateTarget(std::vector<Enemy>& enemies) {
    // Find the first enemy near a soldier
    for (const auto& enemy : enemies) {
        if (isEnemyNearSoldier(enemy)) {
            target = const_cast<Enemy*>(&enemy);
            return;
        }
    }
    // If no enemy is found near a soldier, set target to none
    target = nullptr;
}

bool Barracks::isEnemyNearSoldier(const Enemy& enemy) {
    for (const auto& soldierLocation : soldierLocations) {
        // Check if the enemy is within 20 pixels north or west of the soldiers
        // TODO: Double check area bounds
        if ((enemy.getX() >= soldierLocation.first - 30) && 
            (enemy.getX() <= soldierLocation.first + 80) && 
            (enemy.getY() >= soldierLocation.second - 30) && 
            (enemy.getY() <= soldierLocation.second + 80)) {
            return true;
        }
    }
    return false;
}

const std::vector<std::pair<int, int>>& Barracks::getSoldierLocations() const {
    return soldierLocations;
}