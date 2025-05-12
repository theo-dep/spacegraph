#include "qt/matrix_trait.h"

#include <catch2/catch_test_macros.hpp>

#include <QtGui/QTransform>

TEST_CASE("Construct a node from in place constructor", "[constructor_node]")
{
    qtNode node(std::in_place, QTransform());
}

TEST_CASE("Construct a node from copy constructor", "[constructor_node]")
{
    qtNode node(QMatrix4x4{});
}
