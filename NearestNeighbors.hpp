#pragma once

#include "IRouter.hpp"
#include "Structures.hpp"

class NearestNeighbors : public IRouter
{
public:
    std::list<int> route(const std::vector<Point>& positions, int startIndex) override;
};