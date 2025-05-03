cmake_minimum_required (VERSION 3.8)

project ("Carrier")

include_directories(${PROJECT_SOURCE_DIR})
add_executable (Carrier "main.cpp" "layouts/Reader.cpp" "layouts/Reader.hpp" "Structures.hpp" "SimpleRecursive.cpp" "SimpleRecursive.hpp" "SimplePermutation.cpp" "SimplePermutation.hpp" "NearestNeighbors.cpp" "NearestNeighbors.hpp" "IRouter.hpp" "AntColony.hpp" "AntColony.cpp")
set_property(TARGET Carrier PROPERTY CXX_STANDARD 20)
