#include "barracks.h"

Barracks::Barracks(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost, View* view)
    : Tower(name, health, damage, range, damageType, location, buildCost), view(view), soldierLocations({
        {115, 109},
        {115, 441},
        {595, 544},
        {900, 155},
        {1060, 290}
    }) {}

void Barracks::attack() {
    // Check if the tower has a target and the target is alive
    if (target && target->isAlive()) {
        //std::cout << "Halting enemy: " << target->getName() << std::endl;
        target->haltMovement();
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

bool Barracks::isEnemyNearSoldier(const Enemy& enemy)  {
    // Get the soldier location associated with a barracks tower
    std::pair<int, int> soldierLocation = getTowerSoldierMapping(towerLocations);

    // Check if the enemy is within a certain range of the soldier
    if ((enemy.getX() >= soldierLocation.first - 30) &&
        (enemy.getX() <= soldierLocation.first + 80) &&
        (enemy.getY() >= soldierLocation.second - 30) &&
        (enemy.getY() <= soldierLocation.second + 80)) {
        return true;
    }
    return false;
}

const std::vector<std::pair<int, int>>& Barracks::getSoldierLocations() const {
    return soldierLocations;
}

std::pair<int, int> Barracks::getTowerSoldierMapping(const std::vector<TowerLocation>& towerLocations) const {
    const TowerLocation& thisTowerLocation = this->getLocation(); 

    // Find the index of this barracks tower location
    int index = -1;
    for (size_t i = 0; i < towerLocations.size(); ++i) {
        if (towerLocations[i] == thisTowerLocation) {
            index = static_cast<int>(i);
            break;
        }
    }

    // Return the corresponding soldier location
    if (index != -1) {
        const std::vector<std::pair<int, int>>& soldierLocations = getSoldierLocations();
        if (index < static_cast<int>(soldierLocations.size())) {
            return soldierLocations[index];
        }
    }
    return std::make_pair(-1, -1);
}