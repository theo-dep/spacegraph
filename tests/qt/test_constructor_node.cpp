#include "qt/matrix_trait.h"

#include <catch2/catch_test_macros.hpp>

#include <QtGui/QTransform>

TEST_CASE("Construct a node from in place constructor", "[constructor_node]")
{
    spacetree::Node node(std::in_place_type<QMatrix4x4>, QTransform());
}
