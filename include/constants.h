#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "damage_type.h"

namespace enemy{
    // x,y pixel coordinate, slope, y-intercept of the diagonal line segment for path corners 
    constexpr int corner1X1 {100};
    constexpr int corner1Y1 {635};
    constexpr int corner1X2 {245};
    constexpr int corner1Y2 {505};
    constexpr float corner1Slope {-0.896552};
    constexpr float corner1YIntercept {724.655};

    constexpr int corner2X1 {870};
    constexpr int corner2Y1 {635};
    constexpr int corner2X2 {720};
    constexpr int corner2Y2 {505};
    constexpr float corner2Slope {0.866667};
    constexpr float corner2YIntercept {-119};

    constexpr int corner3X1 {870};
    constexpr int corner3Y1 {230};
    constexpr int corner3X2 {720};
    constexpr int corner3Y2 {125};
    constexpr float corner3Slope {0.7};
    constexpr float corner3YIntercept {-379};

    constexpr int corner4X1 {1035};
    constexpr int corner4Y1 {230};
    constexpr int corner4X2 {1180};
    constexpr int corner4Y2 {125};
    constexpr float corner4Slope {-0.724138};
    constexpr float corner4YIntercept {979.483};

    constexpr int corner5X1 {1035};
    constexpr int corner5Y1 {370};
    constexpr int corner5X2 {1180};
    constexpr int corner5Y2 {265};
    constexpr float corner5Slope {-0.724138};
    constexpr float corner5YIntercept {1119.48};
}

namespace moneyManager{
    constexpr int startAmount {100};
}

namespace tower{
    // stats for specialized towers 
    constexpr int barracksHealth {100};
    constexpr int barracksDamage {100};
    constexpr int barracksRange {0};
    constexpr int barracksAreaOfEffect {0};
    constexpr enum DamageType barracksDamageType {DamageType::NORMAL};
    constexpr int barracksBuildCost {100};

    constexpr int bombHealth {100};
    constexpr int bombDamage {100};
    constexpr int bombRange {100};
    constexpr int bombAreaOfEffect {100};
    constexpr enum DamageType bombDamageType {DamageType::BOMB};
    constexpr int bombBuildCost {100};
    constexpr int bombFireRate {50};

    constexpr int laserHealth {100};
    constexpr int laserDamage {100};
    constexpr int laserRange {100};
    constexpr int laserAreaOfEffect {100};
    constexpr enum DamageType laserDamageType {DamageType::LASER};
    constexpr int laserBuildCost {100};
    constexpr int laserFireRate {50};
}
#endif