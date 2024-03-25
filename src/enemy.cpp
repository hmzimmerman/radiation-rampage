#include "enemy.h" 
#include "constants.h" 

using namespace enemy;

Enemy::Enemy(std::string n, int h, int s, int x1, int y1, Direction direct, int d, DamageType w, DamageType st)
    : name(n), health(h), speed(s), x(x1), y(y1), dir(direct), damage(d), weakness(w), strength(st) {}
    
Enemy::~Enemy() {
    // Destructor implementation
}

void Enemy::takeDamage(int d){
	health -= d;
}

bool Enemy::isAlive() const{
	return health > 0;
}

void Enemy::move(){
	// changing enemy direction if its in a path corner
	if (x == enemy::corner1X && y == enemy::corner1Y){
		dir = Direction::EAST;
	}else if(x == enemy::corner2X && y == enemy::corner2Y){
		dir = Direction::NORTH;
	}else if(x == enemy::corner3X && y == enemy::corner3Y){
		dir = Direction::EAST;
	}else if(x == enemy::corner4X && y == enemy::corner4Y){
		dir = Direction::SOUTH;
	}else if(x == enemy::corner5X && y == enemy::corner5Y){
		dir = Direction::EAST;
	}

	// updating enemy location based on direction
	if(dir == Direction::EAST){
		x += speed;
	}else if(dir == Direction::WEST){
		x -= speed;
	}else if(dir == Direction::NORTH){
		y -= speed;
	}else if(dir == Direction::SOUTH){
		y += speed;
	}
}