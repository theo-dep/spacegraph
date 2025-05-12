#pragma once

#include <spacetree/spacetree.h>

#include <catch2/catch_test_macros.hpp>

#ifndef TYPE
#define TYPE int
#endif

TYPE identity();
TYPE default_value();

TEST_CASE("Transformation to another node failure", "[transform_node]")
{
    SECTION("Node has no parent with no Transformable object specified, get the transformation between this node and itself",
            "Transformation is invalid")
    {
        spacetree::Node<TYPE> node;
        REQUIRE(!node.transform_to(node));
    }
}

TEST_CASE("Transformation to another node successful", "[transform_node]")
{
    SECTION("Node has no parent but constructed with a Transformable object, get the transformation between this node and itself",
            "Transformation is valid, it is an identity transformation")
    {
        spacetree::Node<TYPE> node(std::in_place);
        REQUIRE(node.transform_to(node));
        REQUIRE(*node.transform_to(node) == identity());
    }

    SECTION("Node has no parent but constructed with a default value Transformable object, get the transformation between this node and itself",
            "Transformation is valid, it is a default value transformation")
    {
        spacetree::Node<TYPE> node(default_value());
        REQUIRE(node.transform_to(node));
        REQUIRE(*node.transform_to(node) == default_value());
    }
}
