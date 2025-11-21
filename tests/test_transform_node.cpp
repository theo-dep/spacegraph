#include "test.h"

#include <spacegraph/spacegraph.h>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("Transformation to another node failure", "[transform_node]", glm::mat4, QMatrix4x4, stl::Matrix4)
{
    SECTION("Node has no parent with no Transformable object specified, get the transformation between this node and itself",
            "Transformation is invalid")
    {
        spacegraph::Node node;
        REQUIRE(!node.transform_to<TestType>(node));
    }
}

TEMPLATE_TEST_CASE("Transformation to another node successful", "[transform_node]", glm::mat4, QMatrix4x4, stl::Matrix4)
{
    SECTION("Node has no parent but constructed with a Transformable object, get the transformation between this node and itself",
            "Transformation is valid, it is an identity transformation")
    {
        spacegraph::Node node(std::in_place_type<TestType>);
        REQUIRE(node.transform_to<TestType>(node));
        REQUIRE(*node.transform_to<TestType>(node) == identity<TestType>());
    }

    SECTION("Node has no parent but constructed with a default value Transformable object, get the transformation between this node and itself",
            "Transformation is valid, it is a default value transformation")
    {
        spacegraph::Node node(default_value<TestType>());
        REQUIRE(node.transform_to<TestType>(node));
        REQUIRE(*node.transform_to<TestType>(node) == default_value<TestType>());
    }
}
