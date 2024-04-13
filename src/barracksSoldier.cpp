#include "barracksSoldier.h"
#include "constants.h"

Soldier::Soldier(int health, int x, int y)
    : health(health), x(x), y(y) {}

Soldier::~Soldier() {
    // Destructor implementation
}

void Soldier::attack(Enemy& enemy) {
    using namespace tower;
    enemy.takeDamage(barracksDamage);
}

void Soldier::takeDamage(int damage) {
    health -= damage;
}

bool Soldier::isAlive() const {
    return health > 0;
}

void Soldier::setTimeSinceDeath(double time) {
    timeSinceDeath = time;
}

void Soldier::respawn() {
    timeSinceDeath = 0.0;
    health = 5;
}