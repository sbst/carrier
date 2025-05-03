#include "CircleGenerator.hpp"

#include <random>

CirceGenerator::CirceGenerator(double radius) : m_radius(radius) {}

Points CirceGenerator::generate(int amount)
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dis;
    auto max = m_radius;
    auto min = m_radius * -1;
    auto radius2 = m_radius * m_radius;

    Points layout;
    for (auto i = 0; i < amount; i++)
    {
        Point d = {0, 0};
        do
        {
            d.x = min + dis(gen) * (max - min);
            d.y = min + dis(gen) * (max - min);
        } while (d.x * d.x + d.y * d.y > radius2);
        layout.push_back(d);
    }
    return layout;
}
