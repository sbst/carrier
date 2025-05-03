#pragma once

#include <list>
#include <memory>
#include <vector>

#include "Structures.hpp"

class IRouter
{
public:
    virtual ~IRouter() = default;
    virtual std::list<int> route(const std::vector<Point>& positions, int startIndex) = 0;
};

using IRouterPtr = std::shared_ptr<IRouter>;