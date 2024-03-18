#include "enemy.h"  

Enemy::Enemy(std::string n, int h, int s, int x1, int y1, int d, DamageType w, DamageType st)
    : name(n), health(h), speed(s), x(x1), y(y1), damage(d), weakness(w), strength(st) {}
    
Enemy::~Enemy() {
    // Destructor implementation
}

void Enemy::takeDamage(int d){
	health -= d;
}

bool Enemy::isAlive() const{
	return health > 0;
}