#include "barracks.h"

Barracks::Barracks(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost, View* view)
    : Tower(name, health, damage, range, damageType, location, buildCost), view(view), target(nullptr), soldierLocations({
        {115, 109},
        {115, 441},
        {595, 544},
        {900, 155},
        {1060, 290}
    }) {
    // Initialize soldiers
    for (const auto& location : soldierLocations) {
        soldiers.emplace_back(5, location.first, location.second, this->getDamage());
    }
}

void Barracks::attack() {
    // Check if the tower has a target and the target is alive
    if (target && target->isAlive()) {

        for (auto& soldier : soldiers) {
            if (soldier.isAlive()) {
                target->haltMovement();
                soldier.attack(*target);
                soldier.takeDamage(target->getDamage());
            }
        }
    }
    view->renderSoldiers();
}

void Barracks::updateTarget(std::vector<Enemy>& enemies) {
    // Find the first enemy near a soldier
    for (auto& enemy : enemies) {
        if (isEnemyNearSoldier(enemy)) {
            target = &enemy;
            return;
        }
    }
    // If no enemy is found near a soldier, set target to none
    target = nullptr;
}

bool Barracks::isEnemyNearSoldier(const Enemy& enemy) {
    // Get the soldier location associated with a barracks tower
    std::pair<int, int> soldierLocation = getTowerSoldierMapping();

    // Check if the enemy is North or East of the soldier
    if ((enemy.getX() >= soldierLocation.first - 30) &&
        (enemy.getX() <= soldierLocation.first + 80) &&
        (enemy.getY() >= soldierLocation.second - 30) &&
        (enemy.getY() <= soldierLocation.second + 80)) {
        return true;
    }
    return false;
}

bool Barracks::isReadyToAttack(double elapsedTime) {
    timeSinceLastAttack += elapsedTime;

    if (timeSinceLastAttack >= 1.5) { // Attack once every 1.5 seconds
        timeSinceLastAttack = 0.0;
        return true;
    }
    return false;
}

const std::vector<std::pair<int, int>>& Barracks::getSoldierLocations() const {
    return soldierLocations;
}

std::pair<int, int> Barracks::getTowerSoldierMapping() const {
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
        if (index < static_cast<int>(soldierLocations.size())) {
            return soldierLocations[index];
        }
    }
    return std::make_pair(-1, -1);
}

// Respawn soldier after 8 seconds of death
void Barracks::handleSoldierRespawnTiming(double elapsedTime) {
    for (auto& soldier : soldiers) {
        if (soldier.getHealth() <= 0) {
            double timeSinceDeath = soldier.getTimeSinceDeath();
            timeSinceDeath += elapsedTime;
            soldier.setTimeSinceDeath(timeSinceDeath);
            if (timeSinceDeath >= 8.0) {
                soldier.respawn();
            }
        } else {
            soldier.setTimeSinceDeath(0.0);
        }
    }
}

void Barracks::update(double elapsedTime) {
    handleSoldierRespawnTiming(elapsedTime);
}

int Barracks::getUpgradeCost() const{
    using namespace tower;
    return tower::barracksUpgradeCost;
}