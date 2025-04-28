#pragma once

#include <list>
#include <optional>
#include <vector>

#include "Structures.hpp"

class NearestNeighbors
{
public:
    NearestNeighbors();

    void calculate(const std::vector<Point>& positions, int startIndex);

    double getCost() const;
    std::list<int> getRoute() const;

private:
    double m_cost;
    std::list<int> m_route;
};