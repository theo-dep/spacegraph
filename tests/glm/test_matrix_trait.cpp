#include "false_matrix_trait.h"
#include "glm/matrix_trait.h"

#include <glm/gtx/string_cast.hpp>

#include <catch2/catch_test_macros.hpp>

#include <print>

TEST_CASE("Matrix Trait multiply is successful", "[matrix_trait]")
{
    spacetree::details::Multipliable res = test(glm::mat4(2), glm::mat4(3));
    REQUIRE(erased::is<glm::mat4>(res));

    std::println("glm: {}", glm::to_string(erased::any_cast<glm::mat4>(res)));
}

TEST_CASE("Matrix Trait multiply is not same type", "[matrix_trait]")
{
    REQUIRE_THROWS_AS(test(glm::mat4(2), createFalse(3)), std::bad_cast);
}
