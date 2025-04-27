#include "SimpleRecursive.hpp"

#include <iostream>

void SimpleRecursive::calculate(const std::vector<Point>& positions, int startIndex)
{
    std::unordered_set<int> visited;
    std::list<int> route;
    int cost = 0;
    traverse(positions, startIndex, visited, route, cost);
}

double SimpleRecursive::getCost() const
{
    return m_cost.value_or(0);
}

std::list<int> SimpleRecursive::getRoute() const
{
    return m_route;
}

// void SimpleRecursive::traverseSt(const std::vector<Point>& positions, int startIndex)
// {
//     std::vector<int> order;
//     order.push_back(startIndex);
//     for (auto i = 0; i < positions.size(); i++)
//     {
//         if (i == startIndex)
//             continue;
//         order.push_back(i);
//     }
//     do
//     {
//         double cost = 0;
//         for (auto i = 1; i < order.size(); i++)
//         {
//             cost += distance(positions[order[i - 1]], positions[order[i]]);
//         }

//         if (m_cost.has_value() && m_cost.value() > cost)
//         {
//             m_cost = cost;
//             m_route = std::list<int>(order.begin(), order.end());
//         }

//         if (!m_cost.has_value())
//         {
//             m_cost = cost;
//             m_route = std::list<int>(order.begin(), order.end());
//         }
//     } while (std::next_permutation(order.begin() + 1, order.end()));
// }

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