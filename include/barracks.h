#ifndef BARRACKS_H
#define BARRACKS_H

#include "tower.h"
#include "barracksSoldier.h"
#include "view.h"

class Barracks : public Tower {
    private:
    std::vector<std::pair<int, int>> soldierLocations;
    std::vector<Soldier> soldiers;
    Enemy* target;
    View* view;

    double timeSinceLastAttack;
    void handleSoldierRespawnTiming(double elapsedTime);

public:
    Barracks(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost, View* view);

    void update(double elapsedTime);

    void attack() override;

    void updateTarget(std::vector<Enemy>& enemies) override;

    bool isEnemyNearSoldier(const Enemy& enemy);

    bool isReadyToAttack(double elapsedTime);

    // Return a soldier location that corresponds to the tower location of a barracks tower instance
    std::pair<int, int> getTowerSoldierMapping(const std::vector<TowerLocation>& towerLocations) const;

    // Getters
    const std::vector<std::pair<int, int>>& getSoldierLocations() const;

    const std::vector<Soldier>& getSoldiers() const { return soldiers; }
};

#endif