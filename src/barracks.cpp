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
    view->renderSoldiers();
}

const std::vector<std::pair<int, int>>& Barracks::getSoldierLocations() const {
    return soldierLocations;
}