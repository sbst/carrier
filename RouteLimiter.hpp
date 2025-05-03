#pragma once
#include "IRouter.hpp"

class RouteLimiter : public IRouter
{
public:
    RouteLimiter(IRouterPtr ptrRouter, size_t limit);
    std::list<int> route(const std::vector<Point>& positions, int startIndex) override;

private:
    IRouterPtr m_ptrRouter;
    size_t m_limit;
};