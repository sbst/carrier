#pragma once
#include <list>
#include <optional>
#include <vector>

#include "Structures.hpp"

class SimplePermutation
{
public:
    void calculate(const std::vector<Point>& positions, int startIndex);

    double getCost() const;
    std::list<int> getRoute() const;

private:
    std::optional<double> m_cost;
    std::list<int> m_route;
};