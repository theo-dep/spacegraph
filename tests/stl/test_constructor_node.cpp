#include "stl_matrix_trait.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Construct a node from in place constructor", "[constructor_node]")
{
    spacetree::Node node(std::in_place_type<StlMatrix4>, 1.f);
}

TEST_CASE("Construct a node from copy constructor", "[constructor_node]")
{
    spacetree::Node node(StlMatrix4(1));
}
