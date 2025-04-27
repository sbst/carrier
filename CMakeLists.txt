cmake_minimum_required (VERSION 3.8)

project ("Carrier")

add_executable (Carrier "main.cpp" "LayoutReader.hpp" "LayoutReader.cpp" "Structures.hpp" "SimpleRecursive.cpp" "SimpleRecursive.hpp" "SimplePermutation.cpp" "SimplePermutation.hpp")
set_property(TARGET Carrier PROPERTY CXX_STANDARD 20)
