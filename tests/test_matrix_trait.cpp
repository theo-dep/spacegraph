#include "test.h"

#include <spacegraph/spacegraph.h>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("Matrix Trait set_identity is successful", "[matrix_trait]", glm::mat4, QMatrix4x4, stl::Matrix4)
{
    TestType res = identity<TestType>(2);
    set_identity(spacegraph::tag, res);
    REQUIRE(res == identity<TestType>(1));
}

TEMPLATE_TEST_CASE("Matrix Trait multiply is successful", "[matrix_trait]", glm::mat4, QMatrix4x4, stl::Matrix4)
{
    TestType res = multiply(spacegraph::tag, identity<TestType>(2), identity<TestType>(3));
    REQUIRE(res == identity<TestType>(6));
}
