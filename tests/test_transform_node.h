#pragma once

#include <spacetree/spacetree.h>

#include <catch2/catch_test_macros.hpp>

#ifndef TYPE
#define TYPE int
#endif

TYPE identity();

TEST_CASE("Transformation to another node successful", "[transform_node]")
{
    SECTION("Node has no parent, get the transformation between this node and itself",
            "Transformation is valid, it is an identity transformation")
    {
        spacetree::Node node;
        REQUIRE(node.transform_to(node));
        REQUIRE(erased::any_cast<TYPE>(*node.transform_to(node)) == identity());
    }
}
