#include "glm/matrix_trait.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Construct a node from in place constructor", "[constructor_node]")
{
    spacetree::Node node(std::in_place_type<glm::mat4>, 1.f);
}
