#include "NearestNeighbors.hpp"

#include <algorithm>
#include <unordered_set>

NearestNeighbors::NearestNeighbors() : m_cost(0) {}

double NearestNeighbors::getCost() const
{
    return m_cost;
}

std::list<int> NearestNeighbors::getRoute() const
{
    return m_route;
}

void NearestNeighbors::calculate(const std::vector<Point>& positions, int startIndex)
{
    std::unordered_set<int> visited;
    int current = startIndex;
    while (current != -1)
    {
        m_route.push_back(current);
        visited.insert(current);
        double minDistance = -1;
        int minNode = -1;
        for (auto i = 0; i < positions.size(); i++)
        {
            if (visited.find(i) == visited.end())
            {
                auto curDistance = distance(positions[current], positions[i]);
                if (minNode == -1 || minDistance > curDistance)
                {
                    minDistance = curDistance;
                    minNode = i;
                }
            }
        }
        current = minNode;
    }
}