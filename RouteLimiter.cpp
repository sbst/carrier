#include "RouteLimiter.hpp"

RouteLimiter::RouteLimiter(IRouterPtr ptrRouter, size_t limit) : m_ptrRouter(ptrRouter), m_limit(limit) {}

std::list<int> RouteLimiter::route(const std::vector<Point>& positions, int startIndex)
{
    if (positions.size() > m_limit)
        return {};
    return m_ptrRouter->route(positions, startIndex);
}
