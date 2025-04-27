#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <optional>
#include <unordered_set>
#include <vector>

#include "LayoutReader.hpp"
#include "SimplePermutation.hpp"
#include "SimpleRecursive.hpp"

int main()
{
    auto positions = readPointsFromFile("../layouts/diamond.txt");
    SimpleRecursive rec;
    rec.calculate(positions, 0);
    std::cout << "recursive" << std::endl;
    std::cout << "cost: " << rec.getCost() << std::endl;
    auto route = rec.getRoute();
    std::cout << "route: ";
    for (auto& index : route)
    {
        std::cout << "(" << positions[index].x << "," << positions[index].y << ")" << " ";
    }
    std::cout << std::endl;
    std::cout << "permutation" << std::endl;
    SimplePermutation mut;
    mut.calculate(positions, 0);
    std::cout << "recursive" << std::endl;
    std::cout << "cost: " << mut.getCost() << std::endl;
    route = mut.getRoute();
    std::cout << "route: ";
    for (auto& index : route)
    {
        std::cout << "(" << positions[index].x << "," << positions[index].y << ")" << " ";
    }
    std::cout << std::endl;
    return 0;
}