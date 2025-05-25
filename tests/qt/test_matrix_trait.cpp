#include "qt/matrix_trait.h"

#include <spacegraph/spacegraph.h>

#include <catch2/catch_test_macros.hpp>

QMatrix4x4 create(float val)
{
    QMatrix4x4 mat;
    mat(0, 0) = val;
    mat(1, 1) = val;
    mat(2, 2) = val;
    mat(3, 3) = val;
    return mat;
}

TEST_CASE("Matrix Trait set_identity is successful", "[matrix_trait]")
{
    QMatrix4x4 res = create(2);
    set_identity(spacegraph::tag, res);
    REQUIRE(res == create(1));
}

TEST_CASE("Matrix Trait multiply is successful", "[matrix_trait]")
{
    QMatrix4x4 res = multiply(spacegraph::tag, create(2), create(3));
    REQUIRE(res == create(6));
}
