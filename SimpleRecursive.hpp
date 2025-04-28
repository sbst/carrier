#pragma once
#include <optional>
#include <unordered_set>

#include "IRouter.hpp"
#include "Structures.hpp"

class SimpleRecursive : public IRouter
{
public:
    std::list<int> route(const std::vector<Point>& positions, int startIndex) override;

private:
    void traverse(const std::vector<Point>& positions, int iCurrent, std::unordered_set<int>& visited, std::list<int>& route, double cost);

    std::optional<double> m_cost;
    std::list<int> m_route;
};