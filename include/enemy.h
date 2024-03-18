#ifndef ENEMY_H
#define ENEMY_H

#include <string>

enum class damageType {
    NORMAL,
    ARCHER,
    BOMB
};

class enemy {
private:
    std::string name;
    int health;
    int speed;
    int x;
    int y;
    int damage; 
    damageType weakness;
    damageType strength;

public:
    enemy(std::string name, int health, int speed, DamageType weakness, DamageType strength);

    // Enemy takes damage
    void takeDamage(int damage);
    
    // Checks if health is more than 0
    bool isAlive() const;
    
    // Getters
    std::string getName() const;
    int getHealth() const;
    int getSpeed() const;
    int getX() const;
    int getY() const;
    int getDamage() const;
    damageType getWeakness() const;
    damageType getStrength() const;

    // Setters
    void setName(std::string n) { name = n; }
    void setHealth(int h) { health = h; }
    void setSpeed(int s) { speed = s; }
    void setX(int x1) { x = x1; }
    void setY(int y1) { y = y1; }
    void setDamage(int d) { damage = d; }
    void setWeakness(damageType w) { weakness = w; }
    void setStrength(damageType s) { strength = s; }
};

#endif // ENEMY_H
