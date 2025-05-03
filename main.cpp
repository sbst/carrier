#include <algorithm>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <list>

#include "AntColony.hpp"
#include "NearestNeighbors.hpp"
#include "RouteLimiter.hpp"
#include "SimplePermutation.hpp"
#include "SimpleRecursive.hpp"
#include "layouts/CircleGenerator.hpp"
#include "layouts/Reader.hpp"

void execute(IRouter& router, const std::vector<Point>& positions, int startIndex, const std::string& name)
{
    std::cout << name << std::endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    auto route = router.route(positions, startIndex);
    auto t2 = std::chrono::high_resolution_clock::now();

    if (route.empty())
    {
        std::cout << "skipped" << std::endl;
        return;
    }

    std::cout << "route: ";
    for (auto& index : route)
        std::cout << index << " ";
    std::cout << std::endl;

    std::cout << "nodes: ";
    for (auto& index : route)
        std::cout << positions.at(index) << " ";
    std::cout << std::endl;

    double cost = 0;
    for (auto it = std::next(route.begin()); it != route.end(); it++)
        cost += distance(positions[*(std::prev(it))], positions[*(it)]);
    std::cout << "cost: " << cost << std::endl;
    std::chrono::duration<double, std::milli> ms = t2 - t1;
    std::cout << "time: " << ms.count() << " ms" << std::endl;
}

int main()
{
    auto positions = CirceGenerator(5).generate(50);
    RouteLimiter rec(std::make_shared<SimpleRecursive>(), 11);
    execute(rec, positions, 0, "Recursive");

    RouteLimiter mut(std::make_shared<SimplePermutation>(), 12);
    execute(mut, positions, 0, "Permutations");

    NearestNeighbors nen;
    execute(nen, positions, 0, "NearestNeighbors");

    AntColony aco;
    execute(aco, positions, 0, "AntColony");

    return 0;
}