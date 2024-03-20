#ifndef ENEMY_H
#define ENEMY_H

#include <string>

enum class DamageType {
    NORMAL,
    LASER,
    BOMB
};

enum class Direction {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

class Enemy {
private:
    std::string name;
    int health;
    int speed;
    int x;
    int y;
    Direction dir;
    int damage; 
    DamageType weakness;
    DamageType strength;

public:
	// Constructor
    Enemy(std::string name, int health, int speed, int x, int y, Direction direct, int damage, DamageType weakness, DamageType strength);
    
    // Deconstructor
    ~Enemy();

    // Enemy takes damage
    void takeDamage(int damage);
    
    // Checks if health is more than 0
    bool isAlive() const;
    
    // Moves the enemy
    void move();
    
    // Getters
    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getSpeed() const { return speed; }
    int getX() const { return x; }
    int getY() const { return y; }
    Direction getDirection() const { return dir; }
    int getDamage() const { return damage; }
    DamageType getWeakness() const { return weakness; }
    DamageType getStrength() const { return strength; }

    // Setters
    void setName(std::string n) { name = n; }
    void setHealth(int h) { health = h; }
    void setSpeed(int s) { speed = s; }
    void setX(int x1) { x = x1; }
    void setY(int y1) { y = y1; }
    void setDirection(Direction d) { dir = d; }
    void setDamage(int d) { damage = d; }
    void setWeakness(DamageType w) { weakness = w; }
    void setStrength(DamageType s) { strength = s; }
};

#endif