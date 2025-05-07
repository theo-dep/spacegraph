#pragma once

#include <spacetree/spacetree_amalgamated.h>

#include <valarray>

using FalseMatrixTrait = std::valarray<float>;

inline FalseMatrixTrait createFalse(float val)
{
    return FalseMatrixTrait{ val, 16 };
}

template <>
struct matrix_trait<FalseMatrixTrait>
{
    static void set_identity(FalseMatrixTrait& self)
    {
        self[std::slice(0, 16, 4)] = 1;
    }

    static FalseMatrixTrait multiply(const FalseMatrixTrait& self, const FalseMatrixTrait& other)
    {
        return self * other;
    }
};

inline std::optional<spacetree::details::Transformable> test(const spacetree::details::Transformable& mat, const spacetree::details::Transformable& other)
{
    return mat.multiply(other);
}
