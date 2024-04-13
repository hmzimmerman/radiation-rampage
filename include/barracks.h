#ifndef BARRACKS_H
#define BARRACKS_H

#include "tower.h"
#include "barracksSoldier.h"
#include "view.h"

class Barracks : public Tower {
    private:
    const std::vector<std::pair<int, int>> soldierLocations;
    static std::vector<Soldier> allSoldiers;
    
    Enemy* target;
    View* view;

    double elapsedTime;
    double timeSinceLastAttack;
    void handleSoldierRespawnTiming(double elapsedTime);

public:
    Barracks(std::string name, int health, int damage, int range, DamageType damageType, const TowerLocation& location, int buildCost, View* view);

    void update(double elapsedTime);

    void attack() override;

    double calculateDistance(int x1, int y1, int x2, int y2);

    void updateTarget(std::vector<Enemy>& enemies) override;

    bool isEnemyNearSoldier(const Enemy& enemy);

    bool isReadyToAttack(double elapsedTime);

    void printAllSoldiersHealth() const;

    // Getters
    static const std::vector<Soldier>& getAllSoldiers() { return allSoldiers; }

    const std::vector<std::pair<int, int>>& getSoldierLocations() const { return soldierLocations; }

    std::pair<int, int> getTowerSoldierMapping() const;

    Soldier& getSoldierAtLocation(const std::pair<int, int>& location);
};

#endif