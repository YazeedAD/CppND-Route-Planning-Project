//
// Created by y on 10/7/20.
//

#ifndef OSM_A_STAR_SEARCH_UTILS_H
#define OSM_A_STAR_SEARCH_UTILS_H

#include <iostream>
#include <vector>
#include "route_planner.h"

using namespace std;

// Check whether the value is the range
// Returns false if out of range
bool inRange(float value, float min, float max);

// Compares two nodes
// Returns the true if node_1 > node_2
bool Compare(const RouteModel::Node* node_1, const RouteModel::Node* node_2);

#endif //OSM_A_STAR_SEARCH_UTILS_H
