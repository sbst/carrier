#include "SimpleRecursive.hpp"

#include <iostream>

std::list<int> SimpleRecursive::route(const std::vector<Point>& positions, int startIndex)
{
    std::unordered_set<int> visited;
    std::list<int> route;
    int cost = 0;
    traverse(positions, startIndex, visited, route, cost);
    return m_route;
}

void SimpleRecursive::traverse(const std::vector<Point>& positions, int iCurrent, std::unordered_set<int>& visited, std::list<int>& route, double cost)
{
    visited.insert(iCurrent);
    route.push_back(iCurrent);

    if (positions.size() == visited.size())
    {
        if (m_cost.has_value() && m_cost.value() > cost)
        {
            m_cost = cost;
            m_route = route;
        }

        if (!m_cost.has_value())
        {
            m_cost = cost;
            m_route = route;
        }
    }

    for (auto i = 0; i < positions.size(); i++)
    {
        if (visited.find(i) == visited.end())
        {
            double moveCost = distance(positions[iCurrent], positions[i]);
            traverse(positions, i, visited, route, cost + moveCost);
        }
    }

    route.pop_back();
    visited.erase(iCurrent);
}