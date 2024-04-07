#ifndef SOLDIER_H
#define SOLDIER_H

#include <string>
#include "enemy.h"

class Soldier {
private:
    int health;
    int x;
    int y;
    int damage;

    double timeSinceDeath;

public:
    Soldier(int health, int x, int y, int damage);

    ~Soldier();

    void attack(Enemy& enemy);

    void takeDamage(int damage);

    bool isAlive() const;

    void respawn();

    // Getters
    int getHealth() const { return health; }

    double getTimeSinceDeath() { return timeSinceDeath; }

    // Setters
    void setTimeSinceDeath(double time);
};

#endif