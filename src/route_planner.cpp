#include "route_planner.h"
#include <algorithm>

bool Compare(const RouteModel::Node *node_1, const RouteModel::Node *node_2) {
    float f1 = node_1->g_value + node_1->h_value;
    float f2 = node_2->g_value + node_2->h_value;

    return f1 > f2;
}

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y) : m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.

    // DONE: finds the closest nodes
    RoutePlanner::start_node = &m_Model.FindClosestNode(start_x, start_y);
    RoutePlanner::end_node = &m_Model.FindClosestNode(end_x, end_y);

}


// TODO 3: Implement the CalculateHValue method.

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    // DONE: Calculate H based on end_node
    return (node->distance(*end_node));
}


// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.

// DONE: AddNeighbors
void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {

    current_node->FindNeighbors();
    int neighbors_count = current_node->neighbors.size();

    for (int i = 0; i < neighbors_count; i++) {
        // relate the neighbor's parent to current_node
        current_node->neighbors[i]->parent = current_node;
        // find the Heuristic for this neighbor node
        current_node->neighbors[i]->h_value = CalculateHValue(current_node->neighbors[i]);
        // calculate the g value for this neighbor node
        current_node->neighbors[i]->g_value = current_node->neighbors[i]->distance(*current_node) + current_node->g_value;
        // mark this node as v visted one
        current_node->neighbors[i]->visited = true;
        // add the node to the open ist
        open_list.push_back(current_node->neighbors[i]);
    }


}


// TODO 5: Complete the NextNode method to sort the open list and return the next node.

RouteModel::Node *RoutePlanner::NextNode() {
    // sort the open list in descending order
    std::sort(open_list.begin(), open_list.end(), Compare);
    // take the element with the lowest value of f which is (f+g)
    RouteModel::Node *NextNode = open_list.back();
    // drops the element above
    open_list.pop_back();
    return NextNode;

}

// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    // TODO: Implement your solution here.
    // initiate the previous value
    RouteModel::Node *previous_node = current_node;
    // iterate until you find the start (child-to-parent chain)
    while (previous_node->parent != nullptr) {
        // add the distance from child to parent the cumulative distance
        distance += previous_node->distance(*previous_node->parent);
        // add the node value to the path vector
        path_found.push_back(*previous_node);
        // change value the node as the its parent
        previous_node = previous_node->parent;
    }


    path_found.push_back(*previous_node);
    // Multiply the distance by the scale of the map to get meters.
    distance *= m_Model.MetricScale();
    // to change the order and put the starting point on the first
    std::reverse(path_found.begin(), path_found.end());

    return path_found;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {

    RouteModel::Node *current_node = nullptr;

    // TODO: Implement your solution here.
    // Initialize the starting node.
    // checkout the starting point as visited (it was a bug!)
    start_node->visited = true;
    // add the starting point to the open list
    open_list.push_back(start_node);


    while (!open_list.empty()) {
        // sort the open_list and return the next node
        current_node = NextNode();
        // When the search has reached the end_node, return the final path
        if ((current_node->x == end_node->x) && (current_node->y == end_node->y)) {
            m_Model.path = ConstructFinalPath(current_node);
            return;
        }
        // add all of the neighbors of the current node to the open_list
        AddNeighbors(current_node);
    }

}