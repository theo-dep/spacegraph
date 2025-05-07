#pragma once

#include <spacetree/spacetree_amalgamated.h>

#include <glm/glm.hpp>

template <>
struct matrix_trait<glm::mat4>
{
    static void set_identity(glm::mat4& self)
    {
        self = glm::mat4(1);
    }

    static glm::mat4 multiply(const glm::mat4& self, const glm::mat4& other)
    {
        return glm::matrixCompMult(self, other);
    }
};
