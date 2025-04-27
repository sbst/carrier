#pragma once
#include <list>
#include <optional>
#include <unordered_set>
#include <vector>

#include "Structures.hpp"

class SimpleRecursive
{
public:
    void calculate(const std::vector<Point>& positions, int startIndex);

    double getCost() const;
    std::list<int> getRoute() const;

private:
    void traverse(const std::vector<Point>& positions, int iCurrent, std::unordered_set<int>& visited, std::list<int>& route, double cost);

    std::optional<double> m_cost;
    std::list<int> m_route;
};