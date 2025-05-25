#include "stl/stl_matrix_trait.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Matrix Trait set_identity is successful", "[matrix_trait]")
{
    stl::Matrix4 res(2);
    set_identity(spacegraph::tag, res);
    REQUIRE(res == stl::Matrix4(1));
}

TEST_CASE("Matrix Trait multiply is successful", "[matrix_trait]")
{
    stl::Matrix4 res = multiply(spacegraph::tag, stl::Matrix4(2), stl::Matrix4(3));
    REQUIRE(res == stl::Matrix4(6));
}
