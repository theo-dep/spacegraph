#include "test.h"

#include <spacegraph/spacegraph.h>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("Construct a node from default constructor", "[constructor_node]", glm::mat4, QMatrix4x4, stl::Matrix4)
{
    spacegraph::Node node(std::in_place_type<TestType>);
    REQUIRE(node.transformable<TestType>());
    REQUIRE(*node.transformable<TestType>() == identity<TestType>());
}

TEMPLATE_TEST_CASE("Construct a node from in place constructor", "[constructor_node]", glm::mat4, QMatrix4x4, stl::Matrix4)
{
    spacegraph::Node node(std::in_place_type<TestType>, default_param_constructor<TestType>());
    REQUIRE(node.transformable<TestType>());
    REQUIRE(*node.transformable<TestType>() == TestType(default_param_constructor<TestType>()));
}

TEMPLATE_TEST_CASE("Construct a node from copy constructor", "[constructor_node]", glm::mat4, QMatrix4x4, stl::Matrix4)
{
    spacegraph::Node node(default_value<TestType>());
    REQUIRE(node.transformable<TestType>());
    REQUIRE(*node.transformable<TestType>() == default_value<TestType>());
}
