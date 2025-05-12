#include "stl/stl_matrix_trait.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Matrix Trait set_identity is successful", "[matrix_trait]")
{
    StlMatrix4 res(2);
    matrix_trait<StlMatrix4>::set_identity(res);
    REQUIRE(res == StlMatrix4(1));
}

TEST_CASE("Matrix Trait multiply is successful", "[matrix_trait]")
{
    StlMatrix4 res = matrix_trait<StlMatrix4>::multiply(StlMatrix4(2), StlMatrix4(3));
    REQUIRE(res == StlMatrix4(6));
}
