#include <spacetree/spacetree.h>

#include <false_matrix_trait.h>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <catch2/catch_test_macros.hpp>

#include <print>

template <>
struct matrix_trait<glm::mat4>
{
    static glm::mat4 multiply(const glm::mat4& self, const glm::mat4& other)
    {
        return glm::matrixCompMult(self, other);
    }
};

TEST_CASE("Matrix Trait multiply is successful", "[matrix_trait_glm_1]")
{
    Multipliable res = test(glm::mat4(2), glm::mat4(3));
    REQUIRE(erased::is<glm::mat4>(res));

    std::println("glm: {}", glm::to_string(erased::any_cast<glm::mat4>(res)));
}

TEST_CASE("Matrix Trait multiply is not same type", "[matrix_trait_glm_2]")
{
    REQUIRE_THROWS_AS(test(glm::mat4(2), createFalse(3)), std::bad_cast);
}
