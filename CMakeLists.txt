cmake_minimum_required (VERSION 3.8)

project ("Carrier")

include_directories(${PROJECT_SOURCE_DIR})
add_executable (Carrier "main.cpp"
                        "layouts/Reader.cpp" "layouts/Reader.hpp"
                        "layouts/CircleGenerator.cpp" "layouts/CircleGenerator.hpp"
                        "Structures.hpp"
                        "IRouter.hpp"
                        "SimpleRecursive.cpp" "SimpleRecursive.hpp"
                        "SimplePermutation.cpp" "SimplePermutation.hpp"
                        "NearestNeighbors.cpp" "NearestNeighbors.hpp"
                        "AntColony.hpp" "AntColony.cpp")
set_property(TARGET Carrier PROPERTY CXX_STANDARD 20)
