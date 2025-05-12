#include "stl_matrix_trait.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Construct a node from in place constructor", "[constructor_node]")
{
    stlNode node(std::in_place, 1.f);
}

TEST_CASE("Construct a node from copy constructor", "[constructor_node]")
{
    stlNode node(StlMatrix4(1));
}
