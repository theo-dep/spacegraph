#include "test_matrix_trait.h"
#include "stl_matrix_trait.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Matrix Trait set_identity is successful", "[matrix_trait]")
{
    spacetree::details::Transformable res = test_set_identity(StlMatrix4(2));
    REQUIRE(erased::is<StlMatrix4>(res));
    REQUIRE(erased::any_cast<StlMatrix4>(res) == StlMatrix4(1));
}

TEST_CASE("Matrix Trait multiply is successful", "[matrix_trait]")
{
    std::optional res = test_multiply(StlMatrix4(2), StlMatrix4(3));
    REQUIRE(res);
    REQUIRE(erased::is<StlMatrix4>(*res));
    REQUIRE(erased::any_cast<StlMatrix4>(*res) == StlMatrix4(6));
}
