#include "AntColony.hpp"

#include <cassert>
#include <list>
#include <random>
#include <unordered_set>
#include <utility>
#include <vector>

// TODO: elitism, remove sort, keep routes / 2
std::list<int> AntColony::route(const std::vector<Point>& positions, int startIndex)
{
    int iterations = 100;
    int ants = 50;
    int q = 10;
    double degradation = 0.9;
    std::vector<std::vector<int>> intensity;  //(std::vector<int>(positions.size(), 0));
    for (auto i = 0; i < positions.size(); i++)
    {
        intensity.push_back({});
        for (auto j = 0; j < positions.size(); j++)
        {
            intensity.back().push_back(0);
        }
    }

    std::vector<int> minRoute;
    double minCost = 99999;

    for (auto iteration = 0; iteration < iterations; iteration++)
    {
        std::mt19937 generator(std::random_device{}());  // TODO: no need to init each time
        std::uniform_int_distribution<int> distribution(0, ants);

        std::vector<std::pair<std::vector<int>, double>> routes;
        for (auto ant = 0; ant < ants; ant++)
        {
            routes.push_back(traverse(positions, distribution(generator)));
        }
        std::sort(routes.begin(), routes.end(),
                  [](const std::pair<std::vector<int>, double>& a, const std::pair<std::vector<int>, double>& b)
                  {
                      return a > b;  // TODO: max?
                  });

        for (auto& route : routes)
        {
            // update pheromones table
            const auto& path = route.first;
            double costRoute = route.second;

            if (minCost > costRoute)
            {
                minCost = costRoute;
                minRoute = path;
            }

            double delta = q / costRoute;
            for (auto i = 1; i < positions.size(); i++)
            {
                intensity[path[i - 1]][path[i]] += delta;
                intensity[path[i]][path[i - 1]] += delta;
            }

            // all existing pheromones are degradating each update
            for (auto i = 0; i < intensity.size(); i++)
            {
                for (auto j = 0; j < intensity[i].size(); j++)
                {
                    intensity[i][j] *= degradation;
                }
            }
        }
    }

    return std::list<int>(minRoute.begin(), minRoute.end());
}

std::pair<std::vector<int>, double> AntColony::traverse(const std::vector<Point>& positions, int startIndex)
{
    std::vector<int> route;

    double alpha = 0.9;
    double beta = 1.5;
    // edge weight = pow(pheromones, alpha) / pow(distance, beta)
    // more pheromones and less distance - higher probability to go

    std::unordered_set<int> visited;
    int current = startIndex;

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
                double pheromone = 1e-5;  // std::max(adj[current][i], 1e-5);  // constant to start exploration
                double weight = std::pow(pheromone, alpha) / distance(positions[current], positions[i]);
                neighbors.push_back(i);
                weights.push_back(weight);
            }
        }

        assert(neighbors.size() == weights.size());
        int next = -1;
        if (!neighbors.empty())
        {
            std::mt19937 generator(std::random_device{}());  // TODO: no need to init each time
            // choose next node randomly distributed by weights
            std::discrete_distribution<> distribution(weights.begin(), weights.end());
            std::size_t iWeightedRandomNeighbor = distribution(generator);
            next = neighbors.at(iWeightedRandomNeighbor);
        }
        current = next;
    }
    double cost = 0;
    for (auto i = 1; i < route.size(); i++)
        cost += distance(positions[route[i - 1]], positions[route[i]]);
    return std::make_pair(route, cost);
}