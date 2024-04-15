#include <vector>
#include "towerLocation.h"

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