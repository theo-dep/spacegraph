#include "test_matrix_trait.h"
#include "glm/matrix_trait.h"
#include "stl_matrix_trait.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Matrix Trait set_identity is successful", "[matrix_trait]")
{
    spacetree::details::Transformable res = test_set_identity(glm::mat4(2));
    REQUIRE(erased::is<glm::mat4>(res));
    REQUIRE(erased::any_cast<glm::mat4>(res) == glm::mat4(1));
}

TEST_CASE("Matrix Trait multiply is successful", "[matrix_trait]")
{
    std::optional res = test_multiply(glm::mat4(2), glm::mat4(3));
    REQUIRE(res);
    REQUIRE(erased::is<glm::mat4>(*res));
    REQUIRE(erased::any_cast<glm::mat4>(*res) == glm::mat4(6));
}

TEST_CASE("Matrix Trait multiply is not same type", "[matrix_trait]")
{
    REQUIRE(test_multiply(glm::mat4(2), StlMatrix4(3)) == std::nullopt);
}
