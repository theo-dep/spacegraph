#pragma once

#include <spacetree/spacetree_amalgamated.h>

inline spacetree::details::Transformable test_set_identity(const spacetree::details::Transformable& mat)
{
    spacetree::details::Transformable newer = mat;
    newer.set_identity();
    return newer;
}

inline std::optional<spacetree::details::Transformable> test_multiply(const spacetree::details::Transformable& mat, const spacetree::details::Transformable& other)
{
    return mat.multiply(other);
}
