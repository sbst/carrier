#include "AntColony.hpp"

#include <cassert>
#include <list>
#include <queue>
#include <random>
#include <unordered_set>
#include <utility>
#include <vector>

AntColony::AntColony() : m_generator(std::random_device{}()) {}

std::list<int> AntColony::route(const std::vector<Point>& positions, int startIndex)
{
    int iterations = 75;
    int ants = 10;
    int q = 10;
    double degradation = 0.9;
    std::vector<std::vector<double>> intensityTable(positions.size(), std::vector<double>(positions.size(), 0));
    std::vector<int> minRoute;
    double minCost = 0;

    for (auto iteration = 0; iteration < iterations; iteration++)
    {
        std::uniform_int_distribution<int> distribution(0, positions.size() - 1);

        std::list<RouteData> routes;
        for (auto ant = 0; ant < ants; ant++)
        {
            int antStartIndex = startIndex;  // distribution(generator);
            routes.push_back(traverse(positions, antStartIndex, intensityTable));
        }

        if (!minRoute.empty())  // force best route from previous runs
        {
            routes.push_back(RouteData{minRoute, minCost});
        }

        while (!routes.empty())
        {
            const auto& routeData = routes.front();
            const auto& route = routeData.route;
            double costRoute = routeData.cost;

            if (minRoute.empty() || minCost > costRoute)
            {
                minRoute = route;
                minCost = costRoute;
            }

            // update pheromones trails
            double delta = q / costRoute;
            for (auto i = 1; i < positions.size(); i++)
            {
                intensityTable[route[i - 1]][route[i]] += delta;
                intensityTable[route[i]][route[i - 1]] += delta;
            }
            routes.pop_front();

            // all existing pheromones are degradating each update
            for (auto i = 0; i < intensityTable.size(); i++)
            {
                for (auto j = 0; j < intensityTable[i].size(); j++)
                {
                    intensityTable[i][j] *= degradation;
                }
            }
        }
    }

    return std::list<int>(minRoute.begin(), minRoute.end());
}

AntColony::RouteData AntColony::traverse(const std::vector<Point>& positions, int startIndex, const std::vector<std::vector<double>>& intensity)
{
    thread_local std::mt19937 generator(std::random_device{}());
    std::vector<int> route;

    double alpha = 0.9;
    double beta = 1.5;
    // edge weight = pow(pheromones, alpha) / pow(distance, beta)
    // more pheromones and less distance - higher probability to go

    std::unordered_set<int> visited;
    int current = startIndex;
    double cost = 0;

    while (current != -1)
    {
        visited.insert(current);
        route.push_back(current);

        // create weights for each node based on global pheromones + distance
        std::vector<int> neighbors;
        std::vector<double> weights;
        for (auto i = 0; i < positions.size(); i++)
        {
            if (i == current)
                continue;

            if (visited.find(i) == visited.end())
            {
                double pheromone = std::max(intensity[current][i], 1e-5);  // constant to start exploration
                double weight = std::pow(pheromone, alpha) / std::pow(distance(positions[current], positions[i]), beta);
                neighbors.push_back(i);
                weights.push_back(weight);
            }
        }

        assert(neighbors.size() == weights.size());
        int next = -1;
        if (!neighbors.empty())
        {
            // choose next node randomly distributed by weights
            std::discrete_distribution<> distribution(weights.begin(), weights.end());
            std::size_t iWeightedRandomNeighbor = distribution(generator);
            next = neighbors.at(iWeightedRandomNeighbor);
            cost += distance(positions[current], positions[next]);
        }
        current = next;
    }
    return {route, cost};
}