#ifndef TOWER_H
#define TOWER_H

#include "damage_type.h"
#include "view.h"
#include <string>
#include <vector>

struct TowerLocation {
    int x;
    int y;
    int size; // Size of the square plot
    bool occupied; // Indicate if a tower is already placed here

    TowerLocation(int x, int y) : x(x), y(y), size(80), occupied(false) {}
};

extern std::vector<TowerLocation> towerLocations;

class Tower {
    private:
        std::string name;
        int health;
        int damage;
        int range;
        int areaOfEffect;
        DamageType damageType;
        int x; // X coordinate of tower
        int y; // Y coordinate of tower

    public:
        // Constructor
        Tower(std::string name, int health, int damage, int range, int areaOfEffect, DamageType damageType, int x, int y);

        // Destructor
        ~Tower();

        // Attack enemies
        void attack(int damage);

        // Repair the tower
        int repairCost();

        // Getters
        std::string getName() const { return name; }
        int getHealth() const { return health; }
        int getDamage() const { return damage; }
        int getRange() const { return range; }
        int getAreaOfEffect() const { return areaOfEffect; }
        DamageType getDamageType() const { return damageType; }
        int getX() const { return x; }
        int getY() const { return y; }

        // Setters
        void setHealth(int h) { health = h; }
        void setXCoord(int newX) { x = newX; }
        void setYCoord(int newY) { y = newY; }

        static Tower* createTower(const std::string& towerType, int x, int y);
};

class LaserTower : public Tower {
    private:
        int fireRate;

    public:
        // Constructor
        LaserTower(std::string name, int health, int damage, int range, int areaOfEffect, DamageType damageType, int x, int y, int fireRate);

        // Methods
        void attack();

        // Getters
        int getFireRate() const { return fireRate; }
};

class BombTower : public Tower {
    private:
        int fireRate;

    public:
        // Constructor
        BombTower(std::string name, int health, int damage, int range, int areaOfEffect, DamageType damageType, int x, int y, int rateOfFire);

        // Methods
        void attack();

        // Getters
        int getfireRate() const { return fireRate; }
};

class Barracks : public Tower {
    public:
        // Constructor
        Barracks(std::string name, int health, int damage, int range, int areaOfEffect, DamageType damageType, int x, int y);

        // Methods
        void attack();
};

#endif