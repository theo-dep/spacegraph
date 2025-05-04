#include <spacetree/spacetree.h>

#include <false_matrix_trait.h>

#include <catch2/catch_test_macros.hpp>

#include <QtCore/QDebug>
#include <QtGui/QMatrix4x4>

#include <print>

template <>
struct matrix_trait<QMatrix4x4>
{
    static QMatrix4x4 multiply(const QMatrix4x4& self, const QMatrix4x4& other)
    {
        return self * other;
    }
};

QMatrix4x4 create(float val)
{
    QMatrix4x4 mat;
    mat(0, 0) = val;
    mat(1, 1) = val;
    mat(2, 2) = val;
    mat(3, 3) = val;
    return mat;
}

TEST_CASE("Matrix Trait multiply is successful", "[matrix_trait_qt_1]")
{
    Multipliable res = test(create(2), create(3));
    REQUIRE(erased::is<QMatrix4x4>(res));

    std::println("qt: {}", QDebug::toString(erased::any_cast<QMatrix4x4>(res)).toStdString());
}

TEST_CASE("Matrix Trait multiply is not same type", "[matrix_trait_qt_2]")
{
    REQUIRE_THROWS_AS(test(create(2), createFalse(3)), std::bad_cast);
}
