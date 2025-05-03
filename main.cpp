#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <list>

#include "AntColony.hpp"
#include "NearestNeighbors.hpp"
#include "SimplePermutation.hpp"
#include "SimpleRecursive.hpp"
#include "layouts/Reader.hpp"

void execute(IRouter& router, const std::vector<Point>& positions, int startIndex, const std::string& name)
{
    std::cout << name << std::endl;
    auto route = router.route(positions, startIndex);
    std::cout << "route: ";
    for (auto& index : route)
        std::cout << positions.at(index) << " ";
    std::cout << std::endl;

    assert(route.size() > 1);
    double cost = 0;
    for (auto it = std::next(route.begin()); it != route.end(); it++)
        cost += distance(positions[*(std::prev(it))], positions[*(it)]);
    std::cout << "cost: " << cost << std::endl;
}

int main()
{
    auto positions = readPointsFromFile("../layouts/data/diamond.txt");
    SimpleRecursive rec;
    execute(rec, positions, 0, "Recursive");

    SimplePermutation mut;
    execute(mut, positions, 0, "Permutations");

    NearestNeighbors nen;
    execute(nen, positions, 0, "NearestNeighbors");

    AntColony aco;
    execute(aco, positions, 0, "AntColony");

    return 0;
}