#include "qt/matrix_trait.h"

#include <catch2/catch_test_macros.hpp>

#include <QtGui/QTransform>

TEST_CASE("Construct a node from in place constructor", "[constructor_node]")
{
    [[maybe_unused]] qtNode _(std::in_place, QTransform());
}

TEST_CASE("Construct a node from copy constructor", "[constructor_node]")
{
    [[maybe_unused]] qtNode _(QMatrix4x4{});
}
