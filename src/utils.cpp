//
// Created by y on 10/7/20.
//

#include "utils.h"

bool inRange(float value, float min, float max)
{
    return !(value < 0 || value > 100);
}

//bool Compare(const RouteModel::Node* node_1, const RouteModel::Node* node_2)
//{
//    float f1 = node_1->g_value + node_1->h_value;
//    float f2 = node_2->g_value + node_2->h_value;
//
//    return f1 > f2;
//}