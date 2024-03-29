#include "barracks.h"

Barracks::Barracks(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost)
    : Tower(name, health, damage, range, damageType, location, buildCost) {
}

void Barracks::attack() {
    // TODO
}