#pragma once
#include "IRouter.hpp"

class SimplePermutation : public IRouter
{
public:
    std::list<int> route(const std::vector<Point>& positions, int startIndex) override;
};