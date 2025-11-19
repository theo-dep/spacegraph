#include "test.h"

#include <spacegraph/spacegraph.h>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("Construct a node from in place constructor", "[constructor_node]", glm::mat4, QMatrix4x4, stl::Matrix4)
{
    [[maybe_unused]] spacegraph::Node _(std::in_place_type<TestType>, default_param_constructor<TestType>());
}

TEMPLATE_TEST_CASE("Construct a node from copy constructor", "[constructor_node]", glm::mat4, QMatrix4x4, stl::Matrix4)
{
    [[maybe_unused]] spacegraph::Node _(identity<TestType>(1));
}
