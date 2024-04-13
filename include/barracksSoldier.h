#ifndef SOLDIER_H
#define SOLDIER_H

#include <string>
#include "enemy.h"

class Soldier {
private:
    int health;
    int x;
    int y;

    double timeSinceDeath;

public:
    Soldier(int health, int x, int y);

    ~Soldier();

    void attack(Enemy& enemy);

    void takeDamage(int damage);

    bool isAlive() const;

    void respawn();

    // Getters
    int getHealth() const { return health; }

    int getX() const { return x; }

    int getY() const { return y; }

    double getTimeSinceDeath() { return timeSinceDeath; }

    // Setters
    void setTimeSinceDeath(double time);
};

#endif