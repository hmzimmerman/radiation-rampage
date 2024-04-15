#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <vector>
#include <memory>

#include "view.h"
#include "towerLocation.h"
#include "damage_type.h"
#include "enemy.h"

struct TowerLocation;
extern std::vector<TowerLocation> towerLocations;

class Tower {
    private:
        std::string name;
        int health;
        int damage;
        int range;
        DamageType damageType;
        const TowerLocation& location;
        int buildCost;
        Enemy* target;

    public:
        // Constructor
        Tower(const std::string& name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost);

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

        static std::shared_ptr<Tower> createTower(const std::string& type, const TowerLocation& location, View* view);
};

#endif