#include "test_matrix_trait.h"
#include "qt/matrix_trait.h"
#include "stl_matrix_trait.h"

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
    spacetree::details::Transformable res = test_set_identity(create(2));
    REQUIRE(erased::is<QMatrix4x4>(res));
    REQUIRE(erased::any_cast<QMatrix4x4>(res) == create(1));
}

TEST_CASE("Matrix Trait multiply is successful", "[matrix_trait]")
{
    std::optional res = test_multiply(create(2), create(3));
    REQUIRE(res);
    REQUIRE(erased::is<QMatrix4x4>(*res));
    REQUIRE(erased::any_cast<QMatrix4x4>(*res) == create(6));
}

TEST_CASE("Matrix Trait multiply is not same type", "[matrix_trait]")
{
    REQUIRE(test_multiply(create(2), StlMatrix4(3)) == std::nullopt);
}
