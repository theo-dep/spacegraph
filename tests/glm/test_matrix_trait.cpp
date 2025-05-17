#include "glm/matrix_trait.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Matrix Trait set_identity is successful", "[matrix_trait]")
{
    glm::mat4 res(2);
    set_identity(spacetree::tag, res);
    REQUIRE(res == glm::mat4(1));
}

TEST_CASE("Matrix Trait multiply is successful", "[matrix_trait]")
{
    glm::mat4 res = multiply(spacetree::tag, glm::mat4(2), glm::mat4(3));
    REQUIRE(res == glm::mat4(6));
}
