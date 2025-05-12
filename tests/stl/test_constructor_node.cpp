#include "stl_matrix_trait.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Construct a node from in place constructor", "[constructor_node]")
{
    [[maybe_unused]] stlNode _(std::in_place, 1.f);
}

TEST_CASE("Construct a node from copy constructor", "[constructor_node]")
{
    [[maybe_unused]] stlNode _(StlMatrix4(1));
}
