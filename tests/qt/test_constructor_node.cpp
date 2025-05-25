#include "qt/matrix_trait.h"

#include <spacegraph/spacegraph.h>

#include <catch2/catch_test_macros.hpp>

#include <QtGui/QTransform>

TEST_CASE("Construct a node from in place constructor", "[constructor_node]")
{
    [[maybe_unused]] spacegraph::Node _(std::in_place_type<QMatrix4x4>, QTransform());
}

TEST_CASE("Construct a node from copy constructor", "[constructor_node]")
{
    [[maybe_unused]] spacegraph::Node _(QMatrix4x4{});
}
