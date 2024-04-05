#ifndef BARRACKS_H
#define BARRACKS_H

#include "tower.h"
#include "view.h"

class Barracks : public Tower {
    private:
    std::vector<std::pair<int, int>> soldierLocations;
    //std::vector<std::pair<int, int>> enemyStoppingLocations;

    Enemy* target;
    View* view;

public:
    Barracks(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost, View* view);

    void attack() override;

    void updateTarget(std::vector<Enemy>& enemies) override;

    bool isEnemyNearSoldier(const Enemy& enemy);

    // Getters
    const std::vector<std::pair<int, int>>& getSoldierLocations() const;
};

#endif