#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <vector>
#include "damage_type.h"
#include "view.h"

class Tower;

struct TowerLocation {
    int x;
    int y;
    int size; // Size of the square plot
    bool occupied; // Indicate if a tower is already placed here
    std::string towerType;
    Tower* tower;

    TowerLocation(int x, int y) : x(x), y(y), size(80), occupied(false), tower(nullptr) {}
};

extern std::vector<TowerLocation> towerLocations;

class Tower {
    private:
        std::string name;
        int health;
        int damage;
        int range;
        DamageType damageType;
        TowerLocation location;
        int buildCost;

    public:
        // Constructor
        Tower(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost);

        // Destructor
        ~Tower();

        void attack(int damage);

        void upgrade();

        void repair();

        void sell();

        int repairCost();

        // Getters
        std::string getName() const { return name; }
        int getHealth() const { return health; }
        int getDamage() const { return damage; }
        int getRange() const { return range; }
        DamageType getDamageType() const { return damageType; }
        const TowerLocation& getLocation() const { return location; }

        // Setters
        void setHealth(int h) { health = h; }
        void setBuildCost(int newBuildCost) { buildCost = newBuildCost;}

        static Tower* createTower(const std::string& type, const TowerLocation& location);
};

class Barracks : public Tower {
    public:
        // Constructor
        Barracks(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location,int buildCost);

        // Methods
        void attack();
};

class BombTower : public Tower {
    private:
        int fireRate;

    public:
        // Constructor
        BombTower(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost, int fireRate);

        // Methods
        void attack();

        // Getters
        int getFireRate() const { return fireRate; }
};

class LaserTower : public Tower {
    private:
        int fireRate;

    public:
        // Constructor
        LaserTower(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location,int buildCost, int fireRate);

        // Methods
        void attack();

        // Getters
        int getFireRate() const { return fireRate; }
};

#endif