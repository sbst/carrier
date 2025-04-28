#pragma once

#include <list>
#include <vector>

#include "Structures.hpp"

class IRouter
{
public:
    virtual ~IRouter() = default;
    virtual std::list<int> route(const std::vector<Point>& positions, int startIndex) = 0;
};