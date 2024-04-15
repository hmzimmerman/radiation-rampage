#ifndef TOWERLOCATION_H
#define TOWERLOCATION_H

#include <string>
#include <memory>

class Tower;

struct TowerLocation {
    int x;
    int y;
    int size; // Size of the square plot
    bool occupied; // Indicate if a tower is already placed here
    std::string towerType;
    std::shared_ptr<Tower> tower;

    TowerLocation(int x, int y) : x(x), y(y), size(80), occupied(false), tower(nullptr) {}

    // Equality operator overload
    bool operator==(const TowerLocation& other) const {
        return (x == other.x) && (y == other.y);
    }
};

#endif
