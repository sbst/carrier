#include "SimplePermutation.hpp"

#include <iostream>
#include <optional>

std::list<int> SimplePermutation::route(const std::vector<Point>& positions, int startIndex)
{
    std::optional<double> minCost;
    std::list<int> route;
    std::vector<int> order;
    order.push_back(startIndex);
    for (auto i = 0; i < positions.size(); i++)
    {
        if (i == startIndex)
            continue;
        order.push_back(i);
    }
    do
    {
        double cost = 0;
        for (auto i = 1; i < order.size(); i++)
        {
            cost += distance(positions[order[i - 1]], positions[order[i]]);
        }

        if (minCost.has_value() && minCost.value() > cost)
        {
            minCost = cost;
            route = std::list<int>(order.begin(), order.end());
        }

        if (!minCost.has_value())
        {
            minCost = cost;
            route = std::list<int>(order.begin(), order.end());
        }
    } while (std::next_permutation(order.begin() + 1, order.end()));
    return route;
}
