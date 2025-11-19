#pragma once

#include <spacegraph/spacegraph.h>

#include <glm/glm.hpp>

// test inside spacegraph namespace
namespace spacegraph
{
    inline void set_identity(spacegraph::tag_t, glm::mat4& self)
    {
        self = glm::mat4(1);
    }

    inline glm::mat4 multiply(spacegraph::tag_t, const glm::mat4& self, const glm::mat4& other)
    {
        return glm::matrixCompMult(self, other);
    }
}
