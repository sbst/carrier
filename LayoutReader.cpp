#include "LayoutReader.hpp"

#include <fstream>
#include <sstream>

std::vector<Point> readPointsFromFile(const std::string& file)
{
    std::vector<Point> positions;
    std::ifstream layout;
    layout.open(file);
    std::string line;
    while (std::getline(layout, line))
    {
        std::istringstream iss(line);
        std::string item;
        Point point;
        std::getline(iss, item, ',');
        point.x = std::stod(item);
        std::getline(iss, item, ',');
        point.y = std::stod(item);
        positions.push_back(point);
    }
    layout.close();
    return positions;
}
