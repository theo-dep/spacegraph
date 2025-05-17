#pragma once

#include <glm/glm.hpp>

// test inside spacetree namespace
namespace spacetree
{
    struct tag_t;
    void set_identity(spacetree::tag_t, glm::mat4& self);
    glm::mat4 multiply(spacetree::tag_t, const glm::mat4& self, const glm::mat4& other);
}

#include <spacetree/spacetree.h>

namespace spacetree
{
    inline void set_identity(spacetree::tag_t, glm::mat4& self)
    {
        self = glm::mat4(1);
    }

    inline glm::mat4 multiply(spacetree::tag_t, const glm::mat4& self, const glm::mat4& other)
    {
        return glm::matrixCompMult(self, other);
    }
}
