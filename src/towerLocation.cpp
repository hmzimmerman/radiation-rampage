#include <vector>
#include "towerLocation.h"
#include "tower.h"

std::vector<TowerLocation> TowerLocationManager::towerLocations = {
    TowerLocation(275, 71),
    TowerLocation(275, 405),
    TowerLocation(613, 405),
    TowerLocation(917, 254),
    TowerLocation(1067, 390),
};

std::vector<TowerLocation>& TowerLocationManager::getTowerLocations() {
    return towerLocations;
}

void TowerLocationManager::removeTower(const Tower& tower) {
    for (size_t i = 0; i < towerLocations.size(); ++i) {
        if (towerLocations[i].tower.get() == &tower) {
            towerLocations[i].tower = nullptr;
            towerLocations[i].occupied = false;
            break;
        }
    }
}