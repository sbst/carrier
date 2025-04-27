#include "SimplePermutation.hpp"

#include <iostream>

void SimplePermutation::calculate(const std::vector<Point>& positions, int startIndex)
{
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

        if (m_cost.has_value() && m_cost.value() > cost)
        {
            m_cost = cost;
            m_route = std::list<int>(order.begin(), order.end());
        }

        if (!m_cost.has_value())
        {
            m_cost = cost;
            m_route = std::list<int>(order.begin(), order.end());
        }
    } while (std::next_permutation(order.begin() + 1, order.end()));
}

double SimplePermutation::getCost() const
{
    return m_cost.value_or(0);
}

std::list<int> SimplePermutation::getRoute() const
{
    return m_route;
}
