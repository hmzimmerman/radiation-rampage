#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <vector>
#include "damage_type.h"
#include "view.h"
#include "enemy.h"

class Tower;

struct TowerLocation {
    int x;
    int y;
    int size; // Size of the square plot
    bool occupied; // Indicate if a tower is already placed here
    std::string towerType;
    Tower* tower;

    TowerLocation(int x, int y) : x(x), y(y), size(80), occupied(false), tower(nullptr) {}

    // Equality operator overload
    bool operator==(const TowerLocation& other) const {
        return (x == other.x) && (y == other.y);
    }
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
        Enemy* target;

    public:
        // Constructor
        Tower(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost);

        // Destructor
        virtual ~Tower();

        virtual void attack() = 0;

        bool isInRange(int x, int y) const;

        virtual void updateTarget(std::vector<Enemy>& enemies);

        void upgrade();

        void repair();

        void sell();

        int repairCost();

        // Getters
        const std::string& getName() const { return name; }
        virtual int getDamage() const { return damage; }
        int getRange() const { return range; }
        const TowerLocation& getLocation() const { return location; }
        int getBuildCost() const { return buildCost; }

        virtual int getUpgradeCost() const = 0 ;

        int getRepairCost() const ;
        int getSellEarnings() const ;


        // Setters
        void setHealth(int h) { health = h; }
        void setBuildCost(int newBuildCost) { buildCost = newBuildCost;}

        static Tower* createTower(const std::string& type, const TowerLocation& location, View* view = nullptr);
};

#endif