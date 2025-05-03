#pragma once

#include "Structures.hpp"

class CirceGenerator
{
public:
    explicit CirceGenerator(double radius);
    Points generate(int amount);

private:
    double m_radius;
};