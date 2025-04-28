#include "NearestNeighbors.hpp"

#include <unordered_set>

std::list<int> NearestNeighbors::route(const std::vector<Point>& positions, int startIndex)
{
    std::list<int> route;
    std::unordered_set<int> visited;
    int current = startIndex;
    while (current != -1)
    {
        route.push_back(current);
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
    return route;
}