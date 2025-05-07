#include "false_matrix_trait.h"
#include "qt/matrix_trait.h"

#include <catch2/catch_test_macros.hpp>

#include <QtCore/QDebug>

#include <print>

QMatrix4x4 create(float val)
{
    QMatrix4x4 mat;
    mat(0, 0) = val;
    mat(1, 1) = val;
    mat(2, 2) = val;
    mat(3, 3) = val;
    return mat;
}

TEST_CASE("Matrix Trait multiply is successful", "[matrix_trait]")
{
    spacetree::details::Multipliable res = test(create(2), create(3));
    REQUIRE(erased::is<QMatrix4x4>(res));

    std::println("qt: {}", QDebug::toString(erased::any_cast<QMatrix4x4>(res)).toStdString());
}

TEST_CASE("Matrix Trait multiply is not same type", "[matrix_trait]")
{
    REQUIRE_THROWS_AS(test(create(2), createFalse(3)), std::bad_cast);
}
