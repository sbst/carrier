#include "IRouter.hpp"
#include "Structures.hpp"

class AntColony : public IRouter
{
public:
    std::list<int> route(const std::vector<Point>& positions, int startIndex) override;

private:
    std::pair<std::vector<int>, double> traverse(const std::vector<Point>& positions, int startIndex);
};
