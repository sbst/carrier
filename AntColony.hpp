#include <random>

#include "IRouter.hpp"
#include "Structures.hpp"

class AntColony : public IRouter
{
public:
    AntColony();
    std::list<int> route(const std::vector<Point>& positions, int startIndex) override;

private:
    struct RouteData
    {
        std::vector<int> route;
        double cost;
    };

    RouteData traverse(const std::vector<Point>& positions, int startIndex, const std::vector<std::vector<double>>& intensity);

    std::mt19937 m_generator;
};
