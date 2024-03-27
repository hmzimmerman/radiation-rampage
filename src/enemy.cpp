#include "enemy.h" 
#include "constants.h" 
#include <iostream>
#include <algorithm>


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
	
	
	pathCornerCollision();

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

void Enemy::pathCornerCollision(){
	using namespace enemy;

	if (inPathCornerRange(enemy::corner1X1, enemy::corner1Y1, enemy::corner1X2, enemy::corner1Y2)){
		//check if enemy is above the diagonal line segment
		if (y > ((enemy::corner1Slope*x) + enemy::corner1YIntercept)){
			dir = Direction::EAST;
		}
	}else if (inPathCornerRange(enemy::corner2X1, enemy::corner2Y1, enemy::corner2X2, enemy::corner2Y2)){
		// float slope = ((float)enemy::corner2Y2 - enemy::corner2Y1)/((float)enemy::corner2X2 - enemy::corner2X1);
		// float yIntercept = -(slope*(enemy::corner2X2)) + enemy::corner2Y2;
		// std::cout << "slope " << slope << " ," << yIntercept << std::endl;
		if (y < ((enemy::corner2Slope *x) + enemy::corner2YIntercept)){
			dir = Direction::NORTH;
		}
	}else if (inPathCornerRange(enemy::corner3X1, enemy::corner3Y1, enemy::corner3X2, enemy::corner3Y2)){
		// float slope = ((float)enemy::corner3Y2 - enemy::corner3Y1)/((float)enemy::corner3X2 - enemy::corner3X1);
		// float yIntercept = -(slope*(enemy::corner3X2)) + enemy::corner3Y2;
		// std::cout << "slope " << slope << " ," << yIntercept << std::endl;
		if (y < ((enemy::corner3Slope *x) + enemy::corner3YIntercept)){
			dir = Direction::EAST;
		}
	}else if (inPathCornerRange(enemy::corner4X1, enemy::corner4Y1, enemy::corner4X2, enemy::corner4Y2)){
		if (y > ((enemy::corner4Slope *x) + enemy::corner4YIntercept)){
			dir = Direction::SOUTH;
		}
	}else if (inPathCornerRange(enemy::corner5X1, enemy::corner5Y1, enemy::corner5X2, enemy::corner5Y2)){
		if (y > ((enemy::corner5Slope *x) + enemy::corner5YIntercept)){
			dir = Direction::EAST;
		}
	}

}

bool Enemy::inPathCornerRange(int cornerX1, int cornerY1, int cornerX2, int cornerY2){
	if (((x > std::min(cornerX1, cornerX2)) && (x < std::max(cornerX1, cornerX2))) 
		&&  ((y > std::min(cornerY1, cornerY2)) && (y < std::max(cornerY1, cornerY2)))){
		return true;
	}
	return false;
}