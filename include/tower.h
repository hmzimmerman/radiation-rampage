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

class Tower {
    private:
        std::string name;
        int health;
        int damage;
        int range;
        DamageType damageType;
        const TowerLocation& location;
        int buildCost;
        double fireRate;
        bool upgraded = false;
        Enemy* target;
        double timeSinceLastSlowDegrade;

    public:
        // Constructor
        Tower(const std::string& name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost, double fireRate);

        // Destructor
        virtual ~Tower();

        virtual void attack() = 0;

        bool isInRange(int x, int y) const;

        virtual void updateTarget(std::vector<Enemy>& enemies);

        virtual void upgrade() = 0;

        void repair();

        void sell();

        int repairCost();

        bool isReadyToSlowDegrade(double elapsedTime); // Checks if enough time has passed to slowly degrade tower

        void slowDegrade(); // Reduces tower health by slow degrade amount

        // Getters
        const std::string& getName() const { return name; }
        virtual int getDamage() const { return damage; }
        int getRange() const { return range; }
        const TowerLocation& getLocation() const { return location; }
        double getFireRate() const { return fireRate; }

        int getBuildCost() const { return buildCost; }
        virtual int getUpgradeCost() const = 0;
        bool isUpgraded() const { return upgraded; }
        int getRepairCost() const ;
        int getSellEarnings() const ;

        // Setters
        void setHealth(int newHealth) { health = newHealth; }
        void setDamage(int newDamage) { damage = newDamage; }
        void setRange(int newRange) { range = newRange; }
        void setFireRate(double newFireRate) { fireRate = newFireRate; }
        void setUpgraded(bool upgraded) { this->upgraded = upgraded; }
        void setBuildCost(int newBuildCost) { buildCost = newBuildCost;}

        static std::shared_ptr<Tower> createTower(const std::string& type, const TowerLocation& location, View* view);
};

#endif