#include "barracksSoldier.h"

Soldier::Soldier(int health, int x, int y, int damage)
    : health(health), x(x), y(y), damage(damage) {}

Soldier::~Soldier() {
    // Destructor implementation
}

void Soldier::attack(Enemy& enemy) {
    enemy.takeDamage(damage);
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