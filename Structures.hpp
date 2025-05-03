#pragma once

#include <cmath>
#include <sstream>
#include <vector>

struct Point
{
    double x;
    double y;
};
using Points = std::vector<Point>;

inline std::ostream& operator<<(std::ostream& os, const Point& point)
{
    os << "(" << point.x << "," << point.y << ")";
    return os;
}

static double distance(const Point& a, const Point& b)
{
    return std::sqrt(((b.x - a.x) * (b.x - a.x)) + ((b.y - a.y) * (b.y - a.y)));
}
